#include "Shader.h"

class Renderer
{
private:
    Shader* m_Shader;

public:
    Renderer(Shader* shader);

    void DrawTriangle();
    void DrawRectangle();
    void DrawCube();
};