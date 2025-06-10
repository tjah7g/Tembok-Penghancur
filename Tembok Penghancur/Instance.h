
#ifndef INSTANCE_HPP
#define INSTANCE_HPP
#ifdef _MSC_VER
#pragma once
#endif  

#include "header.h"

class Instance
{
    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();
    
    bool game_is_paused = false;

    bool new_ball = true;
    unsigned ball_direction_rand = 0;

public:
    bool instanceIsLivelive = true;
    int collisionResult = 0;
    
    Ball ball;
    Paddle paddle;
    //Sound soundBall = LoadSound("resources/Click_UI.wav");
    bool isSound = true;
    DottedLine aimingLine;

    Instance();
    Ball getBall();
    virtual void render();
    void updateInst();
    void drawDottedLine(int start_pos_x, int start_pos_y, int end_pos_x, int end_pos_y, int num_points);

private:
    virtual void draw();
    void pauseScreen(int pauseKey);
    void paddleCollisionSideScreen();
    int ballCollisions();
    void keyStrocks();
    void launchBall();

};
#endif
