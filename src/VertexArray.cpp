#include <glad/glad.h>
#include "VertexArray.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray() 
{
  glGenVertexArrays(1, &m_Id);
}

VertexArray::~VertexArray()
{
  glDeleteVertexArrays(1, &m_Id);
}

void VertexArray::LinkVertexBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout)
{
  vb.Bind();

  const auto& attributes = layout.GetAttributes();
  unsigned int offset = 0;

  for(unsigned int i = 0; i < attributes.size(); i++)
  {
    const auto& attribute = attributes[i];

    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i, attribute.count, attribute.type, 
      attribute.normalized, layout.GetStride(), (const void*)offset);

    offset += attribute.count * VertexAttribute::GetSizeByType(attribute.type);
  }

  vb.Unbind();
}

void VertexArray::Bind() const {
    glBindVertexArray(m_Id);
}

void VertexArray::Unbind() const {
    glBindVertexArray(0);
}