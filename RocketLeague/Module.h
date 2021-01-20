#pragma once

//class Application;
struct PhysBody3D;

class Module
{
private :
	bool enabled;

public:
	//Application* App;

	//Module(Application* parent, bool start_enabled = true) : App(parent)
    Module(bool start_enabled = true) : enabled(start_enabled)
	{}

	virtual ~Module()
	{}

	virtual bool Init() 
	{
		return true; 
	}

	virtual bool Start()
	{
		return true;
	}

	virtual update_status PreUpdate(float dt)
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status Update(float dt)
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status PostUpdate(float dt)
	{
		return UPDATE_CONTINUE;
	}

	virtual bool CleanUp() 
	{ 
		return true; 
	}

	virtual void OnCollision(PhysBody3D* body1, PhysBody3D* body2)
	{
		if (body1->is_sensor == true && body2->is_sensor == true)
		{
			if (body1->type == type::GOAL)
			{
				//set score 1, tp body 2
			}
			else
			{
				//set score 1, tp body 1
			}
		}
	}
};