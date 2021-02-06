#include <Windows.h>
#include <WindowsX.h>
#include <CommCtrl.h>
#include <tchar.h>
#include <fstream>
#include <string>
#include <gdiplus.h>
#include <gdiplusgraphics.h>


#pragma comment(lib, "GdiPlus.lib")

using namespace Gdiplus;

#pragma comment(linker,"\"/manifestdependency:type                  = 'win32' \
                                              name                  = 'Microsoft.Windows.Common-Controls' \
                                              version               = '6.0.0.0' \
                                              processorArchitecture = '*' \
                                              publicKeyToken        = '6595b64144ccf1df' \
                                              language              = '*'\"")
#pragma warning(disable : 4996) //��������� ������ deprecate. ���������, ����� ������������ ���������� ������� 

//����������

HWND hwnd = NULL; //���������� ����
void Display(HDC hdc);
/*��� ��������� ����� ����, ����� ���� ���������� WM_SYSCHAR */
RECT rc;
HBRUSH brushes[3]; //����� ��� ��������� ����� ����
int brush_index = 0;

/*������� ���������*/
LRESULT CALLBACK MainWindowProcess(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/*����������� WM_CREATE, WM_DESTROY, WM_SIZE*/

BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void OnDestroy(HWND hwnd);
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int  CmdShow)
{ 
	brushes[0] = (HBRUSH)CreateSolidBrush(RGB(0, 0, 100)); //����������-����� ����
	brushes[1] = (HBRUSH)CreateSolidBrush(RGB(0, 100, 0)); //����������-������� ����
	brushes[2] = (HBRUSH)CreateSolidBrush(RGB(100, 0, 0)); //����������-������� ����

	// ������������ ������� ����� �������� ����...
	WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = MainWindowProcess; // ������� ���������
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);

	wcex.lpszClassName = TEXT("MainWindowProcess"); // ��� ������
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	//wcex.hbrBackground = brushes[brush_index];

	if (0 == RegisterClassEx(&wcex))
	{
		return -1;
	}
	/*---------------------------------------------*/

	LoadLibrary(TEXT("ComCtl32.dll"));

	/*�������� �������� ����� � ��������� ������ */
	hwnd = CreateWindowEx(0, TEXT("MainWindowProcess"), TEXT("Chat"),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, 900, 600, NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		return -1;
	}
	/*--------------------------------------------------*/

	ShowWindow(hwnd, CmdShow); // ���������� ������� ����

	/*���� ��������� ���������*/
	MSG  msg;
	BOOL RetRes;
	while ((RetRes = GetMessage(&msg, NULL, 0, 0)) != FALSE)
	{
		if (RetRes == -1)
		{
			//Error editing
		}
		else 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
	//yjdsq rjvvtynfhb

}

#pragma region Work with Main Window
LRESULT CALLBACK MainWindowProcess(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;             // ������ ��������� ����������
	PAINTSTRUCT ps;      // ��������� ��� ���������

	switch (msg)
	{
		HANDLE_MSG(hwnd, WM_CREATE, OnCreate);
		//HANDLE_MSG(hwnd, WM_COMMAND, OnCommand)
		case WM_PAINT:
			{
				PAINTSTRUCT pstruct;
				HDC hdc = BeginPaint(hwnd, &pstruct);
				Display(hdc);
				EndPaint(hwnd,&ps);
		}break;
		case WM_LBUTTONDOWN:
		{
			DWORD xPos = NULL, yPos = NULL, nSize = NULL;
			TCHAR szBuf[80];

			hdc = GetDC(hwnd);
			// ��������� ���������� ������� ����
			xPos = LOWORD(lParam);
			yPos = HIWORD(lParam);
			nSize = wsprintf(szBuf, TEXT("(%d, %d)"), xPos, yPos);
			TextOut(hdc, xPos, yPos, szBuf, nSize);

			Graphics g(hdc);
			g.Clear(Color::Black);

		}break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

	BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCRStr)
	{
		DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL;

		return TRUE;
	}

	void OnCommand(HWND hWnd, int id, HWND hwnCTRL, UINT codeNotify)
	{
	}

	void OnDestroy(HWND hwnd)
	{
		PostQuitMessage(0); // ���������� ��������� WM_QUIT
	}
	
	void Display(HDC hdc)
	{
		Graphics g(hdc);
		g.Clear(Color::Black);

		//Rect rect;
		//g.GetVisibleClipBounds(&rect);
		//Bitmap buffer(rect.Width, rect.Height, &g);
		//Graphics temp(&buffer);


		//temp.Clear(Color::Aqua);
		//SolidBrush brush(Color::Black);
		//Pen penBrown(&brush,6.f);//��� ��������� �������
		//
		////��� ������� ��������������
		//Point pt1(10,10);
		//Point pt2(300,300);
		//temp.FillRectangle(&brush, 320, 330, 500, 70);
		//temp.DrawLine(&penBrown, pt1, pt2);
		//
		//g.DrawImage(&buffer, rect);
	}

