/* +--------------------------------------------------------------+ 
   | CEngine - engine of the game. DirectX <--> game interaction. |
   | Class that puts the game together.                           |
   +--------------------------------------------------------------+ */

#ifndef __CEngine_h_
#define __CEngine_h_
#include <windows.h>
#include <d3d9.h> // old but good. this thing doesn't needs any better than DX9.
#include "CGame.h"

class CEngine {
	private:
		static CEngine* __inst;
		int width;
		int height;
		HWND hWnd;
		LPDIRECT3D9 pD3D9;
		LPDIRECT3DDEVICE9 pD3DDev;
		LPDIRECT3DVERTEXBUFFER9 pD3DVB;
		CGame* game;
		void __fillVB();
	public:
		CEngine(int,int,HWND);
		CEngine();
		~CEngine();
		static CEngine* createEngine(int, int, HWND);
		static CEngine* instance();
		void load();
		void setResolution(int,int);
		void setWindow(HWND);
		void frame();
		void drawBlock(int, int, int);
};

#endif // __CEngine_h_
