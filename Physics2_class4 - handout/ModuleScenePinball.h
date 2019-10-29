#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;
class b2RevoluteJoint;
class b2PrismaticJoint;

class ModuleScenePinball : public Module
{
public:
	ModuleScenePinball(Application* app, bool start_enabled = true);
	~ModuleScenePinball();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);
	void MoveCamera();
private:

public:
	PhysBody* ball;
	PhysBody* rotAxisL;
	PhysBody* rotAxisR;
	PhysBody* FlipperL;
	PhysBody* FlipperR;
	PhysBody* SlingshotL;
	PhysBody* SlingshotR;
	PhysBody* Bumper1;
	PhysBody* Bumper2;
	PhysBody* Target1;
	PhysBody* Target2;
	// sensor PhysBody* Hole;
	PhysBody* sensor;
	PhysBody* piston1;
	PhysBody* piston2;
	b2RevoluteJoint* FlipperLJoint;
	b2RevoluteJoint* FlipperRJoint;
	b2PrismaticJoint* PistonJoint;
//	p2List<PhysBody*> circles;
//	p2List<PhysBody*> boxes;
//	p2List<PhysBody*> ricks;
/*
	PhysBody* sensor;
	bool sensed;
*/

	SDL_Texture* board;
	SDL_Texture* fliper_Left;
	SDL_Texture* fliper_Right;
	SDL_Texture* balltxt;
/*	SDL_Texture* box;
	SDL_Texture* rick;
	uint bonus_fx;
	p2Point<int> ray;
	bool ray_on;*/

	// Constants for blit flipper Right
	float Flipper_R_rotation = 0;
	int Flipper_R_positon_x = 0;
	int Flipper_R_positon_y = 0;

	//Constants for blit fliper Left
	float Flipper_L_rotation = 0;
	int Flipper_L_positon_x = 0;
	int Flipper_L_positon_y = 0;

	//Constants for blit ball
	float Ball_rotation = 0;

};

