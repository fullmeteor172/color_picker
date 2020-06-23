#include "raylib.h"
#include <iostream>
using namespace std;

int GuiStart();  //Initializes the window
int  DrawSliderGradient(); //Draws the rainbow strip
int DrawSlider(); //Draws the sliding circle
int DrawBoxGradient(); //Draws the square gradient box


static const int screenHeight = 306; //10px padding on both
static const int screenWidth = 500;
int sliderY = screenHeight / 2;
int sliderGradientWidth = 25;
float sliderRadius=8; //Radius of the sliding circle

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

int DrawSliderGradient()
{
    for (int i = 0; i < 306; i++) //Lenth of the strip: 306px
    {
        Color printColor = ColorAt(i);
        for (int j = 0; j < sliderGradientWidth; j++) //Width of the strip: 25px
        {
            DrawPixel(j+306, i, printColor);
        }
    }
    return 0;
}

int DrawSlider()
{
    DrawCircle(306 + sliderGradientWidth / 2, sliderY, sliderRadius, ColorAt(sliderY));
    DrawCircleLines(306 + sliderGradientWidth / 2, sliderY, sliderRadius, WHITE);
    return 0;
}

int DrawBoxGradient()
{
    Color transparent = { 0,0,0,0 };
    DrawRectangleGradientH(0,0,306,306, WHITE, sliderAt);
    DrawRectangleGradientV(0, 0, 306, 306, transparent, BLACK);
    return 0;
}

int GuiStart()
{
    InitWindow(screenWidth, screenHeight, "Color Picker");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        DrawSliderGradient();
        DrawSlider();
        DrawBoxGradient();
        EndDrawing();
    }
    return 0;
}


int main()
{
    GuiStart();
    return 0;
}