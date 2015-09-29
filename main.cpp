// Arcanoid by Yuriy Yazev

#include <vector>
#include "paddle.h"
#include "ball.h"
#include "block.h"
#include <time.h>
#include <Windowsx.h>

using namespace std;

  CPaddle *paddle;
  CBall *ball;
  vector<CBlock>blockVec;

int random()
{
	const int div = 8;
	int i = rand() % div;
	int j = ((float)rand() / (RAND_MAX + 3) * 10);
	if (j > 5) i = -i;
	return i;
}

void InitBlocks()
{
	srand((unsigned)time(NULL));
	CBlock block;
	for (int i = 0; i < RowsInColumn; i++) {
      float r = ((float)rand() / (RAND_MAX + 4) * 10) / 10;
	  float g = ((float)rand() / (RAND_MAX + 3) * 10) / 10;
	  float b = ((float)rand() / (RAND_MAX + 3) * 10) / 10;
		for (int j = 0; j < BlocksInRow; j++) {
			block = CBlock(48+90*j, WinHeight / 2 + 35 + 45*i, 0, 70, 25, r, g, b);
			blockVec.push_back(block);
		}
	}
}

void PrintString(void* font, char* str)	//Вывод строки
{
	char *c = str;
	while (*c)
	{
		glutBitmapCharacter(font, *c);
		c++;
	}
}

void RepaintScreen(int value)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
}

void PaintScreen(const float r, const float g, const float b, const int time)
{
	glClearColor(r, g, b, 1.0);
	glutTimerFunc(time, RepaintScreen, 1);
}

void StartNextLevel()
{
	removedBlocks = 0;
	level++;
	score += 500;
	blockVec.clear();
	ball->SetX(ballXpos);
	ball->SetY(ballYpos);
	InitBlocks();
	PaintScreen(1.0, 1.0, 0.0, 500);
}

void CheckCollision()
{
	if (paddle->GetX() > WinWidth - paddle->GetWidth()) 
		paddle->SetX(WinWidth - paddle->GetWidth());
	if (paddle->GetX() < 0.0) 
		paddle->SetX(0.0);

	if ((ball->GetY() < paddle->GetY() + ball->GetRadius() + paddle->GetHeight()) && (ball->GetY() > paddle->GetY() - paddle->GetHeight())) {
	if ((ball->GetX() > paddle->GetX() - ball->GetRadius()) && (ball->GetX() < paddle->GetX()))
		ball->SetIncX(-ball->GetIncX()); else

	if ((ball->GetX() > paddle->GetX() + paddle->GetWidth()) && (ball->GetX() < paddle->GetX() + paddle->GetWidth() + ball->GetRadius())) 
		ball->SetIncX(-ball->GetIncX()); else

	if ((ball->GetX() > paddle->GetX() - ball->GetRadius()) && (ball->GetX() < paddle->GetX() + paddle->GetWidth() + ball->GetRadius())) {
		score += 10;
		ball->SetIncY(-ball->GetIncY());
		ball->SetY(paddle->GetY() + ball->GetRadius() + paddle->GetHeight());
		ball->SetIncX(ball->GetIncX() + random());//при столкновении шара с ракеткой изменяем скорость перемещения по оси X - для веселья!
	}
	}

	vector<CBlock>::iterator iter = blockVec.begin();
	while (iter != blockVec.end()) {
		if (iter->GetLife() == true) {
		if ((ball->GetX() - ball->GetRadius() < iter->GetX() + iter->GetWidth()) && (ball->GetX() + ball->GetRadius() > iter->GetX())
		&& ((ball->GetY() - ball->GetRadius() < iter->GetY() + iter->GetHeight()) && (ball->GetY()+ ball->GetRadius() > iter->GetY()))) {
			score += 15;
			iter->SetLife(false);
			removedBlocks++;
			ball->SetIncY(-ball->GetIncY());
			ball->SetIncX(ball->GetIncX() - random());//при столкновении шара с блоком изменяем скорость перемещения по оси X - для веселья!
			break;
		}
		}
		iter++;
	}
	if (ball->GetIncX() > 15) ball->SetIncX(15); else
	if (ball->GetIncX() < -15) ball->SetIncX(-15);
	if (removedBlocks == BlocksInRow * RowsInColumn) StartNextLevel();
}

void OutputText()
{
	char label[50] = "Level: ";
	char strScore[10];
	char strLevel[10];
 	_itoa_s(score, strScore, size_t(10), 10);
	_itoa_s(level, strLevel, size_t(10), 10);
	strcat_s(label, strLevel);
	strcat_s(label, "  Score: ");
	strcat_s(label, strScore);

	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(20, WinHeight-40);	
	PrintString(GLUT_BITMAP_TIMES_ROMAN_24, label);
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	CheckCollision();

	if (ball != NULL) ball->Render();
	glColor3f(0.5, 0.1, 0.1);
	if (paddle != NULL) paddle->Render();
	vector<CBlock>::iterator iter = blockVec.begin();
	while (iter != blockVec.end()) {
		iter->Render();
		iter++;
	}

	OutputText();

	glutSwapBuffers();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		case VK_ESCAPE:
				exit(0);
				break;
	}
}

void KeyboardSpecial(int key, int x, int y)
{
	switch (key)
	{
		case VK_LEFT:
				if (paddle != NULL) 
					paddle->SetX(paddle->GetX() - paddle->GetIncX());
				break;

		case VK_RIGHT:
				if (paddle != NULL) 
					paddle->SetX(paddle->GetX() + paddle->GetIncX());
				break;

		case VK_ESCAPE:
				exit(0);
				break;
	}
}

void Reshape(int width, int height)
{
	WinWidth = width;
	WinHeight = height;

	glViewport(0, 0, WinWidth, WinHeight);
	glLoadIdentity();
	gluOrtho2D(0, WinWidth, 0, WinHeight);
}

void Mouse(int x, int y)
{
	paddle->SetX(x);
}

void Timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(30, Timer, 1);
}

void InitObjs()
{
	paddle = new CPaddle(WinWidth / 2, paddleYpos, paddleIncX, paddleWidth, paddleHeight);
	ball = new CBall(ballXpos, ballYpos, ballIncX, ballIncY, ballRadius);

	InitBlocks();
}

LRESULT CALLBACK WindowProc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch(msg)
	{
		case WM_DESTROY:          
			exit(0);
		    PostQuitMessage(0);
		    return 0;

         case WM_KEYDOWN:
             KeyboardSpecial(wparam, 0, 0);
			 return 0;
 
        case WM_SIZE: 
            Reshape(LOWORD(lparam), HIWORD(lparam));
            return 0; 

		case WM_SETCURSOR:
			glutSetCursor(GLUT_CURSOR_NONE);
			return 0;

		case WM_MOUSEMOVE:
			Mouse(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
			return 0;
    
		default:
		    return DefWindowProc(wnd, msg, wparam, lparam);
	}
}

int main(int argc, char* argv[])
{
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(WinWidth, WinHeight);
	glutInitWindowPosition((GetSystemMetrics(SM_CXSCREEN)-WinWidth)/2, (GetSystemMetrics(SM_CYSCREEN)-WinHeight)/2);
	glutCreateWindow("Arcanoid");
	HWND m_window = FindWindowA(NULL, "Arcanoid");
    SetWindowLong(m_window, GWL_WNDPROC, (LONG)WindowProc);
	glutDisplayFunc(Display);
	InitObjs();
	glutTimerFunc(30, Timer, 1);
	glutMainLoop();

	return 0;
}