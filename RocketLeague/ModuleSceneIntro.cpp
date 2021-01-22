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
	point = App->audio->LoadFx("Assets/Sound/points.wav");

	bool ret = true;
    App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
    App->camera->LookAt(vec3(0, 0, 0));

	vec3 rotateZ = (0, 0, 1);
	vec3 rotateY = (0, 1, 0);
	vec3 rotateX = (1, 0, 0);

	btTransform t; // Bullet's transf matrix class. Very easy to work with
	t.setOrigin(btVector3(-65.0, 1.0, 0.0)); // Position (x,y,z) in world ref
	t.setRotation(btQuaternion(0.0, 0.0, 45.0)); // Rotation angles (yaw, pitch, roll) in local ref
	btScalar matrixb[16]; // This is what Bullet provides
	mat4x4 matrixp; // This is what Primitive wants
	t.getOpenGLMatrix(matrixb); // Recover transf matrix from Bullet class
	for (int i = 0; i < 16; i++) matrixp[i] = matrixb[i]; // Copy transf matrix items from Bullet to Primitive class vars
   
   ball = new Sphere(3, 0.75);
	ball->body.SetPos(40000, 3, -40);
	ball->body.type = BALL;
	ball->body.collision_listeners.add(this);
    primitives.PushBack(ball);
	ball->body.GetBody()->setUserPointer(&ball->body);
	ball2 = new Sphere(3, 0.75);
	ball2->body.SetPos(-5000, 3, 0);
	ball2->body.type = BALL;
	ball2->body.collision_listeners.add(this);
	ball2->body.GetBody()->setUserPointer(&ball2->body);
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
	ball7 = new Sphere(3, 0.75);
	ball7->body.SetPos(5000, 3, 0);
	ball7->body.type = BALL;
	ball7->body.collision_listeners.add(this);
	primitives.PushBack(ball7);
	ball8 = new Sphere(3, 0.75);
	ball8->body.SetPos(6000, 3, 0);
	ball8->body.type = BALL;
	primitives.PushBack(ball8);
	ball8->body.collision_listeners.add(this);
	ball9 = new Sphere(3, 0.75);
	ball9->body.SetPos(7000, 3, 0);
	ball9->body.type = BALL;
	ball9->body.collision_listeners.add(this);
	primitives.PushBack(ball9);
	ball10 = new Sphere(3, 0.75);
	ball10->body.SetPos(8000, 3, 0);
	ball10->body.type = BALL;
	ball10->body.collision_listeners.add(this);
	primitives.PushBack(ball10);

	floor.size.Set(140, 3, 140);
	floor.SetPos(0, -1.4, 0);
	floor.body.type = WALL;
	floor.color = Sand;
	floor.body.SetAsSensor(false);
	App->physics->AddBody(floor, 0);

	wall1.size.Set(2, 70, 140);
	wall1.SetPos(-70, 35, 0);
	wall1.body.type = WALL;
	wall1.color = Sky;
	wall1.body.SetAsSensor(false);
	App->physics->AddBody(wall1, 0);

	wall2.size.Set(140, 70, 2);
	wall2.SetPos(0, 35, -70);
	wall2.color = Sky;
	wall2.body.type = WALL;
	wall2.body.SetAsSensor(false);
	App->physics->AddBody(wall2, 0);



	wall3.size.Set(140, 70, 2);
	wall3.SetPos(0, 35, 70);
	wall3.color = Sky;
	wall3.body.type = WALL;
	wall3.body.SetAsSensor(false);
	App->physics->AddBody(wall3, 0);



	wall4.size.Set(2, 70, 140);
	wall4.SetPos(70, 35, 0);
	wall4.color = Sky;
	wall4.body.type = WALL;
	wall4.body.SetAsSensor(false);
	App->physics->AddBody(wall4, 0);



	obs1.size.Set(3, 8, 10);
	obs1.SetPos(25, 0, 0);
	obs1.color = F;
	obs1.body.type = WALL;
	obs1.body.SetAsSensor(false);
	App->physics->AddBody(obs1, 0);

	obs2.size.Set(3, 8, 10);
	obs2.SetPos(-25, 0, 0);
	obs2.color = F;
	obs2.body.type = WALL;
	obs2.body.SetAsSensor(false);
	App->physics->AddBody(obs2, 0);


	obs3.size.Set(10, 8, 3);
	obs3.SetPos(0, 0, -25);
	obs3.color = F;
	obs3.body.type = WALL;
	obs3.body.SetAsSensor(false);
	App->physics->AddBody(obs3, 0);

	obs4.size.Set(10, 8, 3);
	obs4.SetPos(0, 0, 25);
	obs4.color = F;
	obs4.body.type = WALL;
	obs4.body.SetAsSensor(false);
	App->physics->AddBody(obs4, 0);

	obs5.size.Set(10, 8, 10);
	obs5.SetPos(35, 0, 35);
	obs5.color = F;
	obs5.body.type = WALL;
	obs5.body.SetAsSensor(false);
	App->physics->AddBody(obs5, 0);

	obs6.size.Set(10, 8, 10);
	obs6.SetPos(-35, 0, -35);
	obs6.color = F;
	obs6.body.type = WALL;
	obs6.body.SetAsSensor(false);
	App->physics->AddBody(obs6, 0);

	obs7.size.Set(10, 8, 10);
	obs7.SetPos(-35, 0, 35);
	obs7.color = F;
	obs7.body.type = WALL;
	obs7.body.SetAsSensor(false);
	App->physics->AddBody(obs7, 0);

	obs8.size.Set(10, 8, 10);
	obs8.SetPos(35, 0, -35);
	obs8.color = F;
	obs8.body.type = WALL;
	obs8.body.SetAsSensor(false);
	App->physics->AddBody(obs8, 0);


	goal.height = 4;
	goal.radius = 15;
	goal.SetPos(0, -0.5, 0);
	goal.body.type = GOAL;
	goal.color = Rosa;
	goal.SetRotation(120, rotateZ);


	goal2 = new Sphere(15, 0);
	goal2->body.SetPos(0, -0.5, 0);
	goal2->body.type = GOAL;
	primitives.PushBack(goal2);
	goal2->body.SetAsSensor(true);
	goal2->body.collision_listeners.add(this);
	goal2->body.GetBody()->setUserPointer(goal2);

	PhysBody3D* Goal = App->physics->AddBody(*goal2, 0);
	Goal->SetAsSensor(true);
	goal2->radius = 0.5;

	vis1.size.Set(2, 10, 140);
	vis1.color = Red;
	vis1.body.type = WALL;
	vis1.transform = matrixp; // Apply transf matrix to Primitive
	App->physics->AddBody(vis1, 0.0);


	//izquierda

	btTransform t2;
	t2.setOrigin(btVector3(65.0, 1.0, 0.0)); // Position (x,y,z) in world ref
	t2.setRotation(btQuaternion(0.0, 0.0, -45.0)); // Rotation angles (yaw, pitch, roll) in local ref
	btScalar matrixb2[16]; // This is what Bullet provides
	mat4x4 matrixp2; // This is what Primitive wants
	t2.getOpenGLMatrix(matrixb2); // Recover transf matrix from Bullet class
	for (int i = 0; i < 16; i++) matrixp2[i] = matrixb2[i]; // Copy transf matrix items from Bullet to Primitive class vars

	vis2.size.Set(2, 10, 140);
	vis2.color = Red;
	floor.body.type = WALL;
	vis2.transform = matrixp2;
	App->physics->AddBody(vis2, 0);


	//arriba

	btTransform t3;
	t3.setOrigin(btVector3(0.0, 1.0, 65.0)); // Position (x,y,z) in world ref
	t3.setRotation(btQuaternion(0.0, 45.0, 0.0)); // Rotation angles (yaw, pitch, roll) in local ref
	btScalar matrixb3[16]; // This is what Bullet provides
	mat4x4 matrixp3; // This is what Primitive wants
	t3.getOpenGLMatrix(matrixb3); // Recover transf matrix from Bullet class
	for (int i = 0; i < 16; i++) matrixp3[i] = matrixb3[i]; // Copy transf matrix items from Bullet to Primitive class vars

	vis3.size.Set(140, 10, 2);
	vis3.color = Red;
	vis3.body.type = WALL;
	vis3.transform = matrixp3;
	App->physics->AddBody(vis3, 0);


	//abajo

	btTransform t4;
	t4.setOrigin(btVector3(0.0, 1.0, -65.0)); // Position (x,y,z) in world ref
	t4.setRotation(btQuaternion(0.0, -45.0, 0.0)); // Rotation angles (yaw, pitch, roll) in local ref
	btScalar matrixb4[16]; // This is what Bullet provides
	mat4x4 matrixp4; // This is what Primitive wants
	t4.getOpenGLMatrix(matrixb4); // Recover transf matrix from Bullet class
	for (int i = 0; i < 16; i++) matrixp4[i] = matrixb4[i]; // Copy transf matrix items from Bullet to Primitive class vars

	vis4.size.Set(140, 10, 2);
	vis4.color = Red;
	vis4.body.type = WALL;
	vis4.transform = matrixp4;
	App->physics->AddBody(vis4, 0);

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
	floor.Render();
	wall1.Render();
	wall2.Render();
	wall3.Render();
	wall4.Render();
	obs1.Render();
	obs2.Render();
	obs3.Render();
	obs4.Render();
	obs5.Render();
	obs6.Render();
	obs7.Render();
	obs8.Render();
	goal.Render();
	vis1.Render();
	vis2.Render();
	vis3.Render();
	vis4.Render();
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
			App->player->time += 60;
		}
		if (score == 3 && thirdRound == false)
		{
			thirdRound = true;
			ball4->body.SetPos(-50, 3, 0);
			ball5->body.SetPos(50, 3, 0);
			ball6->body.SetPos(0, 3, 50);
			App->player->time += 30;
		}
		if (score == 6 && forthRound == false)
		{
			forthRound = true;
			ball7->body.SetPos(-50, 3, 0);
			ball8->body.SetPos(50, 3, 0);
			ball9->body.SetPos(0, 3, 50);
			ball10->body.SetPos(0, 3, -50);
			App->player->time += 30;
		}
		if (score == 10 && finalRound == false)
		{
			finalRound = true;
			ball->body.SetPos(50, 3, 0);
			ball2->body.SetPos(-50, 3, 0);
			ball3->body.SetPos(40, 3, 10);
			ball4->body.SetPos(-40, 3, 10);
			ball5->body.SetPos(0, 3, -50);
			ball6->body.SetPos(0, 3, 50);
			ball7->body.SetPos(10, 3, 40);
			ball8->body.SetPos(-10, 3, 40);
			ball9->body.SetPos(40, 3, 40);
			ball10->body.SetPos(-40, 3, -40);
			App->player->time += 30;
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
		if (forthRound == true)
		{
			ball7->color = Green;
			ball8->color = Green;
			ball9->color = Green;
			ball10->color = Green;
		}
		if (finalRound == true)
		{
			ball->color = Green;
			ball2->color = Green;
			ball3->color = Green;
			ball4->color = Green;
			ball5->color = Green;
			ball6->color = Green;
			ball7->color = Green;
			ball8->color = Green;
			ball9->color = Green;
			ball10->color = Green;
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
		if (forthRound == true)
		{
			ball7->color = Naranja;
			ball8->color = Naranja;
			ball9->color = Naranja;
			ball10->color = Naranja;
		}
		if (finalRound == true)
		{
			ball->color = Naranja;
			ball2->color = Naranja;
			ball3->color = Naranja;
			ball4->color = Naranja;
			ball5->color = Naranja;
			ball6->color = Naranja;
			ball7->color = Naranja;
			ball8->color = Naranja;
			ball9->color = Naranja;
			ball10->color = Naranja;
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
		if (forthRound == true)
		{
			ball7->color = Red;
			ball8->color = Red;
			ball9->color = Red;
			ball10->color = Red;
		}
		if (finalRound == true)
		{
			ball->color = Red;
			ball2->color = Red;
			ball3->color = Red;
			ball4->color = Red;
			ball5->color = Red;
			ball6->color = Red;
			ball7->color = Red;
			ball8->color = Red;
			ball9->color = Red;
			ball10->color = Red;
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
	if(body1->type == type::BALL && body2->is_sensor == true)
	{
		score++;
		App->audio->PlayFx(point);
		body1->SetPos(50000, 3, -40);
	}
	else if (body2->type == type::BALL && body1->type == type::GOAL)
	{
		//score++;
	}
}

