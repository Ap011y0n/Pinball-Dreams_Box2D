#pragma once
#include "Module.h"
#include "Globals.h"
#include "Box2D/Box2D/Box2D.h"

#define GRAVITY_X 0.0f
#define GRAVITY_Y -7.0f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)


// Small class to return to other modules to track position and rotation of physics bodies
class PhysBody
{
public:
	PhysBody() : listener(NULL), body(NULL)
	{}

	char* name;
	void GetPosition(int& x, int &y) const;
	float GetRotation() const;
	bool Contains(int x, int y) const;
	int RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const;

public:
	int width, height;
	b2Body* body;
	
	Module* listener;
};

// Module --------------------------------------
class ModulePhysics : public Module, public b2ContactListener // TODO
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	PhysBody* CreateCircle(int x, int y, int radius, char* name = "", b2BodyType type = b2_dynamicBody, float restitution = 0.0f);
	PhysBody* CreateRectangle(int x, int y, int width, int height, char* name = "", b2BodyType type = b2_dynamicBody);
	PhysBody* CreateRectangleSensor(int x, int y, int width, int height, char* name = "", int angle = 0, b2BodyType type = b2_staticBody);
	PhysBody* CreateChain(int x, int y, int* points, int size, char* name = "", b2BodyType type = b2_staticBody);
	PhysBody* CreatePolygon(int x, int y, int* points, int size, char* name = "", b2BodyType type = b2_dynamicBody);
	b2RevoluteJoint* CreateRevoluteJoint(b2Body* bodyA, b2Body* bodyB, int AnchorX, int AnchorY, int lowerAngle, int upperAngle);
	b2PrismaticJoint* CreatePrismaticJoint(b2Body* bodyA, b2Body* bodyB, int AnchorX, int AnchorY, int lowerTranslation, int upperTranslation, int maxforce, int referenceAngle = 0, float directionx = 0, float directiony = 1);


	// b2ContactListener ---
	void BeginContact(b2Contact* contact);
	/*	b2RevoluteJointDef revoluteJointDef;*/
	b2RevoluteJoint* revolutejoint;
	b2PrismaticJoint* prismaticjoint;
private:

	bool debug;
	b2World* world;
	b2MouseJoint* mouse_joint;
	b2Body* ground;
	b2Body* body_clicked;
	bool selected = false;
};