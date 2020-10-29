#include "Module.h"

Module::Module(bool startEnabled) :isEnabled(startEnabled)
{

}


bool Module::Awake(pugi::xml_node&)
{
	return true;
}

// Called before the first frame
bool Module::Start()
{
	return true;
}

// Called each loop iteration
bool Module::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Module::Update(float dt)
{
	return true;
}

// Called each loop iteration
bool Module::PostUpdate()
{
	return true;
}

// Called before quitting
bool Module::CleanUp()
{
	return true;
}


void Module::Enable()
{
	if (!isEnabled)
	{
		isEnabled = true;
		Start();
	}
}

void Module::Disable()
{
	if (isEnabled)
	{
		isEnabled = false;
		CleanUp();
	}
}
