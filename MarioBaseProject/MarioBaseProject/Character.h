#pragma once
#include <SDL.h>
#include <iostream>
#include "Commons.h"
#include "Texture2D.h"
#include "LevelMap.h"
using namespace std;

class Texture2D;

class Character
{
protected:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;

	float m_movement_speed; //had to add myself might be wrong
	FACING m_facing_direction; //might have to put back in private but putting here is only thing that worked(was origianlly in private)

	bool m_moving_left;
	bool m_moving_right;
	bool m_jumping;
	bool m_can_jump;
	float m_jump_force;
	float m_collision_radius;
	//week 11 stuff
	bool m_alive; // set true in character.cpp might be wrong ?


	virtual void MoveLeft(float deltatime);
	virtual void MoveRight(float deltatime);
	virtual void AddGravity(float deltatime);
	virtual void Jump();

public:
	Character(SDL_Renderer* renderer, string imagepath, Vector2D start_position, LevelMap* map);
	~Character();

	virtual void Render();
	virtual void Update(float deltatime, SDL_Event e);
	void SetPosition(Vector2D new_position);
	Vector2D GetPostion();

	float GetCollisionRadius();

	Rect2D GetCollisionBox() { return Rect2D(m_position.x, m_position.y, m_texture->GetWidth(), m_texture->GetHeight()); }

	bool IsJumping() { return m_jumping; }
	void CancelJump() { m_jumping = false; } 

	bool SetAlive(bool is_alive) {m_alive = is_alive; return m_alive;}
	bool GetAlive() { return m_alive; }
private:

	 
	LevelMap* m_current_level_map;
};

