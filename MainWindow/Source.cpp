#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<stdio.h>

CONST CHAR gsz_MY_WINDOW_CLASS[] = "MyWindowClass";
CONST CHAR gsz_WINDOW_NAME[] = "My FIRST Window";

INT CALLBACK WINAPI WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1) Регистрация класса окна:
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));

	wc.cbSize = sizeof(wc);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.style = 0; 
	wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION); 
	wc.hIconSm = LoadIcon(hInstance, IDI_APPLICATION); 
	wc.hCursor = LoadCursor(hInstance, IDC_ARROW); 
	wc.hInstance = hInstance; 
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW; 
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.lpszMenuName = NULL; 
	wc.lpszClassName = gsz_MY_WINDOW_CLASS;//проинициализировали поля класса

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class registration failed", "Error", MB_OK | MB_ICONERROR); 
		return 0; 
	}

	//2) Создание окна:
	
	int screen_width = GetSystemMetrics(SM_CXSCREEN);
	int screen_height = GetSystemMetrics(SM_CYSCREEN);
	int window_width = screen_width * 0.75; 
	int window_height = screen_height * 0.75; 
	int start_x = screen_width / 8; 
	int start_y = screen_height  / 8; 

	HWND hwnd = CreateWindowEx
	(
		NULL,	//ExStyle
		gsz_MY_WINDOW_CLASS,	//Class name
		gsz_WINDOW_NAME,		//Window name
		WS_OVERLAPPEDWINDOW,	//dwStyle
		start_x, start_y,	//Начальная позиция окна
		window_width, window_height,	//Размер окна
		NULL,		//HWND родительского окна. У главного окна НЕТ родительского окна
		NULL,		//Menu отсутствует
		hInstance,
		NULL
		);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "Error", MB_OK | MB_ICONERROR); 
		return 0; 
	}

	ShowWindow(hwnd, nCmdShow); 
	UpdateWindow(hwnd); 


	//3)  Запуск цикла сообщений:

	MSG msg; 
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg); 
	}
	return msg.wParam;
}

INT CALLBACK WINAPI WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:		break; 
	case WM_COMMAND:	break; 
	case WM_SIZE:
	case WM_MOVE:
	{

		RECT rect; 
		GetWindowRect(hwnd, &rect); 
		CONST int SIZE = 256; 
		CHAR sz_buffer[SIZE]={};
		sprintf(sz_buffer, "%s, Position:%dx%d, Size:%dx%d", gsz_WINDOW_NAME,
			rect.left, rect.top,
			rect.right - rect.left, rect.bottom - rect.top);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer); 
	}
	break; 
	case WM_DESTROY:	PostQuitMessage(0); break; 
	case WM_CLOSE: 
		switch (MessageBox(hwnd,
			"вы действительно закроете окно?", "Вопрос дорогой",
			MB_YESNO | MB_ICONQUESTION))
		{
		case IDYES: DestroyWindow(hwnd);
			MessageBox(hwnd, "Лучше б двери закрыли", "Полезная инфа", 
				MB_OK | MB_ICONINFORMATION);
			DestroyWindow(hwnd);
			break;
		}
		break; 
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam); 
	}
	return 0; 
}