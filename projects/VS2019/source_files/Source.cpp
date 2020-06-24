#include "raylib.h"
#include <iostream>
using namespace std;

int GuiStart();                         //Initializes the window
int  DrawSliderGradient();              //Draws the rainbow strip
int DrawSlider();                       //Draws the sliding circle
int DrawBoxGradient();                  //Draws the square gradient box
int DrawViewBox();
Color SliderColorAt(int pos);           //Returns the color at posY of slider
Color BoxColorAt(int posX, int posY);   //Returns pixel color for the gradient box at x,y

static const int screenHeight = 306;
static const int screenWidth = 500;
int sliderPosX = 306;
int sliderY = screenHeight / 2;
int selectorX = screenHeight / 2;
int selectorY = screenHeight / 2;
int sliderGradientWidth = 25;
float sliderRadius=8; //Radius of the sliding circle
int mouseX;
int mouseY;
Color sliderAt;
Color boxAt;

int DrawViewBox()
{
    DrawRectangle(306 + sliderGradientWidth, 0, screenWidth - (306 + sliderGradientWidth), 50, BoxColorAt(selectorX, selectorY));
    DrawText("Alpha V0.1", 311 + sliderGradientWidth, 55, 20, SliderColorAt(sliderY));
    return 0;
}

int Map(int x, int inMin, int inMax, int outMin, int outMax)
{
        return (x - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}

Color SliderColorAt(int posY) //Returns RGB Value for the strip at that position
{
    Color printColor = { 0,0,0,0 };
    int interval = posY / 51;
    posY = posY - interval * 51;
    switch (interval)
    {
    case 0: printColor = { 255 , (unsigned char)(posY * 5), 0 ,255 };          //from {255,0,0} -> {255,255,0}
          break;
    case 1: printColor = { (unsigned char)(255 - (posY * 5)), 255, 0, 255 };   //from {255,255,0} -> {0,255,0}
          break;
    case 2: printColor = { 0, 255, (unsigned char)(posY * 5), 255 };           //from {0,255,0} -> {0,255,255}
          break;
    case 3: printColor = { 0, (unsigned char)(255 - (posY * 5)), 255, 255 };   //from {0,255,255} -> {0,0,255}
          break;
    case 4: printColor = { (unsigned char)(posY * 5), 0, 255, 255 };           //from {0,0,255} -> {255,0,255}
          break;
    case 5: printColor = { 255, 0, (unsigned char)(255 - (posY * 5)), 255 };   //from {255,0,255} -> {255,0,0}
          break;
    }
    return printColor;
}

int DrawSliderGradient()
{
    for (int i = 0; i < 306; i++) //Lenth of the strip: 306px
    {
        Color printColor = SliderColorAt(i);
        for (int j = 0; j < sliderGradientWidth; j++) //Width of the strip: 25px
        {
            DrawPixel(j+sliderPosX, i, printColor);
        }
    }
    return 0;
}

int DrawSlider()
{
    int cell = 0; //Fuck knows what this var does but we need it.

    if (IsMouseButtonDown(cell))
    {
        mouseX = GetMouseX();
        mouseY = GetMouseY();
    }
    //Bounds checking
    if (mouseX > sliderPosX && mouseX < sliderPosX + sliderGradientWidth && mouseY > 0 && mouseY < 306)
    {
        sliderY = mouseY;
    }

    DrawCircle(306 + sliderGradientWidth / 2, sliderY, sliderRadius, SliderColorAt(sliderY));
    DrawCircleLines(306 + sliderGradientWidth / 2, sliderY, sliderRadius, WHITE);
    return 0;
}

Color BoxColorAt(int posX, int posY)
{
    //Mapping for the White -> Color gradient
    boxAt.r = Map(posX, 0, 306, 255, SliderColorAt(sliderY).r);
    boxAt.g = Map(posX, 0, 306, 255, SliderColorAt(sliderY).g);
    boxAt.b = Map(posX, 0, 306, 255, SliderColorAt(sliderY).b);
    
    //Mapping for the Color -> Black gradient
    boxAt.r = Map(posY, 0, 306, boxAt.r, 0);
    boxAt.g = Map(posY, 0, 306, boxAt.g, 0);
    boxAt.b = Map(posY, 0, 306, boxAt.b, 0);
    boxAt.a = 255;
    return boxAt;
}

int DrawBoxSelector()
{
    int cell = 0; //Fuck knows what this var does but we need it.

    if (IsMouseButtonDown(cell))
    {
        mouseX = GetMouseX();
        mouseY = GetMouseY();
    }
    //Bounds checking
    if (mouseX > 0 && mouseX < 306  && mouseY > 0 && mouseY < 306)
    {
        selectorX = mouseX;
        selectorY = mouseY;
    }

    DrawCircle(selectorX, selectorY, sliderRadius, BoxColorAt(selectorX, selectorY));
    DrawCircleLines(selectorX, selectorY, sliderRadius, WHITE);
    return 0;
}

int DrawBoxGradient()
{
    for (int i = 0; i < 306; i++)
    {
        for (int j = 0; j < 306; j++)
        {
            DrawPixel(j, i, BoxColorAt(j, i));
        }
    }
    return 0;
}

int GuiStart()
{
    InitWindow(screenWidth, screenHeight, "Color Picker");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DARKGRAY);
        DrawSliderGradient();
        DrawSlider();
        DrawBoxGradient();
        DrawBoxSelector();
        DrawViewBox();
        EndDrawing();
    }
    return 0;
}

int main()
{
    GuiStart();
    return 0;
}