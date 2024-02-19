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
#include "Texture.h"

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
    glEnable(GL_DEPTH_TEST);
    glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    bool drawTriangle = false;
    bool drawRectangle = false;
    bool drawCube = true;
    
    bool beyblade = false;
    bool useRainbow = true;
    bool useTexture = false;
    bool useInputColor = false;

    float size = 1.0f;
    float rotationAngle = 45.0f;

    float rotationVec[] = { 1.0f, 0.0f, 1.0f };
    float positionVec[] = { 0.0f, 0.0f, 0.0f };

    float inputColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    Shader shader = Shader("res\\shaders\\default.vert", "res\\shaders\\default.frag");
    Renderer renderer = Renderer(&shader);

    int selectedTexture = 0;
    const char* textures[] = { "Bricks", "Stone", "Wood Planks" };


    while (!glfwWindowShouldClose(window)) 
    {
        Texture* texture = nullptr;

        switch (selectedTexture)
        {
        case 0:
            texture = new Texture("res\\textures\\bricks.jpg");
            break;
        case 1:
            texture = new Texture("res\\textures\\stone.jpg");
            break;
        case 2:
            texture = new Texture("res\\textures\\wood-planks.jpg");
            break;
        }

        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (drawTriangle)
            renderer.DrawTriangle();

        if (drawRectangle)
            renderer.DrawRectangle();

        if (drawCube)
            renderer.DrawCube();

        ImGui::Begin("OpenGl");

        if (ImGui::CollapsingHeader("Geometry"))
        {
            ImGui::Checkbox("Triangle", &drawTriangle);
            ImGui::Checkbox("Rectangle", &drawRectangle);
            ImGui::Checkbox("Cube", &drawCube);
        };
        
        if (ImGui::CollapsingHeader("Transform"))
        {
            ImGui::Text("Position");
            ImGui::DragFloat("X Axis", &positionVec[0], 0.05f, -5.0f, 5.0f, "X: %.3f");
            ImGui::DragFloat("Y Axis", &positionVec[1], 0.05f, -5.0f, 5.0f, "Y: %.3f");
            ImGui::DragFloat("Z Axis", &positionVec[2], 0.05f, -5.0f, 5.0f, "Z: %.3f");

            ImGui::Text("Rotation");
            ImGui::DragFloat("X Axis", &rotationVec[0], 0.05f, -5.0f, 5.0f, "X: %.3f");
            ImGui::DragFloat("Y Axis", &rotationVec[1], 0.05f, -5.0f, 5.0f, "Y: %.3f");
            ImGui::DragFloat("Z Axis", &rotationVec[2], 0.05f, -5.0f, 5.0f, "Z: %.3f");
            ImGui::SliderFloat("Angle", &rotationAngle, 0.1f, 360.0f, "%.3f°");

            ImGui::Text("Scale");
            ImGui::SliderFloat("Scallar", &size, 0.1f, 2.0f);
        };

        if (ImGui::CollapsingHeader("Style"))
        {
            ImGui::ColorEdit4("Color", inputColor);
            ImGui::Combo("Texture", &selectedTexture, textures, 3);
        }

        if (ImGui::CollapsingHeader("Config"))
        {
            ImGui::Checkbox("Rainbow", &useRainbow);
            ImGui::Checkbox("Texture", &useTexture);
            ImGui::Checkbox("InputColor", &useInputColor);
            ImGui::Checkbox("Beyblade", &beyblade);
            ImGui::ShowStyleSelector("Theme");
        }

        ImGui::End();
        
        
        glm::mat4 trans(1.0f);
        trans = glm::translate(trans, glm::vec3(positionVec[0], positionVec[1], 0.0f));
       
        glm::mat4 model(1.0f);
        model = glm::rotate(model, (beyblade ? (float) glfwGetTime() : 1.0f) * glm::radians(rotationAngle), glm::vec3(rotationVec[0], rotationVec[1], rotationVec[2]));

        glm::mat4 view(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);


        shader.SetMat4f("transform", trans);
        shader.SetMat4f("model", model);
        shader.SetMat4f("view", view);
        shader.SetMat4f("projection", projection);

        shader.SetFloat("size", size);
        shader.SetFloat4fv("inputColor", inputColor);

        shader.SetFloat("useTexture", useTexture);
        shader.SetFloat("useInputColor", useInputColor);
        shader.SetFloat("useRainbow", useRainbow);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();

        delete texture;
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return 0;
}