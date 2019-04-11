/*
;|**********************************************************************;
;* Project           : Basic_C_GUI
;*
;* Program name      : basicTimer.c
;*
;* Author            : SIO TOU LAI (laisiotou1997@gmail.com)
;*
;* Date created      : 11/04/2019
;*
;* Version           : Internal
;*
;* Copyright         : GNU GENERAL PUBLIC LICENSE Version 3
;*
;* Purpose           : Change BK color each second.
;*
;* Revision History  :
;*
;* Date        Author      Ref    Revision (Date in DDMMYYYY format)
;* 11042019    lst97       1      First release
;*
;* Known Issue       :
;*
;|**********************************************************************;
*/

#include <windows.h>

//DEFINE
#define ID_TIMER 1

//DECLAR
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//void CALLBACK TimerProc(HWND, UINT, UINT, DWORD);					[MATHOD TWO]

//DATA
static char szAppName[] = "Basic Timer";
static char szErrorMessage[] = "This program only run on Windows NT!";
static int nClientWidth = 640;
static int nClientHeight = 480;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int nCmdShow) {

	//WNDCLASS -> RegisterClass -> CreateWindow -> ShowWindow -> UpdateWindow -> MsgLoop

	WNDCLASS wndClass;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						//Redraws the entire window if a movement or size adjustment changes.
	wndClass.lpfnWndProc = WndProc;									//A pointer to the window procedure.
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;									//A handle to the instance that contains the window procedure for the class.
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//A handle to the class background brush.
	wndClass.lpszMenuName = NULL;									//The resource name of the class menu, as the name appears in the resource file.
	wndClass.lpszClassName = szAppName;								//The maximum length for lpszClassName is 256.

	if (!RegisterClass(&wndClass)) {								//Value is zero if Register FAIL (!0) = TRUE;
		MessageBox(NULL, szErrorMessage, szAppName, MB_ICONERROR);
		return 0;
	}

	HWND hWnd;
	hWnd = CreateWindow(szAppName, szAppName, WS_TILED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, nClientWidth, nClientHeight, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, SW_SHOWNORMAL);		// nCmdShow
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	//DATA
	HDC hDc;
	PAINTSTRUCT ps;
	static BOOL boolDrawing, boolValidRec;
	static POINT ptStart, ptEnd, ptRecStart, ptRecEnd;

	//CODE
	switch (message) {
	case WM_CREATE:
		SetTimer(hWnd, ID_TIMER, 1000, NULL);
		// SetTimer(hWnd, ID_TIMER, 1000, TimerProc);			[MATHOD TOW]
		return 0;

	case WM_TIMER:
		SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)));
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;

	case WM_PAINT:
		hDc = BeginPaint(hWnd, &ps);
		if (boolValidRec) {
			SelectObject(hDc, GetStockObject(BLACK_BRUSH));
			Rectangle(hDc, ptRecStart.x, ptRecStart.y, ptRecEnd.x, ptRecEnd.y);
		}

		if (boolDrawing) {
			SetROP2(hDc, R2_NOT);
			SelectObject(hDc, GetStockObject(NULL_BRUSH));
			Rectangle(hDc, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);
		}

		EndPaint(hWnd, &ps);
		return 0;

	case WM_CLOSE:
		switch (MessageBox(hWnd, TEXT("Do you really want to quit?"), TEXT("Message"), MB_YESNO | MB_ICONQUESTION)) {
		case IDYES:
			KillTimer(hWnd, ID_TIMER);
			PostQuitMessage(0);
			return 0;
		default:
			break;
		}
		return 0;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

/*  [MATHOD TWO] (CALLBACK)
	//void CALLBACK TimerProc(HWND hWnd, UINT message, UINT iTimerID, DWORD dwTime) {
	//	SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)));
	//	InvalidateRect(hWnd, NULL, TRUE);
	//}
*/
