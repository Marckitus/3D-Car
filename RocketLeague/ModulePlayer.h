#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "PhysVehicle3D.h"


struct PhysVehicle3D;

#define MAX_ACCELERATION 1500.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 1000.0f

class ModulePlayer : public Module
{
public:
	//ModulePlayer(Application* app, bool start_enabled = true);
	ModulePlayer(bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

public:
	int cameray = 150;
	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;
	int time = 120;
	int comodin = 0;
	int gameplay = false;
};