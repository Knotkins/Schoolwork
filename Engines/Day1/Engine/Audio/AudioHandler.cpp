#include "AudioHandler.h"
#include "AudioSource.h"

std::unique_ptr<AudioHandler> AudioHandler::audioInstnace = nullptr;
std::map<std::string, FMOD::Sound*> AudioHandler::soundMap = std::map<std::string, FMOD::Sound*>();
std::map<int, FMOD::Channel*> AudioHandler::channelMap = std::map<int, FMOD::Channel*>();

AudioHandler* AudioHandler::GetInstance()
{
	if (audioInstnace.get() == nullptr) {
		audioInstnace.reset(new AudioHandler);
	}
	return audioInstnace.get();
}

bool AudioHandler::Initialize(glm::vec3 pos_, glm::vec3 vel_, glm::vec3 forward_, glm::vec3 up_)
{
	FMOD::System_Create(&fmodSystem);
	if (!fmodSystem->getNumDrivers(0)) {
		return false;
	}
	else {
	fmodSystem->init(5, FMOD_INIT_NORMAL | FMOD_3D | FMOD_INIT_3D_RIGHTHANDED, nullptr);
	FMOD_VECTOR fmodPos = glmToFmod(pos_);
	FMOD_VECTOR fmodVel = glmToFmod(vel_);
	FMOD_VECTOR fmodForward = glmToFmod(forward_);
	FMOD_VECTOR fmodUp = glmToFmod(up_);
	fmodSystem->set3DListenerAttributes(0, &fmodPos, &fmodVel, &fmodForward, &fmodUp);
	return true;
	}
}

void AudioHandler::OnDestroy()
{
	for (auto m : soundMap) {
		m.first.empty();
		m.second->release();
		m.second = nullptr;
		//delete &m
	}
	for (auto m : channelMap) {
		
		m.second->stop();
		m.second = nullptr;
		//delete &m;
	}

	fmodSystem->release();
	fmodSystem = nullptr;
}

AudioHandler::AudioHandler()
{
}

AudioHandler::~AudioHandler()
{
}

FMOD_VECTOR AudioHandler::glmToFmod(glm::vec3 vector_)
{
	FMOD_VECTOR fmodVec;
	fmodVec.x = vector_.x;
	fmodVec.y = vector_.y;
	fmodVec.z = vector_.z;

	return fmodVec;
}

void AudioHandler::loadSound(std::string name_, bool loop_, bool is3d_, bool howPlay_)
{
	if (getSound(name_)) {
		return;
	}
	FMOD_MODE mode = FMOD_DEFAULT;
	FMOD_MODE loopMode;
	FMOD_MODE is3d;
	FMOD_MODE streamType;
	if (loop_) { loopMode = FMOD_LOOP_NORMAL; }
	else { loopMode = FMOD_LOOP_OFF; }

	if (is3d_) { is3d = FMOD_3D; }
	else { is3d = FMOD_2D; }

	if (howPlay_) { streamType = FMOD_CREATESTREAM; }
	else { streamType = FMOD_CREATECOMPRESSEDSAMPLE; }

	mode = mode | loopMode | is3d | streamType;

	FMOD::Sound* sound = nullptr;

	fmodSystem->createSound(name_.c_str(), mode, nullptr, &sound);
	soundMap.emplace(name_, sound);
}

FMOD::Sound* AudioHandler::getSound(std::string name_)
{
	for (auto m : soundMap) {
		if (m.first == name_) {
			return m.second;
		}
	}
	return nullptr;
}

int AudioHandler::playSound(std::string name_, glm::vec3 pos_, glm::vec3 vel_, float volume_)
{
	int channelID = -1;
	if (!getSound(name_)) {
		loadSound(name_, false, true, false);
	}
	FMOD::Channel* channel = nullptr;
	fmodSystem->playSound(soundMap[name_], nullptr, true, &channel);

	FMOD_VECTOR fmodPos = glmToFmod(pos_);
	FMOD_VECTOR fmodVel = glmToFmod(vel_);
	// I wonder if any of this is right
	FMOD_MODE is3d = FMOD_3D;
	//if(channel->getMode(&is3d) == FMOD_OK) //This certainly isn't
	if (channel->getMode(&is3d) == FMOD_3D)
	{
		channel->set3DAttributes(&fmodPos, &fmodVel);
	}
	channel->setVolume(volume_);

	//Is there meant to be a check for proper settings here? how
	channel->setPaused(false);
	channelID = channels;
	channels++;

	channelMap.emplace(channelID, channel);
	return channelID;
}

void AudioHandler::Update(int channelID_, glm::vec3 pos_, glm::vec3 vel_)
{
	if (channelMap[channelID_]) {
		FMOD_VECTOR fmodPos = glmToFmod(pos_);
		FMOD_VECTOR fmodVel = glmToFmod(vel_);
		channelMap[channelID_]->set3DAttributes(&fmodPos, &fmodVel);
	}
	//fmodSystem->update();
}

bool AudioHandler::isPlaying(int channelID_)
{
	if (channelMap[channelID_]) {
		bool isPlaying;
		channelMap[channelID_]->isPlaying(&isPlaying);
		return isPlaying;
	}
	return false;
}
