#include <Windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName[] = _T("MainFrame");

int APIENTRY WinMain(HINSTANCE This, HINSTANCE Prev, LPSTR cmd);
int mode()
{
	HWND hWnd; //Дескриптор главного окгна программы
	MSG msg; //Структура для хранения сообщений
	WNDCLASS wc; //Класс окна
	//Определение класса окна
	wc.hInstance = This;
	wc.lpszClassName = WinName; //Имя класса окна
	wc.lpfnWndProc = WndProc; //Функция окна
	wc.style = CS_HREDRAW | CS_VREDRAW; //Стиль окна
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //Стандартная иконка
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); //Стандартный курсор
	wc.lpszMenuName = NULL; //Нет меню
	wc.cbClsExtra = 0; //Нет дополнительных данных класса
	wc.cbWndExtra = 0; //Нет дополнительных даннных окна
	//Заполнение окна белым цветом
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); //Установка цвета окна
	if (!RegisterClass(&wc)) return 0; //Регистрация окна класса
	//Создание окна
	hWnd = CreateWindow(WinName, //Имя класса окна 
		_T("Каркас Window-приложения"), //Заголовок окна
		WS_OVERLAPPEDWINDOW, //Стиль окна
		CW_USEDEFAULT, //X
		CW_USEDEFAULT, //Y
		CW_USEDEFAULT, //Width
		CW_USEDEFAULT, //Hight
		HWND_DESKTOP, //Дескриптор родительского окна
		NULL, //Нет меню
		This, //Дескриптор приложения
		NULL); //Дополнительной информации нет
	ShowWindow(hWnd, mode); //Показать меню
	//Цикл обработки сообщений
	while (GetMessage(&msg, NULL, 0, 0)) //Цикл получения сообщений
	{
		TranslateMessage(&msg); //Функция трансляции кодов нажатой клавиши
		DispatchMessage(&msg); //Посылает сообщение функции WndProc()
	} return 0; //При положительном завершении программы в главную функцию 
	//возвращается "0"
}

//Оконная фукция вызываемая операционной системой
//и получает сообщения из  очеред для данного приложения
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{ //Обработчик сообщений
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break; //Завершение программы
		//Обработка сообщения по умолчанию
	default: return DefWindowProc(hWnd, message, wParam, lParam); //Возвращение
		//стандартных параметров по умолчанию
	} return 0;
}