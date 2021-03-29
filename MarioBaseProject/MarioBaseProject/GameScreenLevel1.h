#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H
#include "GameScreen.h"
#include "Commons.h"
#include "Character.h"
#include "LevelMap.h"
#include <vector>


class PowBlock;
class CharacterLuigi;
class CharacterMario;
class CharacterKoopa;
class Texture2D;
class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	void UpdatePOWBlock();
private:
	Texture2D* m_background_texture;
	bool SetUpLevel1();
	CharacterMario* Mario;
	CharacterLuigi* Luigi;
	//week 9
	void SetLevelMap();
	LevelMap* m_level_map;
	PowBlock* m_pow_block;
	//week 10 shake screen
	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos; 
	void DoScreenShake();

	//Tutorial 11 Koopa stuff
	void UpdateEnemies(float deltatime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	vector<CharacterKoopa*> m_enemies;

};
#endif //_GAMESCREENLEVEL1_H
#include "GameScreen.h"
#include "Commons.h"
#include "Character.h"