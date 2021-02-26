#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"

//constructor
GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startscreen)
{
	m_renderer = renderer;
	m_current_screen = nullptr;
	ChangeScreen(startscreen);
}

//destructor
GameScreenManager::~GameScreenManager()
{
	m_renderer = nullptr;
	delete m_current_screen;
	m_current_screen = nullptr;
}

void GameScreenManager::Render()
{
	m_current_screen->Render();
}
void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	m_current_screen->Update(deltaTime, e);
}

void GameScreenManager::ChangeScreen(SCREENS new_screen)
{
	//clear up the old screen
	if (m_current_screen != nullptr)
	{
		delete m_current_screen;
	}
	GameScreenLevel1* tempscreen;

	switch (new_screen)
	{
	case SCREEN_LEVEL1:
		tempscreen = new GameScreenLevel1(m_renderer);
		m_current_screen = (GameScreen*)tempscreen;
		tempscreen = nullptr;
	default:;
	}
}