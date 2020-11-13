#ifndef JSONPARSER_H
#define JSONPARSER_H
#include "json.hpp"
#include "../../Engine/Core/CoreEngine.h"
#include "../../Engine/Rendering/3D/TestComponent.h"
#include "../../Engine/Audio/AudioSource.h"
#include "../../Engine/Rendering/2D/ParticleEmitter.h"

class JsonParser
{
public:
	JsonParser(std::string fileName);
	~JsonParser();

	std::map<std::string, Model*> models;
};

#endif // !JSONPARSER_H