#include "App.h"
#include "Audio.h"
#include "Input.h"
#include "Defs.h"
#include "Log.h"

// Recommended using: Additional Include Directories, instead of 'hardcoding' library location path in code logic
#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"

// Library linkage is configured in Linker Options
#pragma comment(lib, "../Game/Source/External/SDL_mixer/libx86/SDL2_mixer.lib")

Audio::Audio(bool startEnabled) : Module(startEnabled)
{
	music = NULL;
	name.Create("audio");
	volumeMusic = 20;
	volumeFx = 100;
}

// Destructor
Audio::~Audio() {}
void Audio::Unload(int id)
{
	/*if (music != NULL)
	{
		Mix_FreeMusic(music);
	}*/
	ListItem<Mix_Chunk*>* item;
	int cont = 0;
	for (item = fx.start; item != NULL && cont<=id; item = item->next) 
	{
		if (id == cont) 
		{
			Mix_FreeChunk(item->data);
			fx.Del(item);
			break;
		}
		cont++;
	}
	//fx.Clear();
}
bool Audio::Start(bool newGame) 
{
	//LOG("Loading Audio Mixer");
	//bool ret = true;
	//SDL_Init(0);

	//if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
	//{
	//	LOG("SDL_INIT_AUDIO could not initialize! SDL_Error: %s\n", SDL_GetError());
	//	isEnabled = false;
	//	ret = true;
	//}

	//// Load support for the JPG and PNG image formats
	//int flags = MIX_INIT_OGG;
	//int init = Mix_Init(flags);

	//if ((init & flags) != flags)
	//{
	//	LOG("Could not initialize Mixer lib. Mix_Init: %s", Mix_GetError());
	//	isEnabled = false;
	//	ret = true;
	//}

	//// Initialize SDL_mixer
	//if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	//{
	//	LOG("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	//	isEnabled = false;
	//	ret = true;
	//}
	//Mix_VolumeMusic(10);

	return true;
}
// Called before render is available
bool Audio::Awake(pugi::xml_node& config)
{
	LOG("Loading Audio Mixer");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
	{
		LOG("SDL_INIT_AUDIO could not initialize! SDL_Error: %s\n", SDL_GetError());
		isEnabled = false;
		ret = true;
	}

	// Load support for the JPG and PNG image formats
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	if((init & flags) != flags)
	{
		LOG("Could not initialize Mixer lib. Mix_Init: %s", Mix_GetError());
		isEnabled = false;
		ret = true;
	}

	// Initialize SDL_mixer
	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		LOG("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		isEnabled = false;
		ret = true;
	}
	Mix_VolumeMusic(10);

	return ret;
}

bool Audio::Update(float dt)
{
	ListItem<Mix_Chunk*>*auxiliar;
	auxiliar = fx.start;
	while (auxiliar != nullptr) 
	{
		Mix_VolumeChunk(auxiliar->data, volumeFx);
		auxiliar = auxiliar->next;
	}
	
	Mix_VolumeMusic(volumeMusic);
	if (app->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		volumeMusic += 5;
		if (volumeMusic >= 100)
		{
			volumeMusic = 100;
		}
	}
	if (app->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
	{
		volumeMusic -= 5;
		if (volumeMusic <= 0)
		{
			volumeMusic = 0;
		}
	}

	return true;
}

// Called before quitting
bool Audio::CleanUp()
{
	if(!isEnabled)
		return true;

	LOG("Freeing sound FX, closing Mixer and Audio subsystem");

	if(music != NULL)
	{
		Mix_FreeMusic(music);
	}

	ListItem<Mix_Chunk*>* item;
	for(item = fx.start; item != NULL; item = item->next)
		Mix_FreeChunk(item->data);

	fx.Clear();

	Mix_CloseAudio();
	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);

	return true;
}

// Play a music file
bool Audio::PlayMusic(const char* path, float fadeTime)
{
	bool ret = true;

	if(!isEnabled)
		return false;

	if(music != NULL)
	{
		if(fadeTime > 0.0f)
		{
			Mix_FadeOutMusic(int(fadeTime * 1000.0f));
		}
		else
		{
			Mix_HaltMusic();
		}

		// This call blocks until fade out is done
		Mix_FreeMusic(music);
	}

	music = Mix_LoadMUS(path);

	if(music == NULL)
	{
		LOG("Cannot load music %s. Mix_GetError(): %s\n", path, Mix_GetError());
		ret = false;
	}
	else
	{
		if(fadeTime > 0.0f)
		{
			if(Mix_FadeInMusic(music, -1, (int) (fadeTime * 1000.0f)) < 0)
			{
				LOG("Cannot fade in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
		else
		{
			if(Mix_PlayMusic(music, -1) < 0)
			{
				LOG("Cannot play in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
	}

	LOG("Successfully playing %s", path);
	return ret;
}

// Load WAV
unsigned int Audio::LoadFx(const char* path)
{
	unsigned int ret = 0;

	if(!isEnabled)
		return 0;

	Mix_Chunk* chunk = Mix_LoadWAV(path);

	if(chunk == NULL)
	{
		LOG("Cannot load wav %s. Mix_GetError(): %s", path, Mix_GetError());
	}
	else
	{
		fx.Add(chunk);
		ret = fx.count();
	}

	return ret;
}

// Play WAV
bool Audio::PlayFx(unsigned int id, int repeat)
{
	bool ret = false;

	if(!isEnabled)
		return false;

	if(id > 0 && id <= fx.count())
	{
		Mix_PlayChannel(-1, fx[id - 1], repeat);
	}

	return ret;
}