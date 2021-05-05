#pragma once
#include "task1header.h"

bool  V_LBclip(const WorldWindow &w, float *x0, float *y0, float *x1, float *y1);//отсечение по алгоритму Лианга-Барски
static bool LB_tclip(float p, float q);//определение оставить отрезок или нет

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
