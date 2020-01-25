#include "Karkas5.h"
#include <Windows.h>
#include <tchar.h>
#include <fstream>
#include "stdio.h"
#define MAX 100
#define N 30
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName[] = _T("MainFrame");
static int sx, sy;
const int SCALE = 1000;
const int MARK = 4;
void DcInLp(POINT& point)
{
	point.x = point.x * SCALE / sx;
	point.y = SCALE - point.y * SCALE / sy;
}
void transform(HDC& hdc)
{
	SetMapMode(hdc, MM_ANISOTROPIC);
	SetWindowExtEx(hdc, SCALE, -SCALE, NULL);
	SetViewportExtEx(hdc, sx, sy, NULL);
	SetViewportOrgEx(hdc, 0, sy, NULL);
}
void PolyBSplayn(HDC hdc, POINT pt[], int count)
{
	float a0, a1, a2, a3, b0, b1, b2, b3, t;
	int first = -1, X, Y;
	for (int i = 0; i <= count - 1; i++)
	{
		a3 = (-pt[i - 1].x + 3 * (pt[i].x - pt[i + 1].x) + pt[i + 2].x) / 6.0;
		b3 = (-pt[i - 1].y + 3 * (pt[i].y - pt[i + 1].y) + pt[i + 2].y) / 6.0;
		a2 = (pt[i - 1].x - 2 * pt[i].x + pt[i + 1].x) / 2.0;
		b2 = (pt[i - 1].y - 2 * pt[i].y + pt[i + 1].y) / 2.0;
		a1 = (pt[i + 1].x - pt[i - 1].x) / 2.0;
		b1 = (pt[i + 1].y - pt[i - 1].y) / 2.0;
		a0 = (pt[i - 1].x + 4 * pt[i].x + pt[i + 1].x) / 6.0;
		b0 = (pt[i - 1].y + 4 * pt[i].y + pt[i + 1].y) / 6.0;
		for (int j = 0; j <= 30; j++)
		{
			t = (float)j / 30.;
			X = ((a3 * t + a2) * t + a1) * t + a0;
			Y = ((b3 * t + b2) * t + b1) * t + b0;
			if (first)
			{
				first = 0; MoveToEx(hdc, X, Y, NULL);
			}
			else LineTo(hdc, X, Y);
		}
	}
}
static HPEN hDash, hBezier;
static HBRUSH hRect, hSel;
static POINT pt[20];
static POINT point;
RECT rt;
static int count, index;
static bool capture;
int i;
std::ifstream in;
std::ofstream out;
int APIENTRY WinMain(HINSTANCE This, HINSTANCE Prev, LPSTR cmd, int mode)
{
	HWND hWnd;
	MSG msg;
	WNDCLASS wc;
	wc.hInstance = This;
	wc.lpszClassName = WinName;
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	if (!RegisterClass(&wc)) return 0;
	hWnd = CreateWindow(WinName, _T("Каркасс Windows-приложения"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, HWND_DESKTOP, NULL, This, NULL);
	ShowWindow(hWnd, mode);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message)
	{
	case WM_CREATE:
		in.open("dat.txt");	//Открытие файлового потока
		if (in.fail())
		{
			MessageBox(hWnd, _T("Файл dat.txt не найден"),
				_T("Открытие файла"), MB_OK | MB_ICONEXCLAMATION);
			PostQuitMessage(0);
			return 1;
		}
		for (count = 0; in >> pt[count].x; count++) in >> pt[count].y;
		in.close();
		hDash = CreatePen(PS_DASH, 1, 0);
		hBezier = CreatePen(PS_SOLID, 4, RGB(0, 0, 255));
		hRect = CreateSolidBrush(RGB(128, 0, 128));
		hSel = CreateSolidBrush(RGB(255, 0, 0));
		break;
	case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		break;
	case WM_LBUTTONDOWN:
		point.x = LOWORD(lParam);
		point.y = HIWORD(lParam);
		DcInLp(point);
		for (i = 0; i <= count; i++)
		{
			SetRect(&rt, pt[i].x - MARK, pt[i].y - MARK, pt[i].x + MARK, pt[i].y + MARK);
			if (PtInRect(&rt, point))
			{
				index = i;
				capture = true;
				hdc = GetDC(hWnd);
				transform(hdc);
				FillRect(hdc, &rt, hSel);
				ReleaseDC(hWnd, hdc);
				SetCapture(hWnd);
				return 0;
			}
		}
		break;
	case WM_LBUTTONUP:
		if (capture)
		{
			ReleaseCapture();
			capture = false;
		}
		break;
	case WM_MOUSEMOVE:
		if (capture)
		{
			point.x = LOWORD(lParam);
			point.y = HIWORD(lParam);
			DcInLp(point);
			pt[index] = point;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		transform(hdc);
		SelectObject(hdc, hDash);
		Polyline(hdc, pt, count);
		SelectObject(hdc, hBezier);
		PolyBSplayn(hdc, pt, count);
		for (i = 0; i < count; i++)
		{
			SetRect(&rt, pt[i].x - MARK, pt[i].y - MARK, pt[i].x + MARK, pt[i].y + MARK);
			FillRect(hdc, &rt, hRect);
		}
		break;
	case WM_DESTROY: PostQuitMessage(0);
		DeleteObject(hDash);
		DeleteObject(hBezier);
		DeleteObject(hRect);
		DeleteObject(hSel);
		out.open("dat.txt");
		for (i = 0; i < count; i++) out << pt[i].x << '\t' << pt[i].y << '\n';
		out.close();
		break;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}