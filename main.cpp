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

// Shader loading utility
std::string loadShaderSource(const char* path)
{
    std::ifstream file(path);
    if (!file)
    {
        std::cerr << "Failed to open shader file: " << path << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

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

// Shader helpers
unsigned int compileShader(unsigned int type, const char* source)
{
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Shader compilation error:\n" << infoLog << std::endl;
    }
    return shader;
}

unsigned int createShaderProgram(const char* vs, const char* fs)
{
    unsigned int vertex = compileShader(GL_VERTEX_SHADER, vs);
    unsigned int fragment = compileShader(GL_FRAGMENT_SHADER, fs);

    unsigned int program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return program;
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
    std::string vertexCode = loadShaderSource("shaders/vertex.glsl");
    std::string fragmentCode = loadShaderSource("shaders/fragment.glsl");

    const char* vertexShaderSrc = vertexCode.c_str();
    const char* fragmentShaderSrc = fragmentCode.c_str();

    unsigned int shaderProgram = createShaderProgram(vertexShaderSrc, fragmentShaderSrc);

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
        GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUseProgram(shaderProgram);
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}