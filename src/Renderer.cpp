#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

Renderer::Renderer(Shader* shader)
  : m_Shader(shader)
{
}

void Renderer::DrawTriangle(const float* vertices, const unsigned int& size)
{
    VertexArray va = VertexArray();
    VertexBuffer vb = VertexBuffer(vertices, size);
    va.Bind();

    VertexBufferLayout layout = VertexBufferLayout();
    layout.SetAttribute(GL_FLOAT, 3, GL_FALSE);
    layout.SetAttribute(GL_FLOAT, 3, GL_FALSE);
    layout.SetAttribute(GL_FLOAT, 2, GL_FALSE);

    va.LinkVertexBuffer(vb, layout);
    
    m_Shader->Activate();
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    va.Unbind();
    vb.Unbind();
}

void Renderer::DrawRectangle(const float* vertices, const unsigned int& size, 
    const unsigned int* indices, const unsigned int& count)
{
    VertexArray va = VertexArray();
    VertexBuffer vb = VertexBuffer(vertices, size);
    va.Bind();

    VertexBufferLayout layout = VertexBufferLayout();
    layout.SetAttribute(GL_FLOAT, 3, GL_FALSE);
    layout.SetAttribute(GL_FLOAT, 3, GL_FALSE);
    layout.SetAttribute(GL_FLOAT, 2, GL_FALSE);

    va.LinkVertexBuffer(vb, layout);

    IndexBuffer ib = IndexBuffer(indices, count);
    va.Bind();
    ib.Bind();

    m_Shader->Activate();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    vb.Unbind();
    va.Unbind();
    ib.Unbind();
}