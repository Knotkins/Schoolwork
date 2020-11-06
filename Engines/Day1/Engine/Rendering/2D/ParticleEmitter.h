#ifndef PARTICLEEMITTER_H
#define PARTILEEMITTER_H
#include <string>
#include "Particle.h"
#include "../../Math/Randomizer.h"



class ParticleEmitter
{
public:
	ParticleEmitter(int number_, std::string texture_, std::string shaderProgram_);
	~ParticleEmitter();
	void Update(float deltaTime_);
	void Render(Camera* camera_);
	void Stagger();

	int number;

	GLuint texID;
	GLuint shaderID;
	std::vector<Particle*> particles;

	
};

#endif // !PARTICLEEMITTER_H
