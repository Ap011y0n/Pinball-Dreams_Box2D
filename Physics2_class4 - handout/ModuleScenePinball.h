#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;
class b2RevoluteJoint;
class b2PrismaticJoint;
class punctuation
{
public:
	uint value = 0u;
	uint multipilier = 1u;
	punctuation()
	{}
	~punctuation()
	{}
	//operators
	int operator+= (const int add) 
	{
		int ret = add * multipilier + value;
		value = ret;
		return ret;
	}

};

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
	void Input();
	void getSensor(char* name);
	void Warp(int iterator = 0);
	void Light(bool &active);

private:
	punctuation currentpts;

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

	PhysBody* kickerBase;
	PhysBody* kicker;
	PhysBody* SSLPiston;
	PhysBody* SSRPiston;
	PhysBody* SSLPistonBase;
	PhysBody* SSRPistonBase;
	b2RevoluteJoint* FlipperLJoint;
	b2RevoluteJoint* FlipperRJoint;
	b2PrismaticJoint* KickerJoint;
	b2PrismaticJoint* SSLJoint;
	b2PrismaticJoint* SSRJoint;

	PhysBody* DeathSensor;
	PhysBody* ignition1;
	PhysBody* ignition2;
	PhysBody* ignition3;

	PhysBody* sun;

	PhysBody* F_sensor;
	PhysBody* U_sensor;
	PhysBody* E_sensor;
	PhysBody* L_sensor;

	PhysBody* sensor500;
	PhysBody* sensor502;

	PhysBody* W_sensor;
	PhysBody* A_sensor;
	PhysBody* R_sensor;
	PhysBody* P_sensor;

	PhysBody* L2_sensor;
	PhysBody* I_sensor;
	PhysBody* G_sensor;
	PhysBody* H_sensor;
	PhysBody* T_sensor;

	SDL_Texture* board;
	SDL_Texture* flipper_Left;
	SDL_Texture* flipper_Right;
	SDL_Texture* balltxt;

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

	//Puntuation variables
	int font_puntuation = -1;
	char text[10];

	//Sensor bools
	bool warp, Wlight, Alight, Rlight, Plight, Wactive, Aactive, Ractive, Pactive;
	bool Lactive, Iactive, Gactive, Hactive, Tactive;
	uint lightcounter = 1u;

	

	uint puntuation;
	int puntuation_x;
};

