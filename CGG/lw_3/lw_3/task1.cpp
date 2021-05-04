#include <Windows.h>
#include <WindowsX.h>
#include <tchar.h>
#include <strsafe.h>
#include  <Shlobj.h>
#include <map>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;
LRESULT CALLBACK MyWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void Display(Graphics& g, float t);

//Для анимации
void ShiftLeft(PointF points, int n);
Gdiplus::PointF Tween(const Gdiplus::PointF& A, const Gdiplus::PointF& B, float t);


MSG  msg;
HWND hWnd = NULL;
//Gif-изображение
Image* gif;
UINT frameCount = 0;
UINT frameIndex = 0; // индекс активного кадра 4 UINT frameCount; // количество кадров

void ShiftLeft(PointF points,int n)
{
	Gdiplus::Matrix mtrx;
	mtrx.Translate(100, 0);
	mtrx.TransformPoints(&points, n);
}

void SetTransform(Graphics& g, float time)
{
	float Timing_0 = -1.f,
		Timing_1 = 1.f,
		Timing_2 = 2.f,
		Timing_3 = 4.f;
		//Timing_4 = 130.f,
		//Timing_5 = 134.f,
		//Timing_6 = 137.f,
		//Timing_7 = 143.f,
		//Timing_8 = 156.f,
		//Timing_9 = 200.f; 

	//int Timing_1_1 = 350;

	float m[6];
	Gdiplus::Matrix T[3];


	//умножение текущей матрицы на матрицу переноса
	T[0].Translate(400.f, 220.f);
	T[1].Translate(350.f, 220.f);
	
	//T[2].Translate(300.f, 220.f);
	//T[3].Translate(200.f, -50.f);
	//T[4].Translate(0.f, -50.f);

	//умножение текущей матрицы на матрицу поворота вокруг заданной точки
	//T[1].RotateAt(-10.f, PointF{ 470.f, 450.f });
	//T[2].RotateAt(10.f, PointF{ 400.f, 200.f });


	float a[6], b[6];
	if (Timing_1 < time < Timing_2) // первый этап анимации
	{
		T[0].Translate(200.f, 50.f); 

		T[1].RotateAt(-40.f, PointF{ 200.f, 50.f });
	

		//получение элементов матрицы
		T[0].GetElements(a);//элементы из матрицы T будут записаны в a
		T[1].GetElements(b);//элементы из матрицы T будут записаны в b
	}
	
	if (Timing_2 < time < Timing_3) // первый этап анимации
	{

		T[0].Translate(200.f, 0.f);
		T[1].RotateAt(50.f, PointF{ 200.f, 0.f });

		T[1].GetElements(a);
		T[2].GetElements(b);
		//time -= 1.f;
	}
	
	else
	{
		return;
	}

	for (int i = 0; i < _countof(m); ++i)
	{
		m[i] = a[i] * (1.f - time) + b[i] * time;//формула твиннига
	}

	Matrix matrix;
	matrix.SetElements(m[0], m[1], m[2], m[3], m[4], m[5]);
	g.SetTransform(&matrix);

}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR lpszCmdLine, int nCmdShow)
{

	//-------------------------------------------создание оконного класса-------------------------------------------
	WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = MyWindowProc;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = TEXT("Lab1");
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (0 == RegisterClassEx(&wcex))
	{
		return -1;
	}

	ULONG_PTR           gdiplusToken;
	GdiplusStartupInput gdiplusStartupInput;

	// инициализация GDI+
	Status stRet = GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	if (Ok == stRet)
	{
		textura = Image(L"texture2.jpg").GetThumbnailImage(320, 240);
		gif = Image::FromFile(L"gif.gif");
		hWnd = CreateWindowEx(0, TEXT("Lab1"), TEXT("Lab3"), WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
		ShowWindow(hWnd, nCmdShow);

		/* цикл обработки оконных сообщений */

		BOOL bRet;
		for (;;)
		{
			bRet = GetMessage(&msg, NULL, 0, 0);
			if (bRet == -1)
			{
			}
			else if (FALSE == bRet)
			{
				break; // получено WM_QUIT, выход из цикла
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		//-------------------------------------------цикл сообщений-------------------------------------------	
		delete textura;
		GdiplusShutdown(gdiplusToken); // завершение работы GDI+
	} // if
	return (int)msg.wParam;
}

LRESULT CALLBACK MyWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	
	static Bitmap* bitmap = NULL; //для катера
	static float t = 0.f;

	switch (uMsg)
	{

	case WM_CREATE:
					{
						// определение количества кадров в изображении
						frameCount = gif->GetFrameCount(&FrameDimensionTime);
						if (NULL == gif) 
						return -1; // загрузка не удалась
						SetTimer(hWnd, 0, 100, NULL); //Установка таймера для анимации
						return 0;
					}
	case WM_DESTROY:
					{
						if (bitmap != NULL)
						{
							delete bitmap;
						}
						if (NULL != gif) 
							delete gif; // удаляем объект
						PostQuitMessage(0);
						return 0;
					}
	case WM_ERASEBKGND:
					//подавление события чтобы не было мерцания
					return 1;
	case WM_TIMER:
					{
						// увеличиваем индекс кадра (циклически)
						frameIndex = (frameIndex + 1) % frameCount;
						// делаем кадр активным
						gif->SelectActiveFrame(&FrameDimensionTime, frameIndex);

						// требуем обновления клиентской области окна (перерисовки)
						InvalidateRect(hWnd, NULL, FALSE);
						t += 0.01f;
						if (2.f < t) t = 0.f;

						if (bitmap != NULL)
						{
							{
								Graphics g(bitmap);
								Display(g, t);
							}
							Graphics g(hWnd);
							g.DrawImage(bitmap, 0, 0);
						}
					return 0;
					}
	case WM_SIZE:
				{
				if (wParam != SIZE_MINIMIZED)
						{
							if (bitmap != NULL)
							{
								delete bitmap;
							}
							bitmap = new Bitmap{ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
						}
						return 0;
				}	
	case WM_PAINT:
				{
					PAINTSTRUCT ps;
					// начинаем процесс рисования
					HDC hdc = BeginPaint(hWnd, &ps);
					if (bitmap != NULL)
					{
						{
							Graphics g(bitmap);
							Display(g, t);
						}

						Graphics g(hdc);
						g.DrawImage(bitmap, 0, 0);
					}
					// завершаем процесс рисования
					EndPaint(hWnd, &ps);
				}
				return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

Gdiplus::PointF Tween(const Gdiplus::PointF& A, const Gdiplus::PointF& B, float t) 
{
	return Gdiplus::PointF(A.X * (1.f - t) + B.X * t, A.Y * (1.f - t) + B.Y * t);
}

void Display(Graphics &g, float time)
{

	g.SetSmoothingMode(SmoothingModeHighQuality);
	// выполняем очистку перед рисованием
	g.Clear(Color::CornflowerBlue);

	g.DrawImage(gif, 0, 5); // отображение gif-анимации и активного кадра
	g.DrawImage(gif, 500, 5); // отображение gif-анимации и активного кадра
	g.DrawImage(gif, 1000, 5); // отображение gif-анимации и активного кадра


	SolidBrush blackBrush(Color::Black);

	Font font1(L"Times New Roman", 14.f, FontStyleBold);
	Font font2(L"Arial", 80.f, FontStyleBold);
	g.DrawString(L"Лаб №3. Вариант №10 - Катер", -1, &font1, PointF(10.f, 550.f), &blackBrush);


	SetTransform(g, time); //анимация??

	Rect rect(0, 0, 600, 600); //Многоугольник для градиента
//Кисти
	Pen kater_border(Color::Blue, 10.f);//Кисти для заполнения цветом
	SolidBrush brushYellow(Color::Yellow);//Твердая кисть
	HatchBrush hatchBrush(HatchStyleForwardDiagonal, Color::Aquamarine, Color::Bisque);//Штриховая кисть
	LinearGradientBrush linBrush(rect, Color::Indigo, Color::Goldenrod, 40.f); //кисть с линейным градиентом

#pragma region Part of kater
	//Части катера
	Rect kater_part[3] =
	{
		Rect(250,200,460,200),//тело катера
		Rect(710,290,80,90),//мотор катера
		Rect(318,130,160,70),//стул или крыша??
	};

	//Точки для многоугольника
	Point kater_nose[3] =
	{
		Point(40,200), Point(250,200), Point(250,400),
	};

	//Gdiplus::Matrix mtrx;
	//mtrx.Translate(0, -5);
	//mtrx.TransformPoints(kater_nose, 3);
	Point kater_glass[4] =
	{
		Point(170,200), Point(330,77),	Point(480,77), Point(520,200)
	};
	Point kater_handline[4] =
	{
		Point(507,140),
		Point(585,150),
		Point(661,160),
		Point(709,192),
	};

	float border_part[6] =
	{
		0.0f,0.2f, //от 0 до 20% толщина линии
		0.3f, 0.7f,
		0.8f, 1.0f
	};

	

#pragma endregion
	kater_border.SetCompoundArray(border_part, 6); //составное перо

	Color gradient_color[3] =
	{
		Color(255,255,0,0),//red
		Color(255,0,0,255),//blue
		Color(255,0,255,0)//green
	};
	//Точки для изменения цвета
	float pos[4] = { 0.0f, 0.3f, 0.6f, 1.0f };
	//Задаем значения факторов наложения. Т.е. процент от конечного числа линейного градиента
	float factors[4] = { 0.0f, 0.2f, 0.8f, 1.0f };

	//Установка линейного градиента с неоднородным изменением цвета и гаммокоррецией
	linBrush.SetBlend(factors, pos, 4);
	linBrush.SetGammaCorrection(TRUE);

	//Рисование катера
	g.SetSmoothingMode(SmoothingModeHighQuality);
	g.FillRectangle(&linBrush, kater_part[0]);		//корпус
	g.FillRectangle(&hatchBrush, kater_part[1]);	//мотор

	g.DrawRectangles(&kater_border, kater_part, 3);	//нарисованные контуры элементов катера
	g.FillPolygon(&linBrush, kater_nose, 3);			//нос закршенный
	g.DrawPolygon(&kater_border, kater_nose, 3);	//нос контур

	g.FillRectangle(&brushYellow, kater_part[2]);	//кресла
	g.DrawPolygon(&kater_border, kater_glass, 4);	//стекло над креслами

	//Нарисуем ручку
	g.FillClosedCurve(&brushYellow, kater_handline, 4);
	g.DrawClosedCurve(&kater_border, kater_handline, 4);

} // Display

