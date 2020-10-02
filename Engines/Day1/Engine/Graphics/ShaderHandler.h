#ifndef SHADERHANDLER_H
#define SHADERHANDLER_H

#include <sstream>
#include <map>
#include <vector>
#include <memory>
#include <glew.h>
#include "../Core/Debug.h"

class ShaderHandler {
public:
	ShaderHandler(const ShaderHandler&) = delete;
	ShaderHandler(ShaderHandler&&) = delete;

	ShaderHandler& operator = (const ShaderHandler&) = delete;
	ShaderHandler& operator = (const ShaderHandler&&) = delete;

	static ShaderHandler* GetInstance();

	void CreateProram(const std::string& shaderName_, const std::string& vertexShaderFilePath_, const std::string& fragmentShaderFilePath_);
	void OnDestroy();

	GLuint GetShader(const std::string& shaderName_);

private:	
	ShaderHandler();

	~ShaderHandler();
	
	static std::unique_ptr<ShaderHandler> shaderInstance;
	
	friend std::default_delete<ShaderHandler>;

	std::string ReadShader(const std::string& filePath_);

	GLuint CreateShader(GLenum shaderType_, const std::string& source_, const std::string& shaderName_);

	static std::map<std::string, GLuint> programs;
};
#endif // ! SHADERHANDLER_H