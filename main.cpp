#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Mesh.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"
#include "ScreenQuad.h"
#include "Shader.h"

static bool fill = true;
static bool wireframe = false;
static bool point = false;

enum class RenderMesh
{
    Triangle,
    Rectangle,
    Circle,
    ScreenQuad
};

static RenderMesh currentMesh = RenderMesh::Triangle;

// Resize callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Input
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        fill = true;
        wireframe = false;
        point = false;
    }

    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glLineWidth(2.0f);
        fill = false;
		wireframe = true;
        point = false;
    }

    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        glPointSize(5.0f);
        fill = false;
        wireframe = false;
		point = true;
    }

    // Face culling controls
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        glEnable(GL_CULL_FACE);

    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
        glDisable(GL_CULL_FACE);

    // Mesh switching
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
        currentMesh = RenderMesh::Triangle;

    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
        currentMesh = RenderMesh::Rectangle;

    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
        currentMesh = RenderMesh::Circle;

    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
        currentMesh = RenderMesh::ScreenQuad;
}

int main()
{
    // GLFW init
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "GLFW 3.4 + OpenGL 4.6", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    // Shaders
    Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");

	Triangle triangle;
	Rectangle rectangle(0.8f, 0.6f);
	Circle circle(0.5f, 64);
	ScreenQuad screenQuad;

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.05f, 0.08f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();

        switch (currentMesh)
        {
        case RenderMesh::Triangle:
            triangle.Draw();
            break;

        case RenderMesh::Rectangle:
            rectangle.Draw();
            break;

        case RenderMesh::Circle:
            circle.Draw();
            break;

        case RenderMesh::ScreenQuad:
            screenQuad.Draw();
            break;
        }

        GLfloat timeValue = (GLfloat)glfwGetTime();
        GLfloat greenValue = sinf(timeValue) * 0.5f + 0.5f;
		shader.setVec4("ourColor", 0.0f, greenValue, 0.0f, 1.0f);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}