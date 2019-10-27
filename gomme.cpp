#include "gomme.h"

gommes::gommes(){
}

gommes::gommes(int x, int y){
    posX = x;
    posY = y;
}

int gommes::getPosX() const
{
    return posX;
}

int gommes::getPosY() const
{
    return posY;
}

void gommes::setPosX(int x)
{
    posX = x;
}

void gommes::setPosY(int y)
{
    posY = y;
}
