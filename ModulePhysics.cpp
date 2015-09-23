#include "Globals.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "math.h"
#include "Box2D\Box2D\Box2D.h"
#pragma comment (lib, "Box2D/libx86/Debug/Box2D.lib")

#define GRAVITY_X 0.0f
#define GRAVITY_Y -10.0f
#define FRAMES 1.0f / 60.0f
#define VELOCITY_ITERATIONS 8
#define VELOCITY_POSITIONS 3
#define X 100
#define Y 300
#define RADIUS 300

int ModulePhysics::MeterToPixel(float Meter){
	int Pixel = Meter * 300;
	return Pixel;
}
float ModulePhysics::PixelToMeter(int Pixel){
	float Meter = Pixel / 300;
	return Meter;
}

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	debug = true;
	world = NULL;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	// TODO 2: Create a private variable for the world
	// - You need to send it a default gravity
	// - You need init the world in the constructor
	// - Remember to destroy the world after using it
	b2Vec2 gravity(GRAVITY_X, GRAVITY_Y);
	world = new b2World(gravity);


	// TODO 4: Create a a big static circle as "ground"

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(PixelToMeter(X), PixelToMeter(Y));
	b2Body* body = world->CreateBody(&bodyDef);

	b2CircleShape shape;
	shape.m_radius = PixelToMeter(RADIUS);

	b2FixtureDef fixture;
	fixture.shape = &shape;
	body->CreateFixture(&fixture);

	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	// TODO 3: Update the simulation ("step" the world)
	world->Step(FRAMES, VELOCITY_ITERATIONS, VELOCITY_POSITIONS); //first value => frames per second // second value => velocity of Iterations //third value => position of iterations   

	return UPDATE_CONTINUE;
}

// 
update_status ModulePhysics::PostUpdate()
{
	// TODO 5: On space bar press, create a circle on mouse position
	// - You need to transform the position / radius

	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	/*
	for(b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch(f->GetType())
			{
				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), METERS_TO_PIXELS(shape->m_radius), 255, 255, 255);
				}
				break;

				// You will have to add more cases to draw boxes, edges, and polygons ...
			}
		}
	}*/

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	
	delete world;
	return true;
}
