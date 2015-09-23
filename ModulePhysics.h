#pragma once
#include "Module.h"
#include "Globals.h"

class ModulePhysics : public Module
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();
	int MeterToPixel(float meter);
	float PixelToMeter(int pixel);

private:

	bool debug;
	class b2World* world;
};