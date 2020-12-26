#ifndef __GUIBUTTON_H__
#define __GUIBUTTON_H__

#include "GuiControl.h"

#include "Point.h"
#include "SString.h"

class GuiButton : public GuiControl
{
public:

    GuiButton(int id, SDL_Rect bounds, const char *text);
    ~GuiButton();

    bool Update(float dt);
    bool Draw()override;

private:

    // Gui Button specific properties
    // Maybe some animation properties for state change?
};

#endif // __GUIBUTTON_H__
