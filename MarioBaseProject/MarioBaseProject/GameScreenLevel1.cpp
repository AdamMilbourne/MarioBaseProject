#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "Collisions.h"
using namespace std;

//constructor
GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	m_renderer = renderer;
	SetUpLevel1();
}

//destructor
GameScreenLevel1::~GameScreenLevel1()
{
	m_renderer = nullptr;

	delete m_background_texture;
	m_background_texture = nullptr;

	delete Mario;
	Mario = nullptr;

	delete Luigi;
	Luigi = nullptr;

	m_level_map = nullptr;
}


void GameScreenLevel1::Render()
{
	//draw background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
	Mario->Render();
	Luigi->Render();


}


void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	//update character
	Mario->Update(deltaTime, e);
	Luigi->Update(deltaTime, e);
	if (Collisions::Instance()->Circle(Mario, Luigi))
	{
		cout << "Circle hit" << endl;
	}
	if (Collisions::Instance()->Box(Mario->GetCollisionBox(), Luigi->GetCollisionBox()))
	{
		cout << "box hit" << endl;
	}
}

bool GameScreenLevel1::SetUpLevel1()
{
	SetLevelMap();
	//set up player
	Mario = new CharacterMario(m_renderer, "images/Mario.png", Vector2D(64, 330), m_level_map);

	Luigi = new CharacterLuigi(m_renderer, "images/Luigi.png", Vector2D(64, 330), m_level_map);


	//Load Texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("images/BackgroundMB.png"))
	{
		cout << "Failed to load background texture!" << endl;
		return false;
	}

	

}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
								     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
								     { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
								     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
								     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
								     { 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
								     { 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
								     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
								     { 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
								     { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
								     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
								     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
								     { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	//clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}
	//set new one
	m_level_map = new LevelMap(map);
}