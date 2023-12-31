#ifndef _shader_h_
#define _shader_h_

#include <string>

#include <GL/glew.h>

class Shader
{
public:
	Shader();
	~Shader();

	void CreateFromSource(const char* vertexCode, const char* fragmentCode);
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);

	GLuint programID() { return shaderID; }

	void UseShader();

private:
	GLuint shaderID;

	std::string ReadFile(const char* fileLocation);
	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
	void ClearShader();
};

#endif
