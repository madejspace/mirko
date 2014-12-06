#include "CEngine.h"
#include <stdlib.h>
#include "vertex.h"
#define MAX_VERTICES 3
//#include "../stdafx.h"

CEngine* CEngine::__inst = NULL;

CEngine* CEngine::instance()
{
	if (__inst == NULL) __inst = new CEngine();
	return __inst;
}

CEngine* CEngine::createEngine(int w, int h, HWND hWin)
{
	__inst = new CEngine(w, h, hWin);
	return __inst;
}

CEngine::CEngine()
{
	D3DPRESENT_PARAMETERS D3Dpp;
	pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (!pD3D9) {
		MessageBox(0, L"B³¹d - Direct3DCreate9()", L"B³¹d", MB_ICONERROR);
	}

	ZeroMemory(&D3Dpp, sizeof(D3Dpp));
	D3Dpp.Windowed = TRUE;
	D3Dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	if (FAILED(pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &D3Dpp, &pD3DDev)))
	{
		MessageBox(0, L"B³¹d - pD3D9->CreateDevice(...)", L"B³¹d", MB_ICONERROR);
		pD3D9->Release();
	}
}

CEngine::CEngine(int w,int h,HWND hWin)
{
	width = w;
	height = h;
	hWnd = hWin;
	D3DPRESENT_PARAMETERS D3Dpp;
	pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (!pD3D9) {
		MessageBox(0, L"B³¹d - Direct3DCreate9()", L"B³¹d", MB_ICONERROR);
	}

	ZeroMemory(&D3Dpp, sizeof(D3Dpp));
	D3Dpp.Windowed = TRUE;
	D3Dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	if (FAILED(pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &D3Dpp, &pD3DDev)))
	{
		MessageBox(0, L"B³¹d - pD3D9->CreateDevice(...)", L"B³¹d", MB_ICONERROR);
		pD3D9->Release();
	}
}

void CEngine::load()
{
	game = new CGame();
	pD3DDev->CreateVertexBuffer(3 * sizeof(vertex3), 0, CUSTOMFVF, D3DPOOL_MANAGED, &pD3DVB, NULL);
}

CEngine::~CEngine()
{
	delete game;
	pD3DVB->Release();
	pD3DDev->Release();
	pD3D9->Release();
	__inst = NULL;
}

void CEngine::setResolution(int w, int h)
{
	width = w; height = h;
}

void CEngine::setWindow(HWND hWin)
{
	hWnd = hWin;
}


void CEngine::__fillVB()
{
	VOID* data;
	pD3DVB->Lock(0, 0, (void**)&data, 0);

	pD3DVB->Unlock();
}

void CEngine::frame()
{
	pD3DDev->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_XRGB(74, 74, 200), 1.0f, 0);
	pD3DDev->BeginScene();

	game->frame();

	__fillVB();

	pD3DDev->SetFVF(CUSTOMFVF);
	pD3DDev->SetStreamSource(0, pD3DVB, 0, sizeof(vertex3));
	pD3DDev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, MAX_VERTICES / 3);

	pD3DDev->EndScene();

	pD3DDev->Present(0, 0, 0, 0);
}