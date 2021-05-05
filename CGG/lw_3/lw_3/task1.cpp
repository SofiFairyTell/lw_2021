#include <Windows.h>
#include <WindowsX.h>
#include <tchar.h>
#include <strsafe.h>
#include  <Shlobj.h>
#include <map>
#include <gdiplus.h>
#include <vector>
#define  PI 3.1416f 
#include <cmath>

#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;
LRESULT CALLBACK MyWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void Display(Graphics& g, int t);
void DrawWave(Graphics& g);
//Для анимации

Gdiplus::PointF Tween(const Gdiplus::PointF& A, const Gdiplus::PointF& B, float t);

int t; //время
MSG  msg;
HWND hWnd = NULL;
//Gif-изображение
Image* gif;
UINT frameCount = 0;
UINT frameIndex = 0; // индекс активного кадра 4 UINT frameCount; // количество кадров

//Для того чтобы нарисовать волну
class WorldWindow
{
public:
	float Left;
	float Right;
	float Top;
	float Bottom;

	inline WorldWindow(float left, float top, float right, float bottom)
		:Left(left), Top(top), Right(right), Bottom(bottom) {}
	inline float Width() const
	{
		return (Right - Left);
	}
	inline float Height() const
	{
		return (Top - Bottom);
	}
};
class Viewport : public::Rect
{
public:
	inline Viewport(int left, int top, int right, int bottom) :Rect(left, top, right - left, bottom - top) {}
	inline Viewport(const RECT &rect) : Rect(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top) {}
	inline operator RECT() const
	{
		RECT rect = { X,Y, X + Width, Y + Height };
		return rect;
	}
};
class EqualMethod
{
public:

	bool EqualDot(PointF& first, PointF& second, float tolerance = 1e-6f)
	{
		if (abs(first.X - second.X) < tolerance && abs(first.Y - second.Y) < tolerance)
		{
			return true;
		}
		else
			return false;
	}
	inline bool GreaterOrEqual(float a, float b, float tolerance = -1e-3f)
	{
		return !(b - a) > tolerance;
	}
	inline bool Less(float a, float b, float tolerance = -1e-3f)
	{
		return (b - a) > tolerance;
	}
	inline bool Greater(float a, float b, float tolerance = -1e-3f)
	{
		return (a - b) > tolerance;
	}
	inline bool Equal(float a, float b, float tolerance = -1e-3f)
	{
		return (abs(a - b) < tolerance);
	}
	inline bool IsZero(float a, float tolerance)
	{
		return (abs(a) == tolerance);
	}


};



inline void WorldToViewPort(const WorldWindow &w, const Viewport &vp, PointF *points, int count);
inline void ViewPortToWorld(const WorldWindow &w, const Viewport &vp, PointF *points, int count);
bool  V_LBclip(const WorldWindow &w, float *x0, float *y0, float *x1, float *y1);//отсечение по алгоритму Лианга-Барски
static bool LB_tclip(float p, float q);//определение оставить отрезок или нет

// То что ниже надо собирать с x86
//Вычисление Sin и COS
inline float Sin(float angle)
{
	__asm
	{
		fld angle;
		fsin;
	}
}

inline float Cos(float angle)
{
	__asm
	{
		fld angle;
		fcos;
	}
}

inline void WorldToViewPort(const WorldWindow &w, const Viewport &vp, PointF *points, int count)
{
	//Из мирового окна в окно просмотра
	float A = (float)vp.Width / (w.Right - w.Left);
	float B = (float)vp.Height / (w.Bottom - w.Top);
	float C = vp.X - A * w.Left;
	float D = vp.Y - B * w.Top;

	for (unsigned int i = 0; i < count; ++i)
	{
		points[i].X = A * points[i].X + C;
		points[i].Y = B * points[i].Y + D;
	}
}

inline void ViewPortToWorld(const WorldWindow &w, const Viewport &vp, PointF *points, int count)
{
	//Из мирового окна в окно просмотра
	float A = (w.Right - w.Left) / (float)vp.Width;
	float B = (w.Bottom - w.Top) / (float)vp.Height;
	float C = w.Left - A * vp.X;
	float D = w.Top - B * vp.Y;
	for (unsigned int i = 0; i < count; ++i)
	{
		points[i].X = A * points[i].X + C;
		points[i].Y = B * points[i].Y + D;
	}

}

void CalculateDots(std::vector<PointF> &dots, int m)
{
	float t = 0.00f;
	for (int i = 0; i < m; i++)
	{
		float X = t;
		float Y = -2.0f * Cos(t) + 3.0f* Cos(-2.0f / 3.0f * t);;

		dots[i].X += X;
		dots[i].Y += Y;
		t += 0.05f;
	}
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
		
		GdiplusShutdown(gdiplusToken); // завершение работы GDI+
	} // if
	return (int)msg.wParam;
}

LRESULT CALLBACK MyWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	
	static Bitmap* bitmap = NULL; //для катера
	//static float t = 0.f;

	switch (uMsg)
	{

	case WM_CREATE:
					{
						// определение количества кадров в изображении
						frameCount = gif->GetFrameCount(&FrameDimensionTime);
						if (NULL == gif) 
						return -1; // загрузка не удалась
						SetTimer(hWnd, 0, 40, NULL); //Установка таймера для анимации
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
						t++;
						//if (2.f < t) t = 0.f;

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

void DrawWave(Graphics& g)
{
	//Координаты окон для основной фигуры
	Viewport vp(-1200.0f, 350.0f, 1200.0f, 440.0f);
	WorldWindow w(-20.75f, 20.75f, 20.75f, -20.75f);

	//Кисти
	Pen curve_limacon_clip(Color::Blue, 30.f);

	int m = (500 * PI / 0.05f) + 1; //376,8 = 377 точек

	std::vector<PointF> dots(m);
	CalculateDots(dots, m);
	Matrix mtrx;
	//Кисти для заполнения цветом
	for (int i = 0; i < m - 1; i++)
	{
		PointF view[2] = { dots[i],dots[i + 1] };
		if (V_LBclip(w, &view[0].X, &view[0].Y, &view[1].X, &view[1].Y) == 1)
		{
			WorldToViewPort(w, vp, view, 2);
			g.DrawCurve(&curve_limacon_clip, view, 2);
			SolidBrush gr(Color::Blue);
			g.FillClosedCurve(&gr,view,2);
			//if (t > 25 && t < 38)
			//{
			//	mtrx.Translate(0.f, 20.f);
			//	mtrx.TransformPoints(view, 2);
			//}

		}

	}


}
Gdiplus::PointF Tween(const Gdiplus::PointF& A, const Gdiplus::PointF& B, float t) 
{
	return Gdiplus::PointF(A.X * (1.f - t) + B.X * t, A.Y * (1.f - t) + B.Y * t);
}

void Display(Graphics &g, int time)
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

	Rect rect(0, 0, 600, 600); //Многоугольник для градиента
//Кисти
	Pen kater_border(Color::Blue, 10.f);//Кисти для заполнения цветом
	SolidBrush brushYellow(Color::Yellow);//Твердая кисть
	HatchBrush hatchBrush(HatchStyleForwardDiagonal, Color::Aquamarine, Color::Bisque);//Штриховая кисть
	LinearGradientBrush linBrush(rect, Color::Indigo, Color::Goldenrod, 40.f); //кисть с линейным градиентом


	//Время ключевых кадров
	int Timing_0 = -1,
		Timing_1 = 12,
		Timing_2 = 25,
		Timing_3 = 38,
		Timing_4 = 50,
		Timing_5 = 63,
		Timing_6 = 75,
		Timing_7 = 88,
		Timing_8 = 100,
		Timing_9 = 200;
	int Timing_1_1 = 350;

#pragma region Part of kater
	//Части катера
	PointF kater_body[4] =
	{
		PointF(250.f,400.f),
		PointF(250.f,200.f),	
		PointF(710.f,200.f),
		PointF(710.f,400.f),
	};

	PointF kater_motor[4] = 
	{
		PointF(710.f,380.f),
		PointF(710.f,290.f),
		PointF(790.f,290.f),
		PointF(790.f,380.f),
	};
	
	PointF kater_top[4] =
	{
		PointF(318.f,200.f),
		PointF(318.f,130.f),
		PointF(478.f,130.f),
		PointF(478.f,200.f),
	};
	//Точки для многоугольника
	PointF kater_nose[3] =
	{
		PointF(40.f,200.f), 
		PointF(250.f,200.f), 
		PointF(250.f,400.f)
	};

	PointF kater_glass[4] =
	{
		PointF(170.f,200.f), 
		PointF(330.f,77.f),
		PointF(480.f,77.f), 
		PointF(520.f,200.f)
	};
	PointF  kater_handline[4] =
	{
		PointF(507.f,140.f),
		PointF(585.f,150.f),
		PointF(661.f,160.f),
		PointF(709.f,192.f),
	};

	float border_part[6] =
	{
		0.0f,0.2f, //от 0 до 20% толщина линии
		0.3f, 0.7f,
		0.8f, 1.0f
	};
#pragma endregion
	Gdiplus::PointF pnt[1] = {
	Gdiplus::PointF(545.f, 407.f),
	};

	Gdiplus::PointF pnt1[1] = {
		Gdiplus::PointF(393.f, 492.f),
	};

	Gdiplus::PointF pnt2[1] = {
		Gdiplus::PointF(287.f, 492.f),
	};

	Gdiplus::PointF pnt3[1] = {
		Gdiplus::PointF(439.f, 407.f),
	};


	Gdiplus::Matrix mtrx;
	if (time > Timing_0 && time < Timing_1)
	{	
		mtrx.Translate(220, 20);

		mtrx.TransformPoints(kater_body, 4);
		mtrx.TransformPoints(kater_motor, 4);
		mtrx.TransformPoints(kater_top, 4);
		mtrx.TransformPoints(kater_nose, 3);
		mtrx.TransformPoints(kater_glass, 4);
		mtrx.TransformPoints(kater_handline, 4);
	}
	if (time > Timing_1 && time < Timing_2) // �������� ����
	{
		mtrx.Translate(-20, -20);
		mtrx.RotateAt(-4, pnt[0]);

		mtrx.TransformPoints(kater_body, 4);
		mtrx.TransformPoints(kater_motor, 4);
		mtrx.TransformPoints(kater_top, 4);
		mtrx.TransformPoints(kater_nose, 3);
		mtrx.TransformPoints(kater_glass, 4);
		mtrx.TransformPoints(kater_handline, 4);
	}
	if (time > Timing_2 &&time < Timing_4)
	{
		DrawWave(g);

		mtrx.RotateAt(4, pnt1[0]);

		mtrx.TransformPoints(kater_body, 4);
		mtrx.TransformPoints(kater_motor, 4);
		mtrx.TransformPoints(kater_top, 4);
		mtrx.TransformPoints(kater_nose, 3);
		mtrx.TransformPoints(kater_glass, 4);
		mtrx.TransformPoints(kater_handline, 4);

		
	}
	if (time > Timing_3 && time < Timing_4) 
	{
		//mtrx.RotateAt(3, pnt1[0]);
		mtrx.Translate(20, -20);

		mtrx.TransformPoints(kater_body, 4);
		mtrx.TransformPoints(kater_motor, 4);
		mtrx.TransformPoints(kater_top, 4);
		mtrx.TransformPoints(kater_nose, 3);
		mtrx.TransformPoints(kater_glass, 4);
		mtrx.TransformPoints(kater_handline, 4);
	}
	if (time > Timing_4 && time < Timing_5 )
	{
		DrawWave(g);
		mtrx.RotateAt(-4, pnt1[0]);

		mtrx.TransformPoints(kater_body, 4);
		mtrx.TransformPoints(kater_motor, 4);
		mtrx.TransformPoints(kater_top, 4);
		mtrx.TransformPoints(kater_nose, 3);
		mtrx.TransformPoints(kater_glass, 4);
		mtrx.TransformPoints(kater_handline, 4);
	}
	if (time > Timing_5 && time < Timing_6)
	{		
		DrawWave(g);

		mtrx.RotateAt(4, pnt1[0]);

		mtrx.TransformPoints(kater_body, 4);
		mtrx.TransformPoints(kater_motor, 4);
		mtrx.TransformPoints(kater_top, 4);
		mtrx.TransformPoints(kater_nose, 3);
		mtrx.TransformPoints(kater_glass, 4);
		mtrx.TransformPoints(kater_handline, 4);



	}

	if (time > Timing_6 && time < Timing_7)
	{
		mtrx.Translate(-250, 0);

		mtrx.TransformPoints(kater_body, 4);
		mtrx.TransformPoints(kater_motor, 4);
		mtrx.TransformPoints(kater_top, 4);
		mtrx.TransformPoints(kater_nose, 3);
		mtrx.TransformPoints(kater_glass, 4);
		mtrx.TransformPoints(kater_handline, 4);
	}


	if (time < Timing_1_1)
	{
		kater_body[0] = Tween(kater_body[0], kater_body[1], 0.01f);
		kater_body[1] = Tween(kater_body[1], kater_body[2], 0.01f);
		kater_body[2] = Tween(kater_body[2], kater_body[3], 0.01f);
		kater_body[3] = Tween(kater_body[3], kater_body[0], 0.01f);

		kater_nose[0] = Tween(kater_nose[0], kater_nose[1], 0.01f);
		kater_nose[1] = Tween(kater_nose[1], kater_nose[2], 0.01f);
		kater_nose[2] = Tween(kater_nose[2], kater_nose[0], 0.01f);

		kater_top[0] = Tween(kater_top[0], kater_top[1], 0.01f);
		kater_top[1] = Tween(kater_top[1], kater_top[2], 0.01f);
		kater_top[2] = Tween(kater_top[2], kater_top[3], 0.01f);
		kater_top[3] = Tween(kater_top[3], kater_top[0], 0.01f);
	}
	
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
	

	//нарисованные контуры элементов катера

	g.FillPolygon(&linBrush, kater_body,4);		//корпус
	g.FillPolygon(&hatchBrush, kater_motor,4);	//мотор
	g.FillPolygon(&brushYellow, kater_top,4);	//кресла
	g.FillPolygon(&linBrush, kater_nose, 3);	//нос

	g.DrawPolygon(&kater_border,kater_body,4);	//корпус
	g.DrawPolygon(&kater_border,kater_motor,4);	//мотор
	g.DrawPolygon(&kater_border,kater_top,4);	//кресла
	g.DrawPolygon(&kater_border, kater_nose, 3);//нос 
	
	g.DrawPolygon(&kater_border, kater_glass, 4);	//стекло над креслами

	//Нарисуем ручку
	g.FillClosedCurve(&brushYellow, kater_handline, 4);
	g.DrawClosedCurve(&kater_border, kater_handline, 4);

	DrawWave(g);
	




} // Display

static float LB_t0, LB_t1;

static bool  LB_tclip(float p, float q)
{
	bool accept;
	float r;
	EqualMethod Equal = EqualMethod();
	accept = true;                           /* Отрезок принят */
	if (Equal.Equal(p, 0.0f) == 0)
	{
		if (Equal.Less(q, 0.0f)) accept = false;   /* Отбрасывание */
	}
	else
	{
		r = q / p;
		if (Equal.Less(p, 0.0f))
		{
			if (Equal.Greater(r, LB_t1))
				accept = false;      /* Отбрасывание */
			else
				if (Equal.Greater(r, LB_t0))
					LB_t0 = r;
		}
		else
		{
			if (Equal.Less(r, LB_t0))
				accept = false;      /* Отбрасывание */
			else
				if (Equal.Less(r, LB_t1))
				{
					LB_t1 = r;
				}

		}
	}
	return (accept);
}  /* LB_tclip */

bool V_LBclip(const WorldWindow &w, float *x0, float *y0, float *x1, float *y1)
{
	//int   visible;
	bool visible;
	float dx, dy;
	EqualMethod Equal = EqualMethod();
	//Wxlef, Wybot, Wxrig, Wytop

	visible = false;
	LB_t0 = 0;  LB_t1 = 1;
	dx = *x1 - *x0;
	if (LB_tclip(-dx, *x0 - w.Left))
	{
		if (LB_tclip(dx, w.Right - *x0))
		{
			dy = *y1 - *y0;
			if (LB_tclip(-dy, *y0 - w.Bottom))
			{
				if (LB_tclip(dy, w.Top - *y0))
				{
					if (Equal.Less(LB_t1, 1.0f))
					{
						*x1 = *x0 + LB_t1 * dx;
						*y1 = *y0 + LB_t1 * dy;
					}
					if (Equal.Greater(LB_t0, 0.0f))
					{
						*x0 = *x0 + LB_t0 * dx;
						*y0 = *y0 + LB_t0 * dy;
					}
					visible = true;
				}
			}
		}
	}
	return (visible);
}  /* V_LBclip */