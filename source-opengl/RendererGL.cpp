#include <iostream>
#include <cmath>
#include "RendererGL.h"

bool RendererGL::Setup()
{
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    // Configure GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Get primary monitor resolution for fullscreen-like behavior
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    windowWidth = mode->width;
    windowHeight = mode->height;

    // Create window
    window = glfwCreateWindow(windowWidth, windowHeight, "2D Cloth Simulation - OpenGL", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return false;
    }

    // Set viewport
    glViewport(0, 0, windowWidth, windowHeight);

    // Enable VSync
    glfwSwapInterval(1);

    // Create shaders and setup OpenGL objects
    if (!CreateShaders()) {
        return false;
    }

    SetupProjectionMatrix();

    // Setup VAO and VBO for dynamic drawing
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    // Position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return true;
}

bool RendererGL::CreateShaders()
{
    // Compile vertex shader
    GLuint vertexShader = CompileShader(vertexShaderSource, GL_VERTEX_SHADER);
    if (vertexShader == 0) return false;

    // Compile fragment shader
    GLuint fragmentShader = CompileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
    if (fragmentShader == 0) {
        glDeleteShader(vertexShader);
        return false;
    }

    // Create shader program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for linking errors
    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "Shader program linking failed: " << infoLog << std::endl;
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return false;
    }

    // Clean up individual shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
}

GLuint RendererGL::CompileShader(const char* source, GLenum type)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    // Check for compilation errors
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Shader compilation failed: " << infoLog << std::endl;
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

void RendererGL::SetupProjectionMatrix()
{
    // Create orthographic projection matrix for 2D rendering
    // This maps screen coordinates directly to OpenGL coordinates
    glUseProgram(shaderProgram);
    
    // Simple orthographic projection: map (0,0) to (width, height) directly
    float left = 0.0f;
    float right = static_cast<float>(windowWidth);
    float bottom = static_cast<float>(windowHeight); // Flip Y to match SDL coordinate system
    float top = 0.0f;
    float near_plane = -1.0f;
    float far_plane = 1.0f;
    
    // Orthographic projection matrix
    float ortho[16] = {
        2.0f / (right - left), 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f / (top - bottom), 0.0f, 0.0f,
        0.0f, 0.0f, -2.0f / (far_plane - near_plane), 0.0f,
        -(right + left) / (right - left), -(top + bottom) / (top - bottom), -(far_plane + near_plane) / (far_plane - near_plane), 1.0f
    };
    
    GLint projLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, ortho);
}

void RendererGL::ClearScreen(unsigned int color) const
{
    // Convert from RGBA format to separate components
    float r = ((color >> 16) & 0xFF) / 255.0f;
    float g = ((color >> 8) & 0xFF) / 255.0f;
    float b = (color & 0xFF) / 255.0f;
    float a = 1.0f;
    
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void RendererGL::Render() const
{
    glfwSwapBuffers(window);
}

void RendererGL::DrawLine(int x0, int y0, int x1, int y1, unsigned int color) const
{
    // Convert color to RGB components
    float r = ((color >> 16) & 0xFF) / 255.0f;
    float g = ((color >> 8) & 0xFF) / 255.0f;
    float b = (color & 0xFF) / 255.0f;
    
    // Line vertices
    float vertices[] = {
        static_cast<float>(x0), static_cast<float>(y0),
        static_cast<float>(x1), static_cast<float>(y1)
    };
    
    glUseProgram(shaderProgram);
    
    // Set color uniform
    GLint colorLoc = glGetUniformLocation(shaderProgram, "color");
    glUniform3f(colorLoc, r, g, b);
    
    // Upload vertices and draw
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    
    glDrawArrays(GL_LINES, 0, 2);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void RendererGL::DrawPoint(int x, int y, unsigned int color) const
{
    // Convert color to RGB components
    float r = ((color >> 16) & 0xFF) / 255.0f;
    float g = ((color >> 8) & 0xFF) / 255.0f;
    float b = (color & 0xFF) / 255.0f;
    
    // Point vertex
    float vertices[] = {
        static_cast<float>(x), static_cast<float>(y)
    };
    
    glUseProgram(shaderProgram);
    
    // Set color uniform
    GLint colorLoc = glGetUniformLocation(shaderProgram, "color");
    glUniform3f(colorLoc, r, g, b);
    
    // Set point size
    glPointSize(3.0f);
    
    // Upload vertex and draw
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    
    glDrawArrays(GL_POINTS, 0, 1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

RendererGL::~RendererGL()
{
    if (VAO) glDeleteVertexArrays(1, &VAO);
    if (VBO) glDeleteBuffers(1, &VBO);
    if (shaderProgram) glDeleteProgram(shaderProgram);
    
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}
