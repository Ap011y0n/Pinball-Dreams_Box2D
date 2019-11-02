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
	// We define al the rects so we can blit them later on
	F_fuel.x = 0;
	F_fuel.y = 0;
	F_fuel.w = 36;
	F_fuel.h = 36;

	U_fuel.x = 36;
	U_fuel.y = 0;
	U_fuel.w = 36;
	U_fuel.h = 36;

	E_fuel.x = 72;
	E_fuel.y = 0;
	E_fuel.w = 36;
	E_fuel.h = 36;

	L_fuel.x = 108;
	L_fuel.y = 0;
	L_fuel.w = 36;
	L_fuel.h = 36;
	
	L_lights.x = 0;
	L_lights.y = 0;
	L_lights.w = 32;
	L_lights.h = 32;
	
	I_lights.x = 32;
	I_lights.y = 0;
	I_lights.w = 32;
	I_lights.h = 32;
	
	G_lights.x = 64;
	G_lights.y = 0;
	G_lights.w = 32;
	G_lights.h = 32;
	
	H_lights.x = 98;
	H_lights.y = 0;
	H_lights.w = 32;
	H_lights.h = 32;
	
	T_lights.x = 130;
	T_lights.y = 0;
	T_lights.w = 32;
	T_lights.h = 32;

	Ignition_button.x = 0;
	Ignition_button.y = 0;
	Ignition_button.w = 31;
	Ignition_button.h = 31;

	Ssun_button.x = 0;
	Ssun_button.y = 0;
	Ssun_button.w = 31;
	Ssun_button.h = 31;

	Usun_button.x = 32;
	Usun_button.y = 0;
	Usun_button.w = 31;
	Usun_button.h = 31;

	Nsun_button.x = 64;
	Nsun_button.y = 0;
	Nsun_button.w = 31;
	Nsun_button.h = 31;

	W_warp.x = 0;
	W_warp.y = 0;
	W_warp.w = 36;
	W_warp.h = 36;

	A_warp.x = 37;
	A_warp.y = 0;
	A_warp.w = 36;
	A_warp.h = 36;

	R_warp.x = 74;
	R_warp.y = 0;
	R_warp.w = 36;
	R_warp.h = 36;

	P_warp.x = 111;
	P_warp.y = 0;
	P_warp.w = 36;
	P_warp.h = 36;

	W_warp.x = 0;
	W_warp.y = 0;
	W_warp.w = 36;
	W_warp.h = 36;

	multiplier_x2.x = 0;
	multiplier_x2.y = 0;
	multiplier_x2.w = 58;
	multiplier_x2.h = 29;

	multiplier_x3.x = 59;
	multiplier_x3.y = 0;
	multiplier_x3.w = 58;
	multiplier_x3.h = 29;

	multiplier_x4.x = 118;
	multiplier_x4.y = 0;
	multiplier_x4.w = 58;
	multiplier_x4.h = 29;

	multiplier_x6.x = 177;
	multiplier_x6.y = 0;
	multiplier_x6.w = 58;
	multiplier_x6.h = 29;

	multiplier_x8.x = 236;
	multiplier_x8.y = 0;
	multiplier_x8.w = 58;
	multiplier_x8.h = 29;

	number_50.x = 0;
	number_50.y = 0;
	number_50.w = 34;
	number_50.h = 34;

	number_100.x = 35;
	number_100.y = 0;
	number_100.w = 34;
	number_100.h = 34;

	number_250.x = 70;
	number_250.y = 0;
	number_250.w = 34;
	number_250.h = 34;

	number_500.x = 105;
	number_500.y = 0;
	number_500.w = 34;
	number_500.h = 34;

	number_750.x = 0;
	number_750.y = 35;
	number_750.w = 34;
	number_750.h = 34;

	number_1000.x = 35;
	number_1000.y = 35;
	number_1000.w = 34;
	number_1000.h = 34;

	number_2500.x = 70;
	number_2500.y = 35;
	number_2500.w = 34;
	number_2500.h = 34;

	int width = 342;
	for (int i = 0; i < 9; i++) {
		ignitionRect[i].x = width*i;
		ignitionRect[i].y = 0;
		ignitionRect[i].h = 80;
		ignitionRect[i].w = 342;
	}

	int height = 46;
	for (int i = 0; i < 6; i++) {
		words[i].x = 0;
		words[i].y = height*i;
		words[i].h = 46;
		words[i].w = 160;
	}
	blue_button.x = 0;
	blue_button.y = 0;
	blue_button.w = 32;
	blue_button.h = 32;

	red_square.x = 0;
	red_square.y = 0;
	red_square.w = 46;
	red_square.h = 46;

	kickerRect.x = 0;
	kickerRect.y = 0;
	kickerRect.w = 25;
	kickerRect.h = 42;

	width = 30;
	for (int i = 0; i < 5; i++) {
		arrowrect[i].x = width * i;
		arrowrect[i].y = 0;
		arrowrect[i].h = 46;
		arrowrect[i].w = 30;
	}
}

ModuleScenePinball::~ModuleScenePinball()
{}

// Load assets
bool ModuleScenePinball::Start()
{
	LOG("Loading Intro assets");

	bool ret = true;
	//We reset most variables value with this function, here we use it to initializa them
	ResetVar();

	balls = 3;
	end = false;
	KickerjointMotor = 0;
	state = START;
	movecam = true;
	App->renderer->camera.y = 0;
	CurrScore = true;
	PrevScore = MaxScore = false;
	Kickerposy = 1107;

	board = App->textures->Load("Data/Images/pinball_board.png");
	flipper_Left = App->textures->Load("Data/Images/fliper_Left.png");
	flipper_Right = App->textures->Load("Data/Images/fliper_Right.png");
	balltex = App->textures->Load("Data/Images/ball.png");
	bar_points= App->textures->Load("Data/Images/bar_points.png");
	fuel= App->textures->Load("Data/Images/Fuel_letters.png");
	lights = App->textures->Load("Data/Images/Light_letters.png");
	ignition_button= App->textures->Load("Data/Images/red_button.png");
	sun_button = App->textures->Load("Data/Images/sun_letters.png");
	warp_button = App->textures->Load("Data/Images/Warp_letters.png");
	multiplier_button = App->textures->Load("Data/Images/multiplier_letters.png");
	numbers_buttons = App->textures->Load("Data/Images/numbers_buttons.png");
	ignition = App->textures->Load("Data/Images/ignition.png");
	Blue_button = App->textures->Load("Data/Images/blue_button.png");
	Red_square = App->textures->Load("Data/Images/red_bar.png");
	Words = App->textures->Load("Data/Images/word.png");
	Kicker = App->textures->Load("Data/Images/kicker.png");
	arrows = App->textures->Load("Data/Images/Arrows.png");

	font_puntuation = App->fonts->Load("Data/Images/numbers.png", "1234567890", 1);
	//Music and Fx
	App->audio->PlayMusic("Data/Music/Soundtrack_1_.ogg");//THIS IS THE VERSION LOW VOLUME FOR THE SOUNDTRACK SO WE CAN HEAR ALL THE FX
	App->audio->LoadFx("Data/Music/50_giant_ball_fx.wav");
	App->audio->LoadFx("Data/Music/flippers_fx.wav");
	App->audio->LoadFx("Data/Music/warp_fx.wav");
	App->audio->LoadFx("Data/Music/triangle_fx.wav");
	App->audio->LoadFx("Data/Music/spell_inition_fx.wav");
	App->audio->LoadFx("Data/Music/fuel_fx.wav");
	App->audio->LoadFx("Data/Music/losing_fx.wav");

	App->renderer->camera.x = App->renderer->camera.y = 0;
	
	//Create all bodies in scene
	CreateBodies();
	//Create all joints
	FlipperLJoint = App->physics->CreateRevoluteJoint(FlipperL->body, rotAxisL->body, 20, 24, 0, 40);
	FlipperRJoint = App->physics->CreateRevoluteJoint(FlipperR->body, rotAxisR->body, 83, 19, -40, 0);
	trapJoint = App->physics->CreateRevoluteJoint(BalltrapChain->body, Trap->body, 145, 265, -25, 60);

	KickerJoint = App->physics->CreatePrismaticJoint(kickerBase->body, kicker->body, 0, 0, 0, 100,1000);
	SSLJoint = App->physics->CreatePrismaticJoint(SSLPistonBase->body, SSLPiston->body, 0, -10, 20, 30, 400, 66, 0.5 ,0.5);
	SSRJoint = App->physics->CreatePrismaticJoint(SSRPistonBase->body, SSRPiston->body, 0, -10, 20, 30, 400, -66, -0.5, 0.5);
	DoorLJoint = App->physics->CreatePrismaticJoint(Map->body, doorL->body, 365, 115, -20, 100, 4000, -40, -0.5, 0.5);
	DoorRJoint = App->physics->CreatePrismaticJoint(Map->body, doorR->body, 760, 115, -20, 100, 4000, 35, 0.5, 0.5);
	
	ball->listener = this;
	
	return ret;
}

// Load assets
bool ModuleScenePinball::CleanUp()
{
	LOG("Unloading Intro scene");
	App->textures->Unload(board);
	App->textures->Unload(flipper_Left);
	App->textures->Unload(flipper_Right);
	App->textures->Unload(balltex);
	App->textures->Unload(bar_points); 
	App->textures->Unload(fuel);
	App->textures->Unload(lights);
	App->textures->Unload(ignition_button);
	App->textures->Unload(sun_button);
	App->textures->Unload(warp_button);
	App->textures->Unload(multiplier_button);
	App->textures->Unload(numbers_buttons);
	App->textures->Unload(ignition);
	App->textures->Unload(Blue_button);

	return true;
}

// Update: draw background
update_status ModuleScenePinball::Update()
{

	p2SString title("Pinball_Dreams Box2D");
	App->window->SetTitle(title.GetString());

	//Joints motors behaviours
	FlipperLJoint->SetMotorSpeed(-1000 * DEGTORAD);
	FlipperRJoint->SetMotorSpeed(1000 * DEGTORAD);
	if (trap)trapJoint->SetMotorSpeed(1000 * DEGTORAD);
	if (!trap)trapJoint->SetMotorSpeed(-1000 * DEGTORAD);
	if (traptimer + TIMER < SDL_GetTicks()) trap = false;
	if (KickerJoint->IsMotorEnabled())KickerJoint->EnableMotor(false);
	if(SSRJoint->IsMotorEnabled())SSRJoint->EnableMotor(false);
	if (SSLJoint->IsMotorEnabled())SSLJoint->EnableMotor(false);
	if (DoorLJoint->IsMotorEnabled())DoorLJoint->EnableMotor(false);
	if (DoorRJoint->IsMotorEnabled())DoorRJoint->EnableMotor(false);

	Input();
	MoveCamera();
	Blit();
	BlitUI();

	return UPDATE_CONTINUE;
}

void ModuleScenePinball::Blit() {
	//Get coord to blit the images
	Flipper_L_rotation = FlipperL->GetRotation();
	FlipperL->GetPosition(Flipper_L_positon_x, Flipper_L_positon_y);

	Flipper_R_rotation = FlipperR->GetRotation();
	FlipperR->GetPosition(Flipper_R_positon_x, Flipper_R_positon_y);

	int x, y;
	ball->GetPosition(x, y);

	//All renders
	App->renderer->Blit(board, 0, 0, NULL);
	App->renderer->Blit(Kicker, 817, Kickerposy, &kickerRect);

	App->renderer->Blit(flipper_Left, (Flipper_L_positon_x + 5), (Flipper_L_positon_y + 10), NULL, 1.0f, Flipper_L_rotation, -5, -5);
	App->renderer->Blit(flipper_Right, (Flipper_R_positon_x), (Flipper_R_positon_y + 5), NULL, 1.0f, Flipper_R_rotation, -1, 0);

	blitbuttons(); //This function will make all the blits for the animations

	App->renderer->Blit(ignition, 318, 663, &ignitionRect[ignitionit]);
	App->renderer->Blit(balltex, x, y, NULL, 1.0f, 0, 15, 15);

	App->renderer->Blit(bar_points, 142, -App->renderer->camera.y, NULL);
	App->renderer->Blit(Words, 191, -App->renderer->camera.y + 9, &words[worditerator]);
	
}

//This function is mainly used to blit the ui elements, we use module fonts to blit two words, 
//the number of balls remaining, and the score, which is capped to 100000000
void ModuleScenePinball::BlitUI() {
	int spacing;
	if (CurrScore) spacing = currentpts.value;
	if (PrevScore) spacing = previouspts.value;
	if (MaxScore) spacing = highestpts.value;

	if (spacing < 9) {
		puntuation_x = 800;
	}
	if (spacing >= 10) {
		puntuation_x = 768;
	}
	if (spacing >= 100) {
		puntuation_x = 736;
	}
	if (spacing >= 1000) {
		puntuation_x = 704;
	}
	if (spacing >= 10000) {
		puntuation_x = 672;
	}
	if (spacing >= 100000) {
		puntuation_x = 640;
	}
	if (spacing >= 1000000) {
		puntuation_x = 608;
	}
	if (spacing >= 10000000) {
		puntuation_x = 576;
	}
	if (spacing >= 100000000) {
		puntuation_x = 544;
		spacing = 100000000;
	}

	sprintf_s(points, 10, "%d", spacing);
	sprintf_s(lives, 10, "%d", balls);

	App->fonts->BlitText(puntuation_x - 1, 4, font_puntuation, points);

	if (worditerator == 1)
		App->fonts->BlitText(351, 4, font_puntuation, lives);
}


void ModuleScenePinball::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	int x, y;
//Since we only enabled the ball to be the listener, we'll use body b for collision detection

/*	if (bodyA)
	{
		for (b2Fixture* f = bodyA->body->GetFixtureList(); f; f = f->GetNext()) {
			if (f->IsSensor()) {
			}
		}
	}
*/
	//When an object collides, we get its name, and then decide what to do with this ionformation
	if (bodyB)
	{
		if (bodyB->name == "SSRPiston") 
		{ 
			SSRJoint->EnableMotor(true); App->audio->PlayFx(4, 0);
		}
		if (bodyB->name == "SSLPiston") 
		{
			SSLJoint->EnableMotor(true); App->audio->PlayFx(4, 0);
		}
		if (bodyB->name == "Bumper1" || bodyB->name == "Bumper2") {

			App->audio->PlayFx(1, 0);
			int x1 = 0, x2 = 0;
			b2Vec2 vect(x1, x2);
			ball->GetPosition(x1, x2);
			ball->body->ApplyLinearImpulse(b2Vec2(2, 2), vect, true);
			currentpts += 500;
		}

		if (bodyB->name == "Flipper_R" || bodyB->name == "Flipper_L") {
			App->audio->PlayFx(2, 0);
		}

	//In case it's a sensor, we call the function that manages this type of objects
		for (b2Fixture* f = bodyB->body->GetFixtureList(); f; f = f->GetNext()) {
			if (f->IsSensor()) {
				getSensor(bodyB->name);
			}
		}
	}
}

void ModuleScenePinball::MoveCamera() {
	//Depending of the state of the game, camera behaves differently, if the player is actually playing the game, it will follow the ball
	if (state == START) {
		if (movecam) {
			App->renderer->camera.y--;
		}
		if (!movecam) {
			App->renderer->camera.y++;
		}
		if (App->renderer->camera.y > -1) {
			movecam = !movecam;
		}
		if (App->renderer->camera.y < -384) {
			movecam = !movecam;
		}
	}
	if (state == PLAY) {
		int x, y;
		ball->GetPosition(x, y);
		App->renderer->camera.y = -1 * y + SCREEN_HEIGHT / 2;
		if (App->renderer->camera.y > 0) {
			App->renderer->camera.y = 0;
		}
		if (App->renderer->camera.y < -385) {
			App->renderer->camera.y = -385;
		}
	}

	if (state == END) {
		if (movecam) {
			App->renderer->camera.y--;
		}
		if (!movecam) {
			App->renderer->camera.y++;
		}
		if (App->renderer->camera.y > -1) {
			movecam = !movecam;
		}
		if (App->renderer->camera.y < -384) {
			movecam = !movecam;
		}
	}
	
	}

void ModuleScenePinball::Input() {
	//Input in the middle of a match
	if(state == PLAY){
	//Left flipper
		//Changes it's joint motor value
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		FlipperLJoint->SetMotorSpeed(1000 * DEGTORAD);
		FlipperL->GetPosition(Flipper_L_positon_x, Flipper_L_positon_y);
		Flipper_L_rotation = FlipperL->GetRotation();

	}
	//Right flipper
		//Changes it's joint motor value
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		FlipperRJoint->SetMotorSpeed(-1000 * DEGTORAD);
		FlipperR->GetPosition(Flipper_R_positon_x, Flipper_R_positon_y);
		Flipper_R_rotation = FlipperR->GetRotation();
	}
	//Kicker behaviour, charge while pressing down button, and launches the ball when releasing
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
	
		if (KickerjointMotor < 2000) {
			KickerjointMotor += 20;
			kickerRect.h = 42 - KickerjointMotor * 0.0165;
			Kickerposy = 1107 + KickerjointMotor * 0.0165;
		}
	KickerJoint->EnableMotor(false);
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
	{
		KickerJoint->EnableMotor(true);
		KickerJoint->SetMotorSpeed(PIXEL_TO_METERS(KickerjointMotor));
		KickerjointMotor = 0;
		kickerRect.h = 42;
		Kickerposy = 1107;

	}
}
	//Input while not playing a match
	//Press 1 to start playing
	if (state != PLAY) {
		if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
		{
			ball->transform = true;
			balls = 3;
			state = PLAY;
			worditerator = 1;
		}
	}
//Input availaable in all phasesç
	//Iterate between current ball, current score, previoous score and highscore
	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		worditerator = 1;
	}
	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		worditerator = 5;
		CurrScore = true;
		PrevScore = MaxScore = false;
	}
	if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
	{
		worditerator = 4;
		PrevScore = true;
		CurrScore = MaxScore = false;
	}
	if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN)
	{
		worditerator = 3;
		MaxScore = true;
		CurrScore = PrevScore = false;
	}
	
	
}

//recives an index and lights that letter, if that letter was already lightened, activates it,
//then proceed to calculate the number of active letters, and then add a multiplier to score
void ModuleScenePinball::Warp(uint index) {
	
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
		if (Rlight) {
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
		if (Plight) {
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
//If all of them are active a reward is now obtainable in passage and ball trap
void ModuleScenePinball::Light(bool &active) {
	if (L2active && Iactive && Gactive && Hactive && Tactive) {
		L2active = Iactive = Gactive = Hactive = Tactive = false;
	}
		active = true;
	if (L2active && Iactive && Gactive && Hactive && Tactive) {

		if (lightcounter == 3) {
			tenmil = true;
			lightcounter++;
		}
		if (lightcounter == 2) {
			fivemil = true;
			lightcounter++;
		}
		if (lightcounter == 1) {
			extraball = true;
			lightcounter++;
		}
		if (lightcounter == 4) {
			lightcounter = 1;
		}
	}
}

//Two buttons that if are active, reward the player with some points
void ModuleScenePinball::FiveHpts(bool &active) {
	if (FiveH1 && FiveH2)	FiveH1 = FiveH2 = false;
	active = true;
	if (FiveH1 && FiveH2) {
		currentpts += 25000;
	}
}

//if we go throug this section two times, a bool will activate, rewarding the player with some points
void ModuleScenePinball::SunRun() {
	currentpts += 10000;
	switch (Suncounter) {
	case 1:
		if (Sun1Reward) {
			Sun3Reward = false;
			Suncounter++;
			currentpts += 10000;
			break;
		}
		if (!Sun1Reward) {
			Sun1Reward = true;
			break;
		}
	case 2:
		if (Sun2Reward) {
			Sun1Reward = false; 
			Suncounter++;
			currentpts += 20000;
			break;
		}
		if (!Sun2Reward) {
			Sun2Reward = true;
			break;
		}
	case 3:
		if (Sun3Reward) {
			Sun2Reward = false;
			Suncounter = 1u;
			currentpts += 30000;
			break;
		}
		if (!Sun3Reward) {
			Sun3Reward = true;
			break;
		}
	}

	
}

//If we activate all the leters, a bool activates, that allows the player to collect fuel in the left passage
void ModuleScenePinball::Fuel(bool &active) {
	active = true;
	if (Factive && Uactive && Eactive && Lactive) {
		collectFuel = true;
	}
}

//If all ignition buttons are active, an int is increased. 
//This will determine how many letters of ignition will be lightened. 
//If all are lightened, the player will be awarded wit a lot of points
void ModuleScenePinball::Ignition(bool &active) {
	if (Ignition1 && Ignition2 && Ignition3) {
		Ignition1 = Ignition2 = Ignition3 = false;
		if (ignitionit == 8) {
			currentpts += 1000000;
			ignitionit = 0;
		}
	}
	active = true;
	if (Ignition1 && Ignition2 && Ignition3) {
		if (ignitionit < 8) { ignitionit++; }
	}
}

//Everytime the playes goes through it, the points he receives are increased
//Also used to receive other rewards that are activated in other sensors
void ModuleScenePinball::Passage() {
	DoorLJoint->EnableMotor(true);
	if (collectFuel) {
		Factive = Uactive = Eactive = Lactive = false;
		currentpts += 500000;
		collectFuel = false;
	}
	if (fivemil == true) {
		currentpts += 5000000;
		fivemil = false;
	}
	if (tenmil == true) {
		currentpts += 10000000;
		tenmil = false;
	}
	if (passagecounter < 7) {
		passagecounter++;
	}
	else { 
		passagecounter = 1;
	}
	switch (passagecounter) {
	case 1:
		currentpts += 50000;
		break;
	case 2:
		currentpts += 100000;
		break;
	case 3:
		currentpts += 250000;
		break;
	case 4:
		currentpts += 500000;
		break;
	case 5:
		currentpts += 7500000;
		break;
	case 6:
		currentpts += 1000000;
		break;
	case 7:
		currentpts += 2500000;
		break;
	}
}

//The balltrap will trap the ball some seconds and reward the player with more points each time he enters this sensor
//Can also be used to obtain an extra ball if all LIGHT sensors are active
void ModuleScenePinball::balltrap() {
	trap = true;
	traptimer = SDL_GetTicks();
	if (extraball) {
		extraball = false;
		balls++;
	}
	switch (BalltrapCounter) {
	case 1:
		currentpts += 100000;
		break;
	case 2:
		currentpts += 250000;
		break;
	case 3:
		currentpts += 500000;
		break;
	case 4:
		currentpts += 1000000;
		BalltrapCounter = 0;
		break;
	}
	BalltrapCounter++;
}
//Receives the name of a sensor, then starts a determinate proces depending of it's name property
void ModuleScenePinball::getSensor(char* name) {
	if (name == "Door_Sensor") {
		DoorRJoint->EnableMotor(true);
	}
	if (name == "Hole") {
		balltrap();
	}
	if (name == "DeathSensor") {
		Death();
		App->audio->PlayFx(7, 0);
	}
	if (name == "ignition1") {
		Ignition(Ignition1);
		App->audio->PlayFx(5, 0);
	}
	if (name == "ignition2") {
		Ignition(Ignition2);
		App->audio->PlayFx(5, 0);
	}
	if (name == "ignition3") {
		Ignition(Ignition3);
		App->audio->PlayFx(5, 0);
	}
	if (name == "sun") {
		SunRun();
	}
	if (name == "F_sensor") {
		Fuel(Factive);
		App->audio->PlayFx(6, 0);
	}
	if (name == "U_sensor") {
		Fuel(Uactive);
		App->audio->PlayFx(6, 0);
	}
	if (name == "E_sensor") {
		Fuel(Eactive);
		App->audio->PlayFx(6, 0);
	}
	if (name == "L_sensor") {
		Fuel(Lactive);
		App->audio->PlayFx(6, 0);
	}
	if (name == "sensor500") {
		FiveHpts(FiveH1);
	}
	if (name == "sensor502") {
		FiveHpts(FiveH2);
	}
	if (name == "W_sensor") {
		Warp(1);
		App->audio->PlayFx(3, 0);
	}
	if (name == "A_sensor") {
		Warp(2);
		App->audio->PlayFx(3, 0);
	}
	if (name == "R_sensor") {
		Warp(3);
		App->audio->PlayFx(3, 0);
	}
	if (name == "P_sensor") {
		Warp(4);
		App->audio->PlayFx(3, 0);
	}
	if (name == "L2_sensor") {
		Light(L2active);
		App->audio->PlayFx(5, 0);
	}
	if (name == "I_sensor") {
		Light(Iactive);
		App->audio->PlayFx(5, 0);
	}
	if (name == "G_sensor") {
		Light(Gactive);
		App->audio->PlayFx(5, 0);
	}
	if (name == "H_sensor") {
		Light(Hactive);
		App->audio->PlayFx(5, 0);
	}
	if (name == "T_sensor") {
		Light(Tactive);
		App->audio->PlayFx(5, 0);

	}
	if (name == "Passage_Sensor") {
		Passage();
	}
	if (name == "Blue_sensor") {
		sensor_Blue = true;
	}
	if (name == "Blue_sensor_out") {
		sensor_Blue = false;
	}
	if (name == "Blue_sensor_2") {
		sensor_Blue2 = true;
	}
	if (name == "Blue_sensor_out_2") {
		sensor_Blue2 = false;
	}
	
}

//Used to blit the buttons, depending on the variables that are activated in the previous functions
void ModuleScenePinball::blitbuttons()
{
	if (Factive == true) {
		App->renderer->Blit(fuel, 199, 556, &F_fuel);
	}
	if (Uactive == true) {
		App->renderer->Blit(fuel, 198, 603, &U_fuel);
	}
	if (Eactive == true) {
		App->renderer->Blit(fuel, 197, 650, &E_fuel);
	}
	if (Lactive == true) {
		App->renderer->Blit(fuel, 196, 697, &L_fuel);
	}

	if (L2active==true) {
		App->renderer->Blit(lights, 706, 247, &L_lights);
	}
	if (Iactive == true) {
		App->renderer->Blit(lights, 717, 290, &I_lights);
	}
	if (Gactive == true) {
		App->renderer->Blit(lights, 726, 333, &G_lights);
	}
	if (Hactive == true) {
		App->renderer->Blit(lights, 737, 375, &H_lights);
	}
	if (Tactive == true) {
		App->renderer->Blit(lights, 747, 419, &T_lights);
	}

	if (Ignition1 == true) {
		App->renderer->Blit(ignition_button, 446, 539, &Ignition_button);
	}
	if (Ignition2 == true) {
		App->renderer->Blit(ignition_button, 485, 560, &Ignition_button);
	}
	if (Ignition3 == true) {
		App->renderer->Blit(ignition_button, 523, 579, &Ignition_button);
	}

	if (Sun1Reward == true) {
		App->renderer->Blit(sun_button, 627, 502, &Ssun_button);
	}
	if (Sun2Reward == true) {
		App->renderer->Blit(sun_button, 652, 527, &Usun_button);
	}
	if (Sun3Reward == true) {
		App->renderer->Blit(sun_button, 678, 554, &Nsun_button);
	}
	
	if (Wactive == true || Wlight == true) {
		App->renderer->Blit(warp_button, 441, 164, &W_warp);
	}
	if (Aactive == true || Alight == true) {
		App->renderer->Blit(warp_button, 509, 184, &A_warp);
	}
	if (Ractive == true || Rlight == true) {
		App->renderer->Blit(warp_button, 578, 183, &R_warp);
	}
	if (Pactive == true || Plight == true) {
		App->renderer->Blit(warp_button, 648, 164, &P_warp);
	}

	if (currentpts.multipilier == 2) {
		App->renderer->Blit(multiplier_button, 414, 111, &multiplier_x2);
	}
	if (currentpts.multipilier == 3) {
		App->renderer->Blit(multiplier_button, 465, 86, &multiplier_x3);
	}
	if (currentpts.multipilier == 4) {
		App->renderer->Blit(multiplier_button, 529, 73, &multiplier_x4);
	}
	if (currentpts.multipilier == 6) {
		App->renderer->Blit(multiplier_button, 594, 86, &multiplier_x6);
	}
	if (currentpts.multipilier == 8) {
		App->renderer->Blit(multiplier_button, 645, 111, &multiplier_x8);
	}

	if (passagecounter == 1) {
		App->renderer->Blit(numbers_buttons, 200, 433, &number_50);
	}
	if (passagecounter == 2) {
		App->renderer->Blit(numbers_buttons, 194, 388, &number_100);
	}
	if (passagecounter == 3) {
		App->renderer->Blit(numbers_buttons, 197, 342 , &number_250);
	}
	if (passagecounter == 4) {
		App->renderer->Blit(numbers_buttons, 220, 303, &number_500);
	}
	if (passagecounter == 5) {
		App->renderer->Blit(numbers_buttons, 250, 268, &number_750);

	}
	if (passagecounter == 6) {
		App->renderer->Blit(numbers_buttons, 281, 236, &number_1000);

	}
	if (passagecounter == 7) {
		App->renderer->Blit(numbers_buttons, 314, 204, &number_2500);
	}

	if (sensor_Blue == true) {
		App->renderer->Blit(Blue_button, 718, 879, &blue_button);
	}
	if (sensor_Blue2 == true) {
		App->renderer->Blit(Blue_button, 230, 879, &blue_button);
	}

	if (FiveH1 == true) {
		App->renderer->Blit(Red_square, 296, 286, &red_square);
	}
	if (FiveH2 == true) {
		App->renderer->Blit(Red_square, 338, 245, &red_square);
	}
	if (passagecounter != 0) App->renderer->Blit(arrows, 220, 471, &arrowrect[0]);
	if (fivemil) App->renderer->Blit(arrows, 244, 518, &arrowrect[1]);
	if (tenmil) App->renderer->Blit(arrows, 268, 566, &arrowrect[2]);
	if (collectFuel) App->renderer->Blit(arrows, 291, 612, &arrowrect[3]);
	//Not implemented
	//App->renderer->Blit(arrows, 311, 499, &arrowrect[2]);
	//App->renderer->Blit(arrows, 337, 549, &arrowrect[3]);
	if (extraball)App->renderer->Blit(arrows, 363, 597, &arrowrect[1]);
	if(Sun1Reward) App->renderer->Blit(arrows, 660, 738, &arrowrect[4]);
	if (Sun2Reward) App->renderer->Blit(arrows, 686, 688, &arrowrect[4]);
	if (Sun3Reward) App->renderer->Blit(arrows, 711, 638, &arrowrect[4]);
}

//Death interactiopn, activates everytime the ball falls on the void
void ModuleScenePinball::Death() {
	ResetVar();
	worditerator = 1;

	if (balls >= 1) {
		balls--;
			if (balls > 0) {
			ball->transform = true;
		}
			else {
				state = END;
				worditerator = 2;
				if (currentpts.value > highestpts.value) {
					highestpts = currentpts;
				}
				previouspts = currentpts;
				currentpts.value = 0;
				
				movecam = false;
			}
	}

}

//Reset most variables, used everytime the ball falls
void ModuleScenePinball::ResetVar() {
	warp = Wlight = Alight = Rlight = Plight = Wactive = Aactive = Ractive = Pactive = false;
	L2active = Iactive = Gactive = Hactive = Tactive = false;
	lightcounter = 1;
	FiveH1 = FiveH2 = false;
	Factive = Uactive = Eactive = Lactive = false;
	Sun1 = Sun2 = Sun3 = Sun1Reward = Sun2Reward = Sun3Reward = false;
	Suncounter = 1u;
	Ignition1 = Ignition2 = Ignition3 = false;
	passagecounter = 0u;
	currentpts.multipilier = 1;
	collectFuel = false;
	ignitionit = 0;
	worditerator = 0;
	BalltrapCounter = 1;
	trap = false;
	
}

//Create all phys bodies
void ModuleScenePinball::CreateBodies() {
	int pinball_board[138] = {
	585, 1318,
	588, 1126,
	783, 1040,
	795, 1029,
	800, 1017,
	801, 1003,
	801, 834,
	732, 770,
	730, 698,
	777, 615,
	800, 557,
	801, 475,
	789, 463,
	792, 453,
	783, 444,
	735, 244,
	738, 233,
	732, 228,
	728, 235,
	720, 231,
	721, 221,
	710, 229,
	692, 227,
	687, 219,
	686, 177,
	692, 168,
	709, 171,
	744, 204,
	765, 229,
	790, 278,
	798, 314,
	802, 338,
	804, 360,
	806, 392,
	807, 466,
	807, 1214,
	852, 1213,
	849, 363,
	840, 292,
	825, 248,
	798, 200,
	758, 158,
	734, 134,
	711, 114,
	641, 83,
	580, 69,
	518, 69,
	464, 84,
	415, 109,
	372, 141,
	254, 262,
	204, 320,
	187, 367,
	178, 441,
	178, 505,
	187, 519,
	187, 549,
	194, 553,
	195, 735,
	180, 740,
	180, 747,
	220, 782,
	218, 801,
	178, 838,
	178, 1035,
	194, 1052,
	366, 1126,
	370, 1133,
	369, 1325
	};
	int Flipper_L[16] = {
	9, 34,
	88, 65,
	99, 68,
	106, 66,
	108, 58,
	100, 50,
	21, 11,
	9, 15
	};

	int Flipper_R[16] = {
	1, 61,
	1, 53,
	6, 47,
	78, 11,
	92, 9,
	97, 28,
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
	141, 390,
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
	188, 340,
	180, 342,
	129, 246,
	117, 237,
	106, 237,
	96, 245,
	94, 257,
	144, 381,
	144, 390
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

	Map = App->physics->CreateChain(0, 0, pinball_board, 138);
	App->physics->CreateChain(200, 816, MappartL, 24);
	App->physics->CreateChain(580, 816, MappartR, 22);
	BalltrapChain = App->physics->CreateChain(155, 150, MapTunnel, 52);
	App->physics->CreateChain(473, 183, lane, 24);
	App->physics->CreateChain(613, 183, lane, 24);
	App->physics->CreateChain(542, 192, lane, 24);

	//Ball
	ball = App->physics->CreateCircle(810, 1070, 15, "ball", b2_dynamicBody, 0.4);
	ball->xtransform = 830;
	ball->ytransform = 1070;
	
	
	//map components
	App->physics->CreateCircle(481, 1113, 7, "", b2_staticBody);
	rotAxisL = App->physics->CreateCircle(358, 1040, 10, "rotAxisL", b2_staticBody);
	rotAxisR = App->physics->CreateCircle(597, 1040, 10, "rotAxisR", b2_staticBody);
	FlipperL = App->physics->CreatePolygon(358, 1040, Flipper_L, 16, "Flipper_L");
	FlipperR = App->physics->CreatePolygon(510, 1023, Flipper_R, 16, "Flipper_L");
	SlingshotL = App->physics->CreatePolygon(200, 820, slingshotL, 16, "SlingshotL", b2_staticBody);
	SlingshotR = App->physics->CreatePolygon(580, 810, slingshotR, 16, "SlingshotR", b2_staticBody);
	Bumper1 = App->physics->CreateCircle(433, 350, 50, "Bumper1", b2_staticBody);
	Bumper2 = App->physics->CreateCircle(560, 450, 50, "Bumper2", b2_staticBody);
	Target1 = App->physics->CreatePolygon(445, 495, target1, 16, "Target1", b2_staticBody);
	Target2 = App->physics->CreatePolygon(675, 535, target2, 16, "Target2", b2_staticBody);
	Trap = App->physics->CreateRectangle(366, 469, 6, 90, "");
	
	//Joints components
	doorL = App->physics->CreateRectangle(200, 200, 10, 100, "doorL");
	doorR = App->physics->CreateRectangle(900, 200, 10, 100, "doorR");
	kickerBase = App->physics->CreateRectangle(830, 1115, 30, 15, "piston1", b2_staticBody);
	kicker = App->physics->CreateRectangle(830, 1105, 30, 30, "piston2", b2_dynamicBody);
	SSLPiston = App->physics->CreateRectangle(300, 920, 150, 5, "SSLPiston");
	SSRPiston = App->physics->CreateRectangle(690, 920, 150, 5, "SSRPiston");
	SSLPistonBase = App->physics->CreateRectangle(295, 920, 15, 15, "SSLPistonBase", b2_staticBody);
	SSRPistonBase = App->physics->CreateRectangle(682, 920, 15, 15, "SSRPistonBase", b2_staticBody);

	//Sensors
	DoorSensor = App->physics->CreateRectangleSensor(760, 191, 5, 30, "Door_Sensor", 45);
	DeathSensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, 1300, SCREEN_WIDTH, 50, "DeathSensor");

	ignition1 = App->physics->CreateRectangleSensor(471, 534, 30, 5, "ignition1", 28);
	ignition2 = App->physics->CreateRectangleSensor(507, 553, 30, 5, "ignition2", 28);
	ignition3 = App->physics->CreateRectangleSensor(545, 571, 30, 5, "ignition3", 28);

	sun = App->physics->CreateRectangleSensor(753, 620, 30, 100, "sun", 25);

	Hole = App->physics->CreateRectangleSensor(268, 408, 37, 37, "Hole", 60);

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
	I_sensor = App->physics->CreateRectangleSensor(744, 308, 5, 30, "I_sensor", -10);
	G_sensor = App->physics->CreateRectangleSensor(756, 351, 5, 30, "G_sensor", -10);
	H_sensor = App->physics->CreateRectangleSensor(767, 394, 5, 30, "H_sensor", -10);
	T_sensor = App->physics->CreateRectangleSensor(778, 437, 5, 30, "T_sensor", -10);
	Blue_sensor = App->physics->CreateRectangleSensor(735, 900, 30, 5, "Blue_sensor", 0);
	Blue_sensor_out = App->physics->CreateRectangleSensor(700, 977, 30, 5, "Blue_sensor_out", 45);
	Blue_sensor_2 = App->physics->CreateRectangleSensor(248, 900, 30, 5, "Blue_sensor_2", 0);
	Blue_sensor_out_2 = App->physics->CreateRectangleSensor(300, 980, 30, 5, "Blue_sensor_out_2", -45);
	Passage_Sensor = App->physics->CreateRectangleSensor(362, 191, 5, 30, "Passage_Sensor", -45);

}