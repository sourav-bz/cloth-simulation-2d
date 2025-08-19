#pragma once

// Abstract base class for renderers to allow both SDL and OpenGL implementations
class IRenderer {
public:
    virtual ~IRenderer() = default;
    
    virtual int GetWindowWidth() const = 0;
    virtual int GetWindowHeight() const = 0;
    
    virtual void ClearScreen(unsigned int color) const = 0;
    virtual void Render() const = 0;
    virtual void DrawLine(int x0, int y0, int x1, int y1, unsigned int color) const = 0;
    virtual void DrawPoint(int x, int y, unsigned int color) const = 0;
};
