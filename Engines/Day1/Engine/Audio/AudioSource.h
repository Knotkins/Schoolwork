#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H
#include "../Rendering/3D/Component.h"
#include <string>
#include "AudioHandler.h"
class AudioSource : public Component
{
public:
	friend class AudioHandler;
	AudioSource(std::string name_, bool loop_, bool is3d_, bool howPlay_);
	virtual ~AudioSource();
	virtual void OnCreate(GameObject* parent_);
	virtual void Update();
	void PlaySound();
	bool IsPlaying();

private:
	std::string fileName;
	int channelID;
};

#endif // !AUDIOSOURCE_H