#include <windows.h>
//#include "stdafx.h"
#include "src/CEngine.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE* hInst;
HWND hOkno;
CEngine* eng;
bool end = false;

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmd, INT nShow)
{
	hInst = &hInstance;
	WNDCLASSEX wc;
	wc.cbSize = sizeof(wc);
	wc.hInstance = *hInst;
	wc.lpszClassName = L"MirkoCraft";
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = WndProc;
	wc.style = 0;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL; //(HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	RegisterClassEx(&wc);
	RECT r = { 0, 0, 960, 630 };
	AdjustWindowRectEx(&r, WS_SYSMENU, FALSE, 0);
	hOkno = CreateWindowEx(0, L"MirkoCraft", L"MirkoCraft 06_12_2014", WS_SYSMENU, GetSystemMetrics(SM_CXSCREEN) / 2 - 480, GetSystemMetrics(SM_CYSCREEN) / 2 - 315, r.right - r.left, r.bottom - r.top, 0, 0, *hInst, NULL);
	ShowWindow(hOkno, SW_SHOW);
	eng = CEngine::createEngine(960,630,hOkno);
	eng->load();
	//eng->setResolution(960, 630); // default
	MSG msgs;
	while (!end) {
		if (PeekMessage(&msgs, hOkno, 0, 0, PM_REMOVE)) {
			if (msgs.message == WM_QUIT) {
				end = true;
				//MessageBox(0, L"quit", 0, 0);
			}
			TranslateMessage(&msgs);
			DispatchMessage(&msgs);
		}
		else {
			eng->frame();
		}
	}
	delete eng;
	return msgs.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wPar, LPARAM lPar)
{
	switch (msg)
	{
	case WM_TIMER:
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wPar, lPar);
	}
	return 0;
}
