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
void Display(HDC hdc); //������� ��� ������ ������ �� ������
void DrawImg(HDC hdc); //�������� ����������� �� �����
Image* img;
/*��� ��������� ����� ����, ����� ���� ���������� WM_SYSCHAR */
RECT rc;
HBRUSH brushes[3]; //����� ��� ��������� ����� ����
int brush_index = 0;
//���������� ��� �����������

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
	//�������� �����������

	/*������������ GDI+*/
	ULONG_PTR gdToken;
	GdiplusStartupInput gdInput;

	LSTATUS retRes = GdiplusStartup(&gdToken, &gdInput, NULL);	/*�������� �������� ����� � ��������� ������ */
	hwnd = CreateWindowEx(0, TEXT("MainWindowProcess"), TEXT("Curve"),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, 900, 600, NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		return -1;
	}
	/*--------------------------------------------------*/

	//img = Image::FromFile(L"C:\\Users\\it\\Downloads\\CGG\\lw_1\\KATER1.png");
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

	delete(img);
	GdiplusShutdown(gdToken);

	return (int)msg.wParam;

}

#pragma region Work with Main Window
LRESULT CALLBACK MainWindowProcess(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;             // ������ ��������� ����������
	PAINTSTRUCT ps;      // ��������� ��� ���������


	switch (msg)
	{
		HANDLE_MSG(hwnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hwnd, WM_DESTROY, OnDestroy);
		//HANDLE_MSG(hwnd, WM_COMMAND, OnCommand)
	case WM_PAINT:
	{
		PAINTSTRUCT pstruct;
		HDC hdc = BeginPaint(hwnd, &pstruct);
		
		Display(hdc);

		EndPaint(hwnd, &ps);
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
	g.Clear(Color::LightCyan);
	//�����������
	g.SetSmoothingMode(SmoothingModeHighQuality);
	int m = 6;
	PointF *dots = new PointF[m];
	
	for (int i = 0; i < m; i++)
	{
		dots[i].X = 0.1f;
		dots[i].Y = 0.1f;
	}
	//����� ��� ���������� ������
	Pen curvePen(Color::Blue, 10.f);

	
}

