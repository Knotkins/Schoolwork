#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class LightSource {
public:
	LightSource(glm::vec3 position_, glm::vec3 lightColor_, float ambientValue_, float diffuseValue_);
	~LightSource();

	void SetPosition(glm::vec3 position_);
	void SetLightColor(glm::vec3 lightColor_);
	void SetAmbientValue(float ambientValue_);
	void SetDiffuseValue(float diffuseValue_);

	glm::vec3 GetPosition();
	glm::vec3 GetLightColor();

	float GetAmbientValue();
	float GetDiffuseValue();

private:
	glm::vec3 position;
	glm::vec3 lightColor;

	float ambientValue;
	float diffuseValue;
};
#endif // !LIGHTSOURCE_H