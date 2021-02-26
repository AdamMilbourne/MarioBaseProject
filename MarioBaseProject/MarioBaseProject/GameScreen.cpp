#include <SDL.h>
#include "GameScreen.h"
#include <iostream>
using namespace std;


//constructor
GameScreen::GameScreen(SDL_Renderer* renderer)
{
	m_renderer = renderer;
}

//destructor
GameScreen::~GameScreen()
{
	m_renderer = nullptr;
}

void GameScreen::Render() {}
void GameScreen::Update(float deltaTime, SDL_Event e) {}