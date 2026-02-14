#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "stb_image.h"

#include "Mesh.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"
#include "ScreenQuad.h"
#include "Shader.h"

static bool fill = true;
static bool wireframe = false;
static bool point = false;
static int currentAnimType = 1; // start with 1 = sine
static const int maxAnimType = 9; // total number of animations we defined in shader

// How to extend the mesh so it can render a .obj or .fbx file?
// 1. Add a new class ObjMesh that inherits from Mesh.
// 2. Implement a constructor that loads the .obj file and sets up the vertex data.
// 3. Implement the Draw() method to render the loaded mesh.
// 4. Add a new case in the RenderMesh enum and handle it in the main render loop.
// 5. Add input handling to switch to the new mesh type.
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
// TO DO: add control scheme
void processInput(GLFWwindow* window)
{
    static bool aPressedLastFrame = false;

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

    // Cycle animation type with A key
    bool aPressed = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
    if (aPressed && !aPressedLastFrame) // only trigger once per press
    {
        currentAnimType++;
        if (currentAnimType > maxAnimType)
            currentAnimType = 1; // wrap around
        std::cout << "Animation type: " << currentAnimType << std::endl;
    }
    aPressedLastFrame = aPressed;
}

// to do level switch
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
	// to do: add lighting controls here (e.g. toggle directional/point lights, adjust light color/intensity, etc.) and pass them to shader for dynamic lighting effects
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

	// add ecs system here and create entities with different components (e.g. Transform, Renderable, Physics) to manage complex animations and interactions in a more organized way
	Triangle triangle;
	Rectangle rectangle(0.8f, 0.6f);
	Circle circle(0.5f, 64);
	ScreenQuad screenQuad;

    //Fix texture 2
    unsigned int texture;
	unsigned int texture2;
    bool textureLoaded = false;

	// to do add physics-based animation uniforms here (e.g. gravity, mass, etc.) and pass them to shader
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    // texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load the texture
    int width, height, nrChannels;
    unsigned char* data = stbi_load("wall.jpg", &width, &height, &nrChannels, 0);

	// add multiple type of collision detection uniforms here (e.g. bounding box, circle collision, etc.) and pass them to shader for different collision-based animations
    if (data)
    {
        textureLoaded = true;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture, using vertex colors" << std::endl;
    }
    stbi_image_free(data);

	// add coordinate system controls here (e.g. toggle between world/local space, adjust axis orientation, etc.) and pass them to shader for more flexible animation effects

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
		// delta time for animation timing
        processInput(window);

        glClearColor(0.05f, 0.08f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();

		// texture uniform
        shader.setBool("uUseTexture", textureLoaded);
        if (textureLoaded)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, texture2);
            shader.setInt("uTexture", 0);
        }

		// animation uniforms
        shader.setBool("uAnimate", true);
        shader.setFloat("uTime", static_cast<float>(glfwGetTime()));
        shader.setVec3("uOffset", 0.0f, 0.0f, 0.0f);
        shader.setFloat("uSpeed", 1.0f);

        // axis for axis-based animations
        shader.setVec3("uAxis", 0.0f, 1.0f, 0.0f);
        shader.setFloat("uAmp", 0.3f);

        // set the current animation type from the cycling key
        shader.setInt("uAnimType", currentAnimType);

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