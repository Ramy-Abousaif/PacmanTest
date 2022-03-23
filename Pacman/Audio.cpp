#include "Audio.h"
#include <iostream>

Audio::Audio(const char* filePath)
{
	if (SDL_LoadWAV(filePath, &wavSpec, &wavBuffer, &wavLength) == nullptr)
	{
		std::cerr << "Error: " << filePath
			<< " could not be loaded as an audio file" << std::endl;
	}
}

Audio::~Audio()
{
	SDL_FreeWAV(wavBuffer);
	SDL_CloseAudioDevice(deviceID);
}

void Audio::SetUpDevice()
{
	deviceID = SDL_OpenAudioDevice(nullptr, 0, &wavSpec, nullptr, 0);

	if (deviceID == 0)
		std::cerr << "Error with sound device: " << SDL_GetError() << std::endl;
}

void Audio::Play()
{
	int success = SDL_QueueAudio(deviceID, wavBuffer, wavLength);
	SDL_PauseAudioDevice(deviceID, 0);
}

void Audio::Pause()
{
	SDL_PauseAudioDevice(deviceID, 1);
}

void Audio::PlayWithLoop()
{
	int success = SDL_QueueAudio(deviceID, wavBuffer, wavLength);
	SDL_PauseAudioDevice(deviceID, 0);
}
