#include "Enemy.h"

void Enemy::Start()
{
	texture = LoadTexture("Enemy.png");

	//Posicion inicial
	position = { x, y };//Cambiar posición
	float speed = 100;
}

void Enemy::Update()
{
	//Caminar hacia el target que sería el player
	if (playerFollow != nullptr)
	{
		Vector2 dir = Vector2Subtract(playerFollow->position, position);

		float distance = Vector2Length(dir);

		if (distance > 50)
		{
			dir = Vector2Normalize(dir);
			position = Vector2Add(position, Vector2Scale(dir, speed * GetFrameTime()));
		}
	}

}

void Enemy::Draw()
{
	DrawTexture(texture, position.x, position.y, WHITE);
	DrawText(getUID().c_str(), position.x, position.y - 20, 10, WHITE);
}
