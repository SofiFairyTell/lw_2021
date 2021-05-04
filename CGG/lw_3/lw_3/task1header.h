#pragma once
#pragma once

#include <Windows.h>
#include <gdiplus.h>


class WorldWindow
{
public:

	float Left;
	float Top;
	float Right;
	float Bottom;

	inline WorldWindow(float left, float top, float right, float bottom)
		: Left(left), Top(top), Right(right), Bottom(bottom)
	{}

	inline float Width() const
	{
		return (Right - Left);
	}

	inline float Height() const
	{
		return (Top - Bottom);
	}
};

class Viewport : public Gdiplus::Rect
{
public:

	inline Viewport(int left, int top, int right, int bottom)
		: Gdiplus::Rect(left, top, right - left, bottom - top)
	{
	}

	inline Viewport(const RECT& rect)
		: Gdiplus::Rect(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top)
	{
	}

	inline operator RECT() const
	{
		RECT rect = { X, Y, X + Width, Y + Height };
		return rect;
	}
};

inline void WorldToViewport(const WorldWindow& w, const Viewport& vp, Gdiplus::PointF* points, unsigned int count)
{
	float A = vp.Width / (w.Right - w.Left);
	float B = vp.Height / (w.Bottom - w.Top);
	float C = vp.X - A * w.Left;
	float D = vp.Y - B * w.Top;

	for (unsigned int i = 0; i < count; ++i)
	{
		points[i].X = A * points[i].X + C;
		points[i].Y = B * points[i].Y + D;
	}
}

inline void ViewportToWorld(const WorldWindow& w, const Viewport& vp, Gdiplus::PointF* points, unsigned int count)
{
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


