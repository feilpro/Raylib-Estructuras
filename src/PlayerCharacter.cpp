#include "PlayerCharacter.h"


void PlayerCharacter::Start()
{
	texture = LoadTexture("conejito.png");
	textureFoots = LoadTexture("FootPrints.png");
	inventory = new Inventory();

	//Posicion inicial
	position = { 100, 100 };
	float speed = 100;


	scrollBorder = 64;

}

void PlayerCharacter::Draw()
{
	heap.drawFootprints(position, textureFoots);
	DrawTexture(texture, position.x, position.y, WHITE);
	DrawText("PLAYER", position.x, position.y - 40, 10, WHITE);
	if (drawDebugUID)
	{
		DrawText(getUID().c_str(), position.x, position.y - 20, 10, WHITE);

	}

	//hud
	DrawRectangle(10, 10, 100, 30, WHITE);

	if (inventory != nullptr && inventory->currentItem != nullptr)
	{
		DrawText(inventory->currentItem->data->name.c_str(), 20, 20, 10, BLACK);
	}
	else
	{
		DrawText("EMPRT", 20, 20, 10, BLACK);
	}




	DrawText("Inventory", 10, 10, 10, BLACK);
}

void PlayerCharacter::Update()
{
	bool moved = false;

	if (IsKeyDown(KEY_D))
	{
		position.x += speed * GetFrameTime();
		moved = true;
		if (position.x > GetScreenWidth() - scrollBorder)
		{
			position.x = GetScreenWidth() - scrollBorder;
			cameraOffset.x += speed * GetFrameTime();
		}
	}
	if (IsKeyDown(KEY_A))
	{
		position.x -= speed * GetFrameTime();
		moved = true;
		if (position.x < scrollBorder)
		{
			position.x = scrollBorder;
			cameraOffset.x -= speed * GetFrameTime();
		}
	}
	if (IsKeyDown(KEY_W))
	{
		position.y -= speed * GetFrameTime();
		moved = true;
		if (position.y < scrollBorder)
		{
			position.y = scrollBorder;
			cameraOffset.y -= speed * GetFrameTime();
		}
	}
	if (IsKeyDown(KEY_S))
	{
		position.y += speed * GetFrameTime();
		moved = true;
		if (position.y > GetScreenHeight() - scrollBorder)
		{
			position.y = GetScreenHeight() - scrollBorder;
			cameraOffset.y += speed * GetFrameTime();
		}
	}

	if (moved) {
		heap.insert(position, GetTime());
		heap.removeOldFootprints(2.0f);
	}

	if (IsKeyPressed(KEY_I))
	{
		//asume que siempre tiene inventory
		inventory->nextItem();

	}

	if (IsKeyPressed(KEY_O))
	{
		inventory->prevItem();
	}

}

