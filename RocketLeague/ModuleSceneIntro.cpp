#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

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
  
	//Win = App->tex->Load("Assets/Textures/background.png");
	bool ret = true;
    App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
    App->camera->LookAt(vec3(0, 0, 0));
    // Add a ball
   
    ball = new Sphere(3, 0.75);
    ball->body.SetPos(50, 3, 0);
    primitives.PushBack(ball);
   
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

    if (score == 1 && create == false ) 
    {
        App->player->time = 120;
        ball2 = new Sphere(3, 0.75);
        ball2->body.SetPos(-50, 3, 0);
        primitives.PushBack(ball2);
		App->player->time = 120;
		ball3 = new Sphere(3, 0.75);
		ball3->body.SetPos(50, 3, 0);
		primitives.PushBack(ball3);
        create = true;
        ball->body.SetPos(40000, 3, -40);
    }


	if (App->player->time > 60)
	{
		ball->color = Green;
		if (create == true)
		{
			ball2->color = Green;
			ball3->color = Green;
		}
	}
	else if (App->player->time < 60 && App->player->time >20)
	{
		ball->color = Naranja;
		if (create == true)
		{
			ball2->color = Naranja;
			ball3->color = Naranja;
		}
	}
	else if (App->player->time < 20)
	{
		ball->color = Red;
		if (create = true)
		{
			ball2->color = Red;
			ball3->color = Red;
		}
	}
  
	if(App->player->time==0)

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
}

