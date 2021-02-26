#include "CharacterMario.h"
CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagepath, Vector2D start_position) : Character(renderer, imagepath, start_position)
{
	m_renderer = renderer;
}
CharacterMario::~CharacterMario()
{
	m_renderer = nullptr;
}

void CharacterMario::Update(float deltatime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			//m_position.x = m_position.x - 1;
			//m_facing_direction = FACING_LEFT;
			m_moving_left = true;
			cout << "left key pressed" << endl;

			break;
		case SDLK_RIGHT:
			//m_position.x = m_position.x + 1;
			//m_facing_direction = FACING_RIGHT;
			m_moving_right = true;
			cout << "right key pressed" << endl;
			break;

			if (m_can_jump == true)
			{
		case SDLK_UP:
			Jump();
			}
		}

		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			//m_position.x = m_position.x - 1;
			//m_facing_direction = FACING_LEFT;
			m_moving_left = false;
			cout << "left key up" << endl;

			break;
		case SDLK_RIGHT:
			//m_position.x = m_position.x + 1;
			//m_facing_direction = FACING_RIGHT;
			m_moving_right = false;
			cout << "right key up" << endl;
			break;
		}
		break;
	}
	Character::Update(deltatime, e);
}

