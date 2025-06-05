
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
 /*--------------------------------****************************************----------------------------------
  |                                *                                      *                                 |
  |   My Bricks Breaker            *               Main Header            *                                 |
  |                                *                                      *                                 |
  ---------------------------------****************************************----------------------------------*/
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*

  Contains
	the main headers calls
	global enums
	global structs


*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef HEADER_H
#define HEADER_H

#ifdef _MSC_VER
#pragma once
#endif  // _MSC_VER

#include "raylib.h"
#include "raymath.h"    // Required for: Vector2Clamp()

#include <iostream>		// For debugging purposes
#include <string>
#include <vector>
#include <cmath>

using namespace std;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
 /*--------------------------------****************************************----------------------------------
  |                                *                                      *                                 |
  |                                *	          Global Enums            *                                 |
  |                                *                                      *                                 |
  ---------------------------------****************************************----------------------------------*/
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*--------------------------
 |                         |
 |  Ball state enumerator  |
 |                         |
 --------------------------*/
enum BALL_STATE { BALL_NORMAL = 0, BALL_DOUBLE_SIZE, BALL_HALF_SIZE, BALL_DOUBLE_SPEED, BALL_HALF_SPEED };

/*--------------------------
 |                         |
 |  Ball collision state   |
 |                         |
 --------------------------*/
enum BALL_COLLISION { BALL_MISS_PADDLE = 0, BALL_COLLIDED };

/*----------------------------
 |                           |
 |  Paddle state enumerator  |
 |                           |
 ----------------------------*/
enum PADDLE_STATE { NORMAL = 0, PAD_DOUBLE_SIZE, PAD_HALF_SIZE };

/*------------------------------
 |                             |
 |  Window size enumerator    |
 |                             |
 ------------------------------*/
enum ORIGINAL_WINDOW_SIZE { WIN_WD = 800, WIN_HT = 800 };

/*------------------------------
 |                             |
 |   Brick Types enumerator    |
 |                             |
 ------------------------------*/
enum BRICK_TYPES {
	B_LIGHTGRAY = 0, B_GRAY, B_YELLOW, B_ORANGE, B_PINK, B_RED, B_MAROON,
	B_GREEN, B_LIME, B_DARKGREEN, B_SKYBLUE, B_BLUE, B_DARKBLUE, B_PURPLE, B_VIOLET, B_DARKPURPLE,
	B_BEIGE, B_BROWN, B_DARKBROWN, B_MAGENTA
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
 /*--------------------------------****************************************----------------------------------
  |                                *                                      *                                 |
  |                                *	       Global Structs             *                                 |
  |                                *                                      *                                 |
  ---------------------------------****************************************----------------------------------*/
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*----------------

   Ball struct

 ----------------*/
struct Ball {

	float x = 0.0f,
		y = 0.0f,
		velocityX = 250.0f, // x-axis, Change in location in a direction 
		velocityY = 250.0f, // y-axis, Change in location in a direction 
		radius = 4.0f;

	Color color = WHITE;

	void draw()
	{
		DrawCircle((int)x, (int)y, radius, color);
	}
};

/*-------------------

   Paddle struct

 -------------------*/
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

/*-------------------

	Brick struct

 -------------------*/
struct Brick {

	float x = 0.0f,
		y = 0.0f,
		width = 46.0f,
		height = 22.0f;

	Color color = WHITE;

	bool isAlive = true;

	Rectangle rect_collision() // utilized to check ball collision
	{
		return Rectangle{ x , y , width + 8, height + 8 };
	}

	Rectangle rect() // utilized to construct rectangle with rounded edges
	{
		return Rectangle{ x , y , width, height };
	}

	void draw()
	{
		DrawRectangleRounded(rect(), 0.2f, 4, color);// Draw rectangle with rounded edges
		DrawRectangleRoundedLines(rect(), 0.2f, 4, DARKGRAY); // Draw rectangle with rounded edges outline
	}
};

/*-------------------

	Aiming line

 -------------------*/
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
