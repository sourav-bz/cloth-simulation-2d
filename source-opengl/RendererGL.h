#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "IRenderer.h"

class RendererGL : public IRenderer {
private:
    int windowWidth, windowHeight;
    GLFWwindow* window;
    
    // Shader program for basic line/point rendering
    GLuint shaderProgram;
    GLuint VAO, VBO;
    
    // Shader source code
    const char* vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec2 aPos;
        uniform mat4 projection;
        void main() {
            gl_Position = projection * vec4(aPos.x, aPos.y, 0.0, 1.0);
        }
    )";
    
    const char* fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;
        uniform vec3 color;
        void main() {
            FragColor = vec4(color, 1.0);
        }
    )";
    
    bool CreateShaders();
    GLuint CompileShader(const char* source, GLenum type);
    void SetupProjectionMatrix();

public:
    RendererGL() = default;
    ~RendererGL();
    
    int GetWindowWidth() const override { return windowWidth; }
    int GetWindowHeight() const override { return windowHeight; }

    bool Setup();
    void ClearScreen(unsigned int color) const override;
    void Render() const override;
    void DrawLine(int x0, int y0, int x1, int y1, unsigned int color) const override;
    void DrawPoint(int x, int y, unsigned int color) const override;
    
    // GLFW window access for input handling
    GLFWwindow* GetWindow() const { return window; }
};
