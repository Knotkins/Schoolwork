#version 450 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in float size;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform float size;

void main(){
	vec4 distanceFromCamera = view * model * vec4(position, 1.0f, 0.0f);
	float distance = distanceFromCamera.x + distanceFromCamera.y + distanceFromCamera.z;
	float attenuation = inversesqrt(0.1 * distance);
	gl_PointSize = attenuation * size;
	gl_Position = proj * model * vec4(position, 0.0f, 1.0f);
	TexCoords = texCoords;
}