#include<Windows.h>
#include "resource.h"

CONST CHAR* string[] = { "This", "is", "my", "first", "Combo", "Box" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam); 

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hList = GetDlgItem(hwnd, IDC_LIST1);
		for (int i = 0; i < sizeof(string) / sizeof(string[0]); i++)
		{
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)string[i]);
		}
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			HWND hList = GetDlgItem(hwnd, IDC_LIST1);
			CONST int SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			//CHAR sz_output_buffer[SIZE] = "Вы выбрали элемент №";

			int i = SendMessage(hList, LB_GETCURSEL, 0, 0); //получаем номер выделенного элемента КомбоБокс
			SendMessage(hList, LB_GETTEXT, i, (LPARAM)sz_buffer);
			//Сообщение CB_GETLBTEXT читает выбранный элемент выпадающего списка в буфер:
			//sprintf(sz_output_buffer, "Вы выбрали строку № %i со значением \"%s\".", i, sz_buffer);
			//MessageBox(hwnd, sz_output_buffer, "Selected item", MB_OK | MB_ICONINFORMATION);
		}
		break;
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}

		break;
	case WM_CLOSE: EndDialog(hwnd, 0);
	}

	return FALSE; 
}