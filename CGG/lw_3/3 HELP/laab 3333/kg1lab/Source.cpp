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


HWND hWnd = NULL;
ULONG_PTR gdiplusToken;
Gdiplus::GdiplusStartupInput gdiplusStartupInput;
Gdiplus::Image* image;

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
		WS_OVERLAPPEDWINDOW & (~WS_MAXIMIZEBOX) ^ WS_THICKFRAME, CW_USEDEFAULT, 0, 1300, 800, NULL, NULL, hInstance, NULL);

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
		image = Gdiplus::Image::FromFile(L"rocket.gif");
	
		if (image == NULL )
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
		if (image != NULL)
			delete image; // удаляем объект

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

int y = 200; // главные координаты

Gdiplus::PointF hat[3] = { //треугольник наверху
			Gdiplus::PointF(440, y + 50),
			Gdiplus::PointF(400, y + 130),
			Gdiplus::PointF(480, y + 130)
};

Gdiplus::PointF top[8] = { //верхняя часть
			Gdiplus::PointF(400, y + 140),
			Gdiplus::PointF(400, y + 330),
			Gdiplus::PointF(410, y + 340),
			Gdiplus::PointF(470, y + 340),
			Gdiplus::PointF(480, y + 330),
			Gdiplus::PointF(480, y + 140),
			Gdiplus::PointF(470, y + 130),
			Gdiplus::PointF(410, y + 130)
};

Gdiplus::PointF Hfire1[3] = { // скрытый огонь 1
				Gdiplus::PointF(410, y + 340),
				Gdiplus::PointF(470, y + 340),
				Gdiplus::PointF(440, y + 410)
};

Gdiplus::PointF Hfire2[3] = { // скрытый огонь 2
				Gdiplus::PointF(420, y + 340),
				Gdiplus::PointF(460, y + 340),
				Gdiplus::PointF(440, y + 370)
};

Gdiplus::PointF bot[8] = { //нижняя часть
			Gdiplus::PointF(410, y + 340),
			Gdiplus::PointF(400, y + 350),
			Gdiplus::PointF(400, y + 510),
			Gdiplus::PointF(410, y + 520),
			Gdiplus::PointF(470, y + 520),
			Gdiplus::PointF(480, y + 510),
			Gdiplus::PointF(480, y + 350),
			Gdiplus::PointF(470, y + 340)
};

Gdiplus::PointF botl[3] = { //левый треугольник
			Gdiplus::PointF(400, y + 350),
			Gdiplus::PointF(400, y + 520),
			Gdiplus::PointF(330, y + 520)
};

Gdiplus::PointF botr[3] = { // правый треугольник
			Gdiplus::PointF(480, y + 350),
			Gdiplus::PointF(480, y + 520),
			Gdiplus::PointF(550, y + 520)
};
//ромбики
Gdiplus::PointF romb1[4] = {
			Gdiplus::PointF(440, y + 155),
			Gdiplus::PointF(455, y + 170),
			Gdiplus::PointF(440, y + 185),
			Gdiplus::PointF(425, y + 170)
};

Gdiplus::PointF romb2[4] = {
			Gdiplus::PointF(440, y + 205),
			Gdiplus::PointF(455, y + 220),
			Gdiplus::PointF(440, y + 235),
			Gdiplus::PointF(425, y + 220)
};

Gdiplus::PointF romb3[4] = {
			Gdiplus::PointF(440, y + 255),
			Gdiplus::PointF(455, y + 270),
			Gdiplus::PointF(440, y + 285),
			Gdiplus::PointF(425, y + 270)
};

//огонь
Gdiplus::PointF fire1l[3] = {
				Gdiplus::PointF(335, y + 520),
				Gdiplus::PointF(395, y + 520),
				Gdiplus::PointF(365, y + 570)
};

Gdiplus::PointF fire2l[3] = {
				Gdiplus::PointF(340, y + 520),
				Gdiplus::PointF(390, y + 520),
				Gdiplus::PointF(365, y + 560)
};

Gdiplus::PointF fire1r[3] = {
					Gdiplus::PointF(485, y + 520),
					Gdiplus::PointF(545, y + 520),
					Gdiplus::PointF(515, y + 570)
};

Gdiplus::PointF fire2r[3] = {
					Gdiplus::PointF(490, y + 520),
					Gdiplus::PointF(540, y + 520),
					Gdiplus::PointF(515, y + 560)
};

int rx = 0, ry = 0;

Gdiplus::PointF pnt1[1] = {
	Gdiplus::PointF(rx + 350.f, ry + 329.f),
};

Gdiplus::PointF pnt2[1] = {
	Gdiplus::PointF(480.f, y + 520.f),
};

void  Display(HDC  hdc)
{
	// создаем объект класса Graphics для рисования
	Gdiplus::Graphics graph(hdc);

	// определяем размер области рисования
	Gdiplus::Rect rect(0, 0, 1300, 800);
	graph.GetVisibleClipBounds(&rect);

	Gdiplus::Bitmap backbuffer(rect.Width, rect.Height, &graph);
	//создаем объект класса Grapchics для рисования в буфер
	Gdiplus::Graphics g(&backbuffer);

	g.Clear(Gdiplus::Color::White); // выполняем очистку перед рисованием
	g.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);

	// создаем сплошную кисть
	Gdiplus::SolidBrush sBr1(Gdiplus::Color::Black); // сплошная кисть
	Gdiplus::SolidBrush sBr2(Gdiplus::Color(160, 160, 160)); // сплошная кисть (серый)
	Gdiplus::SolidBrush sBr3(Gdiplus::Color(116, 101, 202)); // сплошная кисть (синий)
	Gdiplus::SolidBrush sBr4(Gdiplus::Color(66, 151, 255)); // сплошная кисть (голубой)
	Gdiplus::SolidBrush sBr5(Gdiplus::Color(90, 66, 151, 255)); // сплошная кисть (прозрачность)
	Gdiplus::SolidBrush sBr6(Gdiplus::Color::Red);
	Gdiplus::SolidBrush sBr7(Gdiplus::Color::Yellow);

	Gdiplus::SolidBrush background(Gdiplus::Color::LightBlue);
	

	// создаем перо
	Gdiplus::Pen blackPen(Gdiplus::Color::Black);
	Gdiplus::Pen pen(Gdiplus::Color::Black, 5.f);

	Gdiplus::Pen pen1(Gdiplus::Color(255, 108, 108, 108), 5.f);
	//составное перо
	Gdiplus::Pen pen2(Gdiplus::Color::Black, 3.f);
	float dash[2] = { 0.3f, 2.6f };
	pen2.SetDashPattern(dash, 2);

	 
	{
		Gdiplus::Matrix mtrx;
		Gdiplus::Matrix mtrx1;
		Gdiplus::Matrix mtrx2;

		int Timing_0 = -1,
			Timing_1 = 50,
			Timing_11 = 52,
			Timing_3 = 53,
			Timing_2 = 58,
			Timing_4 = 70;// продолжительность анимации

		int Timing_1_2 = 18;
		int Timing_1_1 = 350;

		

		if (Time < Timing_1) // двигаемся вверх
		{
			mtrx.Translate(0, -5);
			
			mtrx.TransformPoints(hat, 3);
			mtrx.TransformPoints(top, 8);
			mtrx.TransformPoints(Hfire1, 3);
			mtrx.TransformPoints(Hfire2, 3);
			mtrx.TransformPoints(bot, 8);
			mtrx.TransformPoints(botr, 3);
			mtrx.TransformPoints(botl, 3);
			mtrx.TransformPoints(romb1, 4);
			mtrx.TransformPoints(romb2, 4);
			mtrx.TransformPoints(romb3, 4);
			mtrx.TransformPoints(fire1l, 3);
			mtrx.TransformPoints(fire2l, 3);
			mtrx.TransformPoints(fire1r, 3);
			mtrx.TransformPoints(fire2r, 3);

		}

		if (Time > Timing_3)
		{
			mtrx.Translate(0, 10);
			mtrx.TransformPoints(bot, 8);
		}

		if (Time > Timing_3)
		{
			mtrx.Translate(10, 0);
			mtrx.TransformPoints(botr, 3);
		}

		if (Time > Timing_3)
		{
			mtrx.Translate(-20, 0);
			mtrx.TransformPoints(botl, 3);
		}

		if (Time > Timing_1 && Time < Timing_11)
		{
			mtrx1.Translate(0, 1000);
			mtrx1.TransformPoints(fire1l, 3);
			mtrx1.TransformPoints(fire2l, 3);
			mtrx1.TransformPoints(fire1r, 3);
			mtrx1.TransformPoints(fire2r, 3);

		}

		if (Time > Timing_4)
		{
			mtrx2.Translate(0, -5);
			mtrx2.TransformPoints(hat, 3);
			mtrx2.TransformPoints(top, 8);
			mtrx2.TransformPoints(romb1, 4);
			mtrx2.TransformPoints(romb2, 4);
			mtrx2.TransformPoints(romb3, 4);
			mtrx2.TransformPoints(Hfire1, 3);
			mtrx2.TransformPoints(Hfire2, 3);

		}



	/*	if (Time > Timing_3 && Time < Timing_2)
		{
				mtrx.RotateAt(-10, pnt1[1]);
				mtrx.TransformPoints(botl, 3);
				mtrx.Rotate(0);
				mtrx.TransformPoints(botr, 3);	
		}

		if (Time > Timing_2)
		{
			mtrx.Translate(-5, 5);
			mtrx.TransformPoints(botl, 3);
		} */

	
		g.FillRectangle(&background, 0, 0, 1300, 800);

		g.FillPolygon(&sBr2, hat, 3);
		g.DrawPolygon(&blackPen, hat, 3);

		g.FillPolygon(&sBr2, top, 8);
		g.FillPolygon(&sBr3, top, 5);
		g.DrawPolygon(&blackPen, top, 8);

		g.FillPolygon(&sBr6, Hfire1, 3);
		g.DrawPolygon(&blackPen, Hfire1, 3);

		g.FillPolygon(&sBr7, Hfire2, 3);
		g.DrawPolygon(&blackPen, Hfire2, 3);

		g.FillPolygon(&sBr3, bot, 8);
		g.DrawPolygon(&blackPen, bot, 8);

		g.FillPolygon(&sBr3, botl, 3);
		g.DrawPolygon(&blackPen, botl, 3);

		g.FillPolygon(&sBr3, botr, 3);
		g.DrawPolygon(&blackPen, botr, 3);

		g.FillPolygon(&sBr4, romb1, 4);
		g.DrawPolygon(&pen1, romb1, 4);
		g.DrawPolygon(&pen2, romb1, 4);

		g.FillPolygon(&sBr4, romb2, 4);
		g.DrawPolygon(&pen1, romb2, 4);
		g.DrawPolygon(&pen2, romb2, 4);

		g.FillPolygon(&sBr4, romb3, 4);
		g.DrawPolygon(&pen1, romb3, 4);
		g.DrawPolygon(&pen2, romb3, 4);

		g.FillPolygon(&sBr6, fire1l, 3);
		g.DrawPolygon(&blackPen, fire1l, 3);

		g.FillPolygon(&sBr7, fire2l, 3);
		g.DrawPolygon(&blackPen, fire2l, 3);

		g.FillPolygon(&sBr6, fire1r, 3);
		g.DrawPolygon(&blackPen, fire1r, 3);

		g.FillPolygon(&sBr7, fire2r, 3);
		g.DrawPolygon(&blackPen, fire2r, 3);

	}

	g.DrawImage(image, 700, 10, 480, 360);
	graph.DrawImage(&backbuffer, rect); // выводим на экран готовое изображение из буфера								
}  //  Display


//вставка изображения в программе 

Gdiplus::PointF Tween(const Gdiplus::PointF& A, const Gdiplus::PointF& B, float t) // Функция нахождения промежуточных точек
{
	return Gdiplus::PointF(A.X * (1.f - t) + B.X * t, A.Y * (1.f - t) + B.Y * t);
}
