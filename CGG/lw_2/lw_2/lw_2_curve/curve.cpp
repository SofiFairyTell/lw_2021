#include <Windows.h>
#include <WindowsX.h>
#include <CommCtrl.h>
#include <tchar.h>
#include <fstream>
#include <string>
#include <gdiplus.h>
#include <gdiplusgraphics.h>
#include <vector>
#define  PI 3.1416f 
#include <cmath>
#pragma comment(lib, "GdiPlus.lib")
using namespace Gdiplus;
#pragma comment(linker,"\"/manifestdependency:type                  = 'win32' \
                                              name                  = 'Microsoft.Windows.Common-Controls' \
                                              version               = '6.0.0.0' \
                                              processorArchitecture = '*' \
                                              publicKeyToken        = '6595b64144ccf1df' \
                                              language              = '*'\"")
#pragma warning(disable : 4996) //отключает Ошибку deprecate. Возникает, когда используется устаревшая функция 

//Объявления

HWND hwnd = NULL; //дескриптор окна
void Display(HDC hdc); //функция для показа катера на экране
void DrawImg(HDC hdc); //загрузка изображения на экран
void PlotGrid(HWND hwnd, HDC hdc);
int  V_LBclip(float *x0, float *y0, float *x1, float *y1);
static int  LB_tclip(float p, float q);
Image* img;
/*Для изменения цвета окна, когда было обработано WM_SYSCHAR */
RECT rc;
HBRUSH brushes[3]; //кисти для изменения цвета окна
int brush_index = 0;


/*Оконные процедуры*/
LRESULT CALLBACK MainWindowProcess(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/*Обработчики WM_CREATE, WM_DESTROY, WM_SIZE*/

BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void OnDestroy(HWND hwnd);
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);

class WorldWindow
{
	public:
		float Left;
		float Right;
		float Top;
		float Bottom;

		inline WorldWindow(float left, float top, float right, float bottom)
			:Left(left), Top(top), Right(right),Bottom(bottom){}
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
	inline Viewport(int left, int top, int right, int bottom):Rect(left,top,right-left,bottom-top){}
	inline Viewport(const RECT &rect):Rect(rect.left,rect.top, rect.right-rect.left, rect.bottom-rect.top){}
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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int  CmdShow)
{
	brushes[0] = (HBRUSH)CreateSolidBrush(RGB(0, 0, 100)); //Радикально-синий цвет
	brushes[1] = (HBRUSH)CreateSolidBrush(RGB(0, 100, 0)); //Радикально-зеленый цвет
	brushes[2] = (HBRUSH)CreateSolidBrush(RGB(100, 0, 0)); //Радикально-красный цвет

	// регистрируем оконный класс главного окна...
	WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = MainWindowProcess; // оконная процедура
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);

	wcex.lpszClassName = TEXT("MainWindowProcess"); // имя класса
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	//wcex.hbrBackground = brushes[brush_index];

	if (0 == RegisterClassEx(&wcex))
	{
		return -1;
	}
	/*---------------------------------------------*/

	LoadLibrary(TEXT("ComCtl32.dll"));
	//загрузка изображения

	/*Инициализаци GDI+*/
	ULONG_PTR gdToken;
	GdiplusStartupInput gdInput;

	LSTATUS retRes = GdiplusStartup(&gdToken, &gdInput, NULL);	/*Создание главного файла и обработка ошибки */
	hwnd = CreateWindowEx(0, TEXT("MainWindowProcess"), TEXT("Curve"),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, 900, 600, NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		return -1;
	}
	/*--------------------------------------------------*/

	//img = Image::FromFile(L"C:\\Users\\it\\Downloads\\CGG\\lw_1\\KATER1.png");
	ShowWindow(hwnd, CmdShow); // отображаем главное окно

	/*Цикл обработки сообщений*/
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
	HDC hdc;             // индекс контекста устройства
	PAINTSTRUCT ps;      // структура для рисования


	switch (msg)
	{
		HANDLE_MSG(hwnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hwnd, WM_DESTROY, OnDestroy);
		//HANDLE_MSG(hwnd, WM_COMMAND, OnCommand)
	case WM_PAINT:
	{
		PAINTSTRUCT pstruct;
		HDC hdc = BeginPaint(hwnd, &pstruct);
		PlotGrid(hwnd, hdc);
		Display(hdc);

		EndPaint(hwnd, &ps);
	}break;
	case WM_LBUTTONDOWN:
	{
		DWORD xPos = NULL, yPos = NULL, nSize = NULL;
		TCHAR szBuf[80];

		hdc = GetDC(hwnd);
		// Сохраняем координаты курсора мыши
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
	PostQuitMessage(0); // отправляем сообщение WM_QUIT
}

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
	_asm
	{
		fld angle;
		fcos;
	}
}

void Display(HDC hdc)
{
	Graphics g(hdc);
	g.Clear(Color::FloralWhite);
	PlotGrid(hwnd, hdc);//координатная сетка
	//сглаживание
	g.SetSmoothingMode(SmoothingModeHighQuality);
	Rect rect(307, 168, 387, 224);
	
	Viewport vp(0.0f,0.0f, 980.0f, 840.0f);
	WorldWindow w(-15.0f,15.0f,35.0f,-35.0f);
	//Из мирового окна в окно просмотра
	float A =  (float)vp.Width/(w.Right - w.Left) ;
	float B =  (float)vp.Height/(w.Bottom - w.Top);
	float C = vp.X - A * w.Left ;
	float D = vp.Y - B * w.Top;

	int m = 6*PI/0.05f;//376,8 = 377 точек
	
	
	PointF dots[377];
	PointF points[377];
	PointF view[377];
	float t = 0.00f;
 	for (int i = 0; i < m; i++)
	{
			float X = -2.0f * Cos(t) + 3.0f* Cos(-2.0f / 3.0f * t);
			float Y = -2.0f * Sin(t) - 3.0f * Sin(-2.0f / 3.0f * t);
			dots[i].X = A*X+C;
			dots[i].Y = B*Y+D;	
			points[i].X = X;
			points[i].Y = Y;
			t += 0.05f;
	}
	//должна быть Улитка Паскаля, даже две..
	//Кисти для заполнения цветом
	Pen curvePen(Color::OrangeRed, 0.5f);
	g.DrawCurve(&curvePen, dots, m);
	int j = 0;
	float x, y, x0, y0;
	for (int i = 0; i < m-1; i++)
	{
		x = points[i].X;
		y = points[i].Y;
		x0 = points[i + 1].X;
		y0 = points[i + 1].Y;

		if (V_LBclip(&points[i].X, &points[i].Y, &points[i + 1].X, &points[i + 1].Y) == 1)
		{
				view[i].X = A * points[i].X + C;
				view[i].Y = B * points[i].Y + D;
				//view[i+1].X = A * points[i+1].X + C;
				//view[i+1].Y = B * points[i+1].Y + D;
		}
		

	}
	for (int i = 0; i < m; i++)
	{
		
	}
	Pen curvePen2(Color::Black, 1.5f);
	Pen curvePen3(Color::YellowGreen, 1.5f);
	g.DrawRectangle(&curvePen2, rect);
	g.DrawCurve(&curvePen2, view,m);
}
void PlotGrid(HWND hwnd, HDC hdc) {
	
	RECT rect;
	PAINTSTRUCT ps;
	GetClientRect(hwnd, &rect);

	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	HPEN hOldPen = SelectPen(hdc, hPen);
	int i, x, y;
	int Nx = 20, Ny = 20; //Количество координатных линий по x и y

	//  Шаги приращений координатных линий по x и y
	int StepX = (int)(rect.right - rect.left) / Nx;
	int StepY = (int)(rect.bottom - rect.top) / Ny;

	//Проверяем, чтобы шаги приращений по x и y были ненулевыми
	if (StepX < 1) StepX = 1;
	if (StepY < 1) StepY = 1;
	
	//Закрашиваем фон
	FillRect(hdc, &ps.rcPaint, brushes[1]);
	//Рисуем оси 


	//Рисуем координатную сетку
	for (x = rect.left; x <= rect.right; x += StepX)
	{
		MoveToEx(hdc, x, rect.top, NULL);
		LineTo(hdc, x, rect.bottom);
	}

	for (y = rect.top; y <= rect.bottom; y += StepY)
	{
		MoveToEx(hdc, rect.left, y, NULL);
		LineTo(hdc, rect.right, y);
	}
}

/*--------------------------------------------------- 
 * V_LBclip
 *  Реализует алгоритм отсечения Лианга-Барски
 *  с параметрическим заданием линий
 *
 * int  V_LBclip (float *x0, float *y0, float *x1, float *y1)
 *
 * Отсекает отрезок, заданный значениями координат его
 * точек (x0,y0), (x1,y1), по окну отсечения, заданному
 * глобальными скалярами Wxlef, Wybot, Wxrig, Wytop
 *
 * Возвращает:
 *  0 - отрезок не видим
 *  1 - отрезок видим
 */

static float LB_t0, LB_t1;

static int  LB_tclip(float p, float q)
{
	int   accept;
	float r;
	EqualMethod Equal = EqualMethod();
	accept = 1;                           /* Отрезок принят */
	if (Equal.Equal(p,0.0f) == 0) 
	{
		if (Equal.Less(q,0.0f)) accept = 0;             /* Отбрасывание */
	}
	else 
	{
		r = q / p;
		if (Equal.Less(p,0.0f)) 
		{
			if (Equal.Greater(r,LB_t1)) 
				accept = 0;      /* Отбрасывание */
			else 
				if (Equal.Greater(r,LB_t0)) 
					LB_t0 = r;
		}
		else 
		{
			if (Equal.Less(r,LB_t0)) 
				accept = 0;      /* Отбрасывание */
			else 
				if (Equal.Less(r, LB_t1))
				{
					LB_t1 = r;
				}
				
		}
	}
	return (accept);
}  /* LB_tclip */

int  V_LBclip(float *x0, float *y0, float *x1, float *y1)
{ 
	int   visible;
	float dx, dy;
	EqualMethod Equal = EqualMethod();
	//Wxlef, Wybot, Wxrig, Wytop
	WorldWindow w(-1.0f, 1.0f, 3.0f, -3.0f);

	
	visible = 0;
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
					if (Equal.Less(LB_t1,1.0f)) 
					{
						*x1 = *x0 + LB_t1 * dx;
						*y1 = *y0 + LB_t1 * dy;
					}
					if (Equal.Greater(LB_t0,0.0f))
					{
						*x0 = *x0 + LB_t0 * dx;
						*y0 = *y0 + LB_t0 * dy;
					}
					++visible;
				}
			}
		}
}
return (visible);
}  /* V_LBclip */