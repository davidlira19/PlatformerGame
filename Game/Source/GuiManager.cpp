#include "GuiManager.h"

#include "GuiButton.h"
GuiManager::GuiManager(bool startEnabled) : Module(startEnabled)
{
	

}
GuiManager::~GuiManager() {

}

GuiControl* GuiManager::CreateGuiControl(GuiControlType type, int id, SDL_Rect rect, const char* text)
{
	GuiControl* control = nullptr;

	switch (type)
	{
	case GuiControlType::BUTTON:
		control = new GuiButton(id, rect, text);
		break;
	default: 
		break;
	}

	// Created entities are added to the list
	if (control != nullptr)
	{
		controls.Add(control);
	}
	return control;
}
bool GuiManager::PostUpdate() 
{
	ListItem<GuiControl*>* auxiliar;
	auxiliar = controls.start;
	while (auxiliar != nullptr) 
	{
		auxiliar->data->Draw();
		auxiliar = auxiliar->next;
	}
	return true;
}
bool GuiManager::Update(float dt)
{
	accumulatedTime += dt;
	if (accumulatedTime >= updateMsCycle) doLogic = true;

	ListItem<GuiControl*>* auxiliar;
	auxiliar = controls.start;
	while (auxiliar != nullptr)
	{
		auxiliar->data->Update(dt);
		auxiliar = auxiliar->next;
	}

	if (doLogic == true)
	{
		accumulatedTime = 0.0f;
		doLogic = false;
	}

	return true;
}
void GuiManager::DestroyAllGuiControl() 
{
	ListItem<GuiControl*>* auxiliar;
	auxiliar = controls.start;
	while (auxiliar != nullptr)
	{
		delete auxiliar->data;
		auxiliar = auxiliar->next;
	}
	controls.Clear();
}