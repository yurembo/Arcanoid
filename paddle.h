#pragma once

#include "dib.h"

const int paddleHeight = 15,
			paddleWidth = 100,
			paddleYpos = 10,
			paddleIncX = 30;

//класс "Ракетка"
class CPaddle : public CDib
{
protected:
	int width, height;
public:
		CPaddle()
		{
			x = 0; 
			y = 0;
			ix = 0;
			iy = 0;
			width = 0;
			height = 0;
		}
		CPaddle(const int xpos, const int ypos, const int incX, const int w, const int h)
		{
			x = xpos; 
			y = ypos;
			ix = incX;
			iy = 0;
			width = w;
			height = h;
		}
		~CPaddle()
		{
			x = 0; 
			y = 0;
			ix = 0;
			iy = 0;
			width = 0;
			height = 0;
		}
		virtual void Render()
		{
			glPushMatrix();
			glTranslatef(x, y, 0.0);
			glRectf(0.0, height, width, 0.0);
			glPopMatrix();
		}
		int GetHeight() { return height; }
		void SetHeight(const int h) { height = h; }
		int GetWidth() { return width; }
		void SetWidth(const int w) { width = w; }
};