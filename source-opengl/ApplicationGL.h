#pragma once

#include <vector>
#include "Mouse.h"
#include "RendererGL.h"
#include "Cloth.h"

struct ApplicationGL 
{
private:
    RendererGL* renderer = nullptr;
    Mouse* mouse = nullptr;
    Cloth* cloth = nullptr;

    bool isRunning = false;
    double lastUpdateTime;

public:
    ApplicationGL() = default;
    ~ApplicationGL() = default;
    
    bool IsRunning() const;

    void Setup(int clothWidth, int clothHeight, int clothSpacing);
    void Input();
    void Update();
    void Render() const;
    void Destroy();
};
