#include <Windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName[] = _T("MainFrame");

int APIENTRY WinMain(HINSTANCE This, HINSTANCE Prev, LPSTR cmd);
int mode()
{
	HWND hWnd; //���������� �������� ����� ���������
	MSG msg; //��������� ��� �������� ���������
	WNDCLASS wc; //����� ����
	//����������� ������ ����
	wc.hInstance = This;
	wc.lpszClassName = WinName; //��� ������ ����
	wc.lpfnWndProc = WndProc; //������� ����
	wc.style = CS_HREDRAW | CS_VREDRAW; //����� ����
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //����������� ������
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); //����������� ������
	wc.lpszMenuName = NULL; //��� ����
	wc.cbClsExtra = 0; //��� �������������� ������ ������
	wc.cbWndExtra = 0; //��� �������������� ������� ����
	//���������� ���� ����� ������
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); //��������� ����� ����
	if (!RegisterClass(&wc)) return 0; //����������� ���� ������
	//�������� ����
	hWnd = CreateWindow(WinName, //��� ������ ���� 
		_T("������ Window-����������"), //��������� ����
		WS_OVERLAPPEDWINDOW, //����� ����
		CW_USEDEFAULT, //X
		CW_USEDEFAULT, //Y
		CW_USEDEFAULT, //Width
		CW_USEDEFAULT, //Hight
		HWND_DESKTOP, //���������� ������������� ����
		NULL, //��� ����
		This, //���������� ����������
		NULL); //�������������� ���������� ���
	ShowWindow(hWnd, mode); //�������� ����
	//���� ��������� ���������
	while (GetMessage(&msg, NULL, 0, 0)) //���� ��������� ���������
	{
		TranslateMessage(&msg); //������� ���������� ����� ������� �������
		DispatchMessage(&msg); //�������� ��������� ������� WndProc()
	} return 0; //��� ������������� ���������� ��������� � ������� ������� 
	//������������ "0"
}

//������� ������ ���������� ������������ ��������
//� �������� ��������� ��  ������ ��� ������� ����������
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{ //���������� ���������
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break; //���������� ���������
		//��������� ��������� �� ���������
	default: return DefWindowProc(hWnd, message, wParam, lParam); //�����������
		//����������� ���������� �� ���������
	} return 0;
}