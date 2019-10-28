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
	board = App->textures->Load("pinball/pinball_board.png");
	fliper_Left = App->textures->Load("pinball/fliper_Left.png");

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
		136, 146,
		140, 136,
		82, 10
	};
	int slingshotR[16] = {
	126, 12,
	114, 20,
	63, 139,
	64, 147,
	79, 152,
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

	rotAxisL = App->physics->CreateCircle(358, 1040, 10,"rotAxisL", b2_staticBody);
	rotAxisR = App->physics->CreateCircle(597, 1040, 10,"rotAxisR", b2_staticBody);
	FlipperL = App->physics->CreatePolygon(358, 1040, Flipper_L, 16);
	FlipperR = App->physics->CreatePolygon(510, 1023, Flipper_R, 16);
	SlingshotL = App->physics->CreatePolygon(200, 820, slingshotL, 16,"SlingshotL", b2_staticBody);
	SlingshotR = App->physics->CreatePolygon(580, 810, slingshotR, 16,"SlingshotR", b2_staticBody);
	Bumper1 = App->physics->CreateCircle(433, 350, 50,"Bumper1", b2_staticBody);
	Bumper2 = App->physics->CreateCircle(560, 450, 50,"Bumper2", b2_staticBody);
	Target1 = App->physics->CreatePolygon(445, 495, target1, 16,"Target1", b2_staticBody);
	Target2 = App->physics->CreatePolygon(675, 535, target2, 16,"Target2", b2_staticBody);

	piston1 = App->physics->CreateRectangle(830, 1100, 30, 15, "piston1", b2_staticBody);
	piston2 = App->physics->CreateRectangle(830, 1090, 30, 30, "piston1", b2_dynamicBody);
	sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, 1155, SCREEN_WIDTH, 50,"sensor");

	rotAxisL->listener = this;
	rotAxisR->listener = this;
	FlipperL->listener = this;
	FlipperR->listener = this;
	SlingshotL->listener = this;
	SlingshotR->listener = this;
	Bumper1->listener = this;
	Bumper2->listener = this;
	Target1->listener = this;
	Target2->listener = this;
	sensor->listener = this;

	ball = App->physics->CreateCircle(810, 1070, 15, "ball", b2_dynamicBody, 0.4);
	
	//ball->listener = this;


	FlipperLJoint = App->physics->CreateRevoluteJoint(FlipperL->body, rotAxisL->body, 20, 24, 0, 40);
	FlipperRJoint = App->physics->CreateRevoluteJoint(FlipperR->body, rotAxisR->body, 83, 19, -40, 0);
	PistonJoint = App->physics->CreatePrismaticJoint(piston1->body, piston2->body, 0, 0, 0, 100);
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
	float c;
	int a, b;

	int x, y;

	c = FlipperL->GetRotation();
	FlipperL->GetPosition(a, b);
	ball->GetPosition(x, y);

	FlipperLJoint->SetMotorSpeed(-1000 * DEGTORAD);
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) 
	{
		FlipperLJoint->SetMotorSpeed(1000 * DEGTORAD);
		FlipperL->GetPosition(a, b);
		c = FlipperL->GetRotation();

	}
	
	
	FlipperRJoint->SetMotorSpeed(1000 * DEGTORAD);
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) 
	{
		FlipperRJoint->SetMotorSpeed(-1000 * DEGTORAD);
	}
	PistonJoint->EnableMotor(false);
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		PistonJoint->EnableMotor(true);
	}

	p2SString title("Pinball_Dreams Box2D  mouse.x:%d mouse.y %d",
	App->input->GetMouseX(), App->input->GetMouseY());
	App->window->SetTitle(title.GetString());
	MoveCamera();


	//All renders
	App->renderer->Blit(board, 0, 0, NULL);
	App->renderer->Blit(fliper_Left, (a+5),(b+5), NULL, 1.0f, c, 0, 0);
	return UPDATE_CONTINUE;
}

void ModuleScenePinball::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	int x, y;

	//App->audio->PlayFx(bonus_fx);


	if (bodyA)
	{
		LOG("%s", bodyA->name);
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
		LOG("%s", bodyB->name);
		for (b2Fixture* f = bodyB->body->GetFixtureList(); f; f = f->GetNext()) {
			if (f->IsSensor()) {
				//LOG("Sensor B");
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