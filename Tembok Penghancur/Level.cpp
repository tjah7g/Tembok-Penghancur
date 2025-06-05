//////////////////////////////////////////////////////////////////////////////////////////////////////////////
 /*--------------------------------****************************************----------------------------------
  |                                *                                      *                                 |
  |    My Bricks Breaker           *        Level Class Definitions       *                                 |
  |                                *                                      *                                 |
  ---------------------------------****************************************----------------------------------*/
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*

	Renders ball, paddle, FPS, and Bricks
	Child class of the Instance class

*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Level.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//---------------------------------------------- Class Level ----------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

// Constructors
//----------------------------------------------------------------------------------

//--------------------------------------------------------------------- Default constructor
/*---------------------------------------------------

	Default construtor

 ----------------------------------------------------*/
Level::Level()
{
	// empty
}


//--------------------------------------------------------------------- Constructor-1

/*---------------------------------------------------

	Constructor-1
	brick type, sound collision

 ----------------------------------------------------*/
Level::Level(vector<int>& brickType)
{
	// Bricks
	this->brickType = brickType;
	buildBricks();

}

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

// Accessors Methods
//----------------------------------------------------------------------------------

//--------------------------------------------------------------------- Method render()
/*----------------------------------------------------

	Render the Level class

 -----------------------------------------------------*/
void Level::render()
{
	while (true)
	{
		Instance::updateInst();
		update();
		draw();
		// Player missed the ball
		if (Instance::collisionResult == BALL_MISS_PADDLE)
		{
			int textWidth = MeasureText("You missed the ball\n press Q to exit", 60);
			DrawText("You missed the ball\n press Q to exit", GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 60, YELLOW);
			Instance::instanceIsLivelive = false;

		}
	}
}


//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

// Mutators Methods
//---------------------------------------------------------------------------------

//--------------------------------------------------------------------- Method update()

/*----------------------------------------------------

	Updates ball and bricks collision

 -----------------------------------------------------*/
void Level::update()
{
	// Brick iteration
	for (Brick& brick : bricks)
	{
		if (brick.isAlive)
		{
			// The ball has collided with the brick, 
			if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, brick.rect_collision()))
			{
				if (isSound) PlaySound(soundBall);

				if ((ball.x <= brick.x + 8) || // Brick left side
					(ball.x >= brick.x + brick.width + 11)) // Brick right side
				{
					ball.velocityX *= -1; // Changes ball x-axis velocity direction
				}
				else // The ball has collided with the top or bottom of the brick
				{
					ball.velocityY *= -1; // Changes ball y-axis velocity direction
				}
				brick.isAlive = false;
				break;
			}
		}
	}
}

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

// Class Methods Operations (private)
//---------------------------------------------------------------------------------

//--------------------------------------------------------------------- Method draw()
/*---------------------------------------------------

	Displays Ball, paddle, Bricks

 ----------------------------------------------------*/
void Level::draw()
{

	BeginDrawing();
	// -----------------------------------

	ClearBackground(BLACK);

	Instance::ball.draw();
	Instance::paddle.draw();

	if (aimingLine.isAlive)Instance::drawDottedLine(aimingLine.startX, aimingLine.startY,
		aimingLine.endX, aimingLine.endY,
		aimingLine.numDots);

	for (Brick& brick : bricks)
	{
		if (brick.isAlive) brick.draw();
	}

	DrawFPS(10, 775);

	/*if (text)
	{
		int textWidth = MeasureText(text, 60);
		DrawText(text, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 60, YELLOW);
		instance_is_live = false;

	}*/

	// -----------------------------------
	EndDrawing();
}

//--------------------------------------------------------------------- Method build_bricks()

/*----------------------------------------------------

	Build the bricks the game (private)
	Utilized by constructors

 -----------------------------------------------------*/
void Level::buildBricks()
{
	// Creates an object brick and assigns to it a color
	for (int type : brickType)
	{
		Brick brick;

		switch (type)
		{
		case B_LIGHTGRAY:
			brick.color = LIGHTGRAY;
			break;
		case B_GRAY:
			brick.color = GRAY;
			break;
		case B_YELLOW:
			brick.color = YELLOW;
			break;
		case B_ORANGE:
			brick.color = ORANGE;
			break;
		case B_PINK:
			brick.color = PINK;
			break;
		case B_RED:
			brick.color = RED;
			break;
		case B_MAROON:
			brick.color = MAROON;
			break;
		case B_GREEN:
			brick.color = GREEN;
			break;
		case B_LIME:
			brick.color = LIME;
			break;
		case B_DARKGREEN:
			brick.color = DARKGREEN;
			break;
		case B_SKYBLUE:
			brick.color = SKYBLUE;
			break;
		case B_BLUE:
			brick.color = BLUE;
			break;
		case B_DARKBLUE:
			brick.color = DARKBLUE;
			break;
		case B_PURPLE:
			brick.color = PURPLE;
			break;
		case B_VIOLET:
			brick.color = VIOLET;
			break;
		case B_DARKPURPLE:
			brick.color = DARKPURPLE;
			break;
		case B_BEIGE:
			brick.color = BEIGE;
			break;
		case B_BROWN:
			brick.color = BROWN;
			break;
		case B_DARKBROWN:
			brick.color = DARKBROWN;
			break;
		case B_MAGENTA:
			brick.color = MAGENTA;
			break;
		default:
			break;
		}

		bricks.push_back(brick);

	} // for loop color

	int brickIndex = 0;
	// Assigns position to bricks
	for (int rowY = 50; rowY < 240; rowY += 28) // brick rows, y positions
	{

		for (int columnX = 42; columnX < 758; columnX += 52) // brick columns, x positions
		{
			bricks[brickIndex].x = (float)columnX;
			bricks[brickIndex].y = (float)rowY;
			brickIndex++;
		}
	}

} // build_bricks()


