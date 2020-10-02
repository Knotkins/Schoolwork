#include "LightSource.h"

LightSource::LightSource (glm::vec3 position_, glm::vec3 lightColor_, float ambientValue_, float diffuseValue_) {
	position = position_;
	lightColor = lightColor_;
	ambientValue = ambientValue_;
	diffuseValue = diffuseValue_;
}

LightSource::~LightSource() {
}

void LightSource::SetPosition(glm::vec3 position_) {
	position = position_;
}

void LightSource::SetLightColor(glm::vec3 lightColor_) {
	lightColor = lightColor_;
}

void LightSource::SetAmbientValue(float ambientValue_) {
	ambientValue = ambientValue_;
}

void LightSource::SetDiffuseValue(float diffuseValue_) {
	diffuseValue = diffuseValue_;
}

glm::vec3 LightSource::GetPosition() {
	return position;
}

glm::vec3 LightSource::GetLightColor() {
	return lightColor;
}

float LightSource::GetAmbientValue() {
	return ambientValue;
}

float LightSource::GetDiffuseValue() {
	return diffuseValue;
}