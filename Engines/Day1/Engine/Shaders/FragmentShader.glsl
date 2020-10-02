#version 450 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 Color;
in vec3 FragPosition;
out vec4 fColor;

uniform sampler2D inputTexture;
uniform vec3 cameraPosition;

struct Light {
	vec3 lightPosition;
	vec3 lightColor;
	float ambientLight;
	float diffuseLight;
};

struct Material {
    sampler2D diffuseMap;
    float shininess;
	float transparency;
	vec3 ambientMat;
	vec3 diffuseMat;
	vec3 specularMat;
};

uniform Light light;
uniform Material material;

void main() { 

//// LIGHTING
////	Ambient
//	vec3 ambient = light.ambientLight * texture(inputTexture, TexCoords).rgb * light.lightColor;
//	
////	Diffuse
//	vec3 norm = normalize(Normal);
//	vec3 lightDir = normalize(light.lightPosition - FragPosition);
//	float diff = max(dot(norm, lightDir), 0.0f);
//	vec3 diffuse = diff * texture(inputTexture, TexCoords).rgb * light.lightColor;
//
////	Specular
//	float specularStrength = 0.5f;
//	vec3 viewDir = normalize(cameraPosition - FragPosition);
//	vec3 reflectDir = reflect(-lightDir, norm);
//	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32.0f);
//	vec3 specular = specularStrength * spec * light.lightColor;
//
//	vec3 result = ambient + diffuse + specular;

// MATERIAL
	//Ambient
    vec3 ambientMat = light.ambientLight * material.ambientMat * texture(material.diffuseMap, TexCoords).rgb * light.lightColor;
    
    //Diffuse
    vec3 normMat = normalize(Normal);
    vec3 lightDirMat = normalize(light.lightPosition - FragPosition);
    float diffMat = max(dot(normMat, lightDirMat), 0.0);
    vec3 diffuseMat = (diffMat * material.diffuseMat) * texture(material.diffuseMap, TexCoords).rgb * light.lightColor;
    
    //Specular
    vec3 viewDirMat = normalize(cameraPosition-FragPosition);
    vec3 reflectDirMat = reflect(-lightDirMat, normMat);
    float specMat = pow(max(dot(viewDirMat, reflectDirMat), 0.0), material.shininess);
    vec3 specularMat = (specMat * material.specularMat) * light.lightColor;
    vec3 resultMat = ambientMat + diffuseMat + specularMat;

    fColor = vec4(resultMat, material.transparency);
//	fColor = vec4(result, 1.0f);
//	fColor = texture(inputTexture, TexCoords);
//	fColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}