#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;
class b2RevoluteJoint;
class b2PrismaticJoint;
enum scene_state
{
	START,
	PLAY,
	END,
};

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
	void Warp(uint iterator);
	void Light(bool &active);
	void FiveHpts(bool &active);
	void Fuel(bool &active);
	void Ignition(bool &active);
	void SunRun();
	void Passage();
	void blitbuttons();
	void Death();
	void Restart();

private:
	scene_state state;
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

	PhysBody* Passage_Sensor;

	SDL_Texture* board;
	SDL_Texture* flipper_Left;
	SDL_Texture* flipper_Right;
	SDL_Texture* balltxt;
	SDL_Texture* bar_points;


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

	//Constant for blit puntuation_bar
	
	//Puntuation variables
	int font_puntuation = -1;
	char text[10];
	char lives[10];
	uint balls;

	//Sensor bools
	bool warp, Wlight, Alight, Rlight, Plight, Wactive, Aactive, Ractive, Pactive;
	bool L2active, Iactive, Gactive, Hactive, Tactive;
	uint lightcounter = 1u;
	bool FiveH1, FiveH2;
	bool Factive, Uactive, Eactive, Lactive;
	bool Sun1, Sun2, Sun3, Sun1Reward, Sun2Reward, Sun3Reward;
	uint Suncounter = 1u;
	bool Ignition1, Ignition2, Ignition3;
	uint ignitioncounter;
	uint passagecounter;
	uint puntuation;
	int puntuation_x;
	bool end;
	float KickerjointMotor;
	

	//Animations
	SDL_Texture* fuel;
	SDL_Rect F_fuel;
	SDL_Rect U_fuel;
	SDL_Rect E_fuel;
	SDL_Rect L_fuel;

	SDL_Texture* lights;
	SDL_Rect L_lights;
	SDL_Rect I_lights;
	SDL_Rect G_lights;
	SDL_Rect H_lights;
	SDL_Rect T_lights;


	SDL_Texture* multipler;
	SDL_Rect multipler_x2;
	SDL_Rect multipler_x3;
	SDL_Rect multipler_x4;;
	SDL_Rect multipler_x6;
	SDL_Rect multipler_x8;

	SDL_Texture* ignition_button;
	SDL_Rect Ignition_button;
	
};

