#include "raylib.h"
#include <iostream>
using namespace std;

int GuiStart();  //Initializes the window
int DrawGradient();


static const int SCALE_SCREEN = 1;
static const int SCREEN_HEIGHT=500*SCALE_SCREEN;
static const int SCREEN_WIDTH = 750*SCALE_SCREEN;

Color sliderat = { 89,0,255,255 };
Color transparent = { 0,0,0,0 };

int DrawGradient(Color sliderColor)
{
    DrawRectangleGradientH(0,0,255,255, WHITE, sliderColor);
    DrawRectangleGradientV(0, 0, 255, 255, transparent, BLACK);
    return 0;
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

        DrawGradient(sliderat);
        EndDrawing();
    }
    return 0;
}

int main()
{
    GuiStart();
    return 0;
}