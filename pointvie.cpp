#include "pointvie.h"

pointvieImg::pointvieImg(){
    posX = 0;
    posY = 0;
}

pointvieImg::pointvieImg(int x, int y){
    posX = x;
    posY = y;
}

int pointvieImg::getPosX() const
{
    return posX;
}

int pointvieImg::getPosY() const
{
    return posY;
}

void pointvieImg::setPosX(int x)
{
    posX = x;
}

void pointvieImg::setPosY(int y)
{
    posY = y;
}
