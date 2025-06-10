#include "ObjectChest.h"

void ObjectChest::Start()
{
	texture = LoadTexture("Chest.png");

	//Posicion inicial
	position = { 500, 500 };//Cambiar posición
	float speed = 100;
}

void ObjectChest::Update()
{
}

void ObjectChest::Draw()
{
	DrawTexture(texture, position.x - 200, position.y - 200, WHITE);
}
