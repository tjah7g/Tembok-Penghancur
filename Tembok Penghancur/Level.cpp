#include "GameStateManager.h"
#include "BrickFactory.h"
#include "ScoreObserver.h"
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
	GameStateManager::getInstance()->reset();
	while (instanceIsLivelive)
	{
		Instance::updateInst();
		update();

		BeginDrawing();
		ClearBackground(BLACK);

		draw();

		// Tampilkan score di kanan bawah
		int fontSize = 24;
		const char* scoreText = TextFormat("Score: %d", ScoreManager::getInstance()->getScore());
		int textWidth = MeasureText(scoreText, fontSize);
		int textHeight = fontSize;
		int posX = GetScreenWidth() - textWidth - 20;
		int posY = GetScreenHeight() - textHeight - 20;
		DrawText(scoreText, posX, posY, fontSize, YELLOW);
		// Tampilkan FPS
		DrawFPS(10, 775);
		if (bricks.empty())
		{
			GameStateManager::getInstance()->setWin(true);
			GameStateManager::getInstance()->setFinalScore(ScoreManager::getInstance()->getScore());
			instanceIsLivelive = false;
		}

		// Jika kalah
		if (Instance::collisionResult == BALL_MISS_PADDLE)
		{
			GameStateManager::getInstance()->setLose(true);
			GameStateManager::getInstance()->setFinalScore(ScoreManager::getInstance()->getScore());
			instanceIsLivelive = false;
		}


		EndDrawing();
	}

	// Game Over Screen
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		if (GameStateManager::getInstance()->getWin())
		{
			int textWidth = MeasureText("You Win!\nPress Q to exit", 60);
			DrawText("You Win!\nPress Q to exit", GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 60, YELLOW);

			DrawText(TextFormat("Final Score: %d", GameStateManager::getInstance()->getFinalScore()), GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 + 80, 40, YELLOW);
		}
		else if (GameStateManager::getInstance()->getLose())
		{
			int textWidth = MeasureText("You missed the ball\nPress Q to exit", 60);
			DrawText("You missed the ball\nPress Q to exit", GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 60, YELLOW);

			DrawText(TextFormat("Final Score: %d", GameStateManager::getInstance()->getFinalScore()), GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 + 80, 40, YELLOW);
		}

		if (IsKeyPressed(KEY_Q))
		{
			break;
		}

		EndDrawing();
	}
}


void Level::update()
{
	bool brickDestroyed = false;

	for (Brick& brick : bricks)
	{
		if (brick.isAlive &&
			CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, brick.rect_collision()))
		{
			//AudioManager::getInstance()->playSound(soundBall);

			if ((ball.x <= brick.x + 8) || (ball.x >= brick.x + brick.width + 11))
				ball.velocityX *= -1;
			else
				ball.velocityY *= -1;

			brick.isAlive = false;
			scoreObserver.onNotify();
			brickDestroyed = true;
			break;
		}
	}

	// Setelah loop
	if (brickDestroyed)
	{
		bricks.erase(std::remove_if(bricks.begin(), bricks.end(), [](const Brick& b) { return !b.isAlive; }), bricks.end());
	}


}









void Level::draw()
{
	Instance::ball.draw();
	Instance::paddle.draw();

	if (aimingLine.isAlive)
		Instance::drawDottedLine(aimingLine.startX, aimingLine.startY, aimingLine.endX, aimingLine.endY, aimingLine.numDots);

	for (Brick& brick : bricks)
	{
		if (brick.isAlive) brick.draw();
	}

	// Jangan gambar score di sini lagi ? sudah di Level::render()
	// (supaya tidak double tampil)
}




void Level::buildBricks()
{
	bricks.clear(); // Hapus dulu

	int brickIndex = 0;

	for (int rowY = 50; rowY < 240 && brickIndex < brickType.size(); rowY += 28)
	{
		for (int columnX = 42; columnX < 758 && brickIndex < brickType.size(); columnX += 52)
		{
			int type = brickType[brickIndex % brickType.size()];
			Brick brick = BrickFactory::createBrick(type, (float)columnX, (float)rowY);
			bricks.push_back(brick);
			brickIndex++;
		}
	}
}



