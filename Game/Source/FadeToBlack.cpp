#include "App.h"
#include "FadeToBlack.h"
#include "Log.h"
#include "SDL/include/SDL_render.h"
#include "Render.h"
#include "Window.h"
ModuleFadeToBlack::ModuleFadeToBlack(bool startEnabled) : Module(startEnabled)
{
	screenRect = { 0, 0, 1280,720 };
}

ModuleFadeToBlack::~ModuleFadeToBlack()
{

}

bool ModuleFadeToBlack::Start()
{
	LOG("Preparing Fade Screen");

	// Enable blending mode for transparency
	SDL_SetRenderDrawBlendMode(app->render->renderer, SDL_BLENDMODE_BLEND);
	return true;
}

bool ModuleFadeToBlack::Update(float dt)
{
	// Exit this function if we are not performing a fade
	if (currentStep == Fade_Step::NONE) return true;

	if (currentStep == Fade_Step::TO_BLACK)
	{
		++frameCount;
		if (frameCount >= maxFadeFrames)
		{
			// TODO 1: Enable / Disable the modules received when FadeToBlacks(...) gets called
			currentStep = Fade_Step::FROM_BLACK;

			moduleToDisable->Disable();
			moduleToEnable->Enable();
		}
	}
	else
	{
		--frameCount;
		if (frameCount <= 0)
		{
			currentStep = Fade_Step::NONE;
		}
	}

	return true;
}

bool ModuleFadeToBlack::PostUpdate()
{
	// Exit this function if we are not performing a fade
	if (currentStep == Fade_Step::NONE) return true;

	float fadeRatio = (float)frameCount / (float)maxFadeFrames;

	// Render the black square with alpha on the screen
	SDL_SetRenderDrawColor(app->render->renderer, 0, 0, 0, (Uint8)(fadeRatio * 255.0f));
	SDL_RenderFillRect(app->render->renderer, &screenRect);

	return true;
}

bool ModuleFadeToBlack::FadeToBlack(Module* moduleToDisable, Module* moduleToEnable, float frames)
{
	bool ret = false;

	// If we are already in a fade process, ignore this call
	if (currentStep == Fade_Step::NONE)
	{
		currentStep = Fade_Step::TO_BLACK;
		frameCount = 0;
		maxFadeFrames = frames;

		// TODO 1: How do we keep track of the modules received in this function?
		this->moduleToDisable = moduleToDisable;
		this->moduleToEnable = moduleToEnable;

		ret = true;
	}

	return ret;
}