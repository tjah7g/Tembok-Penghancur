
#include "Level.h"

void centerWindow(float windowWidth, float windowHeight);

int main()
{
    
    const int windowWidth = WIN_WD;
    const int windowHeight = WIN_HT;

    SetConfigFlags(FLAG_VSYNC_HINT); 
    InitWindow(windowWidth, windowHeight, "My Bricks Breaker");
    centerWindow(windowWidth, windowHeight);
    //InitAudioDevice();

    vector<int> brickType;
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 14; j++)
        {
            brickType.push_back(i);
        }
    }

    Level level(brickType);
    level.render();
    //CloseAudioDevice();
    CloseWindow(); 

    return 0;
}

void centerWindow(float windowWidth, float windowWeight)
{
    int monitor = GetCurrentMonitor();
    int monitorWidth = GetMonitorWidth(monitor); 
    int monitorHeight = GetMonitorHeight(monitor); 
    SetWindowPosition((int)(monitorWidth / 2) - (int)(windowWidth / 2), (int)(monitorHeight / 2) - (int)(windowWeight / 2));
}
