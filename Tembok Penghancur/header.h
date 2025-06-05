
#ifndef HEADER_H
#define HEADER_H
#ifdef _MSC_VER
#pragma once
#endif  
#include "raylib.h"
#include "raymath.h"    
#include <iostream>		
#include <string>
#include <vector>
#include <cmath>

using namespace std;

enum BALL_STATE { BALL_NORMAL = 0, BALL_DOUBLE_SIZE, BALL_HALF_SIZE, BALL_DOUBLE_SPEED, BALL_HALF_SPEED };
enum BALL_COLLISION { BALL_MISS_PADDLE = 0, BALL_COLLIDED };
enum PADDLE_STATE { NORMAL = 0, PAD_DOUBLE_SIZE, PAD_HALF_SIZE };
enum ORIGINAL_WINDOW_SIZE { WIN_WD = 800, WIN_HT = 800 };
enum BRICK_TYPES {
	B_LIGHTGRAY = 0, B_GRAY, B_YELLOW, B_ORANGE, B_PINK, B_RED, B_MAROON,
	B_GREEN, B_LIME, B_DARKGREEN, B_SKYBLUE, B_BLUE, B_DARKBLUE, B_PURPLE, B_VIOLET, B_DARKPURPLE,
	B_BEIGE, B_BROWN, B_DARKBROWN, B_MAGENTA
};

struct Ball {

	float x = 0.0f,
		y = 0.0f,
		velocityX = 250.0f, 
		velocityY = 250.0f, 
		radius = 4.0f;

	Color color = WHITE;

	void draw()
	{
		DrawCircle((int)x, (int)y, radius, color);
	}
};

struct Paddle {

	float x = WIN_WD / 2.0f + 5,
		y = WIN_HT - 100.0f,
		speed = 400.0f,
		width = 80.0f,
		height = 8.0f;

	Color color = WHITE;

	Rectangle rect()
	{
		return Rectangle{ x , y , width, height };
	}

	void draw()
	{
		DrawRectangleRec(rect(), color);
	}
};

struct Brick {

	float x = 0.0f,
		y = 0.0f,
		width = 46.0f,
		height = 22.0f;

	Color color = WHITE;

	bool isAlive = true;

	Rectangle rect_collision() 
	{
		return Rectangle{ x , y , width + 8, height + 8 };
	}

	Rectangle rect() 
	{
		return Rectangle{ x , y , width, height };
	}

	void draw()
	{
		DrawRectangleRounded(rect(), 0.2f, 4, color);
		DrawRectangleRoundedLines(rect(), 0.2f, 4, DARKGRAY); 
	}
};


struct DottedLine {

	int startX = 0,
		startY = 0,
		endX = 0,
		endY = 0,
		numDots = 10;
	int slope = 0;

	Color color = WHITE;

	bool isAlive = false;
};
#endif
