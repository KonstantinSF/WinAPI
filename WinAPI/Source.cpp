#include <Windows.h>
#include "resource.h"
//#define MSG_BOX

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam); 

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{

#ifdef MSG_BOX
	MessageBox(NULL, "������!��� ���� ������ ���������", "��������� ���� ���������",
		MB_YESNOCANCEL | MB_HELP | MB_ICONWARNING | MB_DEFBUTTON3 |
		MB_SYSTEMMODAL//������ ���� ����
	);
#endif // MSG_BOX
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0); 
	return 0; 
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)//����� �������
{
	switch (uMsg)
	{
	case WM_INITDIALOG: //�������� ��������� ����
	{//��� ��������� ������� ��������� ��� �����
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), (LPSTR)IDI_ICON1); 
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon); //�������� ��������� ����
		SetDlgItemText(hwnd, IDC_EDIT_LOGIN, "Login"); //�������� ����� � EditControl
		SetDlgItemText(hwnd, IDC_EDIT_PASSWORD, "Password"); 
	}
	break; 
	case WM_COMMAND:
		switch (LOWORD(wParam))//��� ������������� ������� �������
		{
		case IDC_BUTTON_COPY:
		{

			CONST INT SIZE = 256; 
			CHAR buffer[SIZE] = {}; 
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN); 
			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD); 
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)buffer); 
			SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)buffer); 
		}
			break; 
		case IDOK: MessageBox(NULL, "���� ������ ������ ��", "Info", MB_OK | MB_ICONINFORMATION); break; 
		case IDCANCEL: EndDialog(hwnd, 0); 
		}
		break; 
	case WM_CLOSE: 
			EndDialog(hwnd, 0); 
	}
	return FALSE; 
}