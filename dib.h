//абстрактный класс - родитель всех фишек
#pragma once

#include "init.h"

class CDib
{
protected:
	int x, y, ix, iy;
public:
	int GetX() { return x; }
	int GetY() { return y; }
	void SetX(const float xpos) { x = xpos; }
	void SetY(const float ypos) { y = ypos; }
	int GetIncX() { return ix; }
	void SetIncX(const float incX) { ix = incX; }
	int GetIncY() { return iy; }
	void SetIncY(const float incY) { iy = incY; }
	virtual void Render() { };
	virtual ~CDib() = 0 { };
};