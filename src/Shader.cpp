#include <iostream>
#include <fstream>
#include <string>

#include "Shader.h"

void Shader::ReadShaderFile(const char* path, std::string *pointer)
{
  std::ifstream shader(path);

  if(!shader.is_open())
  {
    std::cerr << "[error]: Failed to load shader file: " << path << std::endl;
    return;
  }

  *pointer = std::string((std::istreambuf_iterator<char>(shader)), std::istreambuf_iterator<char>());

  shader.close();
}

void Shader::CompileShader(const std::string& source, const ShaderType type, unsigned int* shader)
{
  const char* code = source.c_str();
  *shader = glCreateShader(type);

  glShaderSource(*shader, 1, &code, NULL);
  glCompileShader(*shader);

  GLint success;
  char infoLog[512];

  glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
  if (!success) {
      glGetProgramInfoLog(*shader, 512, NULL, infoLog);
      std::cerr << "[error]: Shader compiled failed" << type << "\n" << infoLog << std::endl;
  }
}

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
  std::string vertexSource, fragmentSource;
  unsigned int vertexShader, fragmentShader;

  Shader::ReadShaderFile(vertexPath, &vertexSource);
  Shader::ReadShaderFile(fragmentPath, &fragmentSource);

  Shader::CompileShader(vertexSource, ShaderType::Vertex, &vertexShader);
  Shader::CompileShader(fragmentSource, ShaderType::Fragment, &fragmentShader);

  m_ShaderProgramId = glCreateProgram();
  
  glAttachShader(m_ShaderProgramId, vertexShader);
  glAttachShader(m_ShaderProgramId, fragmentShader);
  glLinkProgram(m_ShaderProgramId);

  GLint success;
  char infoLog[512];

  glGetProgramiv(m_ShaderProgramId, GL_LINK_STATUS, &success);
  if (!success) {
      glGetProgramInfoLog(m_ShaderProgramId, 512, NULL, infoLog);
      std::cerr << "[error]: Shader program linking failed\n" << infoLog << std::endl;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
  glDeleteProgram(m_ShaderProgramId);
}

void Shader::SetFloat(const char* target, const float& value)
{
  glUniform1f(glGetUniformLocation(m_ShaderProgramId, target), value);
}

void Shader::SetMat4f(const char* target, const glm::mat4 translation)
{
    glUniformMatrix4fv(glGetUniformLocation(m_ShaderProgramId, target), 1, GL_FALSE, glm::value_ptr(translation));
}

void Shader::Activate()
{
  glUseProgram(m_ShaderProgramId);
}

void Shader::Deactivate()
{
  glUseProgram(0);
}
