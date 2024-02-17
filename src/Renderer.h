#include "Shader.h"

class Renderer
{
private:
    Shader* m_Shader;

public:
    Renderer(Shader* shader);

    void DrawTriangle(const float* vertices, const unsigned int& size);
    void DrawRectangle(const float* vertices, const unsigned int& size,
        const unsigned int* indices, const unsigned int& count);
};