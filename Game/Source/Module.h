#ifndef __MODULE_H__
#define __MODULE_H__

#include "SString.h"

#include "PugiXml/src/pugixml.hpp"

class App;

class Module
{
public:

	Module(bool startEnabled);

	void Init()
	{
		active = true;
	}

	// Called before render is available
	// TODO 5: Sending config file to all modules
	virtual bool Awake(pugi::xml_node&);
	

	// Called before the first frame
	virtual bool Start();
	

	// Called each loop iteration
	virtual bool PreUpdate();
	

	// Called each loop iteration
	virtual bool Update(float dt);
	

	// Called each loop iteration
	virtual bool PostUpdate();


	// Called before quitting
	virtual bool CleanUp();

	// L02: DONE 2: Create new virtual methods to Load / Save state
	virtual bool LoadState(pugi::xml_node* nodo)
	{
		return true;
	}

	virtual bool SaveState(pugi::xml_node* nodo) const
	{
		return true;
	}

	void Enable();
	void Disable();
	inline bool IsEnabled() const { return isEnabled; }

public:
	bool isEnabled = true;
	SString name;
	bool active;

};

#endif // __MODULE_H__