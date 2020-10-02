#include "MaterialLoader.h"

MaterialLoader::~MaterialLoader() {
}

void MaterialLoader::LoadMaterial(std::string filePath_) {
	std::ifstream in(filePath_.c_str(), std::ios::in);
	if (!in) {
		Debug::Error("Cannot open MTL file: " + filePath_, "MaterialLoader.cpp", __LINE__);
		return;
	}
	std::string line;
	Material m = Material();
	std::string matName = "";
	while (std::getline(in, line)) {
		if (line.substr(0, 7) == "newmtl ") {
			if (m.diffuseMap != 0) {
				MaterialHandler::GetInstance()->AddMaterial(m);
				m = Material();
			}
			matName = line.substr(7);
			m.diffuseMap = LoadTexture(matName);
			m.name = matName;
		}
		
		if (line.substr(0, 4) == "	Ns ")
		{
			std::istringstream ns(line.substr(4));
			ns >> m.shininess;
		}

		if (line.substr(0, 3) == "	d ")
		{
			std::istringstream d(line.substr(3));
			d >> m.transparency;
		}

		if (line.substr(0, 4) == "	Ka ")
		{
			std::stringstream Ka(line.substr(4));
			float x, y, z;
			Ka >> x >> y >> z;
			m.ambient = glm::vec3(x, y, z);
		}

		if (line.substr(0, 4) == "	Kd ")
		{
			std::stringstream Kd(line.substr(4));
			float x, y, z;
			Kd >> x >> y >> z;
			m.diffuse = glm::vec3(x, y, z);
		}
		
		if (line.substr(0, 4) == "	Ks ")
		{
			std::stringstream Ks(line.substr(4));
			float x, y, z;
			Ks >> x >> y >> z;
			m.specular = glm::vec3(x, y, z);
		}
	}
	if (m.diffuseMap != 0) {
		MaterialHandler::GetInstance()->AddMaterial(m);
	}
	in.close();
}

GLuint MaterialLoader::LoadTexture(std::string fileName_) {
	GLuint currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	if (currentTexture == 0) {
		TextureHandler::GetInstance()->CreateTexture(fileName_, "./Resources/Textures/" + fileName_ + ".jpg");
		currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	}
	return currentTexture;
}