//#include <Windows.h>
//#include <WindowsX.h>
//#include <CommCtrl.h>
//#include <tchar.h>
//#include <fstream>
//#include <string>
//#include <gdiplus.h>
//#include <gdiplusgraphics.h>
//#include <list>
//#include <vector>
//#define  PI 3.1416f 
//#include "Dot.h"
///*
//* ������� - �����
//* ������� -
//*	����� ��������� ���������
//*	��������� �����
//*	��������� �����
//*�����: �������� �������
//*������������: ����� ����������� ����������� �������
//*/
//
//#pragma comment(lib, "GdiPlus.lib")
//
//using namespace Gdiplus;
//
//#pragma comment(linker,"\"/manifestdependency:type                  = 'win32' \
//                                              name                  = 'Microsoft.Windows.Common-Controls' \
//                                              version               = '6.0.0.0' \
//                                              processorArchitecture = '*' \
//                                              publicKeyToken        = '6595b64144ccf1df' \
//                                              language              = '*'\"")
//#pragma warning(disable : 4996) //��������� ������ deprecate. ���������, ����� ������������ ���������� ������� 
//
////����������
//
//HWND hwnd = NULL; //���������� ����
//void Display(HDC hdc); //������� ��� ������ ������ �� ������
//void DrawImg(HDC hdc); //�������� ����������� �� �����
//void CalculateDots(std::vector<PointF> &dots, int m);
//
//Image* img;
///*��� ��������� ����� ����, ����� ���� ���������� WM_SYSCHAR */
//RECT rc;
//HBRUSH brushes[3]; //����� ��� ��������� ����� ����
//int brush_index = 0;
////���������� ��� �����������
//
///*������� ���������*/
//LRESULT CALLBACK MainWindowProcess(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//
///*����������� WM_CREATE, WM_DESTROY, WM_SIZE*/
//
//BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
//void OnDestroy(HWND hwnd);
//void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
//
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int  CmdShow)
//{
//	brushes[0] = (HBRUSH)CreateSolidBrush(RGB(0, 0, 100)); //����������-����� ����
//	brushes[1] = (HBRUSH)CreateSolidBrush(RGB(0, 100, 0)); //����������-������� ����
//	brushes[2] = (HBRUSH)CreateSolidBrush(RGB(100, 0, 0)); //����������-������� ����
//
//	// ������������ ������� ����� �������� ����...
//	WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
//	wcex.style = CS_HREDRAW | CS_VREDRAW;
//	wcex.lpfnWndProc = MainWindowProcess; // ������� ���������
//	wcex.hInstance = hInstance;
//	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
//	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wcex.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
//
//	wcex.lpszClassName = TEXT("MainWindowProcess"); // ��� ������
//	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
//	//wcex.hbrBackground = brushes[brush_index];
//
//	if (0 == RegisterClassEx(&wcex))
//	{
//		return -1;
//	}
//	/*---------------------------------------------*/
//
//	LoadLibrary(TEXT("ComCtl32.dll"));
//	//�������� �����������
//	//img = Image::FromFile(L"C:\\Users\\it\\Downloads\\CGG\\lw_1\\KATER1.png");
//
//	/*������������ GDI+*/
//	ULONG_PTR gdToken;
//	GdiplusStartupInput gdInput;
//
//	LSTATUS retRes = GdiplusStartup(&gdToken, &gdInput, NULL);	/*�������� �������� ����� � ��������� ������ */
//	hwnd = CreateWindowEx(0, TEXT("MainWindowProcess"), TEXT("Kater"),
//		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, 900, 600, NULL, NULL, hInstance, NULL);
//
//	if (hwnd == NULL)
//	{
//		return -1;
//	}
//	/*--------------------------------------------------*/
//
//			//img->FromFile(L"C:\\Users\\it\\Downloads\\CGG\\lw_1\\KATER1.png");
//	img = Image::FromFile(L"C:\\Users\\it\\Downloads\\CGG\\lw_1\\KATER1.png");
//	ShowWindow(hwnd, CmdShow); // ���������� ������� ����
//
//	/*���� ��������� ���������*/
//	MSG  msg;
//	BOOL RetRes;
//	while ((RetRes = GetMessage(&msg, NULL, 0, 0)) != FALSE)
//	{
//		if (RetRes == -1)
//		{
//			//Error editing
//		}
//		else
//		{
//			TranslateMessage(&msg);
//			DispatchMessage(&msg);
//		}
//	}
//
//	delete(img);
//	GdiplusShutdown(gdToken);
//
//	return (int)msg.wParam;
//
//}
//
//#pragma region Work with Main Window
//LRESULT CALLBACK MainWindowProcess(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	HDC hdc;             // ������ ��������� ����������
//	PAINTSTRUCT ps;      // ��������� ��� ���������
//
//	switch (msg)
//	{
//		HANDLE_MSG(hwnd, WM_CREATE, OnCreate);
//		HANDLE_MSG(hwnd, WM_DESTROY, OnDestroy);
//	case WM_PAINT:
//	{
//		PAINTSTRUCT pstruct;
//		HDC hdc = BeginPaint(hwnd, &pstruct);
//		Display(hdc);
//
//		DrawImg(hdc);
//		EndPaint(hwnd, &ps);
//	}break;
//	case WM_LBUTTONDOWN:
//	{
//		DWORD xPos = NULL, yPos = NULL, nSize = NULL;
//		TCHAR szBuf[80];
//
//		hdc = GetDC(hwnd);
//		// ��������� ���������� ������� ����
//		xPos = LOWORD(lParam);
//		yPos = HIWORD(lParam);
//		nSize = wsprintf(szBuf, TEXT("(%d, %d)"), xPos, yPos);
//
//
//
//		TextOut(hdc, xPos, yPos, szBuf, nSize);
//
//	}break;
//
//	}
//	return DefWindowProc(hwnd, msg, wParam, lParam);
//}
//
//BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCRStr)
//{
//	DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL;
//	return TRUE;
//}
//
//void OnDestroy(HWND hwnd)
//{
//	PostQuitMessage(0); // ���������� ��������� WM_QUIT
//}
//
////�� ��� ���� ���� �������� � x86
//inline float Sin(float angle)
//{
//	__asm
//	{
//		fld angle;
//		fsin;
//	}
//}
//
//inline float Cos(float angle)
//{
//	__asm
//	{
//		fld angle;
//		fcos;
//	}
//}
//
//void DrawImg(HDC hdc)
//{
//	Graphics g(hdc);
//	//g.Clear(Color::LightCyan);
//
//	//���� ����������� ����� �������, ��� ���� ���������
//	RectF rectImg;
//	RectF layout(0, 0, 200.f, 150.f);
//	float fRat = (float)img->GetWidth() / (float)img->GetHeight();
//	if (fRat > (layout.Width / layout.Height))
//	{
//		rectImg.Width = layout.Width;
//		rectImg.Height = layout.Width / fRat;
//		rectImg.X = layout.GetLeft();
//		rectImg.Y = layout.GetTop();
//	}
//	else
//	{
//		rectImg.Width = fRat * layout.Height;
//		rectImg.Height = layout.Height;
//		rectImg.X = layout.GetLeft();
//	}
//
//	g.DrawImage(img, rectImg);
//}
//
//void CalculateDots(std::vector<PointF> &dots, int m)
//{
//	float t = 0.00f;
//	for (int i = 0; i < m; i++)
//	{
//		float X = -2.0f * Cos(t) + 3.0f* Cos(-2.0f / 3.0f * t);
//		float Y = -2.0f * Sin(t) - 3.0f * Sin(-2.0f / 3.0f * t);
//
//		dots[i].X += X;
//		dots[i].Y += Y;
//		t += 0.05f;
//	}
//}
//void Display(HDC hdc)
//{
//	Graphics g(hdc);
//	g.Clear(Color::NavajoWhite);
//	//�����������
//	g.SetSmoothingMode(SmoothingModeHighQuality);
//	Rect rect(0, 0, 600, 600); //������������� ��� ���������
//	//�����
//	Pen kater_border(Color::Blue, 10.f);//����� ��� ���������� ������
//	SolidBrush brushYellow(Color::Yellow);//������� �����
//	HatchBrush hatchBrush(HatchStyleForwardDiagonal, Color::Aquamarine, Color::Bisque);//��������� �����
//	HatchBrush hatchBrush_vibes(HatchStyleShingle, Color::Yellow, Color::Red);//��������� �����
//	LinearGradientBrush linBrush(rect, Color::Indigo, Color::Goldenrod, 40.f); //����� � �������� ����������
//
//#pragma region Part of kater
//	//����� ������
//	Rect kater_part[3] =
//	{
//		Rect(250,200,460,200),//���� ������
//		Rect(710,290,80,90),//����� ������
//		Rect(318,130,160,70),//���� ��� �����??
//	};
//
//	//����� ��� ��������������
//	Point kater_nose[3] =
//	{
//		Point(40,200), Point(250,200), Point(250,400),
//	};
//
//	Point kater_glass[4] =
//	{
//		Point(170,200), Point(330,77),	Point(480,77), Point(520,200)
//	};
//	Point kater_handline[4] =
//	{
//		Point(507,140),
//		Point(585,150),
//		Point(661,160),
//		Point(709,192),
//	};
//
//	float border_part[6] =
//	{
//		0.0f,0.2f, //�� 0 �� 20% ������� �����
//		0.3f, 0.7f,
//		0.8f, 1.0f
//	};
//
//#pragma endregion
//	kater_border.SetCompoundArray(border_part, 6); //��������� ����
//
//
//	Color gradient_color[3] =
//	{
//		Color(255,255,0,0),//red
//		Color(255,0,0,255),//blue
//		Color(255,0,255,0)//green
//	};
//	//����� ��� ��������� �����
//	float pos[4] = { 0.0f, 0.3f, 0.6f, 1.0f };
//	//������ �������� �������� ���������. �.�. ������� �� ��������� ����� ��������� ���������
//	float factors[4] = { 0.0f, 0.2f, 0.8f, 1.0f };
//
//	//��������� ��������� ��������� � ������������ ���������� ����� � ��������������
//	linBrush.SetBlend(factors, pos, 4);
//	linBrush.SetGammaCorrection(TRUE);
//
//	//��������� ������
//	g.Clear(Color::CornflowerBlue);
//	g.SetSmoothingMode(SmoothingModeHighQuality);
//
//
//	g.FillRectangle(&linBrush, kater_part[0]);		//������
//	g.FillRectangle(&hatchBrush, kater_part[1]);	//�����
//
//	g.DrawRectangles(&kater_border, kater_part, 3);	//������������ ������� ��������� ������
//	g.FillPolygon(&linBrush, kater_nose, 3);			//��� ����������
//	g.DrawPolygon(&kater_border, kater_nose, 3);	//��� ������
//
//
//	g.FillEllipse(&hatchBrush_vibes, Rect(150, 50, 500, 500));
//
//	g.FillRectangle(&brushYellow, kater_part[2]);	//������
//	g.DrawPolygon(&kater_border, kater_glass, 4);	//������ ��� ��������
//
//
//
//
//
//
//
//	//�������� �����
//	g.FillClosedCurve(&brushYellow, kater_handline, 4);
//	g.DrawClosedCurve(&kater_border, kater_handline, 4);
//
//
//	HatchBrush hatchBrushText(HatchStyleDiagonalBrick, Color::Black, Color::Red);//��������� �����
//	FontFamily fontFamily(L"Times New Roman");
//	Font font(&fontFamily, 40.f, FontStyleBoldItalic);
//
//	LANGID lang = MAKELANGID(LANG_RUSSIAN, SUBLANG_RUSSIAN_RUSSIA);
//	StringFormat sf = new StringFormat(0, lang);
//
//	sf.SetFormatFlags(StringAlignmentNear);
//	RectF rectF(470.f, 310.f, 250.f, 100.f);
//
//	g.DrawString(L"Kater-1", -1, &font, rectF, &sf, &hatchBrushText);
//
//
//	g.DrawEllipse(&kater_border, Rect(270, 240, 100, 100));
//	g.DrawEllipse(&kater_border, Rect(440, 240, 100, 100));
//
//}
//
//
//
