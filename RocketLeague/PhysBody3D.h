#ifndef __PhysBody3D_H__
#define __PhysBody3D_H__

#include "p2List.h"
#include "glmath.h"

class btRigidBody;
class btCollisionShape;
struct btDefaultMotionState;
class Module;

class Sphere;
class Cube;
class Cylinder;
class Plane;

class Primitive;

enum type
{
	BALL,
	GOAL,
	WALL,
	CAR
};

// =================================================
struct PhysBody3D
{
	friend class ModulePhysics3D;
public:
	PhysBody3D();
    PhysBody3D(btRigidBody* body);
	~PhysBody3D();

    void SetBody(Sphere* primitive, float mass);

	void Push(float x, float y, float z);
	void GetTransform(float* matrix) const;
	void SetTransform(const float* matrix) const;
	void SetPos(float x, float y, float z);

    void SetBody(btCollisionShape* shape, Primitive* parent, float mass);
	void SetAsSensor(bool is_sensor);
	btRigidBody* GetBody();

private:
	btRigidBody* body = nullptr;
    btCollisionShape* colShape;
    btDefaultMotionState* motionState;
public:
	bool is_sensor;
	type type;
    Primitive* parentPrimitive;
	p2List<Module*> collision_listeners;
};

#endif // __PhysBody3D_H__