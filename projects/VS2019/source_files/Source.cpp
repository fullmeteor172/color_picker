#include "raylib.h"
#include <iostream>
using namespace std;

int GuiStart();  //Initializes the window
int  DrawSlider();


static const int SCALE_SCREEN = 1;
static const int SCREEN_HEIGHT=500*SCALE_SCREEN;
static const int SCREEN_WIDTH = 750*SCALE_SCREEN;

Color sliderAt = { 255,0,0,255 };

Color ColorAt(int pos) //Returns RGB Value for the strip at that position
{
    Color printColor = { 0,0,0,0 };
    //Step 1: Finding out which interval this belongs to
    int interval = pos / 51;
    pos = pos - interval * 51;
    switch (interval)
    {
    case 0: printColor = { 255 , (unsigned char)(pos * 5), 0 ,255 };          //from {255,0,0} -> {255,255,0}
          break;
    case 1: printColor = { (unsigned char)(255 - (pos * 5)), 255, 0, 255 };   //from {255,255,0} -> {0,255,0}
          break;
    case 2: printColor = { 0, 255, (unsigned char)(pos * 5), 255 };           //from {0,255,0} -> {0,255,255}
          break;
    case 3: printColor = { 0, (unsigned char)(255 - (pos * 5)), 255, 255 };   //from {0,255,255} -> {0,0,255}
          break;
    case 4: printColor = { (unsigned char)(pos * 5), 0, 255, 255 };           //from {0,0,255} -> {255,0,255}
          break;
    case 5: printColor = { 255, 0, (unsigned char)(255 - (pos * 5)), 255 };   //from {255,0,255} -> {255,0,0}
          break;
    }
    return printColor;
}

int DrawSlider()
{
    for (int i = 0; i < 306; i++) //Lenth of the strip: 306px
    {
        Color printColor = ColorAt(i);
        for (int j = 0; j < 20; j++) //Width of the strip: 20px
        {
            DrawPixel(j, i, printColor);
        }
    }
    return 0;
}

/*
int DrawGradient(Color sliderColor)
{
    Color transparent = { 0,0,0,0 };
    DrawRectangleGradientH(0,0,255,255, WHITE, sliderColor);
    DrawRectangleGradientV(0, 0, 255, 255, transparent, BLACK);
    return 0;
}
*/
int GuiStart()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Color Picker");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        DrawSlider();
        EndDrawing();
    }
    return 0;
}


int main()
{
    GuiStart();
    return 0;
}