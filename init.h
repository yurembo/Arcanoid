#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include "gl\glut.h"
#include <stdio.h>

int WinWidth = 800;
int WinHeight = 600;

int score = 0;//������� �����
int level = 1;//����� ������
int removedBlocks = 0;//������ �����

void PaintScreen(const float r, const float g, const float b, const int time);