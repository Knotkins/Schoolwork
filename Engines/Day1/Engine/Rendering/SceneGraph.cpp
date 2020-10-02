#include "SceneGraph.h"

std::unique_ptr<SceneGraph> SceneGraph::sceneGraphInstance = nullptr;
std::map<GLuint, std::vector<Model*>> SceneGraph::sceneModels = 
std::map<GLuint, std::vector<Model*>>();
std::map<std::string, GameObject*> SceneGraph::sceneGameObjects =
std::map<std::string, GameObject*>();

SceneGraph::SceneGraph() {
}

SceneGraph::~SceneGraph() {
	OnDestroy();
}

SceneGraph* SceneGraph::GetInstance() {
	if (sceneGraphInstance.get() == nullptr) {
		sceneGraphInstance.reset(new SceneGraph);
	}
	return sceneGraphInstance.get();
}

void SceneGraph::AddModel(Model* model_) {
	if (sceneModels.find(model_->GetShaderProgram()) == sceneModels.end()) {
		std::vector<Model*> tmp = std::vector<Model*>();
		tmp.reserve(10);
		tmp.push_back(model_);
		sceneModels.insert(std::pair<GLuint, std::vector<Model*>>(model_->GetShaderProgram(), tmp));
	}
	else {
		sceneModels[model_->GetShaderProgram()].push_back(model_);
	}
}

void SceneGraph::AddGameObject(GameObject* go_, std::string nameTag_) {
	if (nameTag_ == "") {
		std::string newTag = "GameObject" + std::to_string(sceneGameObjects.size() + 1);
		go_->SetnameTag(newTag);
		sceneGameObjects[newTag] = go_;
	}
	else if (sceneGameObjects.find(nameTag_) == sceneGameObjects.end()) {
		go_->SetnameTag(nameTag_);
		sceneGameObjects[nameTag_] = go_;
	}
	else {
		Debug::Error("Trying to add a GameObject with a tag " + nameTag_ + " that already exists", "SceneGraph.cpp", __LINE__);
		std::string newTag = "GameObject" + std::to_string(sceneGameObjects.size() + 1);
		go_->SetnameTag(newTag);
		sceneGameObjects[newTag] = go_;
	}
	CollisionHandler::GetInstance()->AddObject(go_);
}

GameObject* SceneGraph::GetGameObject(std::string nameTag_) {
	if (sceneGameObjects.find(nameTag_) != sceneGameObjects.end()) {
		return sceneGameObjects[nameTag_];
	}
	return nullptr;
}

void SceneGraph::Update(const float deltaTime_) {
	for (auto go : sceneGameObjects) {
		go.second->Update(deltaTime_);
	}
}

void SceneGraph::Render(Camera* camera_) {
	TransformMatrix(camera_->GetPerspective(), camera_->GetView());
	for (auto entry : sceneModels) {
		glUseProgram(entry.first);
		for (auto m : entry.second) {
			if (InFrustrum(m->GetPosition())) {
				m->Render(camera_);
			}
		}
	}
}

void SceneGraph::OnDestroy() {
	if (sceneGameObjects.size() > 0) {
 		for (auto go : sceneGameObjects) {
			delete go.second;
			go.second = nullptr;
		}
		sceneGameObjects.clear();
	}

	if (sceneModels.size() > 0) {
		for (auto entry : sceneModels) {
			if (entry.second.size() > 0) {
				for (auto m : entry.second) {
					delete m;
					m = nullptr;
				}
				entry.second.clear();
			}
		}
		sceneModels.clear();
	}
}

void SceneGraph::TransformMatrix(glm::mat4 projecMat_, glm::mat4 viewMat_)
{
	Planes.clear();
	double planeMatrix[4][4];

	planeMatrix[0][0] = viewMat_[0][0] * projecMat_[0][0] + viewMat_[0][1] * projecMat_[1][0] + viewMat_[0][2] * projecMat_[2][0] + viewMat_[0][3] * projecMat_[3][0];
	planeMatrix[0][1] = viewMat_[0][0] * projecMat_[0][1] + viewMat_[0][1] * projecMat_[1][1] + viewMat_[0][2] * projecMat_[2][1] + viewMat_[0][3] * projecMat_[3][1];
	planeMatrix[0][2] = viewMat_[0][0] * projecMat_[0][2] + viewMat_[0][1] * projecMat_[1][2] + viewMat_[0][2] * projecMat_[2][2] + viewMat_[0][3] * projecMat_[3][2];
	planeMatrix[0][3] = viewMat_[0][0] * projecMat_[0][3] + viewMat_[0][1] * projecMat_[1][3] + viewMat_[0][2] * projecMat_[2][3] + viewMat_[0][3] * projecMat_[3][3];

	planeMatrix[1][0] = viewMat_[1][0] * projecMat_[0][0] + viewMat_[1][1] * projecMat_[1][0] + viewMat_[1][2] * projecMat_[2][0] + viewMat_[1][3] * projecMat_[3][0];
	planeMatrix[1][1] = viewMat_[1][0] * projecMat_[0][1] + viewMat_[1][1] * projecMat_[1][1] + viewMat_[1][2] * projecMat_[2][1] + viewMat_[1][3] * projecMat_[3][1];
	planeMatrix[1][2] = viewMat_[1][0] * projecMat_[0][2] + viewMat_[1][1] * projecMat_[1][2] + viewMat_[1][2] * projecMat_[2][2] + viewMat_[1][3] * projecMat_[3][2];
	planeMatrix[1][3] = viewMat_[1][0] * projecMat_[0][3] + viewMat_[1][1] * projecMat_[1][3] + viewMat_[1][2] * projecMat_[2][3] + viewMat_[1][3] * projecMat_[3][3];

	planeMatrix[2][0] = viewMat_[2][0] * projecMat_[0][0] + viewMat_[2][1] * projecMat_[1][0] + viewMat_[2][2] * projecMat_[2][0] + viewMat_[2][3] * projecMat_[3][0];
	planeMatrix[2][1] = viewMat_[2][0] * projecMat_[0][1] + viewMat_[2][1] * projecMat_[1][1] + viewMat_[2][2] * projecMat_[2][1] + viewMat_[2][3] * projecMat_[3][1];
	planeMatrix[2][2] = viewMat_[2][0] * projecMat_[0][2] + viewMat_[2][1] * projecMat_[1][2] + viewMat_[2][2] * projecMat_[2][2] + viewMat_[2][3] * projecMat_[3][2];
	planeMatrix[2][3] = viewMat_[2][0] * projecMat_[0][3] + viewMat_[2][1] * projecMat_[1][3] + viewMat_[2][2] * projecMat_[2][3] + viewMat_[2][3] * projecMat_[3][3];

	planeMatrix[3][0] = viewMat_[3][0] * projecMat_[0][0] + viewMat_[3][1] * projecMat_[1][0] + viewMat_[3][2] * projecMat_[2][0] + viewMat_[3][3] * projecMat_[3][0];
	planeMatrix[3][1] = viewMat_[3][0] * projecMat_[0][1] + viewMat_[3][1] * projecMat_[1][1] + viewMat_[3][2] * projecMat_[2][1] + viewMat_[3][3] * projecMat_[3][1];
	planeMatrix[3][2] = viewMat_[3][0] * projecMat_[0][2] + viewMat_[3][1] * projecMat_[1][2] + viewMat_[3][2] * projecMat_[2][2] + viewMat_[3][3] * projecMat_[3][2];
	planeMatrix[3][3] = viewMat_[3][0] * projecMat_[0][3] + viewMat_[3][1] * projecMat_[1][3] + viewMat_[3][2] * projecMat_[2][3] + viewMat_[3][3] * projecMat_[3][3];


	glm::vec4 upPlane = glm::vec4();
	upPlane.x = planeMatrix[0][3] - planeMatrix[0][1];
	upPlane.y = planeMatrix[1][3] - planeMatrix[1][1];
	upPlane.z = planeMatrix[2][3] - planeMatrix[2][1];
	upPlane.w = planeMatrix[3][3] - planeMatrix[3][1];
	glm::normalize(upPlane);
	Planes.push_back(upPlane);

	glm::vec4 downPlane = glm::vec4();
	downPlane.x = planeMatrix[0][3] + planeMatrix[0][1];
	downPlane.y = planeMatrix[1][3] + planeMatrix[1][1];
	downPlane.z = planeMatrix[2][3] + planeMatrix[2][1];
	downPlane.w = planeMatrix[3][3] + planeMatrix[3][1];
	glm::normalize(downPlane);
	Planes.push_back(downPlane);

	glm::vec4 leftPlane = glm::vec4();
	leftPlane.x = planeMatrix[0][3] + planeMatrix[0][0];
	leftPlane.y = planeMatrix[1][3] + planeMatrix[1][0];
	leftPlane.z = planeMatrix[2][3] + planeMatrix[2][0];
	leftPlane.w = planeMatrix[3][3] + planeMatrix[3][0];
	glm::normalize(leftPlane);
	Planes.push_back(leftPlane);

	glm::vec4 rightPlane = glm::vec4();
	rightPlane.x = planeMatrix[0][3] - planeMatrix[0][0];
	rightPlane.y = planeMatrix[1][3] - planeMatrix[1][0];
	rightPlane.z = planeMatrix[2][3] - planeMatrix[2][0];
	rightPlane.w = planeMatrix[3][3] - planeMatrix[3][0];
	glm::normalize(rightPlane);
	Planes.push_back(rightPlane);

	glm::vec4 nearPlane = glm::vec4();
	nearPlane.x = planeMatrix[0][3] - planeMatrix[0][2];
	nearPlane.y = planeMatrix[1][3] - planeMatrix[1][2];
	nearPlane.z = planeMatrix[2][3] - planeMatrix[2][2];
	nearPlane.w = planeMatrix[3][3] - planeMatrix[3][2];
	glm::normalize(nearPlane);
	Planes.push_back(nearPlane);

	glm::vec4 farPlane = glm::vec4();
	farPlane.x = planeMatrix[0][3] + planeMatrix[0][2];
	farPlane.y = planeMatrix[1][3] + planeMatrix[1][2];
	farPlane.z = planeMatrix[2][3] + planeMatrix[2][2];
	farPlane.w = planeMatrix[3][3] + planeMatrix[3][2];
	glm::normalize(farPlane);
	Planes.push_back(farPlane);
}

bool SceneGraph::InFrustrum(glm::vec3 position_) {
	for (unsigned int i = 0; i < 6; i++) {
		if (Planes[i].x * position_.x + Planes[i].y * position_.y + Planes[i].z * position_.z + Planes[i].w <= 0) {
			return false;
		}
	}
	return true;
}