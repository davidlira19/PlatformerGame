#include "GuiManager.h"
#include"Audio.h"
#include "GuiButton.h"
GuiManager::GuiManager(bool startEnabled) : Module(startEnabled)
{

}
GuiManager::~GuiManager() {

}
bool GuiManager::Start() 
{
	textureButton = app->tex->Load("Assets/Textures/buttons.png");
	clickedFx =app->audio->LoadFx("Assets/Audio/Fx/button_press.wav");
	focusedFx =app->audio->LoadFx("Assets/Audio/Fx/zip_click.wav");
	return true;
}
GuiControl* GuiManager::CreateGuiControl(GuiControlType type, int id, SDL_Rect rect, const char* text)
{
	GuiControl* control = nullptr;

	switch (type)
	{
	case GuiControlType::BUTTON:
		control = new GuiButton(id, rect, text, clickedFx, focusedFx, textureButton);
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
void GuiManager::DestroyGuiControl(GuiControl* entity)
{
	int idex = controls.Find(entity);

	ListItem<GuiControl*>* auxiliar;
	auxiliar = controls.start;
	int cont = 0;
	while (auxiliar != nullptr)
	{
		if (cont == idex) {
			delete auxiliar->data;
			controls.Del(auxiliar);
			auxiliar = nullptr;
			break;
		}
		cont++;
		auxiliar = auxiliar->next;
	}
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
