#include "Globals.h"
#include "Application.h"
#include "ModulePhysics3D.h"
#include "PhysBody3D.h"
#include "PhysVehicle3D.h"
#include "Primitive.h"

#include "glut/glut.h"

#ifdef _DEBUG
	#pragma comment (lib, "Bullet/libx86/BulletDynamics_debug.lib")
	#pragma comment (lib, "Bullet/libx86/BulletCollision_debug.lib")
	#pragma comment (lib, "Bullet/libx86/LinearMath_debug.lib")
#else
	#pragma comment (lib, "Bullet/libx86/BulletDynamics.lib")
	#pragma comment (lib, "Bullet/libx86/BulletCollision.lib")
	#pragma comment (lib, "Bullet/libx86/LinearMath.lib")
#endif

//ModulePhysics3D::ModulePhysics3D(Application* app, bool start_enabled) : Module(app, start_enabled)
ModulePhysics3D::ModulePhysics3D(bool start_enabled) : Module(start_enabled), world(nullptr)
{
	debug = false;

	collision_conf = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collision_conf);
	broad_phase = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver();
	debug_draw = new DebugDrawer();
}

// Destructor
ModulePhysics3D::~ModulePhysics3D()
{
	delete debug_draw;
	delete solver;
	delete broad_phase;
	delete dispatcher;
	delete collision_conf;
}

// Render not available yet----------------------------------
bool ModulePhysics3D::Init()
{
	LOG("Creating 3D Physics simulation");
	bool ret = true;

	return ret;
}

// ---------------------------------------------------------
bool ModulePhysics3D::Start()
{
	LOG("Creating Physics environment");

	world = new btDiscreteDynamicsWorld(dispatcher, broad_phase, solver, collision_conf);
	world->setDebugDrawer(debug_draw);
	world->setGravity(GRAVITY);
	vehicle_raycaster = new btDefaultVehicleRaycaster(world);

	// Big plane as ground
	{
		btCollisionShape* colShape = new btStaticPlaneShape(btVector3(0, 1, 0), 0);

		btDefaultMotionState* myMotionState = new btDefaultMotionState();
		btRigidBody::btRigidBodyConstructionInfo rbInfo(0.0f, myMotionState, colShape);

		btRigidBody* body = new btRigidBody(rbInfo);
		world->addRigidBody(body);
	}
	vec3 rotateZ = (0, 0, 1);
	vec3 rotateY = (0, 1, 0);
	vec3 rotateX = (1, 0, 0);

	floor.size.Set(140, 3, 140);
	floor.SetPos(0, -1.4, 0);
	floor.body.type = WALL;
	float force0 = 30.0f;
	floor.color = Sand;
	AddBody(floor, 0)->Push(-(0 * force0), -(-4 * force0), -(0 * force0));

	wall1.size.Set(2, 70, 140);
	wall1.SetPos(-70, 35, 0);
	wall1.body.type = WALL;
	float force1 = 30.0f;
	wall1.color = Sky;
	AddBody(wall1, 0)->Push(-(-100 * force1), -(35 * force1), -(0 * force1));

	vis1.size.Set(2, 5, 140);
	vis1.SetPos(-68, 3, 0);
	vis1.color = Red;
	vis1.body.type = WALL;
	float force15 = 30.0f;
	//vis4.SetRotation(90, rotateY);
	AddBody(vis1, 0)->Push(-(-100 * force15), -(3 * force15), -(0 * force15));

	wall2.size.Set(140, 70, 2);
	wall2.SetPos(0, 35, -70);
	wall2.color = Sky;
	wall2.body.type = WALL;
	float force2 = 30.0f;
	AddBody(wall2, 0)->Push(-(0 * force2), -(35 * force2), -(-100 * force2));

	vis2.size.Set(140, 5, 2);
	vis2.SetPos(0, 3, -68);
	vis2.color = Red;
	floor.body.type = WALL;
	float force16 = 30.0f;
	//vis2.SetRotation(90, rotateX);
	AddBody(vis2, 0)->Push(-(0 * force16), -(3 * force16), -(-100 * force16));

	wall3.size.Set(140, 70, 2);
	wall3.SetPos(0, 35, 70);
	wall3.color = Sky;
	wall3.body.type = WALL;
	float force3 = 30.0f;
	AddBody(wall3, 0)->Push(-(0 * force3), -(35 * force3), -(100 * force3));

	vis3.size.Set(140, 5, 2);
	vis3.SetPos(0, 3, 68);
	vis3.color = Red;
	vis3.body.type = WALL;
	float force17 = 30.0f;
	//vis4.SetRotation(90, rotateY);
	AddBody(vis3, 0)->Push(-(0 * force17), -(35 * force17), -(100 * force17));

	wall4.size.Set(2, 70, 140);
	wall4.SetPos(70, 35, 0);
	wall4.color = Sky;
	wall4.body.type = WALL;
	float force4 = 30.0f;
	AddBody(wall4, 0)->Push(-(100 * force4), -(35 * force4), -(0 * force4));

	vis4.size.Set(2, 5, 140);
	vis4.SetPos(68, 3, 0);
	vis4.color = Red;
	vis4.body.type = WALL;
	float force14 = 30.0f;
	//vis4.SetRotation(90, rotateZ);
	AddBody(vis4, 0)->Push(-(100 * force14), -(3 * force14), -(0 * force14));

	obs1.size.Set(3, 8, 10);
	obs1.SetPos(25, 0, 0);
	obs1.color = F;
	obs1.body.type = WALL;
	float force5 = 30.0f;
	AddBody(obs1, 0)->Push(-(25 * force5), -(0 * force5), -(0 * force5));

	obs2.size.Set(3, 8, 10);
	obs2.SetPos(-25, 0, 0);
	obs2.color = F;
	obs2.body.type = WALL;
	float force6 = 30.0f;
	AddBody(obs2, 0)->Push(-(-25 * force6), -(0 * force6), -(0 * force6));

	obs3.size.Set(10, 8, 3);
	obs3.SetPos(0, 0, -25);
	obs3.color = F;
	obs3.body.type = WALL;
	float force7 = 30.0f;
	AddBody(obs3, 0)->Push(-(0 * force7), -(0 * force7), -(-25 * force7));

	obs4.size.Set(10, 8, 3);
	obs4.SetPos(0, 0, 25);
	obs4.color = F;
	obs4.body.type = WALL;
	float force8 = 30.0f;
	AddBody(obs4, 0)->Push(-(0 * force8), -(0 * force8), -(25 * force8));

	obs5.size.Set(10, 8, 10);
	obs5.SetPos(35, 0, 35);
	obs5.color = F;
	obs5.body.type = WALL;
	float force9 = 30.0f;
	AddBody(obs5, 0)->Push(-(35 * force9), -(0 * force9), -(35 * force9));

	obs6.size.Set(10, 8, 10);
	obs6.SetPos(-35, 0, -35);
	obs6.color = F;
	obs6.body.type = WALL;
	float force10 = 30.0f;
	AddBody(obs6, 0)->Push(-(35 * force10), -(0 * force10), -(-35 * force10));

	obs7.size.Set(10, 8, 10);
	obs7.SetPos(-35, 0, 35);
	obs7.color = F;
	obs7.body.type = WALL;
	float force11 = 30.0f;
	AddBody(obs7, 0)->Push(-(-35 * force11), -(0 * force11), -(35 * force11));

	obs8.size.Set(10, 8, 10);
	obs8.SetPos(35, 0, -35);
	obs8.color = F;
	obs8.body.type = WALL;
	float force12 = 30.0f;
	AddBody(obs8, 0)->Push(-(35 * force12), -(0 * force12), -(-35 * force12));


	goal.height = 3;
	goal.radius = 5;
	goal.SetPos(0, -0.5, 0);
	goal.body.type = GOAL;
	goal.color = Rosa;
	float force = 30.0f;
	goal.SetRotation(120, rotateZ);

	PhysBody3D* Goal = AddBody(goal, 0);

	return true;
}

// ---------------------------------------------------------
update_status ModulePhysics3D::PreUpdate(float dt)
{
	world->stepSimulation(dt, 15);

	int numManifolds = world->getDispatcher()->getNumManifolds();
	for(int i = 0; i<numManifolds; i++)
	{
		btPersistentManifold* contactManifold = world->getDispatcher()->getManifoldByIndexInternal(i);
		btCollisionObject* obA = (btCollisionObject*)(contactManifold->getBody0());
		btCollisionObject* obB = (btCollisionObject*)(contactManifold->getBody1());

		int numContacts = contactManifold->getNumContacts();
		if(numContacts > 0)
		{
			PhysBody3D* pbodyA = (PhysBody3D*)obA->getUserPointer();
			PhysBody3D* pbodyB = (PhysBody3D*)obB->getUserPointer();

			if(pbodyA && pbodyB)
			{
				p2List_item<Module*>* item = pbodyA->collision_listeners.getFirst();
				while(item)
				{
					item->data->OnCollision(pbodyA, pbodyB);
					item = item->next;
				}

				item = pbodyB->collision_listeners.getFirst();
				while(item)
				{
					item->data->OnCollision(pbodyB, pbodyA);
					item = item->next;
				}
			}
		}
	}

	return UPDATE_CONTINUE;
}

// ---------------------------------------------------------
update_status ModulePhysics3D::Update(float dt)
{
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
	
	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(debug == true)
	{
		world->debugDrawWorld();

		// Render vehicles
		p2List_item<PhysVehicle3D*>* item = vehicles.getFirst();
		while(item)
		{
			item->data->Render();
			item = item->next;
		}

		if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
		{
			Sphere s(1);
			s.SetPos(App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);
			float force = 30.0f;
			AddBody(s)->Push(-(App->camera->Z.x * force), -(App->camera->Z.y * force), -(App->camera->Z.z * force));
		}
	}

	return UPDATE_CONTINUE;
}

// ---------------------------------------------------------
update_status ModulePhysics3D::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModulePhysics3D::CleanUp()
{
	LOG("Destroying 3D Physics simulation");

	// Remove from the world all collision bodies
	for(int i = world->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject* obj = world->getCollisionObjectArray()[i];
		world->removeCollisionObject(obj);
	}

	for(p2List_item<btTypedConstraint*>* item = constraints.getFirst(); item; item = item->next)
	{
		world->removeConstraint(item->data);
		delete item->data;
	}
	
	constraints.clear();

	for(p2List_item<btDefaultMotionState*>* item = motions.getFirst(); item; item = item->next)
		delete item->data;

	motions.clear();

	for(p2List_item<btCollisionShape*>* item = shapes.getFirst(); item; item = item->next)
		delete item->data;

	shapes.clear();

	for(p2List_item<PhysBody3D*>* item = bodies.getFirst(); item; item = item->next)
		delete item->data;

	bodies.clear();

	for(p2List_item<PhysVehicle3D*>* item = vehicles.getFirst(); item; item = item->next)
		delete item->data;

	vehicles.clear();

	delete vehicle_raycaster;
	delete world;

	return true;
}

void ModulePhysics3D::AddBodyToWorld(btRigidBody* body)
{
    world->addRigidBody(body);
}

void ModulePhysics3D::RemoveBodyFromWorld(btRigidBody* body)
{
    world->removeRigidBody(body);
}

// ---------------------------------------------------------
PhysBody3D* ModulePhysics3D::AddBody(const Sphere& sphere, float mass)
{
	btCollisionShape* colShape = new btSphereShape(sphere.radius);
	shapes.add(colShape);

	btTransform startTransform;
	startTransform.setFromOpenGLMatrix(&sphere.transform);

	btVector3 localInertia(0, 0, 0);
	if(mass != 0.f)
		colShape->calculateLocalInertia(mass, localInertia);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	motions.add(myMotionState);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);

	btRigidBody* body = new btRigidBody(rbInfo);
	PhysBody3D* pbody = new PhysBody3D(body);

	body->setUserPointer(pbody);
	world->addRigidBody(body);
	bodies.add(pbody);

	return pbody;
}


// ---------------------------------------------------------
PhysBody3D* ModulePhysics3D::AddBody(const Cube& cube, float mass)
{
	btCollisionShape* colShape = new btBoxShape(btVector3(cube.size.x*0.5f, cube.size.y*0.5f, cube.size.z*0.5f));
	shapes.add(colShape);

	btTransform startTransform;
	startTransform.setFromOpenGLMatrix(&cube.transform);

	btVector3 localInertia(0, 0, 0);
	if(mass != 0.f)
		colShape->calculateLocalInertia(mass, localInertia);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	motions.add(myMotionState);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);

	btRigidBody* body = new btRigidBody(rbInfo);
	PhysBody3D* pbody = new PhysBody3D(body);

	body->setUserPointer(pbody);
	world->addRigidBody(body);
	bodies.add(pbody);

	return pbody;
}

// ---------------------------------------------------------
PhysBody3D* ModulePhysics3D::AddBody(const Cylinder& cylinder, float mass)
{
	btCollisionShape* colShape = new btCylinderShapeX(btVector3(cylinder.height*0.5f, cylinder.radius, 0.0f));
	shapes.add(colShape);

	btTransform startTransform;
	startTransform.setFromOpenGLMatrix(&cylinder.transform);

	btVector3 localInertia(0, 0, 0);
	if(mass != 0.f)
		colShape->calculateLocalInertia(mass, localInertia);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	motions.add(myMotionState);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);

	btRigidBody* body = new btRigidBody(rbInfo);
	PhysBody3D* pbody = new PhysBody3D(body);

	body->setUserPointer(pbody);
	world->addRigidBody(body);
	bodies.add(pbody);

	return pbody;
}

// ---------------------------------------------------------
PhysVehicle3D* ModulePhysics3D::AddVehicle(const VehicleInfo& info)
{
	btCompoundShape* comShape = new btCompoundShape();
	shapes.add(comShape);

	btCollisionShape* colShape = new btBoxShape(btVector3(info.chassis_size.x*0.5f, info.chassis_size.y*0.5f, info.chassis_size.z*0.5f));
	shapes.add(colShape);

	btTransform trans;
	trans.setIdentity();
	trans.setOrigin(btVector3(info.chassis_offset.x, info.chassis_offset.y, info.chassis_offset.z));

	comShape->addChildShape(trans, colShape);

	btTransform startTransform;
	startTransform.setIdentity();

	btVector3 localInertia(0, 0, 0);
	comShape->calculateLocalInertia(info.mass, localInertia);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(info.mass, myMotionState, comShape, localInertia);

	btRigidBody* body = new btRigidBody(rbInfo);
	body->setContactProcessingThreshold(BT_LARGE_FLOAT);
	body->setActivationState(DISABLE_DEACTIVATION);

	world->addRigidBody(body);

	btRaycastVehicle::btVehicleTuning tuning;
	tuning.m_frictionSlip = info.frictionSlip;
	tuning.m_maxSuspensionForce = info.maxSuspensionForce;
	tuning.m_maxSuspensionTravelCm = info.maxSuspensionTravelCm;
	tuning.m_suspensionCompression = info.suspensionCompression;
	tuning.m_suspensionDamping = info.suspensionDamping;
	tuning.m_suspensionStiffness = info.suspensionStiffness;

	btRaycastVehicle* vehicle = new btRaycastVehicle(tuning, body, vehicle_raycaster);

	vehicle->setCoordinateSystem(0, 1, 2);

	for(int i = 0; i < info.num_wheels; ++i)
	{
		btVector3 conn(info.wheels[i].connection.x, info.wheels[i].connection.y, info.wheels[i].connection.z);
		btVector3 dir(info.wheels[i].direction.x, info.wheels[i].direction.y, info.wheels[i].direction.z);
		btVector3 axis(info.wheels[i].axis.x, info.wheels[i].axis.y, info.wheels[i].axis.z);

		vehicle->addWheel(conn, dir, axis, info.wheels[i].suspensionRestLength, info.wheels[i].radius, tuning, info.wheels[i].front);
	}
	// ---------------------

	PhysVehicle3D* pvehicle = new PhysVehicle3D(body, vehicle, info);
	world->addVehicle(vehicle);
	vehicles.add(pvehicle);

	return pvehicle;
}

// ---------------------------------------------------------
void ModulePhysics3D::AddConstraintP2P(PhysBody3D& bodyA, PhysBody3D& bodyB, const vec3& anchorA, const vec3& anchorB)
{
	btTypedConstraint* p2p = new btPoint2PointConstraint(
		*(bodyA.body), 
		*(bodyB.body), 
		btVector3(anchorA.x, anchorA.y, anchorA.z), 
		btVector3(anchorB.x, anchorB.y, anchorB.z));
	world->addConstraint(p2p);
	constraints.add(p2p);
	p2p->setDbgDrawSize(2.0f);
}

void ModulePhysics3D::AddConstraintHinge(PhysBody3D& bodyA, PhysBody3D& bodyB, const vec3& anchorA, const vec3& anchorB, const vec3& axisA, const vec3& axisB, bool disable_collision)
{
	btHingeConstraint* hinge = new btHingeConstraint(
		*(bodyA.body), 
		*(bodyB.body), 
		btVector3(anchorA.x, anchorA.y, anchorA.z),
		btVector3(anchorB.x, anchorB.y, anchorB.z),
		btVector3(axisA.x, axisA.y, axisA.z), 
		btVector3(axisB.x, axisB.y, axisB.z));

	world->addConstraint(hinge, disable_collision);
	constraints.add(hinge);
	hinge->setDbgDrawSize(2.0f);
}

// =============================================
void DebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
	line.origin.Set(from.getX(), from.getY(), from.getZ());
	line.destination.Set(to.getX(), to.getY(), to.getZ());
	line.color.Set(color.getX(), color.getY(), color.getZ());
	line.Render();
}

void DebugDrawer::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
{
	point.transform.translate(PointOnB.getX(), PointOnB.getY(), PointOnB.getZ());
	point.color.Set(color.getX(), color.getY(), color.getZ());
	point.Render();
}

void DebugDrawer::reportErrorWarning(const char* warningString)
{
	LOG("Bullet warning: %s", warningString);
}

void DebugDrawer::draw3dText(const btVector3& location, const char* textString)
{
	LOG("Bullet draw text: %s", textString);
}

void DebugDrawer::setDebugMode(int debugMode)
{
	mode = (DebugDrawModes) debugMode;
}

int	 DebugDrawer::getDebugMode() const
{
	return mode;
}
