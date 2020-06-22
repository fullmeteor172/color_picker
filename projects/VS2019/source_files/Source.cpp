#include "raylib.h"
#include <iostream>
using namespace std;

int GuiStart();  //Initializes the window
int DrawGradient();


static const int SCALE_SCREEN;
static const int SCREEN_HEIGHT;
static const int SCREEN_WIDTH;

int DrawGradient()
{

}

int GuiStart()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Color Picker");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        //PlaceHolder for the slider

        DrawGradient();
        EndDrawing();
    }

}

int main()
{
    GuiStart();
    return 0;
}