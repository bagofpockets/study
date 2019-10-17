// Karkas4.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Karkas4.h"
#include <cmath>

#define MAX_LOADSTRING 100
#define M_PI 3.14

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_KARKAS4, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KARKAS4));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KARKAS4));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_KARKAS4);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	static int sx, sy;
	int a, b, x_scr, y_scr; //Экранные координаты
	/*static HPEN hpen;
	float x[4] = { 6.0, 6.0, 5.9,6.1 }, y[4] = { -0.25, 0.25, 0.0,0.0 }; //Объектные координаты стрелки
	float xMax = 6.5, yMax = 6.5; //Объектные координаты окна
	float Kx, Ky; //Координаты масштабирования объектных координат в экранные*/

	//POINT pt[4] = { {-100,100}, {-100,-100}, {100,-100}, {100,100} };
	POINT pt[5] = { {0,-100}, {59,81}, {-95,-31}, {95,-31}, {-59,81} };
	POINT pt1[5];
	const int WIDTH = 400;
	const int HEIGHT = 300;
	int n = 8, i, j;
	double alpha = M_PI / n;
	double x;
	static HBRUSH hBrush;

	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_CREATE:
	{
		//hpen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	}
	break;
	case WM_SIZE:
	{
		sx = LOWORD(lParam); //Ширина окна в экранных координатах
		sy = HIWORD(lParam); //Высота окна в экранных координатах
	}
	break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);

		/*int i, j;
		float pi, phi, cos_phi, sin_phi, xx, yy;
		pi = 4.0 * atan(1.0); phi = 6 * pi / 180; //Определение угла поворота
		cos_phi = cos(phi); sin_phi = sin(phi); //в радианах

		SelectObject(hdc, hpen); //Синее перо

		Kx = sx / xMax;
		Ky = sy / yMax;

		for (i = 1; 1 <= 14; i++) //Цикл отрисовки 14 стрелок
		{
			for (j = 0; j <= 3; j++) //Цикл пересчёта координат поворота стрелки
			{
				xx = x[j]; yy = y[j];
				x[j] = xx * cos_phi - yy * sin_phi;
				y[j] = xx * sin_phi + yy * cos_phi;
			}
			//Изображение текущей стрелки
			MoveToEx(hdc, x[0] * Kx, sy - y[0] * Ky, NULL); //начало стрелки
			for (j = 1; j <= 3; j++) LineTo(hdc, x[j] * Kx, sy - y[j] * Ky);
			LineTo(hdc, x[1] * Kx, sy - y[1] * Ky); //завершение стрелки
		}*/

		for (i = 0; i <= n; i++)
		{
			hBrush = CreateSolidBrush(RGB(180, 255 - 255. / n * i, 240)); //Создание кисти
			SelectObject(hdc, hBrush);
			for (j = 0; j <= 4; j++)
			{
				pt1[j].x = 500 + (pt[j].x * cos(alpha * i) - pt[j].y * sin(alpha * i)) + i * 10;
				pt1[j].y = 300 + (pt[j].x * sin(alpha * i) + pt[j].y * cos(alpha * i)) + i * 10;
			}
			Polygon(hdc, pt1, 5);
		}
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
	{
		//DeleteObject(hpen);
		PostQuitMessage(0);
	}
	break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
