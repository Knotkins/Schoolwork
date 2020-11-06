#include "ParticleEmitter.h"


ParticleEmitter::ParticleEmitter(int number_, std::string texture_, std::string shaderProgram_)
{
	number = number_;
	particles.reserve(number);
	
	texID = TextureHandler::GetInstance()->GetTexture(texture_);
	shaderID = ShaderHandler::GetInstance()->GetShader(shaderProgram_);

	if (texID == 0 || shaderID == 0) {
		Debug::Error("Could not load texture or shader ID in particle!", __FILE__, __LINE__);
	}
	else {
		for (int i = 0; i < number; i++) {
			Particle* part = new Particle(shaderID, texID);
			particles.push_back(part);
		}
		Stagger();
	}
}

ParticleEmitter::~ParticleEmitter()
{
}

void ParticleEmitter::Update(float deltaTime_)
{
	for (int i = 0; i < number; i++) {
		particles[i]->lifeTime -= deltaTime_;
		if (particles[i]->lifeTime <= 0) {
			particles[i]->~Particle();
			delete particles[i];
			particles.shrink_to_fit();
		}
		else
			particles[i]->position = particles[i]->velocity * deltaTime_;
	}

}

void ParticleEmitter::Render(Camera* camera_)
{
	for (auto m : particles) {
		m->Render(camera_);
	}
}

void ParticleEmitter::Stagger()
{
	for (int i = 0; i < number; i++) {
		particles[i]->velocity = glm::vec3(rand(), rand(), rand()); //USE SCOTT'S RAND FUNCTION
	}
}
// GIVE EMITTER A POSTION, OFFSET CREATED PARTICLES BY THAT POSITION
//SET THE SHADER PROGRAM HERE INSTEAD OF IN PARTICLE