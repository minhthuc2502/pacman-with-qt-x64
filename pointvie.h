#ifndef POINTVIE_H_INCLUDED
#define POINTVIE_H_INCLUDED
#include<list>

class pointvieImg
{
    protected:
        int posX, posY=0;
    public:
        pointvieImg();
        pointvieImg(int, int);
        int getPosX() const;        //recuperer la position x de point de vie affichage
        int getPosY() const;        // recuperer la position y de point de vie affichage
        void setPosX(int );         //mettre la valeur pour la position x de point de vie affichage
        void setPosY(int );         //mettre la valeur pour la position y de point de vie affichage

};


#endif // POINTVIE_H_INCLUDED
