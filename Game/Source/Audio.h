#ifndef __AUDIO_H__
#define __AUDIO_H__

#include "Module.h"

#define DEFAULT_MUSIC_FADE_TIME 2.0f

struct _Mix_Music;
struct Mix_Chunk;

class Audio : public Module
{
public:

	Audio(bool startEnabled);

	// Destructor
	virtual ~Audio();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	bool Update(float dt);
	// Called before quitting
	bool CleanUp();
	bool Start(bool newGame);
	// Play a music file
	bool PlayMusic(const char* path, float fadeTime = DEFAULT_MUSIC_FADE_TIME);

	// Load a WAV in memory
	unsigned int LoadFx(const char* path);

	// Play a previously loaded WAV
	bool PlayFx(unsigned int fx, int repeat = 0);
	void Unload(int id);

	int volumeMusic;
	int volumeFx;
private:
	
	_Mix_Music* music;
	List<Mix_Chunk *>	fx;
};

#endif // __AUDIO_H__