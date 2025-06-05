
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
 /*--------------------------------****************************************----------------------------------
  |                                *                                      *                                 |
  |   My Bricks Breaker            *      Instance Class Definitions      *                                 |
  |                                *                                      *                                 |
  ---------------------------------****************************************----------------------------------*/
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////


  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /*

      Renders only ball, paddle, and FPS
      Parent class to Level class

  */
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Instance.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------- Class Instance ---------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

// Constructors
//----------------------------------------------------------------------------------


//--------------------------------------------------------------------- Default constructor
/*---------------------------------------------------

    Default construtor

 ----------------------------------------------------*/
Instance::Instance()
{
    SetExitKey(KEY_Q); // Set a custom key to exit program (default is ESC)

}


//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

// Accessors Functions
//----------------------------------------------------------------------------------

/*----------------------------------------------------

    Gets the ball

 -----------------------------------------------------*/
 //--------------------------------------------------------------------- getBall()
Ball Instance::getBall()
{
    return ball;
}


/*----------------------------------------------------

    Renders the level
    Not inherited by child classes

 -----------------------------------------------------*/
void Instance::render()
{
    while (true)
    {
        updateInst();
        draw();
    }
}

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

// Mutators Methods
//---------------------------------------------------------------------------------

//--------------------------------------------------------------------- Method update_inst()

/*----------------------------------------------------

    Updates ball and paddle positions and collisions,
    and key strocks

 -----------------------------------------------------*/
void Instance::updateInst()
{
    //-------------------------------------------------------

    // Ball Position and collisions
    //-------------------------------------------------------

    //-- Ball new location 
    //-------------------------------------------------------
    if (!new_ball) // not a new ball
    {
        ball.x += ball.velocityX * GetFrameTime(); // ball new location at x
        ball.y -= ball.velocityY * GetFrameTime(); // ball new location at x
    }
    else // Launch new ball
    {
        launchBall();
    }

    //-- Collisions
    //-------------------------------------------------------
    // Paddle
    // Checks if paddle has collide with the screen sides
    paddleCollisionSideScreen();
    // Ball
    // Checks if the ball has collided with paddle
    collisionResult = ballCollisions();

    // Keystrocks, Paddle position, window state, pause game
    keyStrocks();

} // update_inst()

//--------------------------------------------------------------------- Method drawDottedLine()
/*---------------------------------------------------

    Draws a dotted line

 ----------------------------------------------------*/
void Instance::drawDottedLine(int startPoX, int startPosY, int endPosX, int endPosY, int numPoints)
{
    //-----------------------------------------------------

    // Variable
    //-----------------------------------------------------
    // Lenght of the line relative to the x and y axis
    double changeX = (endPosX - startPoX);
    double changeY = (endPosY - startPosY);
    // Points position
    int pointX = startPoX;
    int pointY = startPosY;

    //-----------------------------------------------------

    // Method operations
    //-----------------------------------------------------
    // Draw the line using points
    for (int i = 0; i < numPoints + 1; i++)
    {
        DrawPixel(pointX, pointY, WHITE);
        pointX += (int)(changeX / numPoints);
        pointY += (int)(changeY / numPoints);
    }
}

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

// Classe Operation Methods (private)
//---------------------------------------------------------------------------------


//--------------------------------------------------------------------- Method draw()
/*---------------------------------------------------

    Display Ball, paddle, and FPS (private)
    Not inherited by child classes

 ----------------------------------------------------*/
void Instance::draw()
{
    BeginDrawing();
    // -----------------------------------

    ClearBackground(BLACK);

    ball.draw();
    paddle.draw();

    if (aimingLine.isAlive) drawDottedLine(aimingLine.startX, aimingLine.startY,
        aimingLine.endX, aimingLine.endY,
        aimingLine.numDots);

    DrawFPS(10, 10);

    // Player missed the ball
    if (collisionResult == BALL_MISS_PADDLE)
    {
        int textWidth = MeasureText("You missed the ball\n press Q to exit", 60);
        DrawText("You missed the ball\n press Q to exit", GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 60, YELLOW);
        instanceIsLivelive = false;

    }

    // -----------------------------------
    EndDrawing();
}

//--------------------------------------------------------------------- Method pauseScreen()
/*----------------------------------------------------

    Pauses the screen, the game (private)
    Utilized by keysStrocks()

 -----------------------------------------------------*/
void Instance::pauseScreen(int pauseKey)
{
    //---------------------------------

    // Method operations
    //---------------------------------
    if (IsKeyPressed(pauseKey))
    {
        //-----------------------------

        // Variables
        //-----------------------------
        const char* text = "The game is paused";
        int textWidth = MeasureText(text, 60);

        // Initializes the pressed key
        BeginDrawing();
        EndDrawing();

        // True until the pause is pressed again
        while (true)
        {
            // Pause message
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText(text, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 60, YELLOW);
            EndDrawing();

            // Exits Programm
            if (WindowShouldClose())
            {
                CloseWindow();
                exit(0);
            }

            else if (IsKeyPressed(pauseKey)) break; // exits while loop and Method   
        }
    }
}

//--------------------------------------------------------------------- Method paddleCollisionSideScree()
/*------------------------------------------------------

    Checks if paddle has collide with the screen sides
    and readjust paddle position (private)
    Utilized by update_inst()

 -------------------------------------------------------*/
void Instance::paddleCollisionSideScreen()
{
    if (paddle.x + paddle.width > GetScreenWidth()) // screen right side
    {
        paddle.x = GetScreenWidth() - paddle.width; // Repositions paddle inside screen
    }
    else if (paddle.x < 0) // screen left side
    {
        paddle.x = 1.0f; // Repositions paddle inside screen
    }
}

//--------------------------------------------------------------------- Method ballCollision()
/*------------------------------------------------------

    Checks ball collisions (private)
    Utilized by updateInst()

 -------------------------------------------------------*/
int Instance::ballCollisions()
{

    int result = BALL_COLLIDED;

    if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, paddle.rect()))
    {
        if (isSound) PlaySound(soundBall);

        // The ball has collided with the paddle, 
        // checks if the ball has collided with the sides of the paddle

        if ((ball.x <= paddle.x) || // Brick left side
            (ball.x >= paddle.x + paddle.width)) // Brick right side
        {
            ball.velocityX *= -1; // Changes ball x-axis velocity direction
        }
        else if (ball.y >= paddle.y + paddle.height)
        {
            ball.velocityY *= -1; // Changes ball y-axis velocity direction
        }
        else if (ball.velocityY < 0) // top of the paddle
        {
            ball.velocityY *= -1; // Changes ball y-axis velocity direction
        }
    }
    // Ball collide with the right side of the screen
    else if (ball.x > GetScreenWidth())
    {
        if (isSound) PlaySound(soundBall);

        ball.x = (float)GetScreenWidth();
        ball.velocityX *= -1; // Changes ball x-axis velocity direction
    }
    // Ball collide with the left side of the screen
    else if (ball.x < 0)
    {
        if (isSound) PlaySound(soundBall);

        ball.x = 0;
        ball.velocityX *= -1; // Changes ball x-axis velocity direction
    }
    // Ball collide with the top of the screen
    else if (ball.y < 0)
    {
        if (isSound) PlaySound(soundBall);

        ball.y = 0;
        ball.velocityY *= -1; // Changes ball y-axis velocity direction
    }
    // Paddle missed the ball
    else if (ball.y > GetScreenHeight())
    {
        result = BALL_MISS_PADDLE;
    }

    return result;

} // ball_collision()

//--------------------------------------------------------------------- Method keyStrocks()
/*------------------------------------------------------

    Checks pressed keys (private)
    window state, closed, escape key pressed
    and adjust paddle position
    Utilized by updateInst()

 -------------------------------------------------------*/
void Instance::keyStrocks()
{

    //--  paddle position
    //------------------------------------------------------- 
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

    //-- Window state, closed, escape key pressed
    //------------------------------------------------------- 
    else if (WindowShouldClose())
    {
        exit(0);
    }
    else if (IsKeyPressed(KEY_ESCAPE)) // Pause game if escape key pressed
    {
        pauseScreen(KEY_ESCAPE);
    }

} // keystrocks()

//--------------------------------------------------------------------- Method launchBall()
/*------------------------------------------------------

    Aiming and Launching the ball

 -------------------------------------------------------*/
void Instance::launchBall()
{
    aimingLine.isAlive = true;

    ball.x = paddle.x + (paddle.width / 2); // ball at midle width of the paddle
    ball.y = paddle.y - paddle.height - 1; // ball at midle height - 30 of the paddle 

    // Aiming keystrocks
    if (IsKeyPressed(KEY_Z) && aimingLine.slope >= -100) // move left
    {
        aimingLine.slope -= 25;
    }
    else if ((IsKeyPressed(KEY_X)) && aimingLine.slope <= 100) // move right
    {
        aimingLine.slope += 25;
    }

    // Init. aiming line
    aimingLine.startX = (int)ball.x;
    aimingLine.startY = (int)ball.y - 4;
    aimingLine.endX = (int)ball.x + aimingLine.slope;
    // end_y is calculated using the pythagorean theorem ((int)ball.y - 4) - (a^2 = c^2 - b^2)
    aimingLine.endY = ((int)ball.y - 4) - (int)sqrt(150 * 150 - (aimingLine.endX - aimingLine.startX) * (aimingLine.endX - aimingLine.startX));

    // Launch the ball
    if (IsKeyPressed(KEY_SPACE))
    {
        new_ball = false;
        aimingLine.isAlive = false;
        aimingLine.slope = 0;
        // Changing ball direction in x-axis
        if (aimingLine.endX < ball.x) ball.velocityX *= -1;
        // Init. ball position
        ball.x = (float)aimingLine.endX;
        ball.y = (float)aimingLine.endY;
    }

}


