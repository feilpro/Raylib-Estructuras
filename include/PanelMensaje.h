#pragma once
#include "raylib.h"
#include <string>


enum PanelState
{
	hidden, moving, showing
};

class PanelMensaje
{
private:
	float timer;
	float desiredPositionY;
	PanelState state = hidden;

	Texture2D icon;
	bool hasIcon;



public:
	Vector2 position;
	Vector2 size;
	int timeOnScreen;
	std::string message;


	
	PanelMensaje(float posX, float width, float height, int _timeOnScreen)
	{
		position = { posX, -height }; //Start off-screen
		size = { width, height };
		timeOnScreen = _timeOnScreen;
		timer = 0;
		desiredPositionY = -height;
		state = hidden;
	}

	PanelState GetState()
	{
		return state;
	}

	void update()
	{
		if (state == hidden)
		{
			return;
		}
		else if (state == moving)
		{
			//interpolacion de movimiento
			if (position.y != desiredPositionY)
			{
				//lerp position
				position.y += (desiredPositionY - position.y) * 1.0f * GetFrameTime();

			}
			if (fabs(position.y - desiredPositionY) < 0.1f)
			{
				position.y = desiredPositionY;

				// Verifica si el mensaje se está ocultando (desaparece)
				if (desiredPositionY < 0)
				{
					state = hidden; // ya salió de la pantalla, está oculto
				}
				else
				{
					state = showing; // entró a la pantalla, empieza a mostrarse
					timer = 0;
				}
			}

		}
		else if (state == showing)
		{
			timer += GetFrameTime();
			if (timer > timeOnScreen)
			{

				// Unload la textura anterior antes de ocultar
				if (hasIcon)
				{
					UnloadTexture(icon);
					hasIcon = false;
				}

				//start moving
				desiredPositionY = -size.y - 10; //move off-screen
				state = moving;
			}
		}

	}


	void draw()
	{
		// Dibuja el fondo del panel
		DrawRectangle(position.x, position.y, size.x, size.y, BEIGE);
		DrawRectangleLines(position.x, position.y, size.x, size.y, DARKBLUE);

		float iconSize = 40;
		float padding = 10;
		float textOffsetX = position.x + padding;

		// Dibuja la imagen si hay una cargada
		if (hasIcon)
		{
			DrawTextureEx(icon, { position.x + padding, position.y + padding }, 0, iconSize / icon.width, WHITE);
			textOffsetX += iconSize + padding; // corre el texto a la derecha del ícono
		}

		// Dibuja el texto del mensaje
		DrawText(message.c_str(), textOffsetX, position.y + padding, 20, DARKGRAY);

	}
	
	void Show(std::string msg)
	{
		//Cada vez que se mande a llamar show, guardar en un stack el mensaje deseado


		state = moving;
		timer = 0;
		message = msg;
		desiredPositionY = 10; // 10 pixels from the top of the screen
		position.y = -size.y - 10; //start off-screen


		std::string ruta = "resources/" + msg + ".png";
		icon = LoadTexture(ruta.c_str());
		hasIcon = true;


	}


};

