// Karkas3.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Karkas3.h"
#include "math.h"

#define MAX_LOADSTRING 100

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
	LoadStringW(hInstance, IDC_KARKAS3, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KARKAS3));

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

	return (int)msg.wParam;
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

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KARKAS3));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_KARKAS3);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
	//POINT pt[5] = { {0,100}, {-59,-81}, {95,31}, {-95,31}, {59,-81} };
	POINT pt[4] = { {-100,100}, {-100,-100}, {100,-100}, {100,100} };
	const int WIDTH = 400;
	const int HEIGHT = 300;
	static int sx, sy, i, k;
	static HBRUSH hBrush;
	HRGN hRgn(NULL);
	
	int a, b, x_scr, y_scr; //Экранные координаты
	double x, h; //Физические координаты

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
		/*i = MessageBox(hWnd, _T("Будем рисовать красную звезду?"),
			_T("Политический вопрос"), MB_YESNO | MB_ICONQUESTION);
		k = (i == IDYES) ? 1 : 0;*/
	}
	break;
	case WM_SIZE:
	{
		sx = LOWORD(lParam); //Ширина окна
		sy = HIWORD(lParam); //Высота окна
	}
	break;
	case WM_PAINT:
	{
		hBrush = CreateSolidBrush(RGB(255, 0, 0)); //Создание кисти

		hdc = BeginPaint(hWnd, &ps);
		
		//Установка режима
		SetMapMode(hdc, MM_ANISOTROPIC);
		//Установка логических размеров вывода, ось У направлена вверх
		SetWindowExtEx(hdc, WIDTH, -HEIGHT, NULL);
		//Установка физических размеров на окно
		SetViewportExtEx(hdc, sx, sy, NULL);
		//Установка начала координат
		SetViewportOrgEx(hdc, sx / 2, sy / 2, NULL);
		/*BeginPath(hdc);
		Polyline(hdc, pt, 5);
		CloseFigure(hdc);
		EndPath(hdc);
		SelectObject(hdc, hBrush);
		SetPolyFillMode(hdc, WINDING); //Режим закрашивания "вся фигура"
		FillPath(hdc);*/

		BeginPath(hdc);
		Ellipse(hdc, -50, 50, 50, -50);
		MoveToEx(hdc,-100,100,NULL);
		Ellipse(hdc, -100, 100, 100, -100);
		EndPath(hdc);
		//CombineRgn(hRgn, CreateEllipticRgn(-100, 100, 100, -100), CreateEllipticRgn(-50, 50, 50, -50), WINDING);
		SelectObject(hdc, hBrush);
		FillPath(hdc); //Режим закрашивания "вся фигура"
		FillPath(hdc);

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
	{
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
