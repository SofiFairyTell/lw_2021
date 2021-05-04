#include <Windows.h>
#include <WindowsX.h>
#include <CommCtrl.h>
#include <tchar.h>
#include <strsafe.h>
#include <gdiplus.h>
#include <gdiplusflat.h>
#include <gdiplustypes.h>
#include <sstream>

#pragma comment(lib, "gdiplus.lib")

int Time = 0;
UINT frameIndex; // индекс активного кадра
UINT frameCount; // количество кадров
int x_image = -290;

HWND hWnd = NULL;
ULONG_PTR gdiplusToken;
Gdiplus::GdiplusStartupInput gdiplusStartupInput;
Gdiplus::Image* image;
Gdiplus::Image* image1;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL PreTranslateMessage(LPMSG lpMsg);

void Display(HDC hdc);
Gdiplus::PointF Tween(const Gdiplus::PointF& A, const Gdiplus::PointF& B, float t);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR lpszCmdLine, int nCmdShow)
{
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = WndProc;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = TEXT("NewWindowClass");
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (RegisterClassEx(&wcex) == 0)
		return -1;
	LoadLibrary(TEXT("ComCtl32.dll"));
	setlocale(LC_ALL, "Russian");

	HWND hWnd = CreateWindowEx(0, TEXT("NewWindowClass"), TEXT("Компьютерная графика и геометрия. Лабораторная работа №3"),
		WS_OVERLAPPEDWINDOW & (~WS_MAXIMIZEBOX) ^ WS_THICKFRAME, CW_USEDEFAULT, 0, 1300, 600, NULL, NULL, hInstance, NULL);

	if (hWnd == NULL)
		return -1;
	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	BOOL bRet;
	for (;;)
	{
		bRet = GetMessage(&msg, NULL, 0, 0);
		if (bRet == -1)
		{
		}
		else if (bRet == FALSE)
			break;
		else if (PreTranslateMessage(&msg) == FALSE)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	Gdiplus::GdiplusShutdown(gdiplusToken); // Завершение работы с библиотекой
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		image = Gdiplus::Image::FromFile(L"lab3.gif");
		image1 = Gdiplus::Image::FromFile(L"lab3_1.gif");
		if (image == NULL || image1 == NULL)
			return -1; // загрузка не удалась
		frameIndex = 0;
		// определение количества кадров в изображении
		frameCount = image->GetFrameCount(&Gdiplus::FrameDimensionTime);
		SetTimer(hWnd, 1, 40, NULL); // устанавливает таймер ~ 25 FPS
		return 0;
	}
	break;

	case WM_TIMER:
	{
		Time++;
		// увеличиваем индекс кадра (циклически)
		frameIndex = (frameIndex + 1) % frameCount;
		// Делаем кадр активным
		image->SelectActiveFrame(&Gdiplus::FrameDimensionTime, frameIndex);
		// требуем обновления клиентской области окна (перерисовки)
		InvalidateRect(hWnd, NULL, FALSE);
		return 0;
	}
	break;

	case WM_DESTROY:
	{
		if (image != NULL || image1 != NULL)
			delete image; // удаляем объект
			delete image1;

		Gdiplus::GdiplusShutdown(gdiplusToken); // завершение работы GDI+
		PostQuitMessage(0);
	}
	break;

	case WM_ERASEBKGND:
		return 1;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		Display(hdc);
		EndPaint(hWnd, &ps);
	}
	return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

BOOL PreTranslateMessage(LPMSG lpMsg)
{
	return IsDialogMessage(hWnd, lpMsg);
}

int x = -210, y = 50; // главные координаты

Gdiplus::PointF left_rama[3] = { // левая рама
	Gdiplus::PointF(x + 250, y + 320),
	Gdiplus::PointF(x + 350, y + 330),
	Gdiplus::PointF(x + 330, y + 280)
};

Gdiplus::PointF right_rama[3] = { // правая рама
	Gdiplus::PointF(x + 330, y + 280),
	Gdiplus::PointF(x + 350, y + 330),
	Gdiplus::PointF(x + 445, y + 235)
};

int sx = x + 430, sy = y + 270;
Gdiplus::PointF right_wheel[8] = { // правое колесо
	Gdiplus::PointF(sx + 30, sy),
	Gdiplus::PointF(sx + 70, sy),
	Gdiplus::PointF(sx + 100, sy + 30),
	Gdiplus::PointF(sx + 100, sy + 70),
	Gdiplus::PointF(sx + 70, sy + 100),
	Gdiplus::PointF(sx + 30, sy + 100),
	Gdiplus::PointF(sx, sy + 70),
	Gdiplus::PointF(sx, sy + 30)
};

int sx2 = x + 200, sy2 = y + 270;
Gdiplus::PointF left_wheel[8] = { // левое колесо
	Gdiplus::PointF(sx2 + 30, sy2),
	Gdiplus::PointF(sx2 + 70, sy2),
	Gdiplus::PointF(sx2 + 100, sy2 + 30),
	Gdiplus::PointF(sx2 + 100, sy2 + 70),
	Gdiplus::PointF(sx2 + 70, sy2 + 100),
	Gdiplus::PointF(sx2 + 30, sy2 + 100),
	Gdiplus::PointF(sx2, sy2 + 70),
	Gdiplus::PointF(sx2, sy2 + 30)
};

Gdiplus::PointF back_pedal[2] = { // педаль заднего плана
	Gdiplus::PointF(x + 350, y + 329),
	Gdiplus::PointF(x + 335, y + 303)
};

Gdiplus::PointF back_pedal1[2] = { // педаль заднего плана
	Gdiplus::PointF(x + 330, y + 303),
	Gdiplus::PointF(x + 340, y + 303)
};

Gdiplus::PointF front_pedal[2] = { // педаль переднего плана
	Gdiplus::PointF(x + 350, y + 329),
	Gdiplus::PointF(x + 365, y + 355)
};
Gdiplus::PointF front_pedal1[2] = { // педаль переднего плана
	Gdiplus::PointF(x + 360, y + 355),
	Gdiplus::PointF(x + 370, y + 355)
};


int sx3 = x + 242, sy3 = y + 312;
Gdiplus::PointF small_star[8] = { // маленькая звезда
	Gdiplus::PointF(sx3 + 5, sy3),
	Gdiplus::PointF(sx3 + 11, sy3),
	Gdiplus::PointF(sx3 + 16, sy3 + 5),
	Gdiplus::PointF(sx3 + 16, sy3 + 11),
	Gdiplus::PointF(sx3 + 11, sy3 + 16),
	Gdiplus::PointF(sx3 + 5, sy3 + 16),
	Gdiplus::PointF(sx3, sy3 + 11),
	Gdiplus::PointF(sx3, sy3 + 5)
};

Gdiplus::PointF small_star1[2] = { // маленькая звезда
	Gdiplus::PointF(x + 242, y + 320),
	Gdiplus::PointF(x + 258, y + 320)
};

Gdiplus::PointF small_star2[2] = { // маленькая звезда
	Gdiplus::PointF(x + 250, y + 312),
	Gdiplus::PointF(x + 250, y + 328)
};

Gdiplus::PointF cep1[2] = { // цепь(верх)
	Gdiplus::PointF(x + 250, y + 312),
	Gdiplus::PointF(x + 350, y + 314)
};

Gdiplus::PointF cep2[2] = { // цепь(низ)
	Gdiplus::PointF(x + 250, y + 328),
	Gdiplus::PointF(x + 350, y + 344)
};

Gdiplus::PointF sit1[2] = { // зеленая пипка под седеньем
	Gdiplus::PointF(x + 350, y + 330),
	Gdiplus::PointF(x + 326, y + 270)
};

Gdiplus::PointF sit2[2] = { // черная пипка под сиденьем
	Gdiplus::PointF(x + 326, y + 270),
	Gdiplus::PointF(x + 318, y + 250)
};

Gdiplus::PointF sit3[2] = { // черная линия в сиденьем
	Gdiplus::PointF(x + 303, y + 250),
	Gdiplus::PointF(x + 333, y + 250)
};

int sx4 = x + 300, sy4 = y + 246;
Gdiplus::PointF sit4[8] = { // черный кружок в сиденье
	Gdiplus::PointF(sx4 + 4, sy4),
	Gdiplus::PointF(sx4 + 8, sy4),
	Gdiplus::PointF(sx4 + 12, sy4 + 4),
	Gdiplus::PointF(sx4 + 12, sy4 + 8),
	Gdiplus::PointF(sx4 + 8, sy4 + 12),
	Gdiplus::PointF(sx4 + 4, sy4 + 12),
	Gdiplus::PointF(sx4, sy4 + 8),
	Gdiplus::PointF(sx4, sy4 + 4)
};


Gdiplus::PointF big_star1[2] = { // большая звезда
	Gdiplus::PointF(x + 335, y + 329),
	Gdiplus::PointF(x + 365, y + 329)
};

Gdiplus::PointF big_star2[2] = { // большая звезда
	Gdiplus::PointF(x + 350, y + 344),
	Gdiplus::PointF(x + 350, y + 314)
};

int sx5 = x + 335, sy5 = y + 314;
Gdiplus::PointF big_star3[8] = { // большая звезда
	Gdiplus::PointF(sx5 + 9, sy5),
	Gdiplus::PointF(sx5 + 21, sy5),
	Gdiplus::PointF(sx5 + 30, sy5 + 9),
	Gdiplus::PointF(sx5 + 30, sy5 + 21),
	Gdiplus::PointF(sx5 + 21, sy5 + 30),
	Gdiplus::PointF(sx5 + 9, sy5 + 30),
	Gdiplus::PointF(sx5, sy5 + 21),
	Gdiplus::PointF(sx5, sy5 + 9)
};

Gdiplus::PointF vilka1[2] = { // вилка
	Gdiplus::PointF(x + 480, y + 320),
	Gdiplus::PointF(x + 445, y + 230)
};

int sx6 = x + 477, sy6 = y + 317;
Gdiplus::PointF vilka2[8] = { // вилка
	Gdiplus::PointF(sx6 + 2, sy6),
	Gdiplus::PointF(sx6 + 4, sy6),
	Gdiplus::PointF(sx6 + 6, sy6 + 2),
	Gdiplus::PointF(sx6 + 6, sy6 + 4),
	Gdiplus::PointF(sx6 + 4, sy6 + 6),
	Gdiplus::PointF(sx6 + 2, sy6 + 6),
	Gdiplus::PointF(sx6, sy6 + 4),
	Gdiplus::PointF(sx6, sy6 + 2)
};

Gdiplus::PointF rul[8] = { // руль
	Gdiplus::PointF(x + 445, y + 230),
	Gdiplus::PointF(x + 438, y + 212),
	Gdiplus::PointF(x + 440, y + 217),
	Gdiplus::PointF(x + 448, y + 213),
	Gdiplus::PointF(x + 447, y + 213),
	Gdiplus::PointF(x + 440, y + 195),
	Gdiplus::PointF(x + 441, y + 196),
	Gdiplus::PointF(x + 425, y + 200)
};

Gdiplus::PointF brick1[4] = { // кирпич 1
	Gdiplus::PointF(x + 1120, y + 170),
	Gdiplus::PointF(x + 1160, y + 170),
	Gdiplus::PointF(x + 1160, y + 200),
	Gdiplus::PointF(x + 1120, y + 200)
};

Gdiplus::PointF brick2[4] = { // кирпич 2
	Gdiplus::PointF(x + 1120, y + 200),
	Gdiplus::PointF(x + 1160, y + 200),
	Gdiplus::PointF(x + 1160, y + 230),
	Gdiplus::PointF(x + 1120, y + 230)
};
Gdiplus::PointF brick3[4] = { // кирпич 3
	Gdiplus::PointF(x + 1120, y + 230),
	Gdiplus::PointF(x + 1160, y + 230),
	Gdiplus::PointF(x + 1160, y + 260),
	Gdiplus::PointF(x + 1120, y + 260)
};

Gdiplus::PointF brick4[4] = { // кирпич 4
	Gdiplus::PointF(x + 1120, y + 260),
	Gdiplus::PointF(x + 1160, y + 260),
	Gdiplus::PointF(x + 1160, y + 290),
	Gdiplus::PointF(x + 1120, y + 290)
};

Gdiplus::PointF brick5[4] = { // кирпич 5
	Gdiplus::PointF(x + 1120, y + 290),
	Gdiplus::PointF(x + 1160, y + 290),
	Gdiplus::PointF(x + 1160, y + 320),
	Gdiplus::PointF(x + 1120, y + 320)
};

Gdiplus::PointF brick6[4] = { // кирпич 6
	Gdiplus::PointF(x + 1120, y + 320),
	Gdiplus::PointF(x + 1160, y + 320),
	Gdiplus::PointF(x + 1160, y + 350),
	Gdiplus::PointF(x + 1120, y + 350)
};

Gdiplus::PointF brick7[4] = { // кирпич 7
	Gdiplus::PointF(x + 1120, y + 350),
	Gdiplus::PointF(x + 1160, y + 350),
	Gdiplus::PointF(x + 1160, y + 380),
	Gdiplus::PointF(x + 1120, y + 380)
};

Gdiplus::PointF pnt1[1] = {
	Gdiplus::PointF(x + 350.f, y + 329.f),
};


void  Display(HDC  hdc)
{
	// создаем объект класса Graphics для рисования
	Gdiplus::Graphics graph(hdc);

	// определяем размер области рисования
	Gdiplus::Rect rect(0, 0, 1300, 600);
	graph.GetVisibleClipBounds(&rect);

	Gdiplus::Bitmap backbuffer(rect.Width, rect.Height, &graph);
	//создаем объект класса Grapchics для рисования в буфер
	Gdiplus::Graphics g(&backbuffer);

	g.Clear(Gdiplus::Color::White); // выполняем очистку перед рисованием
	g.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);

	// создаем сплошную кисть
	Gdiplus::SolidBrush  solidBrush(Gdiplus::Color::Yellow);
	Gdiplus::SolidBrush  grayBrush(Gdiplus::Color::Gray);
	Gdiplus::SolidBrush  blackBrush(Gdiplus::Color::Black);
	Gdiplus::SolidBrush  greenBrush(Gdiplus::Color::Green);
	Gdiplus::SolidBrush  cyanBrush(Gdiplus::Color::Cyan);
	Gdiplus::SolidBrush  dgraBrush(Gdiplus::Color::DimGray);
	Gdiplus::SolidBrush  navyBrush(Gdiplus::Color::Navy);
	Gdiplus::SolidBrush  whiteBrush(Gdiplus::Color::White);
	Gdiplus::SolidBrush  brickBrush(Gdiplus::Color::OrangeRed);
	
	Gdiplus::SolidBrush background(Gdiplus::Color::LightBlue);
	Gdiplus::SolidBrush background1(Gdiplus::Color::Brown);
	Gdiplus::Pen  sostav_pen(Gdiplus::Color::Black, 10.f);
	Gdiplus::HatchBrush  hatch_brush(Gdiplus::HatchStyleForwardDiagonal, Gdiplus::Color::Yellow, Gdiplus::Color::LightBlue);
	//  массив,  определяющий  составное  перо
	float  comp[6] = {
	0.0f,  0.2f,    //  1-я  линия:  от  0%  до  20%  от  толщины  пера
	0.3f,  0.7f,    //  2-я  линия:  от  30%  до  70%  от  толщины  пера
	0.8f,  1.0f };  //  3-я  линия:  от  80%  до  100%  от  толщины  пера

	sostav_pen.SetCompoundArray(comp, 6);
	Gdiplus::HatchBrush hBrush(Gdiplus::HatchStyleDiagonalCross, Gdiplus::Color::Black, Gdiplus::Color::WhiteSmoke);
							
	Gdiplus::Pen pen(Gdiplus::Color::Green, 6.f);
	Gdiplus::Pen brickPen(Gdiplus::Color::Red, 2.f);
	pen.SetEndCap(Gdiplus::LineCapFlat);
	pen.SetLineJoin(Gdiplus::LineJoinBevel);
	

	// создаем перо
	Gdiplus::Pen blackPen(Gdiplus::Color::Black, 4.f);
	Gdiplus::Pen silverPen(Gdiplus::Color::Silver, 3.f);
	Gdiplus::Pen blackPen1(Gdiplus::Color::Black, 6.f);
	blackPen1.SetEndCap(Gdiplus::LineCapRound);
	blackPen1.SetEndCap(Gdiplus::LineCapRound);
	Gdiplus::Pen pen3(Gdiplus::Color::Silver, 2.f);
	pen3.SetDashStyle(Gdiplus::DashStyleDot);


	{
		Gdiplus::Matrix mtrx;
		Gdiplus::Matrix mtrx1;

		int Timing_0 = -1,
			Timing_1 = 35,
			Timing_2 = 60,
			Timing_3 = 76,
			Timing_4 = 130,
			Timing_5 = 134,
			Timing_6 = 137,
			Timing_7 = 143,
			Timing_8 = 156,
			Timing_9 = 200; // прдолжительность анимации

		int Timing_1_2 = 18;
		int Timing_1_1 = 350;

		

		if ((Time > Timing_1_2) && Time < Timing_2) // двигаемся влево
		{
			mtrx.Translate(20, 0);
			
			mtrx.TransformPoints(left_rama, 3);
			mtrx.TransformPoints(right_rama, 3);
			mtrx.TransformPoints(right_wheel, 8);
			mtrx.TransformPoints(left_wheel, 8);
			
			mtrx.TransformPoints(small_star, 8);
			mtrx.TransformPoints(small_star1, 2);
			mtrx.TransformPoints(small_star2, 2);
			mtrx.TransformPoints(cep1, 2);
			mtrx.TransformPoints(cep2, 2);
			mtrx.TransformPoints(sit1, 2);
			mtrx.TransformPoints(sit2, 2);
			mtrx.TransformPoints(sit3, 2);
			mtrx.TransformPoints(sit4, 8);
			
			mtrx.TransformPoints(vilka1, 2);
			mtrx.TransformPoints(vilka2, 8);
			mtrx.TransformPoints(rul, 8);
			mtrx.TransformPoints(pnt1, 1);
			mtrx.TransformPoints(back_pedal, 2);
			mtrx.TransformPoints(back_pedal1, 2);
			mtrx.TransformPoints(front_pedal, 2);
			mtrx.TransformPoints(front_pedal1, 2);
			mtrx.TransformPoints(big_star1, 2);
			mtrx.TransformPoints(big_star2, 2);
			mtrx.TransformPoints(big_star3, 8);
			mtrx.TransformPoints(pnt1, 1);
			
		}

	

		g.FillRectangle(&background, 0, 0, 1300, 600);
		g.FillRectangle(&background1, 0, 375, 1300, 375);

		g.FillClosedCurve(&hBrush, left_wheel, 8);
		g.DrawClosedCurve(&sostav_pen, left_wheel, 8);

		g.FillClosedCurve(&hBrush, right_wheel, 8);
		g.DrawClosedCurve(&sostav_pen, right_wheel, 8);

		g.DrawLine(&blackPen, back_pedal1[0], back_pedal1[1]);
		g.DrawLine(&blackPen, back_pedal[0], back_pedal[1]);
		g.DrawPolygon(&pen, left_rama, 3);
		g.DrawPolygon(&pen, right_rama, 3);

		g.DrawClosedCurve(&silverPen, small_star, 8);
		g.DrawPolygon(&silverPen, small_star1, 2);
		g.DrawPolygon(&silverPen, small_star2, 2);

		g.DrawLine(&pen3, cep1[0], cep1[1]);
		g.DrawLine(&pen3, cep2[0], cep2[1]);

		g.DrawLine(&blackPen, front_pedal1[0], front_pedal1[1]);
		g.DrawLine(&blackPen, front_pedal[0], front_pedal[1]);

		g.DrawLine(&blackPen, rul[0], rul[1]);
		g.DrawLine(&blackPen, rul[2], rul[3]);
		g.DrawLine(&blackPen, rul[4], rul[5]);
		g.DrawLine(&blackPen, rul[6], rul[7]);

		g.DrawLine(&pen, vilka1[0], vilka1[1]);
		g.FillClosedCurve(&blackBrush, vilka2, 8);

		g.DrawLine(&pen, sit1[0], sit1[1]);
		g.DrawLine(&blackPen, sit2[0], sit2[1]);
		g.DrawLine(&blackPen1, sit3[0], sit3[1]);
		g.FillClosedCurve(&blackBrush, sit4, 8);

		g.DrawClosedCurve(&blackPen, big_star3, 8);
		g.DrawPolygon(&blackPen, big_star1, 2);
		g.DrawPolygon(&blackPen, big_star2, 2);

		g.FillPolygon(&brickBrush, brick1, 4);
		g.DrawPolygon(&brickPen, brick1, 4);
		g.FillPolygon(&brickBrush, brick2, 4);
		g.DrawPolygon(&brickPen, brick2, 4);
		g.FillPolygon(&brickBrush, brick3, 4);
		g.DrawPolygon(&brickPen, brick3, 4);
		g.FillPolygon(&brickBrush, brick4, 4);
		g.DrawPolygon(&brickPen, brick4, 4);
		g.FillPolygon(&brickBrush, brick5, 4);
		g.DrawPolygon(&brickPen, brick5, 4);
		g.FillPolygon(&brickBrush, brick6, 4);
		g.DrawPolygon(&brickPen, brick6, 4);
		g.FillPolygon(&brickBrush, brick7, 4);
		g.DrawPolygon(&brickPen, brick7, 4);


		/*===================================================*/






		if (Time > Timing_2 - 13 && Time < Timing_1_1)
		{

			brick1[0] = Tween(brick1[0], brick1[1], 0.1);
			brick1[1] = Tween(brick1[1], brick1[2], 0.1);
			brick1[2] = Tween(brick1[2], brick1[3], 0.1);
			brick1[3] = Tween(brick1[3], brick1[0], 0.1);

			brick2[0] = Tween(brick2[0], brick2[1], 0.1);
			brick2[1] = Tween(brick2[1], brick2[2], 0.1);
			brick2[2] = Tween(brick2[2], brick2[3], 0.1);
			brick2[3] = Tween(brick2[3], brick2[0], 0.1);

			brick3[0] = Tween(brick3[0], brick3[1], 0.1);
			brick3[1] = Tween(brick3[1], brick3[2], 0.1);
			brick3[2] = Tween(brick3[2], brick3[3], 0.1);
			brick3[3] = Tween(brick3[3], brick3[0], 0.1);

			brick4[0] = Tween(brick4[0], brick4[1], 0.1);
			brick4[1] = Tween(brick4[1], brick4[2], 0.1);
			brick4[2] = Tween(brick4[2], brick4[3], 0.1);
			brick4[3] = Tween(brick4[3], brick4[0], 0.1);

			brick5[0] = Tween(brick5[0], brick5[1], 0.1);
			brick5[1] = Tween(brick5[1], brick5[2], 0.1);
			brick5[2] = Tween(brick5[2], brick5[3], 0.1);
			brick5[3] = Tween(brick5[3], brick5[0], 0.1);

			brick6[0] = Tween(brick6[0], brick6[1], 0.1);
			brick6[1] = Tween(brick6[1], brick6[2], 0.1);
			brick6[2] = Tween(brick6[2], brick6[3], 0.1);
			brick6[3] = Tween(brick6[3], brick6[0], 0.1);

			brick7[0] = Tween(brick7[0], brick7[1], 0.1);
			brick7[1] = Tween(brick7[1], brick7[2], 0.1);
			brick7[2] = Tween(brick7[2], brick7[3], 0.1);
			brick7[3] = Tween(brick7[3], brick7[0], 0.1);
			//brick1[8] = brick1[0];
			;

			mtrx.Translate(5, -30);
			mtrx.TransformPoints(brick1, 4);

			mtrx.Translate(5, 15);
			mtrx.TransformPoints(brick2, 4);

			mtrx.Translate(5, 10);
			mtrx.TransformPoints(brick3, 4);

			mtrx.Translate(5, 5);
			mtrx.TransformPoints(brick4, 4);

			mtrx.Translate(5, 0);
			mtrx.TransformPoints(brick5, 4);

			mtrx.Translate(5, 10);
			mtrx.TransformPoints(brick6, 4);

			mtrx.Translate(5, 15);
			mtrx.TransformPoints(brick7, 4);


		}
		/*=======================================================*/
		
		if (Time > Timing_0 && (Time < Timing_1_2))
		{	
			g.DrawImage(image, x_image, 50, 500, 500);
			x_image += 11;
		}

		if (Time > Timing_1_2 && (Time < Timing_1))
		{
			g.DrawImage(image, x_image, 50, 500, 500);
			x_image += 20;
		}

		if (Time > Timing_1)
		{
			g.DrawImage(image1, x_image, 50, 500, 500);
			
		}
	}

	graph.DrawImage(&backbuffer, rect); // выводим на экран готовое изображение из буфера								
}  //  Display


//вставка изображения в программе 

Gdiplus::PointF Tween(const Gdiplus::PointF& A, const Gdiplus::PointF& B, float t) // Функция нахождения промежуточных точек
{
	return Gdiplus::PointF(A.X * (1.f - t) + B.X * t, A.Y * (1.f - t) + B.Y * t);
}
