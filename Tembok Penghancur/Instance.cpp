
#include "Instance.h"

Instance::Instance()
{
    SetExitKey(KEY_Q); 

}

Ball Instance::getBall()
{
    return ball;
}

void Instance::render()
{
    while (true)
    {
        updateInst();
        draw();
    }
}

void Instance::updateInst()
{
    
    if (!new_ball) 
    {
        ball.x += ball.velocityX * GetFrameTime(); 
        ball.y -= ball.velocityY * GetFrameTime(); 
    }
    else 
    {
        launchBall();
    }

    paddleCollisionSideScreen();
    collisionResult = ballCollisions();
    keyStrocks();

} 



void Instance::drawDottedLine(int startPoX, int startPosY, int endPosX, int endPosY, int numPoints)
{
    
    double changeX = (endPosX - startPoX);
    double changeY = (endPosY - startPosY);
    
    int pointX = startPoX;
    int pointY = startPosY;

    for (int i = 0; i < numPoints + 1; i++)
    {
        DrawPixel(pointX, pointY, WHITE);
        pointX += (int)(changeX / numPoints);
        pointY += (int)(changeY / numPoints);
    }
}

void Instance::draw()
{
    BeginDrawing();
    ClearBackground(BLACK);

    ball.draw();
    paddle.draw();
    if (aimingLine.isAlive) drawDottedLine(aimingLine.startX, aimingLine.startY,
        aimingLine.endX, aimingLine.endY,
        aimingLine.numDots);

    DrawFPS(10, 10);

    if (collisionResult == BALL_MISS_PADDLE)
    {
        int textWidth = MeasureText("You missed the ball\n press Q to exit", 60);
        DrawText("You missed the ball\n press Q to exit", GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 60, YELLOW);
        instanceIsLivelive = false;

    }

    EndDrawing();
}

void Instance::pauseScreen(int pauseKey)
{
    
    if (IsKeyPressed(pauseKey))
    {
        
        const char* text = "The game is paused";
        int textWidth = MeasureText(text, 60);

        BeginDrawing();
        EndDrawing();

        while (true)
        {
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText(text, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 60, YELLOW);
            EndDrawing();

            if (WindowShouldClose())
            {
                CloseWindow();
                exit(0);
            }

            else if (IsKeyPressed(pauseKey)) break; 
        }
    }
}

void Instance::paddleCollisionSideScreen()
{
    if (paddle.x + paddle.width > GetScreenWidth()) 
    {
        paddle.x = GetScreenWidth() - paddle.width; 
    }
    else if (paddle.x < 0) 
    {
        paddle.x = 1.0f; 
    }
}

int Instance::ballCollisions()
{
    int result = BALL_COLLIDED;

    if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, paddle.rect()))
    {
        //if (isSound) PlaySound(soundBall);

        if ((ball.x <= paddle.x) || 
            (ball.x >= paddle.x + paddle.width)) 
        {
            ball.velocityX *= -1; 
        }
        else if (ball.y >= paddle.y + paddle.height)
        {
            ball.velocityY *= -1; 
        }
        else if (ball.velocityY < 0) 
        {
            ball.velocityY *= -1; 
        }
    }
    
    else if (ball.x > GetScreenWidth())
    {
        //if (isSound) PlaySound(soundBall);

        ball.x = (float)GetScreenWidth();
        ball.velocityX *= -1; 
    }
    
    else if (ball.x < 0)
    {
        //if (isSound) PlaySound(soundBall);

        ball.x = 0;
        ball.velocityX *= -1; 
    }
    
    else if (ball.y < 0)
    {
        //if (isSound) PlaySound(soundBall);

        ball.y = 0;
        ball.velocityY *= -1; 
    }
    
    else if (ball.y > GetScreenHeight())
    {
        result = BALL_MISS_PADDLE;
    }

    return result;

} 

void Instance::keyStrocks()
{
    if (IsKeyDown(KEY_A))
    {
        paddle.x -= paddle.speed * GetFrameTime();
    }
    else if (IsKeyDown(KEY_D))
    {
        paddle.x += paddle.speed * GetFrameTime();
    }

    else if (IsKeyDown(KEY_LEFT))
    {
        paddle.x -= paddle.speed * GetFrameTime();
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        paddle.x += paddle.speed * GetFrameTime();
    }

    else if (WindowShouldClose())
    {
        exit(0);
    }
    else if (IsKeyPressed(KEY_ESCAPE)) 
    {
        pauseScreen(KEY_ESCAPE);
    }

} 

void Instance::launchBall()
{
    aimingLine.isAlive = true;
    ball.x = paddle.x + (paddle.width / 2); 
    ball.y = paddle.y - paddle.height - 1; 

    if (IsKeyPressed(KEY_Z) && aimingLine.slope >= -100) 
    {
        aimingLine.slope -= 25;
    }
    else if ((IsKeyPressed(KEY_X)) && aimingLine.slope <= 100) 
    {
        aimingLine.slope += 25;
    }

    aimingLine.startX = (int)ball.x;
    aimingLine.startY = (int)ball.y - 4;
    aimingLine.endX = (int)ball.x + aimingLine.slope;
    aimingLine.endY = ((int)ball.y - 4) - (int)sqrt(150 * 150 - (aimingLine.endX - aimingLine.startX) * (aimingLine.endX - aimingLine.startX));

    if (IsKeyPressed(KEY_SPACE))
    {
        new_ball = false;
        aimingLine.isAlive = false;
        aimingLine.slope = 0;
        
        if (aimingLine.endX < ball.x) ball.velocityX *= -1;
        
        ball.x = (float)aimingLine.endX;
        ball.y = (float)aimingLine.endY;
    }

}
