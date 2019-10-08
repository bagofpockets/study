// Karkas2.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Karkas2.h"
#include "math.h"

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
    LoadStringW(hInstance, IDC_KARKAS2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KARKAS2));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KARKAS2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_KARKAS2);
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
	static long int sx, sy;
	static HPEN hpen, hpen1, hpen2, hpen3, hpen4;
	int a, b, n, x_scr, y_scr, z_scr; //Экранные координаты
	double x, y, z, x_min, x_max, y_min, y_max, Kx, Ky, h; //Физические координаты

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
		hpen2 = CreatePen(PS_SOLID, 2, RGB(0, 255, 255));
		hpen3 = CreatePen(PS_SOLID, 2, RGB(255, 255, 0));
		hpen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
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
            hdc = BeginPaint(hWnd, &ps);
			a = sx / 2; //Координаты
			b = sy / 2; //центра окна
			x_min = -100;
			x_max = 100;
			y_min = -100;
			y_max = 100;
			h = 3 * M_PI / a; //Шаг по оси x

			SelectObject(hdc, hpen);
			MoveToEx(hdc, 0, b, NULL);
			LineTo(hdc, sx, b);
			MoveToEx(hdc, a, 0, NULL);
			LineTo(hdc, a, sy);

			//y = tan x + 3
			bool flag = true;
			MoveToEx(hdc, 0, b -= 30, NULL);
			SelectObject(hdc, hpen3);
			for (x = -M_PI, x_scr = 0; x < M_PI; x += h)
			{
				x_scr = (x + M_PI) * a / M_PI;
				y_scr = b - b * tan(x);
				if ((x == -M_PI / 2) || (x == M_PI / 2)) continue; 
				else LineTo(hdc, x_scr + h, y_scr + h);
				
				
			}

			/*for (x = -M_PI, x_scr = 0; x < M_PI; x += h)
			{
				x_scr = (x + M_PI) * a / M_PI;
				y_scr = b - b * sin(x);
				LineTo(hdc, x_scr, y_scr);
			}*/

			/*SelectObject(hdc, hpen3);
			for (x = -M_PI, x_scr = 0; x < M_PI; x += h)
			{
				x_scr = (x + M_PI) * a / M_PI;
				y_scr = b - b * x * x;
				LineTo(hdc, x_scr, y_scr);
			}*/

			/*Kx = (sx - 220) / (x_max - x_min);
			Ky = (sy - 220) / (y_max - y_min);
			MoveToEx(hdc, 20, sy - 20, NULL);
			LineTo(hdc, sx - 20, 20);
			n = y_max - y_min;
			for (y = y_min; y < y_max; y += 5)
			{
				hpen1 = CreatePen(PS_SOLID, 2, RGB(255, 255 - 255. / n * (y + y_min), 255 - 255. / n * (y + y_min)));
				SelectObject(hdc, hpen1);
				z = b - 100 * sin(M_PI / 50 * sqrt(x_min * x_min + y * y));
				MoveToEx(hdc, x_min * Kx + a + y, z + y, NULL);
				for (x = x_min; x < x_max; x += 5)
				{
					z = b - 100 * sin(M_PI / 50 * sqrt(x * x + y * y));
					LineTo(hdc, x * Kx + a + y, z + y);
				}
			}*/

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
	{
		DeleteObject(hpen);
		DeleteObject(hpen1);
		DeleteObject(hpen2);
		DeleteObject(hpen3);
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
