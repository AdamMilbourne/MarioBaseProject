#include "CharacterLuigi.h"
CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, string imagepath, Vector2D start_position) : Character(renderer, imagepath, start_position)
{
	m_renderer = renderer;
}
CharacterLuigi::~CharacterLuigi()
{
	m_renderer = nullptr;
}

void CharacterLuigi::Update(float deltatime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			//m_position.x = m_position.x - 1;
			//m_facing_direction = FACING_LEFT;
			m_moving_left = true;
			cout << "a pressed" << endl;

			break;
		case SDLK_d:
			//m_position.x = m_position.x + 1;
			//m_facing_direction = FACING_RIGHT;
			m_moving_right = true;
			cout << "d pressed" << endl;
			break;

			if (m_can_jump == true)
			{
		case SDLK_w:
			Jump();
			}
		}

		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			//m_position.x = m_position.x - 1;
			//m_facing_direction = FACING_LEFT;
			m_moving_left = false;
			cout << "a key up" << endl;

			break;
		case SDLK_d:
			//m_position.x = m_position.x + 1;
			//m_facing_direction = FACING_RIGHT;
			m_moving_right = false;
			cout << "d key up" << endl;
			break;
		}
		break;
	}
	Character::Update(deltatime, e);
}