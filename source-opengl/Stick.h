#pragma once

#include "IRenderer.h"

class Point;
class Stick
{
private:
    Point& p0;
    Point& p1;
    float length;

    bool isActive = true;
    bool isSelected = false;

    unsigned int color = 0xFF2C3E50;
    unsigned int colorWhenSelected = 0xFFE74C3C;

public:
    Stick(Point& p0, Point& p1, float length);
    ~Stick() = default;

    void SetIsSelected(bool value);

    void Update();
    void Draw(const IRenderer* renderer) const;
    void Break();
};
