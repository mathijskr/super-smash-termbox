#include "player.h"

/* Initialize player. */
void Player__init(Player *this, int x, int y, int color)
{
	this->dead = false;

	this->x = x;
	this->y = y;

	this->vx = 0.0f;
	this->vy = 0.0f;

	this->ax = 0.0f;
	this->ay = 0.0f;

	this->direction = DIRECTION_RIGHT;

	this->color = color;

	this->bullet = Bullet__create('@', this->color);
}

/* Construct a new player. */
Player* Player__create(int x, int y, int color)
{
	/* Allocate memory. */
	struct Player* result = (struct Player*) malloc(sizeof(struct Player));

	/* Set function pointers. */
	result->init = Player__init;
	result->moveLeft = Player__moveLeft;
	result->moveRight = Player__moveRight;
	result->jump = Player__jump;
	result->physics = Player__physics;
	result->shoot = Player__shoot;
	result->draw = Player__draw;
	result->destroy = Player__destroy;

	/* Initialize a new player. */
	result->init(result, x, y, color);

	return result;
}

void Player__physics(Player *this, int floor)
{
	/* Increase or decrease speed. */
	this->vx += this->ax;
	this->vy += this->ay;

	/* Increase or decrease position. */
	this->x += this->vx;
	this->y += this->vy;

	if(this->y >= floor - PLAYER_SIZE_Y / 2.0f)
	{
		this->vy = 0.0f;
		this->ay = 0.0f;

		this->y = floor - PLAYER_SIZE_Y / 2.0f;
	}
	/* Let player fall down. */
	else
		this->ay = GRAVITY;


	if(this->bullet->exists == true)
	{
		this->bullet->update(this->bullet);
		this->bullet->draw(this->bullet);
	}
}

void Player__moveLeft(Player *this)
{
	this->x -= PLAYER_MOVEMENT_SPEED;
	this->direction = DIRECTION_LEFT;
}

void Player__moveRight(Player *this)
{
	this->x += PLAYER_MOVEMENT_SPEED;
	this->direction = DIRECTION_RIGHT;
}

void Player__jump(Player *this, int floor)
{
	/* Check if player is standing still. */
	if(this->vy <= 0.001f && this->vy >= -0.001f)
		this->vy -= JUMP_POWER;
}

void Player__shoot(Player *this)
{
	if(this->bullet->exists == false)
		this->bullet->shoot(this->bullet, this->x, this->y, this->direction);
}

void Player__draw(Player *this)
{
	if(!this->dead)
		for(int i = 0; i < 3; i++)
			for(int j = 0; j < 3; j++)
				tb_change_cell(this->x + j, this->y + i, Player__graphics[i][j], this->color, BACKGROUND_COLOR);
	else
		for(int i = 0; i < 3; i++)
			for(int j = 0; j < 3; j++)
				tb_change_cell(this->x + j, this->y + i, Player__graphics_dead[i][j], this->color, BACKGROUND_COLOR);
}

/* Destructor. */
void Player__destroy(Player* this)
{
	if(this)
		free(this);
	if(this->bullet)
		this->bullet->destroy(this->bullet);
}
