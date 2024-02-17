#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Renderer.h"

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{   
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Graphics Engine", NULL, NULL);

    if (!window)
    {
        std::cout << "[error]: Failed to create glfw window." << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "[error]: Failed to load glad." << std::endl;

        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    
    float triangleVertices[] = {
            0.5f, -0.5f, 0.0f,       0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f,
            0.0f, 0.5f, 0.0f,        1.0f, 0.0f, 0.0f,
    };

    float rectangleVertices[] = { 
            -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f,
            0.5, 0.0f, 0.0f,        1.0f, 0.0f, 0.0f,
            -0.5f, 0.0f, 0.0f,      0.0f, 1.0f, 1.0f,
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    bool drawTriangle = true;
    bool drawRectangle = false;

    float size = 1.0f;
    float position[] = { 0.0f, 0.0f };

    Shader shader = Shader("res\\shaders\\default.vert", "res\\shaders\\default.frag");
    Renderer renderer = Renderer(&shader);

    while (!glfwWindowShouldClose(window)) 
    {
        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (drawTriangle)
            renderer.DrawTriangle(triangleVertices, sizeof(triangleVertices));

        if (drawRectangle)
            renderer.DrawRectangle(rectangleVertices, sizeof(rectangleVertices), indices, 6);

        ImGui::Begin("OpenGl");

        if (ImGui::CollapsingHeader("Geometry"))
        {
            ImGui::Checkbox("Triangle", &drawTriangle);
            ImGui::Checkbox("Rectangle", &drawRectangle);
        };
        
        if (ImGui::CollapsingHeader("Transform"))
        {
            ImGui::DragFloat("X", &position[0], 0.05f, -2.0f, 2.0f, "X: %.3f");
            ImGui::DragFloat("Y", &position[1], 0.05f, -2.0f, 2.0f, "Y: %.3f");
            ImGui::SliderFloat("Size Scallar", &size, 0.1f, 2.0f);
        };

        ImGui::End();
        
        
        glm::mat4 trans(1.0f);
        trans = glm::translate(trans, glm::vec3(position[0], position[1], 0.0f));

        shader.SetMat4f("transform", trans);
        shader.SetFloat("size", size);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return 0;
}