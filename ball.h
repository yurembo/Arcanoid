#include "dib.h"

const int ballRadius = 15,
ballXpos = WinWidth / 2,
ballYpos = WinHeight / 2,
ballIncX = 10,
ballIncY = 10;

class CBall : public CDib
{
private:
	GLUquadricObj* qO;
	int rad;
public:
	CBall(const int xpos, const int ypos, const int incX, const int incY, const int radius)
	{
		x = xpos;
		y = ypos;
		ix = incX;
		iy = incY;
		rad = radius;
		qO = gluNewQuadric();
	}
	~CBall()
	{
		gluDeleteQuadric(qO);
		x = 0;
		y = 0;
		ix = 0;
		iy = 0;
		rad = 0;
	}
	void Move()
	{
		x = x - ix;
		y = y - iy;
		if (x > WinWidth - rad) {
			ix = -ix;
			x = WinWidth - rad;
		}
		if  (x < rad) {
			ix = -ix;
			x = rad;
		}
		if (y > WinHeight - rad) {
			iy = -iy;
			y = WinHeight - rad;
		}
		if (y < rad) {
			score -= 20;
			iy = -iy;
			y = rad;
			PaintScreen(1.0, 0.0, 0.0, 100);
		}
	}
	void Render()
	{
		Move();
		glPushMatrix();
		glTranslatef(x, y, 0.0);
		glColor3f(0.0, 0.0, 1.0);
		gluDisk(qO, 0.0, rad, 30, 30);
		glPopMatrix();
	}
	int GetRadius() { return rad; }
	void SetRadius(const int radius) { rad = radius; }
};