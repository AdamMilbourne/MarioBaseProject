#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H
#include "GameScreen.h"
#include "Commons.h"
#include "Character.h"
#include "LevelMap.h"

class CharacterLuigi;
class CharacterMario;
class Texture2D;
class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
private:
	Texture2D* m_background_texture;
	bool SetUpLevel1();
	CharacterMario* Mario;
	CharacterLuigi* Luigi;
	//week 9
	void SetLevelMap();
	LevelMap* m_level_map;
};
#endif //_GAMESCREENLEVEL1_H
#include "GameScreen.h"
#include "Commons.h"
#include "Character.h"