#pragma once

#include "Renderer.h"

class Point;
class Stick
{
private:
	Point& p0;
	Point& p1;
	float length;

	bool isActive = true;
	bool isSelected = false;

	Uint32 color = 0xFF2C3E50;
	Uint32 colorWhenSelected = 0xFFE74C3C;

public:
	Stick(Point& p0, Point& p1, float lenght);
	~Stick() = default;

	void SetIsSelected(bool value);

	void Update();
	void Draw(const Renderer* renderer) const;
	void Break();
};