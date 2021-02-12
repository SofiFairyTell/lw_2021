#include <windows.h>
#include <gdiplus.h>
#include<gdiplusstringformat.h>
#include<gdiplusenums.h>

void(*image)(HDC); //Pointer to image drawing function
HDC hdc;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void draw(HDC hdc);
void Draw_Image(HDC hdc);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR pCmdLine, int nCmdShow)
{
   
    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);

    //Initialize GDI+
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusTokens;
    Gdiplus::GdiplusStartup(&gdiplusTokens, &gdiplusStartupInput, NULL);

    // Create the window.

    HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"Laboratornaya rabota #1", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
                            
    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    image(hdc) = Draw_Image;
    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    //Destroy GDI+
    Gdiplus::GdiplusShutdown(gdiplusTokens);
    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        hdc = BeginPaint(hwnd, &ps);
        draw(hdc);
        EndPaint(hwnd,&ps);
    }
    return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void draw(HDC hdc)
{
    Gdiplus::Point point;
    Gdiplus::Rect rect(340, 400, 70, 70);
    Gdiplus::Rect rect2(700, 400, 70, 70);
    Gdiplus::Rect rect3();
    Gdiplus::Graphics gf(hdc);
    Gdiplus::Pen pen(Gdiplus::Color(255, 0, 0, 0),5.f);
    float comp[6] = {
        0.0f,0.2f,
        0.3f,0.7f,
        0.9f,11.0f
    };
    pen.SetCompoundArray(comp, 6);
    Gdiplus::SolidBrush brush(Gdiplus::Color(255,0,0,0)); //black brush
    Gdiplus::SolidBrush brush2(Gdiplus::Color(255,0,191,255)); //windows
    Gdiplus::SolidBrush brushLights(Gdiplus::Color(255,255,215,0)); // lights front
    Gdiplus::SolidBrush brushLightsBack(Gdiplus::Color(255,255,140,0)); // lights back
    Gdiplus::LinearGradientBrush linearBrush(Gdiplus::Point(200,10),Gdiplus::Point(300,20),Gdiplus::Color(255,178,34,34),Gdiplus::Color(255,128,0,0));
  //  Gdiplus::Bitmap img(L"car3.jpg"); 
                                    /*
                                      1. Must be global (doesn't matter how). You must draw image when window is called.
                                      2. Clearing image from memory.
                                      */
    ///Car body
    gf.DrawRectangle(&pen, 320, 330, 500, 70);
    gf.FillRectangle(&linearBrush, 320, 330, 500, 70);
  
    gf.DrawRectangle(&pen, 325, 330, 15, 6);
    gf.FillRectangle(&brushLightsBack, 325, 330, 15, 6);

    gf.DrawRectangle(&pen, 800, 330, 15, 6);
    gf.FillRectangle(&brushLights, 800, 330, 15, 6);
    /// Wheels
    gf.FillEllipse(&brush, rect);
    gf.DrawEllipse(&pen, rect);

    gf.FillEllipse(&brush, rect2);
    gf.DrawEllipse(&pen, rect2);

    Gdiplus::Point points[6] =
    {
        Gdiplus::Point(350,330),Gdiplus::Point(380,240),
        Gdiplus::Point(380,240),Gdiplus::Point(720,240),
        Gdiplus::Point(720,240),Gdiplus::Point(780,330)
    };
    gf.DrawLines(&pen, points, 6);
    ///</summary>
    gf.DrawLine(&pen, 570, 240, 570, 330);

    /// Font
    Gdiplus::FontFamily fontfamily(L"Arial");
    Gdiplus::Font font(&fontfamily, 16, Gdiplus::FontStyleItalic, Gdiplus::UnitPixel);

    gf.DrawString(L"Avtomobil", 10, &font, Gdiplus::PointF(60.f, 60.f),&brush);
   
}

///<summary>
/// Draw image to the window
/// <param>HDC hdc</param>
/// <returns>Prints jpg image to our window on call</returns>
/// </summary>
void Draw_Image(HDC hdc)
{
    Gdiplus::Graphics graphics(hdc);
    Gdiplus::Image image(L"car3.jpg");
    Gdiplus::Pen pen(Gdiplus::Color(82,194,235),3);
    graphics.DrawImage(&image, 900, 50);
    Gdiplus::Rect rect(200, 50, 150, 75);
    graphics.DrawRectangle(&pen, rect);
    graphics.DrawImage(&image, rect);
}