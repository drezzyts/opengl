#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

Renderer::Renderer(Shader* shader)
  : m_Shader(shader)
{
}

void Renderer::DrawTriangle()
{
    float vertices[] = {
               0.5f, -0.5f, 0.0f,       0.0f, 0.0f, 1.0f,      1.0f, 0.0f,
               -0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f,      0.0f, 0.0f,
               0.0f, 0.5f, 0.0f,        1.0f, 0.0f, 0.0f,      0.0f, 1.0f
    };

    float size = sizeof(vertices);
    
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

void Renderer::DrawRectangle()
{
    float vertices[] = {
            0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,       0.0f, 0.0f,
            0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f,       1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f,        1.0f, 0.0f, 0.0f,       1.0f, 0.5f,
            -0.5f,  0.5f, 0.0f,      0.0f, 1.0f, 1.0f,       0.0f, 0.5f
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    float size = sizeof(vertices);
    unsigned int count = 6;

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

void Renderer::DrawCube()
{
    float vertices[] = {
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

     0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f
    };
    
    float size = sizeof(vertices);

    VertexArray va = VertexArray();
    VertexBuffer vb = VertexBuffer(vertices, size);
    va.Bind();

    VertexBufferLayout layout = VertexBufferLayout();
    layout.SetAttribute(GL_FLOAT, 3, GL_FALSE);
    layout.SetAttribute(GL_FLOAT, 3, GL_FALSE);
    layout.SetAttribute(GL_FLOAT, 2, GL_FALSE);

    va.LinkVertexBuffer(vb, layout);

    m_Shader->Activate();

    glDrawArrays(GL_TRIANGLES, 0, 36);

    va.Unbind();
    vb.Unbind();
}