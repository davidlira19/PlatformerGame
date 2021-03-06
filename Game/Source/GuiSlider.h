#ifndef __GUISLIDER_H__
#define __GUISLIDER_H__

#include "GuiControl.h"

#include "Point.h"
#include "SString.h"

class GuiSlider : public GuiControl
{
public:

	GuiSlider(int id, SDL_Rect bounds, const char* text, unsigned int clickedFx, unsigned int focusedFx, SDL_Texture* textureButton, SDL_Texture* textureSlider);
	virtual ~GuiSlider();

	bool Update( float dt);
	bool Draw();

	int value;
	int minValue;
	int maxValue;

	int GetMusicValue() override;

private:

	// GuiSlider specific properties
	// Maybe some animation properties for state change?
	SDL_Rect slider;
	bool drawRect;
	
};

#endif // __GUISLIDER_H__
