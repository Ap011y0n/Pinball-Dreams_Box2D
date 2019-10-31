#include "p2Defs.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleScenePinball.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModuleWindow.h"
#include "ModuleFonts.h"
#include <stdio.h>

ModuleScenePinball::ModuleScenePinball(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleScenePinball::~ModuleScenePinball()
{}

// Load assets
bool ModuleScenePinball::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	warp = Wlight = Alight = Rlight = Plight = Wactive = Aactive = Ractive = Pactive = false;
	Lactive = Iactive = Gactive = Hactive = Tactive = false; 
	lightcounter = 1;
	
	board = App->textures->Load("pinball/pinball_board_2.png");
	flipper_Left = App->textures->Load("pinball/fliper_Left.png");
	flipper_Right = App->textures->Load("pinball/fliper_Right.png");
	balltxt = App->textures->Load("pinball/ball.png");
	font_puntuation = App->fonts->Load("pinball/numbers.png", "1234567890", 1);
	App->renderer->camera.x = App->renderer->camera.y = 0;


	int pinball_board[94] = {
	194, 341,
	228, 288,
	389, 128,
	456, 85,
	532, 67,
	591, 69,
	685, 98,
	740, 137,
	787, 183,
	825, 241,
	843, 304,
	849, 359,
	850, 1101,
	810, 1101,
	806, 388,
	803, 348,
	792, 298,
	770, 232,
	738, 198,
	708, 170,
	689, 172,
	688, 220,
	706, 230,
	737, 234,
	790, 466,
	801, 474,
	800, 569,
	732, 698,
	732, 767,
	800, 834,
	801, 1011,
	789, 1034,
	589, 1127,
	590, 1230,
	370, 1225,
	369, 1130,
	197, 1050,
	178, 1034,
	179, 835,
	222, 792,
	181, 747,
	194, 735,
	198, 559,
	189, 542,
	189, 523,
	179, 505,
	183, 383
	};
	int Flipper_L[16] = {
	9, 34,
	88, 65,
	99, 68,
	106, 66,
	108, 58,
	100, 50,
	20, 7,
	9, 15
	};
	int Flipper_R[16] = {
	1, 61,
	1, 53,
	6, 47,
	86, 5,
	99, 12,
	99, 29,
	14, 64,
	6, 64
	};
	int MappartL[24] = {
	17, 39,
	14, 44,
	17, 50,
	15, 160,
	21, 170,
	138, 221,
	148, 210,
	155, 207,
	27, 161,
	22, 148,
	22, 48,
	25, 42
	};
	int MappartR[22] = {
	181, 40,
	177, 47,
	178, 52,
	178, 160,
	28, 211,
	38, 215,
	40, 227,
	175, 170,
	185, 161,
	184, 51,
	187, 47
	};
	int slingshotL[16] = {
	74, 10,
	71, 15,
	69, 123,
	71, 128,
	122, 149,
	132, 146,
	135, 140,
	78, 14
	};
	int slingshotR[16] = {
	127, 14,
	117, 24,
	67, 142,
	69, 150,
	82, 151,
	129, 135,
	134, 126,
	133, 20
	};
	int MapTunnel[52] = {
	144, 388,
	78, 250,
	81, 222,
	98, 184,
	112, 161,
	256, 19,
	273, 16,
	281, 21,
	280, 67,
	269, 76,
	253, 73,
	226, 63,
	209, 73,
	113, 170,
	112, 186,
	121, 205,
	137, 236,
	187, 336,
	180, 340,
	131, 241,
	120, 232,
	104, 232,
	92, 242,
	88, 258,
	148, 378,
	149, 385
	};
	int lane[24] = {
	4, 18,
	8, 9,
	15, 6,
	26, 6,
	32, 10,
	34, 17,
	34, 53,
	33, 61,
	27, 65,
	11, 65,
	5, 61,
	4, 52
	};
	int target1[16] = {
	15, 14,
	16, 26,
	122, 81,
	135, 80,
	141, 67,
	131, 56,
	32, 7,
	22, 7
	};
	int target2[16] = {
	42, 107,
	30, 114,
	19, 109,
	18, 98,
	58, 19,
	69, 13,
	79, 18,
	79, 29
	};
	
	App->physics->CreateChain(0, 0, pinball_board, 94);
	App->physics->CreateChain(200, 816, MappartL, 24);
	App->physics->CreateChain(580, 816, MappartR, 22);
	App->physics->CreateChain(155, 150, MapTunnel, 52);
	App->physics->CreateChain(473, 183, lane, 24);
	App->physics->CreateChain(613, 183, lane, 24);
	App->physics->CreateChain(542, 192, lane, 24);

	//Ball
	ball = App->physics->CreateCircle(810, 1070, 15, "ball", b2_dynamicBody, 0.4);
	//ball = App->physics->CreateCircle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 15, "ball", b2_staticBody, 0.4);
	//map components
	rotAxisL = App->physics->CreateCircle(358, 1040, 10,"rotAxisL", b2_staticBody);
	rotAxisR = App->physics->CreateCircle(597, 1040, 10,"rotAxisR", b2_staticBody);
	FlipperL = App->physics->CreatePolygon(358, 1040, Flipper_L, 16, "Flipper_L");
	FlipperR = App->physics->CreatePolygon(510, 1023, Flipper_R, 16, "Flipper_L");
	SlingshotL = App->physics->CreatePolygon(200, 820, slingshotL, 16,"SlingshotL", b2_staticBody);
	SlingshotR = App->physics->CreatePolygon(580, 810, slingshotR, 16,"SlingshotR", b2_staticBody);
	Bumper1 = App->physics->CreateCircle(433, 350, 50,"Bumper1", b2_staticBody);
	Bumper2 = App->physics->CreateCircle(560, 450, 50,"Bumper2", b2_staticBody);
	Target1 = App->physics->CreatePolygon(445, 495, target1, 16,"Target1", b2_staticBody);
	Target2 = App->physics->CreatePolygon(675, 535, target2, 16,"Target2", b2_staticBody);

	//Pistons
	kickerBase = App->physics->CreateRectangle(830, 1100, 30, 15, "piston1", b2_staticBody);
	kicker = App->physics->CreateRectangle(830, 1090, 30, 30, "piston2", b2_dynamicBody);
	SSLPiston = App->physics->CreateRectangle(300, 920, 150, 5, "SSLPiston");
	SSRPiston = App->physics->CreateRectangle(690, 920, 150, 5, "SSRPiston");
	SSLPistonBase = App->physics->CreateRectangle(295, 920, 15, 15, "SSLPistonBase", b2_staticBody);
	SSRPistonBase = App->physics->CreateRectangle(682, 920, 15, 15, "SSRPistonBase", b2_staticBody);

	//Sensors
	DeathSensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, 1155, SCREEN_WIDTH, 50, "DeathSensor");
	
	ignition1 = App->physics->CreateRectangleSensor(471, 534, 30, 5, "ignition1", 28);
	ignition2 = App->physics->CreateRectangleSensor(507, 553, 30, 5, "ignition2", 28);
	ignition3 = App->physics->CreateRectangleSensor(545, 571, 30, 5, "ignition3", 28);

	sun = App->physics->CreateRectangleSensor(753, 620, 30, 100, "sun", 25);

	F_sensor = App->physics->CreateRectangleSensor(218, 575, 37, 37, "F_sensor");
	U_sensor = App->physics->CreateRectangleSensor(218, 622, 37, 37, "U_sensor");
	E_sensor = App->physics->CreateRectangleSensor(218, 669, 37, 37, "E_sensor");
	L_sensor = App->physics->CreateRectangleSensor(218, 716, 37, 37, "L_sensor");

	sensor500 = App->physics->CreateRectangleSensor(306, 293, 50, 10, "sensor500", -45);
	sensor502 = App->physics->CreateRectangleSensor(346, 253, 50, 10, "sensor502", -45);
																 
	W_sensor = App->physics->CreateRectangleSensor(459, 180, 37, 37, "W_sensor");
	A_sensor = App->physics->CreateRectangleSensor(525, 198, 37, 37, "A_sensor");
	R_sensor = App->physics->CreateRectangleSensor(595, 199, 37, 37, "R_sensor");
	P_sensor = App->physics->CreateRectangleSensor(666, 185, 37, 37, "P_sensor");

	L2_sensor = App->physics->CreateRectangleSensor(734, 265, 5, 30, "L2_sensor", -10);
	I_sensor = App->physics->CreateRectangleSensor( 744, 308, 5, 30, "I_sensor" , -10);
	G_sensor = App->physics->CreateRectangleSensor( 756, 351, 5, 30, "G_sensor" , -10);
	H_sensor = App->physics->CreateRectangleSensor( 767, 394, 5, 30, "H_sensor" , -10);
	T_sensor = App->physics->CreateRectangleSensor( 778, 437, 5, 30, "T_sensor" , -10);
	

	//joints
	FlipperLJoint = App->physics->CreateRevoluteJoint(FlipperL->body, rotAxisL->body, 20, 24, 0, 40);
	FlipperRJoint = App->physics->CreateRevoluteJoint(FlipperR->body, rotAxisR->body, 83, 19, -40, 0);
	KickerJoint = App->physics->CreatePrismaticJoint(kickerBase->body, kicker->body, 0, 0, 0, 100,1000);
	SSLJoint = App->physics->CreatePrismaticJoint(SSLPistonBase->body, SSLPiston->body, 0, -10, 20, 30, 400, 66, 0.5 ,0.5);
	SSRJoint = App->physics->CreatePrismaticJoint(SSRPistonBase->body, SSRPiston->body, 0, -10, 20, 30, 400, -66, -0.5, 0.5);

	ball->listener = this;

	return ret;
}

// Load assets
bool ModuleScenePinball::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleScenePinball::Update()
{
	Ball_rotation = ball->GetRotation();

	Flipper_L_rotation = FlipperL->GetRotation();
	FlipperL->GetPosition(Flipper_L_positon_x, Flipper_L_positon_y);

	Flipper_R_rotation = FlipperR->GetRotation();
	FlipperR->GetPosition(Flipper_R_positon_x, Flipper_R_positon_y);


	int x, y;
	ball->GetPosition(x, y);

	FlipperLJoint->SetMotorSpeed(-1000 * DEGTORAD);
	FlipperRJoint->SetMotorSpeed(1000 * DEGTORAD);
	
	if (KickerJoint->IsMotorEnabled())KickerJoint->EnableMotor(false);
	if(SSRJoint->IsMotorEnabled())SSRJoint->EnableMotor(false);
	if (SSLJoint->IsMotorEnabled())SSLJoint->EnableMotor(false);

	Input();

	p2SString title("Pinball_Dreams Box2D  mouse.x:%d mouse.y %d",
	App->input->GetMouseX(), App->input->GetMouseY());
	App->window->SetTitle(title.GetString());
	MoveCamera();


	//All renders
	App->renderer->Blit(board, 0, 0, NULL);

	App->renderer->Blit(flipper_Left, (Flipper_L_positon_x+5),(Flipper_L_positon_y+10), NULL, 1.0f, Flipper_L_rotation, -5, -5);
	App->renderer->Blit(flipper_Right, (Flipper_R_positon_x), (Flipper_R_positon_y +5), NULL, 1.0f, Flipper_R_rotation, -1,0);
	App->renderer->Blit(balltxt, x, y, NULL, 1.0f, Ball_rotation, 15, 15);
	
	//Puntuation
	currentpts.value = currentpts.value+100;
	sprintf_s(text, 10, "%d",currentpts.value);
	if (currentpts.value < 9) {
		puntuation_x = 800;
	}
	if (currentpts.value >= 10) {
		puntuation_x = 768;
	}
	if (currentpts.value >= 100) {
		puntuation_x = 736;
	}
	if (currentpts.value >= 1000) {
		puntuation_x = 704;
	}
	if (currentpts.value >= 10000) {
		puntuation_x = 672;
	}
	if (currentpts.value >= 100000) {
		puntuation_x = 640;
	}
	App->fonts->BlitText(puntuation_x,App->renderer->camera.y+4, font_puntuation,text);
	return UPDATE_CONTINUE;
}

void ModuleScenePinball::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	int x, y;

	//App->audio->PlayFx(bonus_fx);


	if (bodyA)
	{
		for (b2Fixture* f = bodyA->body->GetFixtureList(); f; f = f->GetNext()) {
			if (f->IsSensor()) {
				//LOG("Sensor A");
			}
		}
		bodyA->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}

	if (bodyB)
	{
		if (bodyB->name == "SSRPiston")SSRJoint->EnableMotor(true);
		if (bodyB->name == "SSLPiston")SSLJoint->EnableMotor(true);
		if (bodyB->name == "Bumper1" || bodyB->name == "Bumper2") {
			int x1 = 0, x2 = 0;
			b2Vec2 vect(x1, x2);
			ball->GetPosition(x1, x2);
		
			ball->body->ApplyLinearImpulse(b2Vec2(2, 2), vect, true);
		}
		for (b2Fixture* f = bodyB->body->GetFixtureList(); f; f = f->GetNext()) {
			if (f->IsSensor()) {
				getSensor(bodyB->name);
			}
		}
		bodyB->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}
}

void ModuleScenePinball::MoveCamera() {
	
	int x, y;
	ball->GetPosition(x, y);
//	LOG("camera.y = %d", App->renderer->camera.y);
	App->renderer->camera.y =-1*y +SCREEN_HEIGHT/2;
}
void ModuleScenePinball::Input() {
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		FlipperLJoint->SetMotorSpeed(1000 * DEGTORAD);
		FlipperL->GetPosition(Flipper_L_positon_x, Flipper_L_positon_y);
		Flipper_L_rotation = FlipperL->GetRotation();

	}
	
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		FlipperRJoint->SetMotorSpeed(-1000 * DEGTORAD);
		FlipperR->GetPosition(Flipper_R_positon_x, Flipper_R_positon_y);
		Flipper_R_rotation = FlipperR->GetRotation();
	}
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		KickerJoint->EnableMotor(true);
	
	}
	if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN) {
		LOG("%d", currentpts.multipilier);
	
	}
	
	
}

//recives an index, then proceed to calculate the number of active letters, and then add a multiplier to score
void ModuleScenePinball::Warp(int index) {
	
	switch (index) {
	case 1:
		if (Wlight) {
			Wactive = true;
			Wlight = false; 
		break;
		}
		if (!Wlight) { 
			Wlight = true;
			Alight = false;
			Rlight = false;
			Plight = false;
			break;
		}
		
	case 2:
		if (Alight) {
			Aactive = true;
			Alight = false;
			break;
		}
		if (!Alight) {
			Alight = true;
			Wlight = false;
			Rlight = false;
			Plight = false;
			break;
		}

	case 3:
		if (!Rlight) {
			Ractive = true;
			Rlight = false;
			break;
		}
		if (!Rlight) {
			Rlight = true;
			Wlight = false;
			Alight = false;
			Plight = false;
			break;
		}

	case 4:
		if (!Plight) {
			Pactive = true;
			Plight = false;
			break;
		}
		if (!Plight) {
			Plight = true;
			Wlight = false;
			Alight = false;
			Rlight = false;
			break;
		}
		
		}
	if (Wactive && Aactive && Ractive && Pactive) {
		Wactive = Aactive = Ractive = Pactive = false;
		if (currentpts.multipilier < 8) {
			if (currentpts.multipilier >= 4)	currentpts.multipilier ++;
				currentpts.multipilier ++;
		}
	}

}
//receives a light bool, and activates it
void ModuleScenePinball::Light(bool &active) {
	active = true;
	if (Lactive && Iactive && Gactive && Hactive && Tactive) {
		if (lightcounter == 3) {
			LOG("contador %d", lightcounter);
			lightcounter++;
		}
		if (lightcounter == 2) {
			LOG("contador %d", lightcounter);
			lightcounter++;
		}
		if (lightcounter == 1) {
			LOG("contador %d", lightcounter);
			lightcounter++;
		}
		
		if (lightcounter == 4)lightcounter = 1;
		Lactive = Iactive = Gactive = Hactive = Tactive = false;
		
	}
}

//Receives the name of a sensor, then starts a determinate proces depending of it's name property
void ModuleScenePinball::getSensor(char* name) {
	if (name == "DeathSensor") {

	}
	if (name == "ignition1") {

	}
	if (name == "ignition2") {

	}
	if (name == "ignition3") {

	}
	if (name == "sun") {

	}
	if (name == "F_sensor") {

	}
	if (name == "U_sensor") {

	}
	if (name == "E_sensor") {

	}
	if (name == "L_sensor") {

	}
	if (name == "sensor500") {

	}
	if (name == "sensor502") {

	}
	if (name == "W_sensor") {
		Warp(1);
	}
	if (name == "A_sensor") {
		Warp(2);
	}
	if (name == "R_sensor") {
		Warp(3);
	}
	if (name == "P_sensor") {
		Warp(4);
	}
	if (name == "L2_sensor") {
		Light(Lactive);
	}
	if (name == "I_sensor") {
		Light(Iactive);
	}
	if (name == "G_sensor") {
		Light(Gactive);
	}
	if (name == "H_sensor") {
		Light(Hactive);
	}
	if (name == "T_sensor") {
		Light(Tactive);
	}
	

}

