#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

enum ShaderType 
{
  Vertex = GL_VERTEX_SHADER,
  Fragment = GL_FRAGMENT_SHADER,
};

class Shader 
{
  private:
    unsigned int m_ShaderProgramId;

    static void ReadShaderFile(const char* path, std::string* pointer);
    static void CompileShader(const std::string &source, const ShaderType type, unsigned int *shader);

  public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void SetFloat(const char* target, const float& value);
    void SetFloat4fv(const char* target, const float* values);
    void SetMat4f(const char* target, const glm::mat4 translation);

    void Activate();
    void Deactivate();
};

