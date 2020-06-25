#include "raylib.h"
#include <iostream>
using namespace std;

int GuiStart();                         //Initializes the window
int  DrawSliderGradient();              //Draws the rainbow strip
int DrawSlider();                       //Draws the sliding circle
int DrawBoxGradient();                  //Draws the square gradient box
int DrawViewBox();                      //Draws the color box
int DrawText();                         //Draws the R,G,B text
Color SliderColorAt(int pos);           //Returns the color at posY of slider
Color BoxColorAt(int posX, int posY);   //Returns pixel color for the gradient box at x,y

static const int screenHeight = 346;
static const int screenWidth = 560;
int sliderPosX = 346;
int sliderY = screenHeight / 2;
int selectorX = screenHeight / 2;
int selectorY = screenHeight / 2;
int sliderGradientWidth = 25;
float sliderRadius = 8; //Radius of the sliding circle
int mouseX;
int mouseY;
Color sliderAt;
Color boxAt;
Color bgGrey = { 54,54,54,255 };

int DrawText()
{
    int r = (int)BoxColorAt(selectorX - 20, selectorY - 20).r;
    int g = (int)BoxColorAt(selectorX - 20, selectorY - 20).g;
    int b = (int)BoxColorAt(selectorX - 20, selectorY - 20).b;

    DrawText(TextFormat("R: %i\nG: %i\nB: %i",r,g,b), 346 + sliderGradientWidth + 20, 90, 20, LIGHTGRAY);
    return 0;
}

int DrawViewBox()
{
    DrawRectangle(346 + sliderGradientWidth+20, 20, screenWidth -(346 + sliderGradientWidth + 20 )-20, 50, BoxColorAt(selectorX-20, selectorY-20));
    DrawRectangleLines(344 + sliderGradientWidth + 20, 18, screenWidth - (346 + sliderGradientWidth + 20) - 16, 54, DARKGRAY);
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
            DrawPixel(j + sliderPosX, i+20, printColor);
        }
    }
    DrawRectangleLines(344, 18, 29, 310, DARKGRAY);
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
    if (mouseX > sliderPosX && mouseX < sliderPosX + sliderGradientWidth && mouseY > 20 && mouseY < 326)
    {
        sliderY = mouseY;
    }

    DrawCircle(346 + sliderGradientWidth / 2, sliderY, sliderRadius, SliderColorAt(sliderY-20));
    DrawCircleLines(346 + sliderGradientWidth / 2, sliderY, sliderRadius, WHITE);
    return 0;
}

Color BoxColorAt(int posX, int posY)
{
    //Mapping for the White -> Color gradient
    boxAt.r = Map(posX, 0, 306, 255, SliderColorAt(sliderY-20).r);
    boxAt.g = Map(posX, 0, 306, 255, SliderColorAt(sliderY-20).g);
    boxAt.b = Map(posX, 0, 306, 255, SliderColorAt(sliderY-20).b);

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
    if (mouseX > 20 && mouseX < 326 && mouseY > 20 && mouseY < 326)
    {
        selectorX = mouseX;
        selectorY = mouseY;
    }

    DrawCircle(selectorX, selectorY, sliderRadius, BoxColorAt(selectorX-20, selectorY-20));
    DrawCircleLines(selectorX, selectorY, sliderRadius, WHITE);
    return 0;
}

int DrawBoxGradient()
{
    for (int i = 0; i < 306; i++)
    {
        for (int j = 0; j < 306; j++)
        {
            DrawPixel(j+20, i+20, BoxColorAt(j, i));
        }
    }
    DrawRectangleLines(18, 18, 310, 310, DARKGRAY);
    return 0;
}

int GuiStart()
{
    InitWindow(screenWidth, screenHeight, "Color Picker");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(bgGrey);
        DrawSliderGradient();
        DrawSlider();
        DrawBoxGradient();
        DrawBoxSelector();
        DrawViewBox();
        DrawText();
        EndDrawing();
    }
    return 0;
}

int main()
{
    GuiStart();
    return 0;
}