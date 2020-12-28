#include "GuiManager.h"
#include "Audio.h"
#include "GuiButton.h"
#include "GuiCheckbox.h"
#include "GuiSlider.h"
#include"SceneLevel1.h"
#include"SceneLevel2.h"
#include"Player.h"
#include"Welcome.h"
GuiManager::GuiManager(bool startEnabled) : Module(startEnabled)
{

}
GuiManager::~GuiManager() {

}
bool GuiManager::Start(bool newGame)
{
	pausedAnimation.PushBack({ 2773,975,451,770 });
	pausedAnimation.PushBack({ 2323,1003,451,742 });
	pausedAnimation.PushBack({ 1873,1027,451,721 });
	pausedAnimation.PushBack({ 1423,1055,451,693 });
	pausedAnimation.PushBack({ 973,1086,451,662 });
	pausedAnimation.PushBack({ 523,1116,451,632 });
	pausedAnimation.PushBack({ 73,1116,451,632 });
	pausedAnimation.loop = false;
	pausedAnimation.pingpong = false;
	pausedAnimation.speed = 0.25f;

	textureButton = app->tex->Load("Assets/Textures/buttons.png");
	clickedFx =app->audio->LoadFx("Assets/Audio/Fx/button_press.wav");
	focusedFx =app->audio->LoadFx("Assets/Audio/Fx/zip_click.wav");
	textureSlider= app->tex->Load("Assets/Textures/slider.png");
	return true;
}
bool GuiManager::CleanUp()
{
	app->tex->UnLoad(textureSlider);
	app->tex->UnLoad(textureButton);
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
	case GuiControlType::CHECKBOX:
		control = new GuiCheckBox(id, rect, text, clickedFx, focusedFx, textureButton);
		break;
	case GuiControlType::SLIDER:
		control = new GuiSlider(id, rect, text, clickedFx, focusedFx, textureButton, textureSlider);
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
	if (app->sceneLevel1->menu == true || app->sceneLevel2->menu == true)
	{
		
		if (pausedAnimation.HasFinished() == false)
		{	
			pausedAnimation.Update();
		}
		app->render->DrawTexture(textureSlider, app->player->position.x - 115, app->player->position.y - 200, &pausedAnimation.GetCurrentFrame());
	}
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
