#include "paddle.h"

const int BlocksInRow = 8,
		  RowsInColumn = 6,
		  blockWidth = 70,
		  blockHeight = 25;

class CBlock : public CPaddle
{
private:
	float r, g, b;
	bool life;//жив или нет - перерисовывать или нет
public:
		CBlock()
		{
			x = 0; 
			y = 0;
			ix = 0;
			iy = 0;
			width = 0;
			height = 0;
			r = 0;
			g = 0;
			b = 0;
			life = true;
		}
		CBlock(const int xpos, const int ypos, const int incX, const int w, const int h, const float R, const float G, const float B)
		{
			x = xpos; 
			y = ypos;
			ix = incX;
			iy = 0;
			width = w;
			height = h;
			r = R;
			g = G;
			b = B;
			life = true;
		}
		~CBlock()
		{
			x = 0; 
			y = 0;
			ix = 0;
			iy = 0;
			width = 0;
			height = 0;
			r = 0;
			g = 0;
			b = 0;
			life = false;
		}
		void Render()
		{
			glColor3f(r, g, b);
			if (life)
				CPaddle::Render();
		}
		bool GetLife() { return life; }
		void SetLife(const bool b) { life = b; }
};