#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "math.h"

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	world = NULL;
	mouse_joint = NULL;
	debug = false;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));
	world->SetContactListener(this);

	// needed to create joints like mouse joint
	b2BodyDef bd;
	ground = world->CreateBody(&bd);

	return true;
}

update_status ModulePhysics::PreUpdate()
{
	world->Step(1.0f / 60.0f, 6, 2);

	for(b2Contact* c = world->GetContactList(); c; c = c->GetNext())
	{
		if(c->GetFixtureA()->IsSensor() && c->IsTouching())
		{
			PhysBody* pb1 = (PhysBody*)(c->GetFixtureA()->GetBody()->GetUserData().pointer);
			PhysBody* pb2 = (PhysBody*)(c->GetFixtureA()->GetBody()->GetUserData().pointer);
			if(pb1 && pb2 && pb1->listener)
				pb1->listener->OnCollision(pb1, pb2);
		}
	}

	return UPDATE_CONTINUE;
}

//Create circles ---------------------------------------------------------------------------
PhysBody* ModulePhysics::CreateCircle(int x, int y, int radius, const char* name, b2BodyType type, float restitution)
{
	b2BodyDef body;
	body.type = type;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
	body.gravityScale = 1;
	b2Body* b = world->CreateBody(&body);
	b2CircleShape shape;

	shape.m_radius = PIXEL_TO_METERS(radius);
	b2FixtureDef fixture;
	fixture.friction = 0.1;
	fixture.shape = &shape;
	fixture.density = 1.0f;
	fixture.restitution = restitution;
	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->name = strdup(name);
	pbody->body = b;
	pbody->width = pbody->height = radius;

	return pbody;
}

//Create Rectangles ---------------------------------------------------------------------------
PhysBody* ModulePhysics::CreateRectangle(int x, int y, int width, int height, const char* name, b2BodyType type)
{
	b2BodyDef body;
	body.type = type;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);
	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;
	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->name = strdup(name);
	pbody->body = b;
	pbody->width = width * 0.5f;
	pbody->height = height * 0.5f;

	return pbody;
}

//Create Rectangles that are sensors ---------------------------------------------------------------------------
PhysBody* ModulePhysics::CreateRectangleSensor(int x, int y, int width, int height, const char* name, int angle, b2BodyType type)
{
	b2BodyDef body;
	body.type = type;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
	body.angle = angle * DEGTORAD;

	b2Body* b = world->CreateBody(&body);
	
	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;
	fixture.isSensor = true;


	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	pbody->name = strdup(name);
	pbody->width = width;
	pbody->height = height;

	return pbody;
}

//Create chains ---------------------------------------------------------------------------
PhysBody* ModulePhysics::CreateChain(int x, int y, int* points, int size, const char* name, b2BodyType type)
{
	b2BodyDef body;
	body.type = type;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2ChainShape shape;
	b2Vec2* p = new b2Vec2[size / 2];

	for(uint i = 0; i < size / 2; ++i)
	{
		p[i].x = PIXEL_TO_METERS(points[i * 2 + 0]);
		p[i].y = PIXEL_TO_METERS(points[i * 2 + 1]);
	}

	shape.CreateLoop(p, size / 2);

	b2FixtureDef fixture;
	fixture.shape = &shape;

	b->CreateFixture(&fixture);

	delete p;

	PhysBody* pbody = new PhysBody();
	pbody->name = strdup(name);
	pbody->body = b;
	pbody->width = pbody->height = 0;

	return pbody;
}

//create polygon ---------------------------------------------------------------------------
PhysBody*  ModulePhysics::CreatePolygon(int x, int y, int* points, int size, const char* name, b2BodyType type)
{
	b2BodyDef body;
	body.type = type; 
	body.position.Set(PIXEL_TO_METERS (x), PIXEL_TO_METERS(y)); 

	b2Body* b = world->CreateBody(&body);

	b2PolygonShape polygonShape;
	b2Vec2* p = new b2Vec2[size / 2];

	for (uint i = 0; i < size / 2; ++i)
	{
		p[i].x = PIXEL_TO_METERS(points[i * 2 + 0]);
		p[i].y = PIXEL_TO_METERS(points[i * 2 + 1]);
	}
	polygonShape.Set(p, size / 2); //pass array to the shape

	b2FixtureDef myFixtureDef;
	myFixtureDef.density = 1.0f;
	myFixtureDef.shape = &polygonShape; //change the shape of the fixture
	b->CreateFixture(&myFixtureDef); //add a fixture to the body
	
	delete p;
	PhysBody* pbody = new PhysBody();
	pbody->name = strdup(name);
	pbody->body = b;
	pbody->width = pbody->height = 0;
	return pbody;
}

//method to create revolute joints ---------------------------------------------------------------------------
b2RevoluteJoint*  ModulePhysics::CreateRevoluteJoint(b2Body* bodyA, b2Body* bodyB, int AnchorX, int AnchorY, int lowerAngle, int upperAngle) {
	b2RevoluteJointDef revoluteJointDef;
	
	revoluteJointDef.bodyA = bodyA;
	revoluteJointDef.bodyB = bodyB;
	revoluteJointDef.collideConnected = false;
	revoluteJointDef.localAnchorA.Set(PIXEL_TO_METERS(AnchorX), PIXEL_TO_METERS(AnchorY));
	revoluteJointDef.localAnchorB.Set(0, 0);
	revoluteJointDef.referenceAngle = 0 * DEGTORAD;
	revoluteJointDef.enableLimit = true;
	revoluteJointDef.lowerAngle = lowerAngle * DEGTORAD;
	revoluteJointDef.upperAngle = upperAngle * DEGTORAD;
	revoluteJointDef.enableMotor = true;
	revoluteJointDef.maxMotorTorque = 300;
	revoluteJointDef.motorSpeed = -100 * DEGTORAD;


 revolutejoint = (b2RevoluteJoint*)world->CreateJoint(&revoluteJointDef);
return revolutejoint;
}

//method to create prismatic joints ---------------------------------------------------------------------------
b2PrismaticJoint* ModulePhysics::CreatePrismaticJoint(b2Body* bodyA, b2Body* bodyB, int AnchorX, int AnchorY, int lowerTranslation, int upperTranslation, int maxforce, int referenceAngle, float directionx, float directiony) {
	b2PrismaticJointDef prismaticJointDef;

	prismaticJointDef.bodyA = bodyA;
	prismaticJointDef.bodyB = bodyB;
	prismaticJointDef.collideConnected = false;
	prismaticJointDef.localAxisA.Set(directionx, -1*directiony);
	prismaticJointDef.localAnchorA.Set(PIXEL_TO_METERS(AnchorX), PIXEL_TO_METERS(AnchorY));
	prismaticJointDef.localAnchorB.Set(0, 0);
	prismaticJointDef.referenceAngle = referenceAngle * DEGTORAD;
	prismaticJointDef.enableLimit = true;
	prismaticJointDef.lowerTranslation = lowerTranslation * DEGTORAD;
	prismaticJointDef.upperTranslation = upperTranslation * DEGTORAD;
	prismaticJointDef.enableMotor = false;
	prismaticJointDef.maxMotorForce = maxforce;
	prismaticJointDef.motorSpeed = PIXEL_TO_METERS(1000);


	prismaticjoint = (b2PrismaticJoint*)world->CreateJoint(&prismaticJointDef);
	return prismaticjoint;
}



update_status ModulePhysics::PostUpdate()
{
	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		PhysBody* phys = (PhysBody*)(b->GetUserData().pointer);
		if (phys && phys->transform) {
			phys->transform = false;
			b2Vec2 pos(PIXEL_TO_METERS(phys->xtransform), PIXEL_TO_METERS(phys->ytransform));
			b->SetTransform(pos, 0);
		}
	}
	selected = false;
	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	// This will iterate all objects in the world and draw the circles

	for(b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		PhysBody* phys = (PhysBody*)(b->GetUserData().pointer);

		for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch(f->GetType())
			{
				// Draw circles ------------------------------------------------
				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					//added +camera.x and +camera.y, to avoid conflict between visual representation and circles when moving camera
					App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x) + App->renderer->camera.x, METERS_TO_PIXELS(pos.y) + App->renderer->camera.y, METERS_TO_PIXELS(shape->m_radius), 255, 255, 255);
				}
				break;

				// Draw polygons ------------------------------------------------
				case b2Shape::e_polygon:
				{
					b2PolygonShape* polygonShape = (b2PolygonShape*)f->GetShape();
					int32 count = polygonShape->GetChildCount();
					b2Vec2 prev, v;

					for(int32 i = 0; i < count; ++i)
					{
						v = b->GetWorldPoint(polygonShape->m_vertices[i]);
						if(i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);

						prev = v;
					}

					v = b->GetWorldPoint(polygonShape->m_vertices[0]);
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);
				}
				break;

				// Draw chains contour -------------------------------------------
				case b2Shape::e_chain:
				{
					b2ChainShape* shape = (b2ChainShape*)f->GetShape();
					b2Vec2 prev, v;

					for(int32 i = 0; i < shape->m_count; ++i)
					{
						v = b->GetWorldPoint(shape->m_vertices[i]);
						if(i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
						prev = v;
					}

					v = b->GetWorldPoint(shape->m_vertices[0]);
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
				}
				break;

				// Draw a single segment(edge) ----------------------------------
				case b2Shape::e_edge:
				{
					b2EdgeShape* shape = (b2EdgeShape*)f->GetShape();
					b2Vec2 v1, v2;

					v1 = b->GetWorldPoint(shape->m_vertex0);
					v1 = b->GetWorldPoint(shape->m_vertex1);
					App->renderer->DrawLine(METERS_TO_PIXELS(v1.x), METERS_TO_PIXELS(v1.y), METERS_TO_PIXELS(v2.x), METERS_TO_PIXELS(v2.y), 100, 100, 255);
				}
				break;
			}

			// If mouse button 1 is pressed ...
		
			if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN) {

				PhysBody* phys = (PhysBody*)(b->GetUserData().pointer);
				if (phys && phys->Contains(App->input->GetMouseX(), App->input->GetMouseY())){
					body_clicked = b;
					selected = true;
					LOG("contains");
				}
			}
			// test if the current body contains mouse position
		}
	}

	// If a body was selected we will attach a mouse joint to it
	// so we can pull it around
	//If a body was selected, create a mouse joint
	// using mouse_joint class property
	
	if(selected == true){
	b2Vec2 mouse_position(PIXEL_TO_METERS(App->input->GetMouseX()), PIXEL_TO_METERS(App->input->GetMouseY()));
	b2MouseJointDef def;
	b2LinearStiffness(def.stiffness, def.damping, 2.0f, 0.5f, ground, body_clicked);
	def.maxForce = 100.0f * body_clicked->GetMass();

	mouse_joint = (b2MouseJoint*)world->CreateJoint(&def);
	}
	
	if (body_clicked != NULL){
	if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT) {
		b2Vec2 mouse_position(PIXEL_TO_METERS(App->input->GetMouseX()), PIXEL_TO_METERS(App->input->GetMouseY()));
		mouse_joint->SetTarget(mouse_position);
		App->renderer->DrawLine(App->input->GetMouseX(), App->input->GetMouseY(), METERS_TO_PIXELS(mouse_joint->GetAnchorB().x), METERS_TO_PIXELS(mouse_joint->GetAnchorB().y),225,0,0);
	}
	//If the player keeps pressing the mouse button, update
	// target position and draw a red line between both anchor points
	
	if(App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_UP){
		if (mouse_joint != NULL){
		world->DestroyJoint(mouse_joint);
		mouse_joint = NULL;
		body_clicked = NULL;
		}
		
	 }
	}
	//If the player releases the mouse button, destroy the joint

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!
	delete world;

	return true;
}

void PhysBody::GetPosition(int& x, int &y) const
{
	b2Vec2 pos = body->GetPosition();
	x = METERS_TO_PIXELS(pos.x) - (width);
	y = METERS_TO_PIXELS(pos.y) - (height);
}


float PhysBody::GetRotation() const
{
	return RADTODEG * body->GetAngle();
}

bool PhysBody::Contains(int x, int y) const
{
	b2Vec2 p(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	const b2Fixture* fixture = body->GetFixtureList();

	while(fixture != NULL)
	{
		if(fixture->GetShape()->TestPoint(body->GetTransform(), p) == true)
			return true;
		fixture = fixture->GetNext();
	}

	return false;
}

int PhysBody::RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const
{
	int ret = -1;

	b2RayCastInput input;
	b2RayCastOutput output;

	input.p1.Set(PIXEL_TO_METERS(x1), PIXEL_TO_METERS(y1));
	input.p2.Set(PIXEL_TO_METERS(x2), PIXEL_TO_METERS(y2));
	input.maxFraction = 1.0f;

	const b2Fixture* fixture = body->GetFixtureList();

	while(fixture != NULL)
	{
		if(fixture->GetShape()->RayCast(&output, input, body->GetTransform(), 0) == true)
		{
			float fx = x2 - x1;
			float fy = y2 - y1;
			float dist = sqrtf((fx*fx) + (fy*fy));

			normal_x = output.normal.x;
			normal_y = output.normal.y;

			return output.fraction * dist;
		}
		fixture = fixture->GetNext();
	}

	return ret;
}

void ModulePhysics::BeginContact(b2Contact* contact)
{
	//Gets a contact, then we get the data of the pysbody that is colliding, 
	//and calling all modules that are listeners to actiavte their Oncollision methods
	PhysBody* physA = (PhysBody*)(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
	PhysBody* physB = (PhysBody*)(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

	if(physA && physA->listener != NULL)
		physA->listener->OnCollision(physA, physB);

	if(physB && physB->listener != NULL)
		physB->listener->OnCollision(physB, physA);
}
