//Alejandra Gabriela Sandoval Ruíz
/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <limits>
#include <cstdio>      
#include <cstdint>     
#include <map>


#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include "LLNode.h"
#include "LinkedList.h"
#include "Inventory.h"
#include "Item.h"
#include "PlayerCharacter.h"
#include "Stack.h"
#include "Queue.h"
#include "PanelMensaje.h"
#include "Enemy.h"
#include "MessageSystem.h"
#include "GameObject.h"
#include "ObjectChest.h"
#include "Heap.h"

extern "C"
{
#include "md5.h"

}

MessageSystem* messageSystem;

// Definición de mapa 2D
typedef std::vector<std::vector<int>> Map2D;

std::string selectedMap = "map1.txt";
std::string selectedMusic = "ILUETNI.XM";

void LoadMap(Map2D& _map, size_t _x, size_t _y, const std::string& filename)
{
	std::ifstream filemap(filename);
	if (filemap.is_open())
	{
		char c;
		for (size_t j = 0; j < _y; j++)
		{
			for (size_t i = 0; i < _x; i++)
			{
				filemap.get(c);
				if (filemap.eof())
				{
					std::cout << "final inesperado del archivo de mapa" << std::endl;
					return;
				}
				_map[j][i] = c - '0';
			}
			filemap.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
	else
	{
		std::cout << "no se pudo abrir el archivo de mapa :(" << std::endl;
		return;
	}
}

Music LoadBGM(const char* filename)
{
	return LoadMusicStream(filename);
	//const char* default = "LIRIUM.XM";
	//std::fstream configfile("config.ini");
	//if (configfile.is_open())
	//{
	//	std::string linea;
	//	char buffer[64];
	//	while (std::getline(configfile, linea))
	//	{
	//		std::cout << "Linea leída: " << linea << std::endl;
	//		char* llave = strtok((char*)linea.c_str(), "="); //con el token =
	//		if (strcmp("music", llave) == 0)
	//		{
	//			char* valor = strtok(NULL, "=");
	//			std::cout << "Se encontró la llave music" << std::endl;
	//		}
	//	}
	//}
	//else
	//{
	//	std::cout << "No se pudo abrir el config.ini, usando BGM default" << std::endl;
	//	return LoadMusicStream("LIRIUM.XM");
	//}
}


Vector2 posEnemy = { 0,0 };

//Arreglo de game objects
std::vector<GameObject*> gameobjects;

int main()
{
	//Tamaño de los tileSize
	int tileSize = 50;
	//Calcular ventana en base al tileSize
	int maxTilesH = 20;
	int maxTilesV = 16;


	// Create the window and OpenGL context
	InitWindow(maxTilesH * tileSize, maxTilesV * tileSize, "Tiles");

	InitAudioDevice();

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");


	// Ejemplo de vector
	std::vector<int> misdatos(15, 0);
	for (int i = 0; i < 15; i++)
		std::cout << "valor: " << misdatos[i] << std::endl;

	//Purueba de lista Ligada
	int a = 16;
	LLNode<int>* nodo = new LLNode<int>(&a);

	LinkedList<int>* lista = new LinkedList<int>(nodo);
	lista->AddNode(new int(28));
	lista->AddNode(new int(28));
	lista->RemoveLastNode();

	//Prueba de stack o pila
	Stack<float> pila(10);
	std::cout << "Pila vacía: " << std::boolalpha << pila.isEmpty() << std::endl;
	pila.push(1.0f);
	pila.push(3.1416f);
	pila.push(2.71828);
	std::cout << "num de elementos de la pila: " << pila.size() << std::endl;
	float temp = pila.pop();
	std::cout << "num de elementos de la pila: " << pila.size() << std::endl;

	//Prueba de Queue
	Queue<int> q = Queue<int>(3);
	std::cout << "Cola vacia: " << std::boolalpha << q.isEmpty() << std::endl;
	q.enqueue(10);
	q.enqueue(24);
	q.enqueue(42);
	q.enqueue(99);
	q.debugPrintContents();
	int temp2 = q.dequeue();
	temp2 = q.dequeue();
	temp2 = q.dequeue();
	q.debugPrintContents();
	q.enqueue(24);
	q.debugPrintContents();
	std::cout << "num de elementos de la cola: " << q.size() << std::endl;
	std::cout << "peek: " << q.dequeue() << std::endl;
	int temp3 = q.dequeue();
	q.debugPrintContents();


	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);





	//std::vector<int> misdatos(15, 0);
	//for (int i = 0; i < 15; i++)
	//	std::cout << "valor: " << misdatos[i] << std::endl;
	const char* maps[3] = { "map1.txt", "map2.txt", "map3.txt" };
	const char* musicTracks[3] = { "ILUETNI.XM", "TECNO1.XM", "LIRIUM.XM" };



	//Prubea de Inventario
	Inventory* inventario = new Inventory();
	inventario->AddItem(new Item("Espada", 1));
	inventario->AddItem(new Item("Pocion", 2));
	inventario->AddItem(new Item("Mondongo", 3));
	inventario->debugPrintContents();




	PlayerCharacter* player = new PlayerCharacter("player1");
	player->Start();
	player->inventory = inventario;
	player->drawDebugUID = true;



	//hacer unos dos o tres enemigos que se muevan hacia el jugador
	Enemy* enemy1 = new Enemy("enemy1",600,620 );
	enemy1->playerFollow = player;
	enemy1->Start();
	Enemy* enemy2 = new Enemy("enemy2",600,700 );
	enemy2->playerFollow = player;
	enemy2->Start();



	ObjectChest* objChest = new ObjectChest("objChest");
	objChest->Start();



	//Arreglo de objectos a la lista de GameObject
	gameobjects.push_back(player);
	gameobjects.push_back(enemy1);
	gameobjects.push_back(enemy2);
	gameobjects.push_back(objChest);


	//todos los gameobjects deberemos guardar su uid en esta tabla
	std::map<std::string, std::string> tablaUID;

	tablaUID[player->getUID()] = player->name;
	tablaUID[enemy1->getUID()] = enemy1->name;
	tablaUID[enemy2->getUID()] = enemy2->name;
	tablaUID[objChest->getUID()] = objChest->name;

	for (const auto& par : tablaUID) {
		std::cout << "UID: " << par.first << " - Nombre: " << par.second << std::endl;
	}



	//Pila de mensajes
	messageSystem = new MessageSystem();

	 //Agrega varios logros a la pila de mensajes
	messageSystem->AgregarMensaje("Evade Enemigos");
	messageSystem->AgregarMensaje("Explorador");
	messageSystem->AgregarMensaje("Primeros Pasos");
	messageSystem->AgregarMensaje("Nuevo Jugador");


	//Prueba de calculo de hash md5 usando la biblioteca de zunawe
	uint8_t result[16];
	char* mensaje = "hola mundo";
	md5String(mensaje, result);
	//imprimir el hash en hexadecimal
	//printHash
	std::cout << "hash computado: ";
	for (int i = 0; i < 16; i++)
	{
		//std::cout << std::hex << result[i];
		printf("%02X", result[i]);
	}
	std::cout << std::endl;




	//Modo C para crear un mapa 2D
	char** tilemap = (char**)malloc(maxTilesV * sizeof(char*));
	if (tilemap == NULL)
	{
		return 1;
	}
	//columna
	for (int i = 0; i < maxTilesV; i++)
	{
		tilemap[i] = (char*)malloc(maxTilesH * sizeof(char));
		memset(tilemap[i], 0, maxTilesH * sizeof(char));
		if (tilemap[i] == NULL)
		{
			return 1;
		}
	}
	for (int i = 0; i < maxTilesV; i++)
	{
		for (int j = 0; j < maxTilesH; j++)
		{
			printf("%i, ", tilemap[i][j]);
		}
		printf("\n");
	}
	//cargar nuestros tiles
	enum TileType {
		Pasto, Piedra, Tierra, Metal
	};
	Texture tiles[4];
	tiles[0] = LoadTexture("Pasto.png");
	tiles[1] = LoadTexture("Piedra.png");
	tiles[2] = LoadTexture("Tierra.png");
	tiles[3] = LoadTexture("Metal.png");


	int selectedMapIndex = -1;
	while (!WindowShouldClose() && selectedMapIndex == -1)
	{

		//Menú
		BeginDrawing();
		ClearBackground(BLACK);
		DrawText("Elige el nivel:", 220, 100, 85, WHITE);
		DrawText("Nivel 1 - tecla 1", 300, 250, 65, GREEN);
		DrawText("Nivel 2 - tecla 2", 300, 350, 65, GREEN);
		DrawText("Nivel 3 - tecla 3", 300, 450, 65, GREEN);
		EndDrawing();

		//Se elige el mapa de acuerdo a las teclas
		if (IsKeyPressed(KEY_ONE))
		{
			selectedMapIndex = 0;
		}
		if (IsKeyPressed(KEY_TWO))
		{
			selectedMapIndex = 1;
		}
		if (IsKeyPressed(KEY_THREE))
		{
			selectedMapIndex = 2;
		}
	}

	if (selectedMapIndex == -1)
	{
		return 0;
	}

	selectedMap = maps[selectedMapIndex];
	selectedMusic = musicTracks[selectedMapIndex];

	//Mapa 2D con std::vector
	Map2D mapa(maxTilesV, std::vector<int>(maxTilesH, 0));
	LoadMap(mapa, maxTilesH, maxTilesV, selectedMap);

	//Parte del Audio
	Music bgm = LoadBGM(selectedMusic.c_str());
	PlayMusicStream(bgm);


	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{

		// Update
		for (GameObject* obj : gameobjects)
		{
			if (obj->isEnabled())
			{
				obj->Update();
			}
		}

		messageSystem->Update();


		if (IsKeyPressed(KEY_M))
		{
			messageSystem->AgregarMensaje("nuevo mensaje");
		}


		UpdateMusicStream(bgm);


		// drawing
		BeginDrawing();
		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(DARKGRAY);
		for (int i = 0; i < maxTilesV; i++)
		{
			for (int j = 0; j < maxTilesH; j++)
			{
				DrawTexture(tiles[mapa[i][j]], j * tileSize, i * tileSize, WHITE);
			}
		}

		// draw some text using the default font
		DrawText("Tiles", 20, 20, 20, YELLOW);

		// draw our texture to the screen

		for (GameObject* obj : gameobjects)
		{
			if (obj->isEnabled())
			{
				obj->Draw();
			}
		}



		messageSystem->Draw();

		//Panel


		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up


	for (GameObject* obj : gameobjects)
	{
		delete obj;
	}

	delete messageSystem;
	UnloadMusicStream(bgm);
	CloseAudioDevice();
	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}