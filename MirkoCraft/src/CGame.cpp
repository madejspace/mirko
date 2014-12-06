#include "CGame.h"
#include "CEngine.h"

CEngine* engine;

CGame::CGame()
{
	engine = CEngine::instance();
}

CGame::~CGame()
{

}

void CGame::frame()
{
	
}