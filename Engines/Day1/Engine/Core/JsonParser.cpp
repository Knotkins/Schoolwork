#include "JsonParser.h"

JsonParser::JsonParser(std::string fileName)
{
	std::ifstream file(fileName);
	nlohmann::json j;
	file >> j;
	file.close();

	for (int i = 0; i < j["scene"]["texture"].size(); i++) {
		std::string name = j["scene"]["texture"][i]["name"].get<std::string>();
		std::string path = j["scene"]["texture"][i]["path"].get<std::string>();
		TextureHandler::GetInstance()->CreateTexture(name, path);
	}

	for (int i = 0; i < j["scene"]["model"].size(); i++) {
		std::string name = j["scene"]["model"][i]["name"].get<std::string>();
		std::string obj = j["scene"]["model"][i]["obj"].get<std::string>();
		std::string mtl = j["scene"]["model"][i]["mtl"].get<std::string>();
		std::string shader = j["scene"]["model"][i]["shader"].get<std::string>();
		Model* model = new Model(obj, mtl, ShaderHandler::GetInstance()->GetShader(shader));
		models[name] = model;
		SceneGraph::GetInstance()->AddModel(model);
	}
	for (int i = 0; i < j["scene"]["gameObject"].size(); i++) {
		int id = j["scene"]["gameObject"][i]["id"].get<int>();
		std::string name = j["scene"]["gameObject"][i]["name"].get<std::string>();
		std::string modelName = j["scene"]["gameObject"][i]["model"].get<std::string>();
		std::vector<float> position = j["scene"]["gameObject"][i]["position"].get<std::vector<float>>();
		glm::vec3 pos = glm::vec3(position[0], position[1], position[2]);
		
		GameObject* gameObject = new GameObject(models[modelName], pos);
		SceneGraph::GetInstance()->AddGameObject(gameObject, name);

		if (j["scene"]["gameObject"][i]["components"].size() > 0) {
			if (j["scene"]["gameObject"][i]["components"].contains("TestComponent")) {
				SceneGraph::GetInstance()->GetGameObject(name)->AddComponent<TestComponent>();
			}
			if (j["scene"]["gameObject"][i]["components"].contains("AudioSource")) {
				SceneGraph::GetInstance()->GetGameObject(name)->AddComponent<AudioSource>(
					j["scene"]["gameObject"][i]["components"]["AudioSource"]["path"],
					j["scene"]["gameObject"][i]["components"]["AudioSource"]["loop"],
					j["scene"]["gameObject"][i]["components"]["AudioSource"]["is3d"],
					j["scene"]["gameObject"][i]["components"]["AudioSource"]["howPlay"]);
			}
		}
	}
	for (int i = 0; i < j["scene"]["guiObject"].size(); i++) {
		int id = j["scene"]["guiObject"][i]["id"].get<int>();
		std::string name = j["scene"]["guiObject"][i]["name"].get<std::string>();
		std::vector<float> position = j["scene"]["guiObject"][i]["position"].get<std::vector<float>>();
		glm::vec2 pos = glm::vec2(position[0], position[1]);

		GuiObject* gui = new GuiObject(pos);
		SceneGraph::GetInstance()->AddGuiObject(gui, name);

		if (j["scene"]["guiObject"][i]["components"].size() > 0) {
			if (j["scene"]["guiObject"][i]["components"].contains("GuiImageCcomponent")) {
				std::string ICName = j["scene"]["guiObject"][i]["components"]["GuiImageCcomponent"]["name"].get<std::string>();
				std::vector<float> offset = j["scene"]["guiObject"][i]["components"]["GuiImageCcomponent"]["offset"].get<std::vector<float>>();
				glm::vec2 off = glm::vec2(offset[0], offset[1]);
				float scale = j["scene"]["guiObject"][i]["components"]["GuiImageCcomponent"]["scale"];
				float angle = j["scene"]["guiObject"][i]["components"]["GuiImageCcomponent"]["angle"];
				std::vector<float> tint = j["scene"]["guiObject"][i]["components"]["GuiImageCcomponent"]["tint"].get<std::vector<float>>();
				glm::vec4 tintGood = glm::vec4(tint[0], tint[1], tint[2], tint[3]);
				SceneGraph::GetInstance()->GetGuiObject(name)->AddComponent<GuiImageCcomponent>();
				SceneGraph::GetInstance()->GetGuiObject(name)->GetComponent<GuiImageCcomponent>()->OnCreate(
					ICName, off, scale, angle, tintGood);
			}

		}
	}
}

JsonParser::~JsonParser()
{

}
