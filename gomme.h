#ifndef GOMME_H_INCLUDED
#define GOMME_H_INCLUDED

class gommes
{
    protected:
        int posX, posY=0;
    public:
        gommes();
        gommes(int, int);
        int getPosX() const;    // recuperer la position x des gommes
        int getPosY() const;    // recuperer la position y des gommes
        void setPosX(int );     //mettre la valeur pour la position x des gommes
        void setPosY(int );     //mettre la valeur pour la position y des gommes

};

#endif // GOMME_H_INCLUDED
