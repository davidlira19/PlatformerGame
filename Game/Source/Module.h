#ifndef __MODULE_H__
#define __MODULE_H__

#include"Collider.h"
#include "SString.h"
#include "PugiXml/src/pugixml.hpp"
class GuiControl;
class App;

class Module
{
public:

	Module(bool startEnabled)
	{
		isEnabled = startEnabled;
	
	}

	void Init() {}

	// Called before render is available
	// Sending config file to all modules
	virtual bool Awake(pugi::xml_node&)
	{
		return true;
	}

	// Called before the first frame
	virtual bool Start(bool newGame)
	{
		return true;
	}

	// Called each loop iteration
	virtual bool PreUpdate()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool Update(float dt)
	{
		return true;
	}

	// Called each loop iteration
	virtual bool PostUpdate()
	{
		return true;
	}

	// Called before quitting
	virtual bool CleanUp()
	{
		return true;
	}

	// Create new virtual methods to Load / Save state
	virtual bool LoadState(pugi::xml_node* nodo)
	{
		return true;
	}

	virtual bool SaveState(pugi::xml_node* nodo)
	{
		return true;
	}

	void Module::Enable()
	{
		if (!isEnabled)
		{
			isEnabled = true;
			Start(false);
		}
	}

	// Switches isEnabled and calls CleanUp() method
	void Module::Disable()
	{
		if (isEnabled)
		{
			isEnabled = false;
			CleanUp();
		}
	}

	virtual void OnCollision(Collider* c1, Collider* c2)
	{

	}
	virtual bool OnGuiMouseClickEvent(GuiControl* control)
	{
		return true;
	}
public:

	bool isEnabled = true;
	SString name;

};

#endif // __MODULE_H__