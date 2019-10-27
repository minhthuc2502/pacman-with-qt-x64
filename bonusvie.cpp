#include "bonusvie.h"

bonusVie::bonusVie(){
}

bonusVie::bonusVie(int x, int y){
    posX = x;
    posY = y;
}

int bonusVie::getPosX() const
{
    return posX;
}

int bonusVie::getPosY() const
{
    return posY;
}

void bonusVie::setPosX(int x)
{
    posX = x;
}

void bonusVie::setPosY(int y)
{
    posY = y;
}
