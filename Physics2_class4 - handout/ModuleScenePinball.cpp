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
	
	App->physics->CreateChain(0, 0, pinball_board, 94);
	

	rotAxisL = App->physics->CreateCircle(358, 1040, 10, b2_staticBody);
	rotAxisR = App->physics->CreateCircle(597, 1040, 10, b2_staticBody);
	FlipperL = App->physics->CreatePolygon(358, 1040, Flipper_L, 16);
	FlipperR = App->physics->CreatePolygon(510, 1023, Flipper_R, 16);
	

	sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, 1155, SCREEN_WIDTH, 50);

	sensor->listener = this;
	ball = App->physics->CreateCircle(810, 1070, 15, b2_dynamicBody, 0.4);
	
	//ball->listener = this;


	FlipperLJoint = App->physics->CreateRevoluteJoint(FlipperL->body, rotAxisL->body, 20, 24, 0, 40);
	FlipperRJoint = App->physics->CreateRevoluteJoint(FlipperR->body, rotAxisR->body, 83, 19, -40, 0);
	
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
	int x, y;
	ball->GetPosition(x, y);
	LOG("x %d x %d", x, y);
	FlipperLJoint->SetMotorSpeed(-1000 * DEGTORAD);
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
		FlipperLJoint->SetMotorSpeed(1000 * DEGTORAD);
	}
	FlipperRJoint->SetMotorSpeed(1000 * DEGTORAD);
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
		FlipperRJoint->SetMotorSpeed(-1000 * DEGTORAD);
	}

	p2SString title("Pinball_Dreams Box2D  mouse.x:%d mouse.y %d",
	App->input->GetMouseX(), App->input->GetMouseY());
	App->window->SetTitle(title.GetString());
	MoveCamera();
	App->renderer->Blit(board, 0, 0, NULL);
	
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