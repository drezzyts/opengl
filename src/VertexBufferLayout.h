#pragma once

#include <glad/glad.h>
#include <vector>

struct VertexAttribute 
{
  unsigned int type;
  unsigned int count;
  unsigned char normalized;

  static unsigned int GetSizeByType(unsigned int type) 
  {
    switch(type) 
    {
      case GL_FLOAT: return sizeof(float);
      case GL_UNSIGNED_INT: return sizeof(unsigned int);
      case GL_UNSIGNED_BYTE: return 1;
      default: return 0;
   }
  }  
};

class VertexBufferLayout
{
  private:
    std::vector<VertexAttribute> m_Attributes;
    unsigned int m_Stride;
  
  public:
      VertexBufferLayout()
          : m_Stride(0) {};

    void SetAttribute(unsigned int type, unsigned int count, unsigned char normalized) {
      m_Attributes.push_back({ type, count, normalized });
      m_Stride += count * VertexAttribute::GetSizeByType(type);
    }

    inline const std::vector<VertexAttribute> GetAttributes() const& { return m_Attributes; }
    inline unsigned int GetStride() const { return m_Stride; }
};