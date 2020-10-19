#include "AudioSource.h"
#include "AudioHandler.h"

AudioSource::AudioSource(std::string name_, bool loop_, bool is3d_, bool howPlay_)
{
	channelID = -1;
	fileName = name_;
	AudioHandler audioHandler;
	audioHandler.loadSound(name_, loop_, is3d_, howPlay_);
}

AudioSource::~AudioSource()
{
}

void AudioSource::OnCreate(GameObject* parent_)
{
	parent = parent_;
}

void AudioSource::Update()
{
}

void AudioSource::PlaySound()
{
	AudioHandler audioHandler;
	channelID = audioHandler.playSound(fileName, glm::vec3(0.0,0.0,0.0)); //Shoudld have parent.getPos(), but you can't use function from a pointer..
}
bool AudioSource::IsPlaying()
{
	AudioHandler audioHandler;
	return audioHandler.isPlaying(channelID);
}
