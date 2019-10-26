#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;
class b2RevoluteJoint;


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
	b2RevoluteJoint* FlipperLJoint;
	b2RevoluteJoint* FlipperRJoint;
//	p2List<PhysBody*> circles;
//	p2List<PhysBody*> boxes;
//	p2List<PhysBody*> ricks;
/*
	PhysBody* sensor;
	bool sensed;
*/

	SDL_Texture* board;
	SDL_Texture* fliper_Left;
/*	SDL_Texture* box;
	SDL_Texture* rick;
	uint bonus_fx;
	p2Point<int> ray;
	bool ray_on;*/
};

