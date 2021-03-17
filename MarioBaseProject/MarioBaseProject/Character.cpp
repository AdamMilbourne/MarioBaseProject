#include "Character.h"
#include "constants.h"

Character::Character(SDL_Renderer* renderer, string imagepath, Vector2D start_position, LevelMap* map)
{
	m_renderer = renderer;

	m_position = start_position;

	m_texture = new Texture2D(m_renderer);
	if (!m_texture->LoadFromFile(imagepath))
	{
		cout << "Failed to load Mario Image" << endl;
	}

	m_facing_direction = FACING_RIGHT;

	m_moving_left = false;
	m_moving_right = false;

	m_collision_radius = 15.0f;

	m_current_level_map = map;
}
Character::~Character()
{
	m_renderer = nullptr;
}

float Character::GetCollisionRadius()
{
	return m_collision_radius;
}

void Character::Render()
{
	m_texture->Render(m_position, SDL_FLIP_NONE);

	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(m_position, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
	}
}
void Character::Update(float deltatime, SDL_Event e)
{
	//deal with jumping first
	if (m_jumping)
	{
		//adjust position
		m_position.y -= m_jump_force * deltatime;

		//reduce jump force
		m_jump_force -= JUMP_FORCE_DECREMENT * deltatime;

		//is jump force 0?
		if (m_jump_force <= 0.0f)
			m_jumping = false;
	}

	if (m_moving_left)
	{
		MoveLeft(deltatime);
	}
	else if (m_moving_right)
	{
		MoveRight(deltatime);
	}

	//collisions position variables 
	int centralX_position = (int)(m_position.x + (m_texture->GetWidth() * 0.5)) / TILE_WIDTH;
	int foot_position = (int)(m_position.y + m_texture->GetHeight()) / TILE_HEIGHT;
	//deals with gravity 
	if (m_current_level_map->GetTileAt(foot_position, centralX_position) == 0)
	{
		AddGravity(deltatime);
	}
	else
	{
		//collided with ground to jump again
		m_can_jump = true;
	}
}
void Character::SetPosition(Vector2D new_position)
{
	m_position = new_position;

}
Vector2D Character::GetPostion()
{
	return m_position;
}

void Character::MoveRight(float deltatime)
{
	m_position.x += deltatime * MOVEMENTSPEED;
	m_facing_direction = FACING_RIGHT;
}

void Character::MoveLeft(float deltatime)
{
	m_position.x -= deltatime * MOVEMENTSPEED;
	m_facing_direction = FACING_LEFT;
}

void Character::AddGravity(float deltatime)
{
	if (m_position.y + MARIO_HEIGHT <= SCREEN_HEIGHT)
	{
		m_position.y += GRAVITY * deltatime;
	}
	else
	{
		m_can_jump = true;
	}
}

void Character::Jump()
{
	if (!m_jumping)
	{
		m_jump_force = INITIAL_JUMP_FORCE;
		m_jumping = true;
		m_can_jump = false;
	}

}
