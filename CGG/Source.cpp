#include <Windows.h>
#include <gdiplus.h>

#pragma comment(lib, "GdiPlus.lib")
//Forward declaration of the WndProc function
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
typedef void(*image)(HDC); //Pointer to image drawing function
HDC Hdc;
using namespace Gdiplus;
void draw(HDC hdc);
void Draw_Image(HDC hdc);
//Main entry point


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    //Window class name
    const wchar_t windowName[] = L"Window Class";

    //Initialize GDI+
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusTokens;
    GdiplusStartup(&gdiplusTokens, &gdiplusStartupInput, NULL);

    image image = Draw_Image;
   PAINTSTRUCT imagestr;
 
    //Set up window class
    WNDCLASS wnd;
    wnd.cbClsExtra = 0;
    wnd.cbWndExtra = 0;
    wnd.hCursor = LoadCursor(0, IDC_ARROW);
    wnd.hIcon = LoadIcon(0, IDI_WINLOGO);
    wnd.lpszMenuName = 0;
    wnd.style = 0;
    wnd.hbrBackground = 0;
    wnd.lpfnWndProc = WndProc;
    wnd.hInstance = hInstance;
    wnd.lpszClassName = windowName;

    //Register window class
    RegisterClass(&wnd);

    //Create window
    //! This returns NULL
    HWND hWnd = CreateWindowEx(
        0,
        windowName,
        L"Лабораторная работа №1",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    //Simple check to see if window creation failed
    if (hWnd == NULL) {
        //Pause
        system("PAUSE");
        return -1;
    }

    //Show the window
    ShowWindow(hWnd, nCmdShow);

    //Main message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    //Destroy GDI+
    GdiplusShutdown(gdiplusTokens);
}

//WndProc function
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {



    switch (msg) {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hDc = BeginPaint(hWnd, &ps);
        FillRect(hDc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
        draw(hDc);
        Hdc = BeginPaint(hWnd, &ps);
        image image = Draw_Image;
        image(hDc);
        EndPaint(hWnd, &ps);
    

        return 0;
    }
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0;
    }
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

void draw(HDC hdc)
{
    Point point;
    Rect rect(340, 400, 70, 70);
    Rect rect2(700, 400, 70, 70);
    //   Rect rect3();
    Graphics gf(hdc);
    Pen pen(Color(255, 0, 0, 0), 5.f);
    float comp[6] = {
        0.0f,0.2f,
        0.3f,0.7f,
        0.9f,11.0f
    };
    pen.SetCompoundArray(comp, 6);
    SolidBrush brush(Color(255, 0, 0, 0)); //black brush
    SolidBrush brush2(Color(255, 0, 191, 255)); //windows
    SolidBrush brushLights(Color(255, 255, 215, 0)); // lights front
    SolidBrush brushLightsBack(Color(255, 255, 140, 0)); // lights back
    LinearGradientBrush linearBrush(Point(200, 10), Point(300, 20), Color(255, 178, 34, 34), Color(255, 128, 0, 0));
    //   Bitmap img(L"car3.jpg"); 
                                      /*
                                        1. Must be global (doesn't matter how). You must draw image when window is called.
                                        2. Clearing image from memory.
                                        */
                                        //Car body
    gf.DrawRectangle(&pen, 320, 330, 500, 70);
    gf.FillRectangle(&linearBrush, 320, 330, 500, 70);

    gf.DrawRectangle(&pen, 325, 330, 15, 6);
    gf.FillRectangle(&brushLightsBack, 325, 330, 15, 6);

    gf.DrawRectangle(&pen, 800, 330, 15, 6);
    gf.FillRectangle(&brushLights, 800, 330, 15, 6);
    // Wheels
    gf.FillEllipse(&brush, rect);
    gf.DrawEllipse(&pen, rect);

    gf.FillEllipse(&brush, rect2);
    gf.DrawEllipse(&pen, rect2);

    Point points[6] =
    {
         Point(350,330), Point(380,240),
         Point(380,240), Point(720,240),
         Point(720,240), Point(780,330)
    };
    gf.DrawLines(&pen, points, 6);
    ///</summary>
    gf.DrawLine(&pen, 570, 240, 570, 330);

    /// Font
    FontFamily fontfamily(L"Arial");
    Font font(&fontfamily, 16, FontStyleItalic, UnitPixel);

    gf.DrawString(L"Автобомиль", 10, &font, PointF(60.f, 60.f), &brush);

}

void Draw_Image(HDC hdc)
{
     Graphics graphics(hdc);
     Image image(L"car3.jpg");
     Pen pen( Color(82,194,235),3);
     Rect rect(200, 50, 150, 75);
    graphics.DrawRectangle(&pen, rect);
    graphics.DrawImage(&image, rect);
}