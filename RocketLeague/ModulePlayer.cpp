#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

//ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
ModulePlayer::ModulePlayer(bool start_enabled) : Module(start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	VehicleInfo car;

	// Car properties ----------------------------------------
	car.chassis_size.Set(4, 3, 6);
	car.chassis_offset.Set(0, 1.5, 0);
	car.mass = 100.00f;
	car.suspensionStiffness = 15.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.88f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.2f;
	float wheel_radius = 0.6f;
	float wheel_width = 0.5f;
	float suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x*0.5f;
	float half_length = car.chassis_size.z*0.5f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	vehicle = App->physics->AddVehicle(car);
	vehicle->SetPos(0, 4, -50);
	
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	turn = acceleration = brake = 0.0f;
	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		gameplay = true;
		vehicle->SetPos(0, 4, -50);
		time = 120;
		App->scene_intro->score = 0;
		App->scene_intro->ball->body.SetPos(50, 3, 0);
		App->scene_intro->ball2->body.SetPos(50000, 3, -40);
		App->scene_intro->ball3->body.SetPos(4000, 3, -40);
		App->scene_intro->ball4->body.SetPos(41000, 3, -40);
		App->scene_intro->ball5->body.SetPos(53000, 3, -40);
		App->scene_intro->ball6->body.SetPos(4400, 3, -40);
		App->scene_intro->ball7->body.SetPos(4400, 3, -40);
		App->scene_intro->ball8->body.SetPos(4400, 3, -40);
		App->scene_intro->ball9->body.SetPos(4400, 3, -40);
		App->scene_intro->ball10->body.SetPos(4400, 3, -40);
		App->scene_intro->firstRound = false;
		App->scene_intro->secondRound = false;
		App->scene_intro->thirdRound = false;
		App->scene_intro->forthRound = false;
		App->scene_intro->finalRound = false;
		
	}
	if(gameplay == true)
	{
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		if (acceleration > 0) acceleration = MAX_ACCELERATION;
		else if (acceleration <= 0) acceleration = (MAX_ACCELERATION + BRAKE_POWER);

		if (vehicle->GetKmh() >= 100.0)
		{
			acceleration = 0;
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		if (turn < TURN_DEGREES)
			turn += TURN_DEGREES;
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		if (turn > -TURN_DEGREES)
			turn -= TURN_DEGREES;
	}

	if (App->input->GetKey(SDL_SCANCODE_RSHIFT) == KEY_REPEAT)
	{
		brake = BRAKE_POWER;

	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		if (acceleration >= 0) acceleration = -(MAX_ACCELERATION + BRAKE_POWER);
		else if (acceleration < 0) acceleration = -(MAX_ACCELERATION - 200);

		if (vehicle->GetKmh() <= -80.0)
		{
			acceleration = 0;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)
	{
		App->scene_intro->score++;
		App->audio->PlayFx(App->scene_intro->point);

	}



	// Apply controls to vehicle
	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);
	}

	// Render vehicle
	vehicle->Render();
	
	vec3 position(0, 0, 0);
	position = vehicle->GetPos();
	
	App->camera->LookAt(0);//vehicle->GetPos() + vec3{ 0.0, 1.0, 0.0 } *2.0); // Look at car's CM (a bit up)
	App->camera->Position = vehicle->GetPos();
	App->camera->Position.y += cameray;
	if (gameplay == true) 
	{
		if (comodin < 60)comodin++;
		if (comodin == 60) {
			time--;
			comodin = 0;
		}
	}

    // Info
	char title[80];
	sprintf_s(title, "Golf Kart | Car speed: %.1f km/h Time left: %d   %d   Points: %d", vehicle->GetKmh(), time, comodin, App->scene_intro->score);
	App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}



