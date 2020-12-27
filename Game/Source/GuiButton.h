#ifndef __GUIBUTTON_H__
#define __GUIBUTTON_H__

#include "GuiControl.h"
#include "Textures.h"
#include"Audio.h"
#include "Point.h"
#include "SString.h"

class GuiButton : public GuiControl
{
public:

    GuiButton(int id, SDL_Rect bounds, const char *text, unsigned int clickedFx, unsigned int focusedFx);
    ~GuiButton();

    bool Update(float dt);
    bool Draw()override;

private:
	bool buttonsColliders;
    SDL_Texture* textureButtons;
    // Gui Button specific properties
    // Maybe some animation properties for state change?
};

#endif // __GUIBUTTON_H__
