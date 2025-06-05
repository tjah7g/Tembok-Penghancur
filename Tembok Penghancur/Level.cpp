
#include "Level.h"

Level::Level()
{
	
}

Level::Level(vector<int>& brickType)
{
	
	this->brickType = brickType;
	buildBricks();

}

void Level::render()
{
	while (true)
	{
		Instance::updateInst();
		update();
		draw();
		
		if (Instance::collisionResult == BALL_MISS_PADDLE)
		{
			int textWidth = MeasureText("You missed the ball\n press Q to exit", 60);
			DrawText("You missed the ball\n press Q to exit", GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 60, YELLOW);
			Instance::instanceIsLivelive = false;

		}
	}
}

void Level::update()
{
	
	for (Brick& brick : bricks)
	{
		if (brick.isAlive)
		{
			
			if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, brick.rect_collision()))
			{
				if (isSound) PlaySound(soundBall);

				if ((ball.x <= brick.x + 8) || 
					(ball.x >= brick.x + brick.width + 11)) 
				{
					ball.velocityX *= -1; 
				}
				else 
				{
					ball.velocityY *= -1; 
				}
				brick.isAlive = false;
				break;
			}
		}
	}
}









void Level::draw()
{

	BeginDrawing();
	

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



	
	EndDrawing();
}




void Level::buildBricks()
{
	
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

	} 

	int brickIndex = 0;
	
	for (int rowY = 50; rowY < 240; rowY += 28) 
	{

		for (int columnX = 42; columnX < 758; columnX += 52) 
		{
			bricks[brickIndex].x = (float)columnX;
			bricks[brickIndex].y = (float)rowY;
			brickIndex++;
		}
	}

} 


