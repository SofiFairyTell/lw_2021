#include <Windows.h>
#include <WindowsX.h>
#include <CommCtrl.h>
#include <tchar.h>
#include <fstream>
#include <string>
#include <gdiplus.h>
#include <gdiplusgraphics.h>

/*
* Рисунок - КАТЕР
* Объекты - 
*	Кисти линейного градиента
*	Составные перья
*	Штриховые кисти
*Текст: название рисунка
*Допнительное: вывод растроового изображения рисунка
*/

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
void Display(HDC hdc);
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
	/*Инициализаци GDI+*/
	ULONG_PTR gdToken;
	GdiplusStartupInput gdInput;
	
	LSTATUS retRes = GdiplusStartup(&gdToken, &gdInput, NULL);
		
	/*Создание главного файла и обработка ошибки */
	hwnd = CreateWindowEx(0, TEXT("MainWindowProcess"), TEXT("Chat"),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, 900, 600, NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		return -1;
	}
	/*--------------------------------------------------*/

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
	
	void Display(HDC hdc)
	{
		Graphics g(hdc);
		g.Clear(Color::LightCyan);

		Rect rect(0,0,600,600); //Многоугольник для градиента
		
		//Части катера
		Rect kater_part[4] = 
		{
			Rect(250,200,360,200),//тело катера
			Rect(610,290,100,100),//мотор катера
			Rect(318,130,160,70),//стул или крыша??
			Rect(40,100,360, 300)//нос катера
		};

		//Точки для многоугольника
		Point kater_nose[3] =
		{
			Point(40,200),
			Point(250,200),
			Point(250,400),
		};

		Point kater_glass[4] =
		{
			Point(250,200),
			Point(330,77),
			Point(480,77),
			Point(520,200)
		};
		//Кисти для заполнения цветом
		Pen kater_border(Color::Blue);

		LinearGradientBrush linBrush(rect,Color::Indigo,Color::Goldenrod,40.f);
		
		Color gradient_color[3] =
		{
			Color(255,255,0,0),//red
			Color(255,0,0,255),//blue
			Color(255,0,255,0)//green
		};
		//Точки для изменения цвета
		float pos[4] = { 0.0f, 0.3f, 0.6f, 1.0f	};
		//Задаем значения факторов наложения. Т.е. процент от конечного числа линейного градиента
		float factors[4] = { 0.0f, 0.2f, 0.8f, 1.0f};
		//Установка линейного градиента с неоднородным изменением цвета и гаммнокоррецией
		linBrush.SetBlend(factors,pos,4);
		linBrush.SetGammaCorrection(TRUE);

		SolidBrush brush(Color::LightSkyBlue);
		SolidBrush brush2(Color::Yellow);

		//Рисование катера

		g.FillRectangle(&linBrush,kater_part[0]); //корпус
		g.FillPolygon(&linBrush,kater_nose,3);//nose
		g.DrawPolygon(&kater_border, kater_glass, 4);//стекло над креслами

		g.FillRectangle(&brush, kater_part[1]);
		g.FillRectangle(&brush2, kater_part[2]);

		g.DrawRectangles(&kater_border, kater_part,3);
		

		//g.GetVisibleClipBounds(&rect);
		
		//Bitmap buffer(rect.Width, rect.Height, &g);
		//Graphics temp(&buffer);


		//temp.Clear(Color::Aqua);
		//SolidBrush brush(Color::Black);
		//Pen penBrown(&brush,6.f);//Для рисования контура
		//
		////Для первого прямоугольника
		//Point pt1(10,10);
		//Point pt2(300,300);
		//temp.FillRectangle(&brush, 320, 330, 500, 70);
		//temp.DrawLine(&penBrown, pt1, pt2);
		
		//g.DrawImage(&buffer, rect);
	}

