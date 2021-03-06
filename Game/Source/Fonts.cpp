#include "App.h"

#include "Textures.h"
#include "Render.h"
#include "Fonts.h"
#include "Log.h"

#include<string.h>

Fonts::Fonts(bool isEnabled) : Module(isEnabled)
{

}

Fonts::~Fonts()
{

}

// Load new texture from file path
int Fonts::Load(const char* texturePath, const char* characters, uint rows)
{
	int id = -1;

	if (texturePath == nullptr || characters == nullptr || rows == 0)
	{
		LOG("Could not load font");
		return id;
	}

	SDL_Texture* tex = app->tex->Load(texturePath);

	if (tex == nullptr || strlen(characters) >= MAX_FONT_CHARS)
	{
		LOG("Could not load font at %s with characters '%s'", texturePath, characters);
		return id;
	}

	id = 0;
	for (; id < MAX_FONTS; ++id)
		if (fonts[id].texture == nullptr)
			break;

	if (id == MAX_FONTS)
	{
		LOG("Cannot load font %s. Array is full (max %d).", texturePath, MAX_FONTS);
		return id;
	}

	Font& font = fonts[id];

	font.texture = tex;
	font.rows = rows;

	//Finish storing font data

	// totalLength ---	length of the lookup table
	// table ---------  All characters displayed in the same order as the texture
	// columns -------  Amount of chars per row of the texture
	// char_w --------	Width of each character
	// char_h --------	Height of each character

	strcpy_s(fonts[id].table, MAX_FONT_CHARS, characters);
	font.totalLength = strlen(characters);
	font.columns = fonts[id].totalLength / rows;

	uint tex_w, tex_h;
	app->tex->GetSize(tex, tex_w, tex_h);
	font.charw = 32;
	font.charh = 55;

	LOG("Successfully loaded BMP font from %s", texturePath);

	return id;
}

void Fonts::UnLoad(int fontId)
{
	if (fontId >= 0 && fontId < MAX_FONTS && fonts[fontId].texture != nullptr)
	{
		app->tex->UnLoad(fonts[fontId].texture);
		fonts[fontId].texture = nullptr;
		LOG("Successfully Unloaded BMP font_id %d", fontId);
	}
}

void Fonts::BlitText(int x, int y, int fontId, const char* text) const
{
	if (text == nullptr || fontId < 0 || fontId >= MAX_FONTS || fonts[fontId].texture == nullptr)
	{
		LOG("Unable to render text with bmp font id %d", fontId);
		return;
	}

	const Font* font = &fonts[fontId];
	SDL_Rect spriteRect;
	uint len = strlen(text);

	spriteRect.w = font->charw;
	spriteRect.h = font->charh;

	for (uint i = 0; i < len; ++i)
	{
		//Find the character in the table and its position in the texture, then Blit
		uint charIndex = 0;

		// Find the location of the current character in the lookup table
		for (uint j = 0; j < font->totalLength; ++j)
		{
			if (font->table[j] == text[i])
			{
				charIndex = j;
				break;
			}
		}

		// Retrieve the position of the current character in the sprite
		spriteRect.x = spriteRect.w * (charIndex % font->columns);
		spriteRect.y = spriteRect.h * (charIndex / font->columns);

		app->render->DrawTexture(font->texture, x, y, &spriteRect);

		// Advance the position where we blit the next character
		x += 34;
	}
}
