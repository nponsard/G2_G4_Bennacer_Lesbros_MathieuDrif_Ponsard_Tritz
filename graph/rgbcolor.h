#ifndef RGBCOLOR_H
#define RGBCOLOR_H

#include "freeglut.h" //GLubyte
#include "../tools/IEditable.h"

class RGBcolor : public nsUtil::IEditable
{
public:
    GLubyte Red;
    GLubyte Green;
    GLubyte Blue;

    RGBcolor (const GLubyte & R = 0, const GLubyte & G = 0, const GLubyte & B = 0) : Red (R), Green (G), Blue (B) {}

    bool operator == (const RGBcolor & col) {return col.Red == Red && col.Green == Green && col.Blue == Blue;}
protected :
   virtual std::ostream & _Edit (std::ostream & os = std::cout) const;
};

//https://www.rapidtables.com/web/color/RGB_Color.html
const RGBcolor KBlack     {  0,   0,   0};
const RGBcolor KWhite     {255, 255, 255};
const RGBcolor KRed       {255,   0,   0};
const RGBcolor KLime      {0  , 255,   0};
const RGBcolor KBlue      {0  ,   0, 255};
const RGBcolor KYellow    {255, 255,   0};
const RGBcolor KCyan      {0  , 255, 255};
const RGBcolor KMagenta   {255,   0, 255};
const RGBcolor KSilver 	  {192, 192, 192};
const RGBcolor KGray      {128, 128, 128};
const RGBcolor KMaroon    {128,   0,   0};
const RGBcolor KOlive     {128, 128,   0};
const RGBcolor KGreen     {0  , 128,   0};
const RGBcolor KPurple    {128,   0, 128};
const RGBcolor KTeal      {0  , 128, 128};
const RGBcolor KNavy      {0  ,   0, 128};

#endif // RGBCOLOR_H
