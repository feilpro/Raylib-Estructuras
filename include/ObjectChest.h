#pragma once
#include "raylib.h"
#include "GameObject.h"
#include <string>


class ObjectChest: public GameObject
{
public:


	ObjectChest(char* _name) : GameObject(_name)
	{
	}

	void Start() override;
	void Update() override;
	void Draw() override;



};

