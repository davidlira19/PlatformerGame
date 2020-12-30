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
	outAnimation = false;
	pausedAnimationIn.PushBack({ 2773,975,451,770 });
	pausedAnimationIn.PushBack({ 2323,1003,451,742 });
	pausedAnimationIn.PushBack({ 1873,1027,451,721 });
	pausedAnimationIn.PushBack({ 1423,1055,451,693 });
	pausedAnimationIn.PushBack({ 973,1086,451,662 });
	pausedAnimationIn.PushBack({ 523,1116,451,632 });
	pausedAnimationIn.PushBack({ 73,1116,451,632 });
	pausedAnimationIn.loop = false;
	pausedAnimationIn.speed = 0.25f;

	pausedAnimationOut.PushBack({ 73,1116,451,632 });
	pausedAnimationOut.PushBack({ 523,1116,451,632 });
	pausedAnimationOut.PushBack({ 973,1086,451,662 });
	pausedAnimationOut.PushBack({ 1423,1055,451,693 });
	pausedAnimationOut.PushBack({ 1873,1027,451,721 });
	pausedAnimationOut.PushBack({ 2323,1003,451,742 });
	pausedAnimationOut.PushBack({ 2773,975,451,770 });
	pausedAnimationOut.loop = false;
	pausedAnimationOut.speed = 0.25f;
	textureButton = app->tex->Load("Assets/Textures/buttons.png");
	clickedFx =app->audio->LoadFx("Assets/Audio/Fx/button_press.wav");
	focusedFx =app->audio->LoadFx("Assets/Audio/Fx/zip_click.wav");
	textureSlider= app->tex->Load("Assets/Textures/slider.png");
	menuEfect = app->audio->LoadFx("Assets/Audio/Fx/menu_efect.wav");
	
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
	
	if (app->sceneLevel1->menu == true || app->sceneLevel2->menu == true)
	{
		SDL_Rect rect = pausedAnimationIn.GetCurrentFrame();
		app->render->DrawTexture(textureSlider, app->player->position.x - 115, app->player->position.y - 200, &rect);
		if (rect.x != 73) 
		{
			pausedAnimationIn.Update();
		}		
	}
	if ((app->sceneLevel1->menu == false && outAnimation == true) || (app->sceneLevel2->menu == false && outAnimation == true))
	{
		SDL_Rect rect = pausedAnimationOut.GetCurrentFrame();
		app->render->DrawTexture(textureSlider, app->player->position.x - 115, app->player->position.y - 200, &rect);
		pausedAnimationOut.Update();
		if (rect.x == 2773)
		{
			outAnimation = false;
		}
	}
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

//controls.Clear();
bool GuiManager::PreUpdate()
{
	ListItem<GuiControl*>* auxiliar;
	auxiliar = controls.start;
	while (auxiliar != nullptr)
	{
		if (auxiliar->data->pendingToDelete == true) 
		{
			delete auxiliar->data;
			controls.Del(auxiliar);
		}
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
		auxiliar->data->pendingToDelete = true;
		auxiliar = auxiliar->next;
	}

}
