#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "CharacterKoopa.h"
#include "Character.h"
#include "Collisions.h"
#include "PowBlock.h"
#include <Windows.h>
using namespace std;

//constructor
GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	m_renderer = renderer;
	SetUpLevel1();

	
}
//set start parameters


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

	delete m_pow_block;  
	m_pow_block = nullptr;

	m_enemies.clear();

}


void GameScreenLevel1::Render()
{

	//draw enemies
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Render();
	}

	//draw background
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);
	Mario->Render();
	Luigi->Render();

	m_pow_block->Render();
}


void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	if (m_screenshake)
	{
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 3.0f;

		if (m_shake_time <= 0.0f)
		{
			m_shake_time = false;
			m_background_yPos = 0.0f;
		}
	}
	UpdateEnemies(deltaTime, e); //might also be in wrong place test out later
	UpdatePOWBlock(); //might be wrong place in function but should be fine as update is called indefinately 
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
	
		CreateKoopaRight(Vector2D(50, 32), FACING_RIGHT, KOOPA_SPEED);
		CreateKoopaRight(Vector2D(100, 32), FACING_RIGHT, KOOPA_SPEED);
		CreateKoopaRight(Vector2D(200, 32), FACING_RIGHT, KOOPA_SPEED);
		CreateKoopaLeft(Vector2D(450, 32), FACING_LEFT, KOOPA_SPEED);
		CreateKoopaLeft(Vector2D(520, 32), FACING_LEFT, KOOPA_SPEED);
		CreateKoopaLeft(Vector2D(490, 32), FACING_LEFT, KOOPA_SPEED);
		

		

		

	

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

	m_pow_block = new PowBlock(m_renderer, m_level_map);
	m_screenshake = false;
	m_background_yPos = 0.0f;


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
								       { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } 
									 };

	//clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}
	//set new one
	m_level_map = new LevelMap(map);
}

void GameScreenLevel1::DoScreenShake()
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->TakeDamage();
	}
}

void GameScreenLevel1::UpdatePOWBlock()
{
	if (Collisions::Instance()->Box(m_pow_block->GetCollisionBox(),Mario->GetCollisionBox()))
	{
		if (m_pow_block->IsAvailable())
		{
			if (Mario->IsJumping())
			{
				DoScreenShake();
				cout << "pow block collision" << endl;
				m_pow_block->TakeHit();
				Mario->CancelJump();
			}
		}
	}
	if (Collisions::Instance()->Box(m_pow_block->GetCollisionBox(), Luigi->GetCollisionBox()))
	{
		if (m_pow_block->IsAvailable())
		{
			if (Luigi->IsJumping())
			{
				DoScreenShake();
				cout << "pow block collision" << endl;
				m_pow_block->TakeHit();
				Luigi->CancelJump();
			}
		}
	}
}

void GameScreenLevel1::UpdateEnemies(float deltatime, SDL_Event e)
{
	if (!m_enemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_enemies.size(); i++)
		{
			//check if the enemy is on the bottom row of tiles
			if (m_enemies[i]->GetPosition().y > 300.0f)
			{
				//is the enemy off screen to the left / right?
				if (m_enemies[i]->GetPosition().x < (float)(-m_enemies[i]->GetCollisionBox().width * 0.5f) || m_enemies[
					i]->GetPosition().x > SCREEN_WIDTH - (float)(m_enemies[i]->GetCollisionBox().width * 0.55f))
					m_enemies[i]->SetAlive(false);
			}
			//now do the update

			m_enemies[i]->Update(deltatime, e);

			//check to see if enemy collides with player
			if ((m_enemies[i]->GetPosition().y > 300.0f || m_enemies[i]->GetPosition().y <= 64.0f) && (m_enemies[i]->
				GetPosition().x < 64.0f || m_enemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//ignore collisions if behind pipe
			}
			else
			{
				if (Collisions::Instance()->Circle(m_enemies[i], Mario))
				{
					if (m_enemies[i]->GetInjured())
					{
						m_enemies[i]->SetAlive(false);
					}

					else
					{
						//MAKE MARIO DIE
						Mario->SetAlive(false);
					}

				}
				else if (Collisions::Instance()->Circle(m_enemies[i], Luigi))
				{
					if (m_enemies[i]->GetInjured())
					{
						m_enemies[i]->SetAlive(false);
					}

					else
					{
						//MAKE Luigi DIE
				
					
					}

				}
			}

			//if the enemy is no longer alive then schedule it for deletion
			if (!m_enemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}

		//remove dead enemies -1 each update

		if (enemyIndexToDelete != -1)
		{
			m_enemies.erase(m_enemies.begin() + enemyIndexToDelete);
		}
	}
	
}

void GameScreenLevel1::CreateKoopaRight(Vector2D position, FACING direction, float speed)
{
	
	Koopa = new CharacterKoopa(m_renderer, "images/Koopa.png", m_level_map, position, FACING_RIGHT, KOOPA_SPEED);
	m_enemies.push_back(Koopa);
}
void GameScreenLevel1::CreateKoopaLeft(Vector2D position, FACING direction, float speed)
{

	Koopa = new CharacterKoopa(m_renderer, "images/Koopa.png", m_level_map, position, FACING_LEFT, KOOPA_SPEED);
	m_enemies.push_back(Koopa);
}