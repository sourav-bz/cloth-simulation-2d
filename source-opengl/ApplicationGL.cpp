#include <iostream>
#include "ApplicationGL.h"

void ApplicationGL::Setup(int clothWidth, int clothHeight, int clothSpacing)
{
    renderer = new RendererGL();
    mouse = new Mouse();
    
    isRunning = renderer->Setup();

    clothWidth /= clothSpacing;
    clothHeight /= clothSpacing;
    int startX = renderer->GetWindowWidth() * 0.5f - clothWidth * clothSpacing * 0.5f;
    int startY = renderer->GetWindowHeight() * 0.1f;

    cloth = new Cloth(clothWidth, clothHeight, clothSpacing, startX, startY);

    lastUpdateTime = glfwGetTime();
}

void ApplicationGL::Input()
{
    glfwPollEvents();
    
    GLFWwindow* window = renderer->GetWindow();
    
    // Check if window should close
    if (glfwWindowShouldClose(window)) {
        isRunning = false;
        return;
    }
    
    // Handle keyboard input
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        isRunning = false;
    }
    
    // Handle mouse position
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    mouse->UpdatePosition(static_cast<int>(xpos), static_cast<int>(ypos));
    
    // Handle mouse buttons
    static bool leftWasPressed = false;
    static bool rightWasPressed = false;
    
    bool leftPressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
    bool rightPressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
    
    // Left mouse button
    if (leftPressed && !leftWasPressed) {
        mouse->SetLeftMouseButton(true);
    } else if (!leftPressed && leftWasPressed) {
        mouse->SetLeftMouseButton(false);
    }
    
    // Right mouse button  
    if (rightPressed && !rightWasPressed) {
        mouse->SetRightMouseButton(true);
    } else if (!rightPressed && rightWasPressed) {
        mouse->SetRightMouseButton(false);
    }
    
    leftWasPressed = leftPressed;
    rightWasPressed = rightPressed;
}

// Mouse scroll callback function (needs to be static for GLFW)
static Mouse* g_mouse = nullptr;

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (g_mouse) {
        if (yoffset > 0) {
            g_mouse->IncreaseCursorSize(10);
        } else if (yoffset < 0) {
            g_mouse->IncreaseCursorSize(-10);
        }
    }
}

void ApplicationGL::Update()
{    
    // Set up scroll callback (only needs to be done once, but doing it here for simplicity)
    g_mouse = mouse;
    glfwSetScrollCallback(renderer->GetWindow(), scrollCallback);
    
    double currentTime = glfwGetTime();
    float deltaTime = static_cast<float>(currentTime - lastUpdateTime);

    cloth->Update(renderer, mouse, deltaTime);

    lastUpdateTime = currentTime;
}

void ApplicationGL::Render() const
{
    renderer->ClearScreen(0xFFF5F5F5);

    cloth->Draw(renderer);

    renderer->Render();
}

bool ApplicationGL::IsRunning() const
{
    return isRunning;
}

void ApplicationGL::Destroy()
{
    delete mouse;
    delete renderer;
    delete cloth;
}
