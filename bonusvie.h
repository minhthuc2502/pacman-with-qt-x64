#ifndef BONUSVIE_H_INCLUDED
#define BONUSVIE_H_INCLUDED

class bonusVie
{
    protected:
        int posX, posY=0;
    public:
        bonusVie();
        bonusVie(int, int);
        int getPosX() const;
        int getPosY() const;
        void setPosX(int );
        void setPosY(int );
};


#endif // BONUSVIE_H_INCLUDED
