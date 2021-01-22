#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
	//ModuleSceneIntro(Application* app, bool start_enabled = true);
    ModuleSceneIntro(bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
    update_status PostUpdate(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

public:

    // Array of primitives
    p2DynArray<Primitive*> primitives;

	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;

	Cylinder goal;
	Sphere* goal2;
	Sphere* ball;
	Sphere* ball2;
	Sphere* ball3;
	Sphere* ball4;
	Sphere* ball5;
	Sphere* ball6;
	Sphere* ball7;
	Sphere* ball8;
	Sphere* ball9;
	Sphere* ball10;
	Cube floor;
	Cube wall1;
	Cube wall2;
	Cube wall3;
	Cube wall4;
	Cube obs1;
	Cube obs2;
	Cube obs3;
	Cube obs4;
	Cube obs5;
	Cube obs6;
	Cube obs7;
	Cube obs8;
	Cube vis1;
	Cube vis2;
	Cube vis3;
	Cube vis4;

	SDL_Texture* Win;
	SDL_Texture* Lose;


	int score = 0;
	bool firstRound = false;
	bool secondRound = false;
	bool thirdRound = false;
	bool forthRound = false;
	bool finalRound = false;
};
