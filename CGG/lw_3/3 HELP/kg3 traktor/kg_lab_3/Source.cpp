#include <Windows.h>
#include <WindowsX.h>
#include <CommCtrl.h>
#include <tchar.h>
#include <strsafe.h>
#include <gdiplus.h>
#include <gdiplusflat.h>
#include <gdiplustypes.h>
#include <sstream>

#pragma comment(lib, "gdiplus.lib")

int Time = 0;
UINT frameIndex; // индекс активного кадра
UINT frameCount; // количество кадров

HWND hWnd = NULL;
ULONG_PTR gdiplusToken;
Gdiplus::GdiplusStartupInput gdiplusStartupInput;
Gdiplus::Image* image;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL PreTranslateMessage(LPMSG lpMsg);

void Display(HDC hdc);
Gdiplus::PointF Tween(const Gdiplus::PointF& A, const Gdiplus::PointF& B, float t);
void Tween(const Gdiplus::PointF* A, const Gdiplus::PointF* B, Gdiplus::PointF* P, int count, float t);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR lpszCmdLine, int nCmdShow)
{
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = WndProc;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = TEXT("NewWindowClass");
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (RegisterClassEx(&wcex) == 0)
		return -1;
	LoadLibrary(TEXT("ComCtl32.dll"));
	setlocale(LC_ALL, "Russian");

	HWND hWnd = CreateWindowEx(0, TEXT("NewWindowClass"), TEXT("Компьютерная графика и геометрия. Лабораторная работа №3"),
		WS_OVERLAPPEDWINDOW & (~WS_MAXIMIZEBOX) ^ WS_THICKFRAME,CW_USEDEFAULT, 0, 1100, 600, NULL, NULL, hInstance, NULL);

	if (hWnd == NULL)
		return -1;
	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	BOOL bRet;
	for (;;)
	{
		bRet = GetMessage(&msg, NULL, 0, 0);
		if (bRet == -1)
		{ }
		else if (bRet == FALSE)
			break;
		else if (PreTranslateMessage(&msg) == FALSE)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	Gdiplus::GdiplusShutdown(gdiplusToken); // Завершение работы с библиотекой
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CREATE:
		{
			image = Gdiplus::Image::FromFile(L"man.gif");
			if (image == NULL)
				return -1; // загрузка не удалась
			frameIndex = 0;
			// определение количества кадров в изображении
			frameCount = image->GetFrameCount(&Gdiplus::FrameDimensionTime);
			SetTimer(hWnd, 1, 40, NULL); // устанавливает таймер ~ 25 FPS
			return 0;
		}
		break;

		case WM_TIMER:
		{
			Time++;
			// увеличиваем индекс кадра (циклически)
			frameIndex = (frameIndex + 1) % frameCount;
			// Делаем кадр активным
			image->SelectActiveFrame(&Gdiplus::FrameDimensionTime, frameIndex);
			// требуем обновления клиентской области окна (перерисовки)
			InvalidateRect(hWnd, NULL, FALSE);
			return 0;
		}
		break;
	
		case WM_DESTROY:
		{
			if (image != NULL)
				delete image; // удаляем объект
			Gdiplus::GdiplusShutdown(gdiplusToken); // завершение работы GDI+
			PostQuitMessage(0);
		}
		break;

		case WM_ERASEBKGND:
			return 1;

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			Display(hdc);
			EndPaint(hWnd, &ps);
		}
		return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

BOOL PreTranslateMessage(LPMSG lpMsg)
{
	return IsDialogMessage(hWnd, lpMsg);
}

Gdiplus::PointF cabin[6] = { // кабина
	Gdiplus::PointF(690, 470),
	Gdiplus::PointF(750, 470),
	Gdiplus::PointF(850, 390),
	Gdiplus::PointF(840, 280),
	Gdiplus::PointF(720, 280),
	Gdiplus::PointF(690, 390)
};

Gdiplus::PointF roof[4] = { // крыша
	Gdiplus::PointF(710, 260),
	Gdiplus::PointF(850, 260),
	Gdiplus::PointF(850, 282),
	Gdiplus::PointF(710, 282)
};

Gdiplus::PointF flashlight[4] = { // лампочка
	Gdiplus::PointF(820, 235),
	Gdiplus::PointF(840, 235),
	Gdiplus::PointF(840, 255),
	Gdiplus::PointF(820, 255)
};

Gdiplus::PointF post[4] = { // лампочка
	Gdiplus::PointF(828, 255),
	Gdiplus::PointF(832, 255),
	Gdiplus::PointF(832, 260),
	Gdiplus::PointF(828, 260)
};

Gdiplus::PointF frame1[4] = {
	Gdiplus::PointF(600, 440),
	Gdiplus::PointF(850, 440),
	Gdiplus::PointF(850, 500),
	Gdiplus::PointF(600, 500)
};

Gdiplus::PointF frame2[5] = {
	Gdiplus::PointF(580, 390),
	Gdiplus::PointF(690, 390),
	Gdiplus::PointF(690, 470),
	Gdiplus::PointF(560, 470),
	Gdiplus::PointF(560, 410)
};

Gdiplus::PointF frame3[25] = {
	Gdiplus::PointF(753, 470),
	Gdiplus::PointF(804, 455),
	Gdiplus::PointF(838, 430),
	Gdiplus::PointF(854, 410),
	Gdiplus::PointF(865, 390),
	Gdiplus::PointF(857, 387),
	Gdiplus::PointF(847, 382),
	Gdiplus::PointF(836, 379),
	Gdiplus::PointF(826, 378),
	Gdiplus::PointF(812, 378),
	Gdiplus::PointF(804, 379),
	Gdiplus::PointF(789, 383),
	Gdiplus::PointF(780, 387),
	Gdiplus::PointF(773, 391),
	Gdiplus::PointF(767, 395),
	Gdiplus::PointF(763, 398),
	Gdiplus::PointF(759, 401),
	Gdiplus::PointF(755, 405),
	Gdiplus::PointF(751, 409),
	Gdiplus::PointF(747, 414),
	Gdiplus::PointF(743, 421),
	Gdiplus::PointF(739, 426),
	Gdiplus::PointF(735, 434),
	Gdiplus::PointF(731, 447),
	Gdiplus::PointF(728, 469)
};

Gdiplus::PointF back_arch[30] = {
	Gdiplus::PointF(745, 442),
	Gdiplus::PointF(752, 427),
	Gdiplus::PointF(755, 423),
	Gdiplus::PointF(759, 418),
	Gdiplus::PointF(768, 409),
	Gdiplus::PointF(773, 405),
	Gdiplus::PointF(779, 401),
	Gdiplus::PointF(787, 397),
	Gdiplus::PointF(798, 393),
	Gdiplus::PointF(808, 390),
	Gdiplus::PointF(831, 390),
	Gdiplus::PointF(841, 393),
	Gdiplus::PointF(852, 397),
	Gdiplus::PointF(860, 401),
	Gdiplus::PointF(866, 405),
	Gdiplus::PointF(871, 409),
	Gdiplus::PointF(884, 423),
	Gdiplus::PointF(882, 412),
	Gdiplus::PointF(874, 404),
	Gdiplus::PointF(863, 396),
	Gdiplus::PointF(855, 392),
	Gdiplus::PointF(844, 388),
	Gdiplus::PointF(832, 385),
	Gdiplus::PointF(807, 385),
	Gdiplus::PointF(795, 388),
	Gdiplus::PointF(784, 393),
	Gdiplus::PointF(770, 400),
	Gdiplus::PointF(765, 404),
	Gdiplus::PointF(753, 416),
	Gdiplus::PointF(747, 425)
};

Gdiplus::PointF front_arch[25] = {
	Gdiplus::PointF(651, 493),
	Gdiplus::PointF(656, 483),
	Gdiplus::PointF(656, 474),
	Gdiplus::PointF(655, 469),
	Gdiplus::PointF(653, 463),
	Gdiplus::PointF(648, 453),
	Gdiplus::PointF(646, 450),
	Gdiplus::PointF(643, 446),
	Gdiplus::PointF(636, 439),
	Gdiplus::PointF(632, 436),
	Gdiplus::PointF(629, 434),
	Gdiplus::PointF(619, 429),
	Gdiplus::PointF(613, 427),
	Gdiplus::PointF(608, 426),
	Gdiplus::PointF(601, 426),
	Gdiplus::PointF(589, 430),
	Gdiplus::PointF(589, 431),
	Gdiplus::PointF(608, 432),
	Gdiplus::PointF(616, 434),
	Gdiplus::PointF(631, 442),
	Gdiplus::PointF(640, 451),
	Gdiplus::PointF(642, 454),
	Gdiplus::PointF(644, 457),
	Gdiplus::PointF(647, 463),
	Gdiplus::PointF(649, 469)
};

Gdiplus::PointF degree_up[4] = { // верхняя ступень
	Gdiplus::PointF(695, 445),
	Gdiplus::PointF(720, 445),
	Gdiplus::PointF(720, 450),
	Gdiplus::PointF(695, 450)
};

Gdiplus::PointF degree_middle[4] = { // средняя ступень
	Gdiplus::PointF(degree_up[0].X, degree_up[0].Y + 20),
	Gdiplus::PointF(degree_up[1].X, degree_up[1].Y + 20),
	Gdiplus::PointF(degree_up[2].X, degree_up[2].Y + 20),
	Gdiplus::PointF(degree_up[3].X, degree_up[3].Y + 20)
};

Gdiplus::PointF degree_down[4] = { // нижняя ступень
	Gdiplus::PointF(degree_up[0].X, degree_up[0].Y + 40),
	Gdiplus::PointF(degree_up[1].X, degree_up[1].Y + 40),
	Gdiplus::PointF(degree_up[2].X, degree_up[2].Y + 40),
	Gdiplus::PointF(degree_up[3].X, degree_up[3].Y + 40)
};

Gdiplus::PointF ellipse1[8] = {
	Gdiplus::PointF(497, 317),
	Gdiplus::PointF(503, 317),
	Gdiplus::PointF(507, 313),
	Gdiplus::PointF(507, 307),
	Gdiplus::PointF(503, 303),
	Gdiplus::PointF(497, 303),
	Gdiplus::PointF(493, 307),
	Gdiplus::PointF(493, 313)
};

Gdiplus::PointF ellipse2[8] = {
	Gdiplus::PointF(641, 416),
	Gdiplus::PointF(649, 416),
	Gdiplus::PointF(654, 411),
	Gdiplus::PointF(654, 403),
	Gdiplus::PointF(649, 398),
	Gdiplus::PointF(641, 398),
	Gdiplus::PointF(636, 403),
	Gdiplus::PointF(636, 411)
};

Gdiplus::PointF back_wheel_1[8] = {
	Gdiplus::PointF(792, 540),
	Gdiplus::PointF(848, 540),
	Gdiplus::PointF(888, 500),
	Gdiplus::PointF(888, 440),
	Gdiplus::PointF(848, 400),
	Gdiplus::PointF(792, 400),
	Gdiplus::PointF(752, 440),
	Gdiplus::PointF(752, 500)
};

Gdiplus::PointF back_wheel_2[8] = {
	Gdiplus::PointF(799, 420),
	Gdiplus::PointF(841, 420),
	Gdiplus::PointF(870, 450),
	Gdiplus::PointF(870, 492),
	Gdiplus::PointF(841, 520),
	Gdiplus::PointF(799, 520),
	Gdiplus::PointF(770, 492),
	Gdiplus::PointF(770, 450)
};

Gdiplus::PointF back_wheel_3[8] = {
	Gdiplus::PointF(814, 485),
	Gdiplus::PointF(826, 485),
	Gdiplus::PointF(835, 476),
	Gdiplus::PointF(835, 464),
	Gdiplus::PointF(826, 455),
	Gdiplus::PointF(814, 455),
	Gdiplus::PointF(805, 464),
	Gdiplus::PointF(805, 476)
};

Gdiplus::PointF front_wheel_1[8] = {
	Gdiplus::PointF(570, 540),
	Gdiplus::PointF(610, 540),
	Gdiplus::PointF(640, 511),
	Gdiplus::PointF(640, 471),
	Gdiplus::PointF(610, 440),
	Gdiplus::PointF(570, 440),
	Gdiplus::PointF(540, 471),
	Gdiplus::PointF(540, 511)
};

Gdiplus::PointF front_wheel_2[8] = {
	Gdiplus::PointF(576, 525),
	Gdiplus::PointF(604, 525),
	Gdiplus::PointF(625, 504),
	Gdiplus::PointF(625, 476),
	Gdiplus::PointF(604, 455),
	Gdiplus::PointF(576, 455),
	Gdiplus::PointF(555, 476),
	Gdiplus::PointF(555, 504)
};

Gdiplus::PointF front_wheel_3[8] = {
	Gdiplus::PointF(584, 505),
	Gdiplus::PointF(596, 505),
	Gdiplus::PointF(605, 496),
	Gdiplus::PointF(605, 484),
	Gdiplus::PointF(596, 475),
	Gdiplus::PointF(584, 475),
	Gdiplus::PointF(575, 484),
	Gdiplus::PointF(575, 496)
};

Gdiplus::PointF bucket_1[21] = {
	Gdiplus::PointF(631, 413),
	Gdiplus::PointF(639, 420),
	Gdiplus::PointF(652, 420),
	Gdiplus::PointF(658, 412),
	Gdiplus::PointF(658, 404),
	Gdiplus::PointF(619, 334),
	Gdiplus::PointF(611, 324),
	Gdiplus::PointF(603, 320),
	Gdiplus::PointF(542, 294),
	Gdiplus::PointF(517, 294),
	Gdiplus::PointF(489, 303),
	Gdiplus::PointF(482, 309),
	Gdiplus::PointF(482, 316),
	Gdiplus::PointF(486, 321),
	Gdiplus::PointF(494, 322),
	Gdiplus::PointF(523, 314),
	Gdiplus::PointF(528, 313),
	Gdiplus::PointF(532, 314),
	Gdiplus::PointF(583, 332),
	Gdiplus::PointF(591, 339),
	Gdiplus::PointF(596, 346)
};

Gdiplus::PointF bucket_2[21] = {
	Gdiplus::PointF(506, 314),
	Gdiplus::PointF(508, 296),
	Gdiplus::PointF(522, 291),
	Gdiplus::PointF(531, 285),
	Gdiplus::PointF(537, 278),
	Gdiplus::PointF(540, 272),
	Gdiplus::PointF(543, 263),
	Gdiplus::PointF(551, 254),
	Gdiplus::PointF(551, 246),
	Gdiplus::PointF(539, 246),
	Gdiplus::PointF(457, 241),
	Gdiplus::PointF(418, 235),
	Gdiplus::PointF(418, 243),
	Gdiplus::PointF(421, 246),
	Gdiplus::PointF(424, 254),
	Gdiplus::PointF(431, 272),
	Gdiplus::PointF(438, 284),
	Gdiplus::PointF(448, 292),
	Gdiplus::PointF(458, 298),
	Gdiplus::PointF(474, 303),
	Gdiplus::PointF(490, 319)
};

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

Gdiplus::PointF gorka[21] = {
	Gdiplus::PointF(0, 560),
	Gdiplus::PointF(209, 540),
	Gdiplus::PointF(245, 527),
	Gdiplus::PointF(236, 508),
	Gdiplus::PointF(175, 506),
	Gdiplus::PointF(166, 493),
	Gdiplus::PointF(162, 479),
	Gdiplus::PointF(159, 465),
	Gdiplus::PointF(156, 450),
	Gdiplus::PointF(154, 437),
	Gdiplus::PointF(138, 431),
	Gdiplus::PointF(133, 402),
	Gdiplus::PointF(120, 393),
	Gdiplus::PointF(102, 402),
	Gdiplus::PointF(94, 401),
	Gdiplus::PointF(88, 394),
	Gdiplus::PointF(78, 361),
	Gdiplus::PointF(49, 343),
	Gdiplus::PointF(44, 330),
	Gdiplus::PointF(11, 315),
	Gdiplus::PointF(0, 302)
};

Gdiplus::PointF gorka1[9] = {
	Gdiplus::PointF(175, 506),
	Gdiplus::PointF(235, 510),
	Gdiplus::PointF(212, 471),
	Gdiplus::PointF(170, 459),
	Gdiplus::PointF(154, 438),
	Gdiplus::PointF(156, 450),
	Gdiplus::PointF(159, 465),
	Gdiplus::PointF(162, 479),
	Gdiplus::PointF(166, 493),
};

Gdiplus::PointF gorka2[19] = {
	Gdiplus::PointF(252, 431),
	Gdiplus::PointF(246, 430),
	Gdiplus::PointF(234, 435),
	Gdiplus::PointF(232, 441),
	Gdiplus::PointF(227, 443),
	Gdiplus::PointF(225, 449),
	Gdiplus::PointF(210, 462),
	Gdiplus::PointF(207, 463),
	Gdiplus::PointF(205, 471),
	Gdiplus::PointF(205, 480),
	Gdiplus::PointF(206, 484),
	Gdiplus::PointF(203, 489),
	Gdiplus::PointF(190, 502),
	Gdiplus::PointF(193, 516),
	Gdiplus::PointF(192, 520),
	Gdiplus::PointF(191, 524),
	Gdiplus::PointF(193, 529),
	Gdiplus::PointF(200, 522),
	Gdiplus::PointF(252, 437)
};

Gdiplus::PointF layer1[4] = {
	Gdiplus::PointF(200, 565),
	Gdiplus::PointF(279, 554),
	Gdiplus::PointF(267, 536),
	Gdiplus::PointF(189, 548)
};

Gdiplus::PointF layer2[5] = {
	Gdiplus::PointF(208, 572),
	Gdiplus::PointF(285, 551),
	Gdiplus::PointF(278, 527),
	Gdiplus::PointF(190, 550),
	Gdiplus::PointF(199, 564)
};

Gdiplus::PointF layer3[7] = {
	Gdiplus::PointF(205, 573),
	Gdiplus::PointF(272, 555),
	Gdiplus::PointF(241, 516),
	Gdiplus::PointF(172, 509),
	Gdiplus::PointF(180, 528),
	Gdiplus::PointF(188, 544),
	Gdiplus::PointF(197, 559)
};

Gdiplus::Point kv[4] = {
	Gdiplus::Point(200, 390),
	Gdiplus::Point(290, 390),
	Gdiplus::Point(290, 505),
	Gdiplus::Point(200, 505)
};

Gdiplus::Point kv1[4] = {
	Gdiplus::Point(0, 590),
	Gdiplus::Point(290, 590),
	Gdiplus::Point(290, 515),
	Gdiplus::Point(0, 515)
};

Gdiplus::PointF tube1[6] = {
	Gdiplus::PointF(673, 408),
	Gdiplus::PointF(678, 408),
	Gdiplus::PointF(681, 405),
	Gdiplus::PointF(681, 388),
	Gdiplus::PointF(670, 388),
	Gdiplus::PointF(670, 405)
};

Gdiplus::PointF tube2[4] = {
	Gdiplus::PointF(665, 394),
	Gdiplus::PointF(686, 394),
	Gdiplus::PointF(686, 303),
	Gdiplus::PointF(665, 303)
};

Gdiplus::PointF tube3[4] = {
	Gdiplus::PointF(670, 303),
	Gdiplus::PointF(681, 303),
	Gdiplus::PointF(681, 248),
	Gdiplus::PointF(670, 248)
};

Gdiplus::PointF krug[9] = {
	/*Gdiplus::PointF(599, 220),
	Gdiplus::PointF(641, 220),
	Gdiplus::PointF(670, 190),
	Gdiplus::PointF(670, 148),
	Gdiplus::PointF(641, 118),
	Gdiplus::PointF(599, 118),
	Gdiplus::PointF(569, 148),
	Gdiplus::PointF(569, 190),
	Gdiplus::PointF(599, 220)*/

	Gdiplus::PointF(469, 259),
	Gdiplus::PointF(472, 258),
	Gdiplus::PointF(471, 256),
	Gdiplus::PointF(472, 254),
	Gdiplus::PointF(469, 253),
	Gdiplus::PointF(466, 254),
	Gdiplus::PointF(465, 256),
	Gdiplus::PointF(466, 258),
	Gdiplus::PointF(469, 259)
};

Gdiplus::PointF krug_[8] = {
	Gdiplus::PointF(514, 185),
	Gdiplus::PointF(526, 185),
	Gdiplus::PointF(535, 176),
	Gdiplus::PointF(535, 164),
	Gdiplus::PointF(526, 155),
	Gdiplus::PointF(514, 155),
	Gdiplus::PointF(505, 164),
	Gdiplus::PointF(505, 176)
};

void Display(HDC hdc)
{
	// создаем объект класса Graphics для рисования
	Gdiplus::Graphics graph(hdc);
	
	// определяем размер области рисования
	Gdiplus::Rect rect(0, 0, 1000, 600);
	graph.GetVisibleClipBounds(&rect);

	Gdiplus::Bitmap backbuffer(rect.Width, rect.Height, &graph);
	//создаем объект класса Grapchics для рисования в буфер
	Gdiplus::Graphics g(&backbuffer);

	g.Clear(Gdiplus::Color::White); // выполняем очистку перед рисованием
	g.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);

	Gdiplus::Pen black_pen(Gdiplus::Color::Black); // перо
	Gdiplus::SolidBrush black_brush(Gdiplus::Color::Black); // сплошная кисть
	Gdiplus::SolidBrush lightblue_brush(Gdiplus::Color(214, 239, 253)); // сплошная кисть
	Gdiplus::SolidBrush lightgray_brush(Gdiplus::Color(167, 167, 167)); // сплошная кисть
	Gdiplus::SolidBrush orange_brush(Gdiplus::Color(237, 120, 2)); // сплошная кисть
	Gdiplus::SolidBrush green_brush(Gdiplus::Color(178, 204, 21)); // сплошная кисть
	Gdiplus::SolidBrush gray_brush(Gdiplus::Color(255, 45, 45, 48)); // сплошная кисть
	Gdiplus::SolidBrush red_brush(Gdiplus::Color::Red); // сплошная кисть
	Gdiplus::SolidBrush lightgreen_brush(Gdiplus::Color(203, 216, 84)); // сплошная кисть
	Gdiplus::SolidBrush brown_brush(Gdiplus::Color(119, 85, 58)); // сплошная кисть
	Gdiplus::SolidBrush air_brush(Gdiplus::Color(147, 212, 247)); // сплошная кисть
	Gdiplus::HatchBrush hBr1(Gdiplus::HatchStyleWeave, Gdiplus::Color::Black, Gdiplus::Color::DarkGray); // штриховая кисть
	Gdiplus::HatchBrush hBr2(Gdiplus::HatchStyle05Percent, Gdiplus::Color(163, 107, 50), Gdiplus::Color(218, 163, 96));
	Gdiplus::HatchBrush hBr3(Gdiplus::HatchStyle10Percent, Gdiplus::Color::Black, Gdiplus::Color::Silver);

	{
		Gdiplus::Matrix mtrx;

		int Timing_0 = -1,
			Timing_1 = 50,
			Timing_2 = 72,
			Timing_3 = 76,
			Timing_4 = 130,
			Timing_5 = 134,
			Timing_6 = 137,
			Timing_7 = 143,
			Timing_8 = 156,
			Timing_9 = 200; // прдолжительность анимации

		int Timing_1_1 = 350;

		if (Time < Timing_1) // двигаемся влево
		{
			mtrx.Translate(-2, 0);

			mtrx.TransformPoints(cabin, 6);
			mtrx.TransformPoints(roof, 4);
			mtrx.TransformPoints(flashlight, 4);
			mtrx.TransformPoints(post, 4);
			mtrx.TransformPoints(frame1, 4);
			mtrx.TransformPoints(frame2, 5);
			mtrx.TransformPoints(frame3, 25);
			mtrx.TransformPoints(tube1, 6);
			mtrx.TransformPoints(tube2, 4);
			mtrx.TransformPoints(tube3, 4);
			mtrx.TransformPoints(back_arch, 30);
			mtrx.TransformPoints(front_arch, 25);
			mtrx.TransformPoints(degree_up, 4);
			mtrx.TransformPoints(degree_middle, 4);
			mtrx.TransformPoints(degree_down, 4);
			mtrx.TransformPoints(back_wheel_1, 8);
			mtrx.TransformPoints(back_wheel_2, 8);
			mtrx.TransformPoints(back_wheel_3, 8);
			mtrx.TransformPoints(front_wheel_1, 8);
			mtrx.TransformPoints(front_wheel_2, 8);
			mtrx.TransformPoints(front_wheel_3, 8);
			mtrx.TransformPoints(bucket_1, 21);
			mtrx.TransformPoints(bucket_2, 21);
			mtrx.TransformPoints(ellipse1, 8);
			mtrx.TransformPoints(ellipse2, 8);
		}

		if (Time > Timing_1 && Time < Timing_2) // опускаем ковш
		{
			mtrx.RotateAt(-3, pnt[0]);

			mtrx.TransformPoints(bucket_1, 21);
			mtrx.TransformPoints(bucket_2, 21);
			mtrx.TransformPoints(ellipse1, 8);
		}

		if (Time > Timing_2 && Time < Timing_3) // фиксируем ковш у земли
		{
			mtrx.RotateAt(-3, pnt1[0]);

			mtrx.TransformPoints(bucket_2, 21);
		}

		if (Time > Timing_3 && Time < Timing_4) // двигаемся влево
		{
			mtrx.Translate(-2, 0);

			mtrx.TransformPoints(cabin, 6);
			mtrx.TransformPoints(roof, 4);
			mtrx.TransformPoints(flashlight, 4);
			mtrx.TransformPoints(post, 4);
			mtrx.TransformPoints(frame1, 4);
			mtrx.TransformPoints(frame2, 5);
			mtrx.TransformPoints(frame3, 25);
			mtrx.TransformPoints(tube1, 6);
			mtrx.TransformPoints(tube2, 4);
			mtrx.TransformPoints(tube3, 4);
			mtrx.TransformPoints(back_arch, 30);
			mtrx.TransformPoints(front_arch, 25);
			mtrx.TransformPoints(degree_up, 4);
			mtrx.TransformPoints(degree_middle, 4);
			mtrx.TransformPoints(degree_down, 4);
			mtrx.TransformPoints(back_wheel_1, 8);
			mtrx.TransformPoints(back_wheel_2, 8);
			mtrx.TransformPoints(back_wheel_3, 8);
			mtrx.TransformPoints(front_wheel_1, 8);
			mtrx.TransformPoints(front_wheel_2, 8);
			mtrx.TransformPoints(front_wheel_3, 8);
			mtrx.TransformPoints(bucket_1, 21);
			mtrx.TransformPoints(bucket_2, 21);
			mtrx.TransformPoints(ellipse1, 8);
			mtrx.TransformPoints(ellipse2, 8);
		}

		if (Time > Timing_4 && Time < Timing_5) // подгребаем землю
		{
			mtrx.RotateAt(3, pnt2[0]);

			mtrx.TransformPoints(bucket_2, 21);
			mtrx.TransformPoints(layer1, 4);
			mtrx.TransformPoints(layer2, 5);
		}

		if (Time > Timing_5 && Time < Timing_6) // поднимаем ковш
		{
			mtrx.RotateAt(3, pnt3[0]);

			mtrx.TransformPoints(bucket_1, 21);
			mtrx.TransformPoints(bucket_2, 21);
			mtrx.TransformPoints(ellipse1, 8);
			mtrx.TransformPoints(layer2, 5);
			mtrx.TransformPoints(gorka2, 19);
		}

		if (Time > Timing_6 && Time < Timing_7) // поднимаем ковш
		{
			mtrx.RotateAt(3, pnt3[0]);

			mtrx.TransformPoints(bucket_1, 21);
			mtrx.TransformPoints(bucket_2, 21);
			mtrx.TransformPoints(ellipse1, 8);
			mtrx.TransformPoints(layer3, 7);
			mtrx.TransformPoints(gorka2, 19);

			mtrx.Translate(1000, 0);

			mtrx.TransformPoints(kv, 4);
		}

		if (Time > Timing_7 && Time < Timing_8) // поднимаем ковш
		{
			mtrx.RotateAt(3, pnt3[0]);

			mtrx.TransformPoints(bucket_1, 21);
			mtrx.TransformPoints(bucket_2, 21);
			mtrx.TransformPoints(ellipse1, 8);
			mtrx.TransformPoints(gorka2, 19);
		}

		if (Time > Timing_8 && Time < Timing_9) // двигаемся вправо
		{
			mtrx.Translate(2, 0);

			mtrx.TransformPoints(cabin, 6);
			mtrx.TransformPoints(roof, 4);
			mtrx.TransformPoints(flashlight, 4);
			mtrx.TransformPoints(post, 4);
			mtrx.TransformPoints(frame1, 4);
			mtrx.TransformPoints(frame2, 5);
			mtrx.TransformPoints(frame3, 25);
			mtrx.TransformPoints(tube1, 6);
			mtrx.TransformPoints(tube2, 4);
			mtrx.TransformPoints(tube3, 4);
			mtrx.TransformPoints(back_arch, 30);
			mtrx.TransformPoints(front_arch, 25);
			mtrx.TransformPoints(degree_up, 4);
			mtrx.TransformPoints(degree_middle, 4);
			mtrx.TransformPoints(degree_down, 4);
			mtrx.TransformPoints(back_wheel_1, 8);
			mtrx.TransformPoints(back_wheel_2, 8);
			mtrx.TransformPoints(back_wheel_3, 8);
			mtrx.TransformPoints(front_wheel_1, 8);
			mtrx.TransformPoints(front_wheel_2, 8);
			mtrx.TransformPoints(front_wheel_3, 8);
			mtrx.TransformPoints(bucket_1, 21);
			mtrx.TransformPoints(bucket_2, 21);
			mtrx.TransformPoints(ellipse1, 8);
			mtrx.TransformPoints(ellipse2, 8);
			mtrx.TransformPoints(gorka2, 19);
		}

		g.FillRectangle(&air_brush, 0, 0, 1100, 520);
		g.FillClosedCurve(&hBr2, gorka2, 19);
		g.FillPolygon(&air_brush, kv, 4);
		g.FillRectangle(&brown_brush, 0, 507, 1100, 200);
		g.FillClosedCurve(&hBr2, gorka1, 9);
		g.FillPolygon(&air_brush, layer3, 7);
		g.FillPolygon(&brown_brush, kv1, 4);
		g.FillClosedCurve(&hBr2, gorka, 21);
		g.FillPolygon(&brown_brush, layer1, 4);
		g.FillPolygon(&brown_brush, layer2, 5);
		g.FillPolygon(&lightblue_brush, cabin, 6);
		g.DrawPolygon(&black_pen, cabin, 6);
		g.FillPolygon(&lightgray_brush, roof, 4);
		g.FillPolygon(&orange_brush, flashlight, 4);
		g.FillPolygon(&black_brush, post, 4);
		g.FillPolygon(&black_brush, frame1, 4);
		g.FillPolygon(&green_brush, frame2, 5);
		g.FillPolygon(&green_brush, frame3, 25);

		g.FillClosedCurve(&lightgray_brush, tube1, 6);
		g.FillPolygon(&hBr3, tube2, 4);
		g.FillPolygon(&lightgray_brush, tube3, 4);

		g.FillClosedCurve(&gray_brush, back_arch, 30);
		g.FillClosedCurve(&gray_brush, front_arch, 25);
		g.FillPolygon(&gray_brush, degree_up, 4);
		g.FillPolygon(&gray_brush, degree_middle, 4);
		g.FillPolygon(&gray_brush, degree_down, 4);
		g.FillClosedCurve(&hBr1, back_wheel_1, 8);
		g.FillClosedCurve(&red_brush, back_wheel_2, 8);
		g.FillClosedCurve(&black_brush, back_wheel_3, 8);
		g.FillClosedCurve(&hBr1, front_wheel_1, 8);
		g.FillClosedCurve(&red_brush, front_wheel_2, 8);
		g.FillClosedCurve(&black_brush, front_wheel_3, 8);
		g.FillClosedCurve(&gray_brush, bucket_2, 21);
		g.FillPolygon(&lightgray_brush, bucket_1, 21);
		g.DrawClosedCurve(&black_pen, ellipse1, 8);
		g.DrawClosedCurve(&black_pen, ellipse2, 8);


		/*===================================================*/




		g.FillPolygon(&red_brush, krug, 9);

		if (Time < Timing_1_1)
		{

			krug[0] = Tween(krug[0], krug[1], 0.01);
			krug[1] = Tween(krug[1], krug[2], 0.01);
			krug[2] = Tween(krug[2], krug[3], 0.01);
			krug[3] = Tween(krug[3], krug[4], 0.01);
			krug[4] = Tween(krug[4], krug[5], 0.01);
			krug[5] = Tween(krug[5], krug[6], 0.01);
			krug[6] = Tween(krug[6], krug[7], 0.01);
			krug[7] = Tween(krug[7], krug[8], 0.01);
			krug[8] = krug[0];
;
		}
		/*=======================================================*/

		if (Time > Timing_0)
		{
			g.DrawImage(image, 910, 410, 161, 150);
		}
	}
	graph.DrawImage(&backbuffer, rect); // выводим на экран готовое изображение из буфера
} // Display

Gdiplus::PointF Tween(const Gdiplus::PointF& A, const Gdiplus::PointF& B, float t) // Функция нахождения промежуточных точек
{
	return Gdiplus::PointF(A.X * (1.f - t) + B.X * t, A.Y * (1.f - t) + B.Y * t);
}

/*void Tween(const Gdiplus::PointF* A, const Gdiplus::PointF* B, Gdiplus::PointF* P, int count, float t)
{
	for (int i = 0; i < count; i++)
		P[i] = Tween(A[i], B[i], t);
}*/