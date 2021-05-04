#include <Windows.h>
#include <windowsx.h>
#include <CommCtrl.h>
#include <tchar.h>
#include <Richedit.h>
#include <sstream>
#include <strsafe.h>
#include <string.h>
#include <Psapi.h>
#include <gdiplus.h>
#include <gdiplusflat.h>
#include <memory>
#include <gdiplustypes.h>

#pragma comment(lib, "gdiplus.lib")

#include <cmath>
const float pi = 3.14159265358979323846;


#include <vector>
#include "task1header.h"


using namespace Gdiplus;
using namespace std;

HWND hAddWnd = NULL;

ULONG_PTR gdiplusToken;

GdiplusStartupInput gdiplusStartupInput;
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL PreTranslateMessage(LPMSG lpMsg);

Gdiplus::PointF Tween(const Gdiplus::PointF& A, const Gdiplus::PointF& B, float t)
{
	return Gdiplus::PointF(A.X * (1.f - t) + B.X * t, A.Y * (1.f - t) + B.Y * t);
}



Image* img;
Image* ornament_image;

const int XMAX = 1500;
const int YMAX = 800;

const int tao = 25; // try 250!
int time_ = 0;
int time_cur = 0;
int time_next = 0;


int frame_count = -1;
int frame_index = -1;

// half of size of square wheel
const float a = 100;

// loop consists of 2 * n arcs
const int n = 10;


float ground_bot_level = 0;
float ground_top_level = (sqrt(2) - 1) * a;
float axis_level = sqrt(2) * a;

float arc_width = pi / 2 * sqrt(2) * a;

const float loop_radius = (arc_width / 2) / sin(pi / (2 * n));
const PointF loop_center = PointF(15 * arc_width, loop_radius);

const WorldWindow ww(0, 20 * a, 30 * a, 0);
const Viewport vp(0, 0, 750, 500);

const float cell = 0.20 * a;
PointF origin(44, (ww.Height() - axis_level) * vp.Width / ww.Width() - 6 * cell);

PointF rear_wheel_center = PointF(arc_width / 2, axis_level);

vector<PointF> rear_wheel_cur{
	rear_wheel_center + PointF(-a, -a),
	rear_wheel_center + PointF(-a, a),
	rear_wheel_center + PointF(a, a),
	rear_wheel_center + PointF(a, -a),
};
vector<PointF> rear_wheel_next = rear_wheel_cur;

PointF front_wheel_center = PointF(3 * arc_width, axis_level);

vector<PointF> front_wheel_cur{
	front_wheel_center + PointF(-sqrt(2) * a, 0),
	front_wheel_center + PointF(0, +sqrt(2) * a),
	front_wheel_center + PointF(+sqrt(2) * a, 0),
	front_wheel_center + PointF(0, -sqrt(2) * a),
};
vector<PointF> front_wheel_next = front_wheel_cur;


PointF pedals_star = Tween(rear_wheel_center, front_wheel_center, 0.5);
PointF seat = rear_wheel_center + PointF(arc_width, arc_width);
PointF node = front_wheel_center + PointF(-0.5 * arc_width, arc_width);
PointF rudder = node + PointF(-0.1 * arc_width, 0.2 * arc_width);

PointF handle_back = rudder;
PointF handle_front = rudder + PointF(0.3 * arc_width, 0);

PointF seat_front = seat + PointF(-0.2 * arc_width, 0.05 * arc_width);
PointF seat_back = seat + PointF(0.2 * arc_width, 0.05 * arc_width);




vector<PointF> body_cur{
	node,
	front_wheel_center,
	rudder,
	node,
	seat,
	rear_wheel_center,
	pedals_star,
	seat,
	pedals_star
};

vector<PointF> body_next = body_cur;

vector<PointF> rudder_cur{
	handle_back,
	handle_front
};

vector<PointF> rudder_next = rudder_cur;

vector<PointF> seat_cur{
	seat_back, seat_front
};

vector<PointF> seat_next = seat_cur;





void Display(HDC hdc);
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void OnDestroy(HWND hwnd);


int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR lpszCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = WndProc;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);

	//wcex.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	wcex.hbrBackground = NULL;

	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = TEXT("NewWindowClass");
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (0 == RegisterClassEx(&wcex))
	{
		return -1;
	}

	LoadLibrary(TEXT("ComCtl32.dll"));
	setlocale(LC_ALL, "Russian");

	// necessary for normal size of client area !!!
	RECT rect = { 0, 0, XMAX, YMAX };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW & (~WS_MAXIMIZEBOX) ^ WS_THICKFRAME, false, 0);

	HWND hWnd = CreateWindowEx(
		0, TEXT("NewWindowClass"), TEXT("Лабораторная работа №3"), WS_OVERLAPPEDWINDOW & (~WS_MAXIMIZEBOX) ^ WS_THICKFRAME, CW_USEDEFAULT,
		0,

		// necessary for normal size of client area !!!
		rect.right - rect.left, rect.bottom - rect.top,
		NULL, NULL, hInstance, NULL
	);

	if (NULL == hWnd)
	{
		return -1;
	}

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	BOOL bRet;
	for (;;)
	{
		bRet = GetMessage(&msg, NULL, 0, 0);
		if (bRet == -1)
		{
		}
		else if (FALSE == bRet)
		{
			break;
		}
		else if (PreTranslateMessage(&msg) == FALSE)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);

	case WM_ERASEBKGND:
	{
		return 1;
	}

	case WM_TIMER:
	{
		frame_index = (frame_index + 1) % frame_count;

		time_ += tao;

		img->SelectActiveFrame(&FrameDimensionTime, frame_index);

		InvalidateRect(hWnd, NULL, FALSE);

		return 0;
	}

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		Display(hdc);
		EndPaint(hWnd, &ps);
		return 0;
	}

	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

BOOL PreTranslateMessage(LPMSG lpMsg)
{
	return IsDialogMessage(hAddWnd, lpMsg);
}

BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
	Status stRet = GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	img = new Image(L"bike2.gif");
	ornament_image = new Image(L"tile2.bmp");

	frame_count = img->GetFrameCount(&FrameDimensionTime);

	SetTimer(hwnd, 1, tao, NULL);

	return TRUE;
}

void OnDestroy(HWND hwnd)
{
	delete img;
	delete ornament_image;
	GdiplusShutdown(gdiplusToken);
	PostQuitMessage(0);
}

void DrawBackGround(Graphics& g) 
{
	//Инструменты для рисования
	Pen pen(Color::Orange, 1);
	HatchBrush brush(HatchStyleDivot, Color::Orange, Color::Red);

	PointF p;
	for (int i = 0; i < 100; ++i) {
		vector<PointF> step = {
			p,
			p + PointF(arc_width * 0.25, 0.75 * ground_top_level),
			p + PointF(arc_width / 2, ground_top_level),
			p + PointF(arc_width * 0.75, 0.75 * ground_top_level),
			p + PointF(arc_width, 0)
		};
		WorldToViewport(ww, vp, step.data(), step.size());
		g.DrawPolygon(&pen, step.data(), step.size());
		p.X += arc_width;
		g.FillPolygon(&brush, step.data(), step.size());
	}

	// loop

	p = PointF(loop_center.X, 0);
	vector<PointF> loop_step = {
		p,
		p + PointF(arc_width * 0.25, 0.35 * ground_top_level),
		p + PointF(arc_width / 2, 0.80 * ground_top_level),
		p + PointF(arc_width * 0.75, 0.35 * ground_top_level),
		p + PointF(arc_width, 0)
	};

	Matrix mx;
	mx.RotateAt(180.0 / (2 * n), p, MatrixOrderAppend);
	mx.TransformPoints(loop_step.data(), loop_step.size());




	for (int i = 0; i < 2 * n; ++i) {
		auto loop_step_copy = loop_step;
		WorldToViewport(ww, vp, loop_step_copy.data(), loop_step_copy.size());
		g.DrawPolygon(&pen, loop_step_copy.data(), loop_step_copy.size());
		g.FillPolygon(&brush, loop_step_copy.data(), loop_step_copy.size());

		Matrix tmp;
		tmp.RotateAt(180.0 / n, loop_center, MatrixOrderAppend);
		tmp.TransformPoints(loop_step.data(), loop_step.size());

	}



	TextureBrush underground_brush(ornament_image, WrapMode::WrapModeTile);
	g.FillRectangle(&underground_brush, 0, vp.GetBottom(), XMAX, YMAX);
}

void Display(HDC hdc)
{
	Graphics g(hdc);

	g.SetSmoothingMode(SmoothingModeAntiAlias);

	Rect rect;
	g.GetVisibleClipBounds(&rect);

	Bitmap back_buffer(rect.Width, rect.Height, &g);
	Graphics temp(&back_buffer);

	// clear BEFORE drawing
	temp.Clear(Color::White);

	origin.X += arc_width / 10 * vp.Width / ww.Width();

	DrawBackGround(temp);


	if (time_ % (5 * tao) == 0) {

		rear_wheel_cur = rear_wheel_next;
		front_wheel_cur = front_wheel_next;

		body_cur = body_next;
		rudder_cur = rudder_next;
		seat_cur = seat_next;

		time_cur = time_next;
		time_next += 5 * tao;

		if (28 * 5 * tao <= time_ && time_ < 28 * 5 * tao + 2 * n * 10 * tao) {
			Matrix m;

			m.RotateAt(-45, rear_wheel_center, MatrixOrderAppend);
			m.RotateAt(180 / (2 * n), loop_center, MatrixOrderAppend);
			m.TransformPoints(rear_wheel_next.data(), rear_wheel_next.size());

			m.Reset();
			m.RotateAt(180 / (2 * n), loop_center, MatrixOrderPrepend);
			m.TransformPoints(&rear_wheel_center);
		}
		else
		{
			Matrix m;
			m.RotateAt(-45, rear_wheel_center, MatrixOrderAppend);
			m.Translate(arc_width / 2, 0, MatrixOrderAppend);

			m.TransformPoints(rear_wheel_next.data(), rear_wheel_next.size());
			rear_wheel_center.X += arc_width / 2;
		}

		if (25 * 5 * tao <= time_ && time_ < 25 * 5 * tao + 2 * n * 10 * tao) {
			Matrix m;

			m.RotateAt(-45, front_wheel_center, MatrixOrderAppend);
			m.RotateAt(180 / (2 * n), loop_center, MatrixOrderAppend);
			m.TransformPoints(front_wheel_next.data(), front_wheel_next.size());

			m.Reset();
			m.RotateAt(180 / (2 * n), loop_center, MatrixOrderPrepend);
			m.TransformPoints(&front_wheel_center);
			m.TransformPoints(&node);

			m.TransformPoints(&seat);
			m.TransformPoints(&handle_back);
			m.TransformPoints(&handle_front);
			m.TransformPoints(&rudder);
			m.TransformPoints(&seat_back);
			m.TransformPoints(&seat_front);
		}
		else
		{
			Matrix m;
			m.RotateAt(-45, front_wheel_center, MatrixOrderAppend);
			m.Translate(arc_width / 2, 0, MatrixOrderAppend);

			m.TransformPoints(front_wheel_next.data(), front_wheel_next.size());
			front_wheel_center.X += arc_width / 2;

			node.X += arc_width / 2;
			rudder.X += arc_width / 2;
			seat.X += arc_width / 2;

			handle_back.X += arc_width / 2;
			handle_front.X += arc_width / 2;

			seat_back.X += arc_width / 2;
			seat_front.X += arc_width / 2;

		}

		pedals_star = Tween(rear_wheel_center, front_wheel_center, 0.5);

		body_next = {
			node,
			front_wheel_center,
			rudder,
			node,
			seat,
			rear_wheel_center,
			pedals_star,
			seat,
			pedals_star
		};

		seat_next = {
			seat_back, seat_front
		};

		rudder_next = { handle_back, handle_front };
	}

	Pen black_pen(Color::Black, 5);
	HatchBrush wheels_brush(HatchStyle::HatchStyleWave, Color::Black, Color::LightBlue);

	auto front_wheel_copy = front_wheel_next;
	for (int i = 0; i < front_wheel_copy.size(); ++i) {
		front_wheel_copy[i] = Tween(front_wheel_cur[i], front_wheel_next[i], 1.0 * (time_ - time_cur) / (5 * tao));
	}
	WorldToViewport(ww, vp, front_wheel_copy.data(), front_wheel_copy.size());
	temp.DrawPolygon(&black_pen, front_wheel_copy.data(), front_wheel_copy.size());
	temp.FillPolygon(&wheels_brush, front_wheel_copy.data(), front_wheel_copy.size());

	auto rear_wheel_copy = rear_wheel_next;
	for (int i = 0; i < rear_wheel_copy.size(); ++i) {
		rear_wheel_copy[i] = Tween(rear_wheel_cur[i], rear_wheel_next[i], 1.0 * (time_ - time_cur) / (5 * tao));
	}
	WorldToViewport(ww, vp, rear_wheel_copy.data(), rear_wheel_copy.size());
	temp.DrawPolygon(&black_pen, rear_wheel_copy.data(), rear_wheel_copy.size());
	temp.FillPolygon(&wheels_brush, rear_wheel_copy.data(), rear_wheel_copy.size());



	Pen red_pen(Color::Red, 1);
	black_pen.SetMiterLimit(1);

	auto body_copy = body_next;
	for (int i = 0; i < body_copy.size(); ++i) {
		body_copy[i] = Tween(body_cur[i], body_next[i], 1.0 * (time_ - time_cur) / (5 * tao));
	}
	WorldToViewport(ww, vp, body_copy.data(), body_copy.size());
	temp.DrawPolygon(&red_pen, body_copy.data(), body_copy.size());

	auto rudder_copy = rudder_next;
	for (int i = 0; i < rudder_copy.size(); ++i) {
		rudder_copy[i] = Tween(rudder_cur[i], rudder_next[i], 1.0 * (time_ - time_cur) / (5 * tao));
	}
	WorldToViewport(ww, vp, rudder_copy.data(), rudder_copy.size());

	temp.DrawPolygon(&black_pen, rudder_copy.data(), rudder_copy.size());

	auto seat_copy = seat_next;
	for (int i = 0; i < seat_copy.size(); ++i) {
		seat_copy[i] = Tween(seat_cur[i], seat_next[i], 1.0 * (time_ - time_cur) / (5 * tao));
	}
	WorldToViewport(ww, vp, seat_copy.data(), seat_copy.size());
	temp.DrawPolygon(&black_pen, seat_copy.data(), seat_copy.size());

	SolidBrush black_brush(Color::Black);

	temp.FillEllipse(&black_brush, Rect(Point(round(body_copy.back().X), round(body_copy.back().Y)) - Point(round(a / 10), round(a / 10)), Size(a / 5, a / 5)));

	// pedals
	temp.DrawLine(&black_pen,
		Point(round(body_copy.back().X), round(body_copy.back().Y)) + Point(0, round(a / 5)),
		Point(round(body_copy.back().X), round(body_copy.back().Y)) - Point(0, round(a / 5))
	);

	temp.DrawLine(&black_pen,
		Point(round(body_copy.back().X), round(body_copy.back().Y)) + Point(round(a / 15), round(a / 5)),
		Point(round(body_copy.back().X), round(body_copy.back().Y)) + Point(-round(a / 15), round(a / 5))
	);

	temp.DrawLine(&black_pen,
		Point(round(body_copy.back().X), round(body_copy.back().Y)) + Point(round(a / 15), -round(a / 5)),
		Point(round(body_copy.back().X), round(body_copy.back().Y)) + Point(-round(a / 15), -round(a / 5))
	);

	temp.DrawLine(&black_pen,
		Point(round(body_copy.back().X), round(body_copy.back().Y)) + Point(0, round(a / 5)),
		Point(round(body_copy.back().X), round(body_copy.back().Y)) - Point(0, round(a / 5))
	);

	temp.DrawLine(&black_pen, PointF(), PointF());
	temp.DrawLine(&black_pen, PointF(), PointF());

	// draw text
	Font font(L"Arial", 40.f, FontStyleRegular);
	SolidBrush WhiteBrush(Color::Black);
	temp.DrawString(L"Велосипед", -1, &font, PointF(0, 0), StringFormat::GenericDefault(), &WhiteBrush);

	// draw gif-image
	temp.DrawImage(img, XMAX - 200, 0, 200, 150);

	g.DrawImage(&back_buffer, rect);
}
