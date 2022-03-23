#ifndef AUDIO_H
#define AUDIO_H

#include "SDL.h"

class Audio
{
public:
	Audio(const char* filePath);
	~Audio();

	void SetUpDevice();
	void Play();
	void Pause();
	void PlayWithLoop();

private:
	SDL_AudioDeviceID deviceID;
	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8* wavBuffer;
};
#endif