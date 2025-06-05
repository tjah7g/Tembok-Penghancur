#ifndef BUTTON_P_HPP
#define BUTTON_P_HPP
#ifdef _MSC_VER
#pragma once
#endif  
#include "raylib.h"
#include <iostream>	
#include <string>
#include <vector>

using namespace std;

class ButtonP
{
public:

    Font font = GetFontDefault(); 
    float fontSize = 32,
    fontSpacing = 2.0f;
    Color fontColor = RAYWHITE;
    bool isRayFont = true;
    bool is_font = false;
    string text = "Button";
    Vector2 textSize = MeasureTextEx(font, text.c_str(), fontSize, fontSpacing),
    oneCharSize = MeasureTextEx(font, "C", fontSize, fontSpacing);
    bool resizeBtn = true;
    float btnWidth = (textSize.x + 3.5f * oneCharSize.x),
    btnHeight = textSize.y * (float)(2.0f * (textSize.y / fontSize));
    Vector2 btnPos = { 750, 100 };
    Rectangle rect{ btnPos.x, btnPos.y, btnWidth, btnHeight },
        originalRect = rect;
    
    Vector2 textPos =
    {
        rect.x + (rect.width - textSize.x) / 2,
        rect.y + (rect.height - textSize.y) / 2
    };
    
    Rectangle rectText{ textPos.x, textPos.y, textSize.x, textSize.y },
        originalRectText = rectText;

    Color btnHoverColor = GRAY,
        btnPressedColor = DARKGRAY;
    
    string imgPath; 
    Image img;
    
    Texture2D btnIdle = LoadTextureFromImage(img);  
    Texture2D btnHover = btnIdle;
    Texture2D btnPressed = btnIdle;
    Texture2D* btnLive = &btnIdle;
    
    Image textImg;
    Texture2D textIdle = LoadTextureFromImage(textImg);
    Texture2D textHover = textIdle;
    Texture2D textPressed = textIdle;
    Texture2D* textLive = &textIdle;

    int windowWidth = GetScreenWidth();
    int windowHeight = GetScreenHeight();
    Vector2 windowScale = { (float)GetScreenWidth() / windowWidth, (float)GetScreenHeight() / windowHeight };
    ButtonP();
    ButtonP(string text, float x, float y, string imgPath);
    ButtonP(string text, float x, float y, string imgPath, float fontSize);
    ButtonP(string text, float x, float y, string imgPath, float fontSize, Color fontColor);
    ButtonP(string text, float x, float y, string imgPath, Font& font);
    ~ButtonP();
    void draw();
    int update();
    void setFontSize(float fontSize);
    void setFontSizeNoResize(float fontSize);
    void setText(string text);
    void setTextNoResize(string text);
    void setTextPosition(float x, float y);
    void setHoverColor(Color btnHoverColor);
    void setPressedColor(Color btnPressedColor);

private:
    void buildBtn();

};
#endif