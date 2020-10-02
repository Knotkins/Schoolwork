#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include <memory>
#include <map>
#include <vector>
#include "3D/GameObject.h"
#include "../Math/CollisionHandler.h"

class SceneGraph {
public:
	SceneGraph(const SceneGraph&) = delete;
	SceneGraph(SceneGraph&&) = delete;

	SceneGraph& operator = (const SceneGraph&) = delete;
	SceneGraph& operator = (SceneGraph&&) = delete;

	static SceneGraph* GetInstance();
	void AddModel(Model* model_);
	void AddGameObject(GameObject* go_, std::string nameTag_ = "");
	GameObject* GetGameObject(std::string nameTag_);
	void Update(const float deltaTime_);
	void Render(Camera* camera_);
	void OnDestroy();

	void TransformMatrix(glm::mat4 projecMat_, glm::mat4 viewMat_);
	bool InFrustrum(glm::vec3 position_);

private:
	SceneGraph();
	~SceneGraph();

	static std::unique_ptr<SceneGraph> sceneGraphInstance;
	friend std::default_delete<SceneGraph>;
	static std::map<GLuint, std::vector<Model*>> sceneModels;
	static std::map<std::string, GameObject*> sceneGameObjects;

	std::vector<glm::vec4> Planes;
};

#endif // !SCENEGRAPH_H