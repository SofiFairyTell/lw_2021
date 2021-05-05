#pragma once

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
