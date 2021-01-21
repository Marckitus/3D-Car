#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModulePhysics3D.h"

//ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
ModuleSceneIntro::ModuleSceneIntro(bool start_enabled) : Module(start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
    App->audio->PlayMusic("Assets/Sound/Initial D - Deja Vu.ogg");

	bool ret = true;
    App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
    App->camera->LookAt(vec3(0, 0, 0));
    // Add a ball
   
    ball = new Sphere(3, 0.75);
	ball->body.SetPos(40000, 3, -40);
	ball->body.type = BALL;
	ball->body.collision_listeners.add(this);
    primitives.PushBack(ball);
	ball2 = new Sphere(3, 0.75);
	ball2->body.SetPos(-5000, 3, 0);
	ball2->body.type = BALL;
	ball2->body.collision_listeners.add(this);
	primitives.PushBack(ball2);
	ball3 = new Sphere(3, 0.75);
	ball3->body.SetPos(5000, 3, 0);
	ball3->body.type = BALL;
	ball3->body.collision_listeners.add(this);
	primitives.PushBack(ball3);
	ball4 = new Sphere(3, 0.75);
	ball4->body.SetPos(6000, 3, 0);
	ball4->body.type = BALL;
	primitives.PushBack(ball4);
	ball4->body.collision_listeners.add(this);
	ball5 = new Sphere(3, 0.75);
	ball5->body.SetPos(7000, 3, 0);
	ball5->body.type = BALL;
	ball5->body.collision_listeners.add(this);
	primitives.PushBack(ball5);
	ball6 = new Sphere(3, 0.75);
	ball6->body.SetPos(8000, 3, 0);
	ball6->body.type = BALL;
	ball6->body.collision_listeners.add(this);
	primitives.PushBack(ball6);
   
 	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
    Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();
	if(App->player->time > 0)
	{
		if (firstRound == false)
		{
			ball->body.SetPos(50, 3, 0);
			firstRound = true;
		}
		if (score == 1 && secondRound == false)
		{
			secondRound = true;
			ball2->body.SetPos(-50, 3, 0);
			ball3->body.SetPos(50, 3, 0);
			ball->body.SetPos(40000, 3, -40);
			App->player->time = 120;
		}
		if (score == 3 && thirdRound == false)
		{
			thirdRound = true;
			ball4->body.SetPos(-50, 3, 0);
			ball5->body.SetPos(50, 3, 0);
			ball6->body.SetPos(0, 3, 50);
			ball2->body.SetPos(50000, 3, -40);
			ball3->body.SetPos(4000, 3, -40);
			App->player->time = 120;
		}

	}
	else
	{
		App->player->gameplay = false;
	}
	if (App->player->time > 60)
	{
		ball->color = Green;
		if (secondRound == true)
		{
			ball2->color = Green;
			ball3->color = Green;
		}
		if (thirdRound == true)
		{
			ball4->color = Green;
			ball5->color = Green;
			ball6->color = Green;
		}
	}
	else if (App->player->time < 60 && App->player->time >20)
	{
		ball->color = Naranja;
		if (secondRound == true)
		{
			ball2->color = Naranja;
			ball3->color = Naranja;
		}
		if (thirdRound == true)
		{
			ball4->color = Naranja;
			ball5->color = Naranja;
			ball6->color = Naranja;
		}
	}
	else if (App->player->time < 20)
	{
		ball->color = Red;
		if (secondRound == true)
		{
			ball2->color = Red;
			ball3->color = Red;
		}
		if (thirdRound == true)
		{
			ball4->color = Red;
			ball5->color = Red;
			ball6->color = Red;
		}
	}

	if (App->player->time == 0)
	{
		ball->Update();
		App->player->gameplay = false;
		
		
	}

	for (uint n = 0; n < primitives.Count(); n++)
		primitives[n]->Update();

	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{
    for (uint n = 0; n < primitives.Count(); n++)
    {
        primitives[n]->Render();
    }

    return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if(body1 == &App->physics->goal.body && body2 == &ball->body)
	{

	}
	else if (body2 == &App->physics->goal.body && body1 == &ball->body)
	{

	}
}

