#ifndef JEU_H
#define JEU_H

#include <list>
#include<cstdlib>
#include "pointvie.h"
#include "gomme.h"
#include "bonusvie.h"
using namespace std;

typedef enum {VIDE, MUR, BONUSVIE} Case;
typedef enum {GAUCHE, DROITE, HAUT, BAS} Direction;

class Jeu;

class Fantome
{
    friend class Jeu;

  protected:
    int posX, posY;
    Direction dir;

  public:
    Fantome();
    int getPosX() const;
    int getPosY() const;
    void setPosX(int );
    void setPosY(int );
    void setDir(Direction );
};


class Jeu
{
  private:
    class Pacman
{
    friend class Jeu;
    protected:
        int posPacmanX, posPacmanY; //la position de pacman
        Direction dirPacman;    // la direction de Pacman
        int pointVie;   // point de vie de pacman
        int but;        // nombre de but(notes) de joueur
    public:
        Pacman(){}
        Pacman(int x,int y,Direction d){
            posPacmanX = x;
            posPacmanY = y;
            dirPacman = d;
        }
        // Retourne la position du Pacman
        int getPacmanX() const;
        int getPacmanY() const;
        // Set et Get la direction de Pacman
        void setPacmanDir(Direction );
        Direction getPacmanDir() const;
        //Retourne le point de vie de Pacman
        int getPacmanVie()const;
        void setPacmanVie(int );
        //Retourne le but du joueur
        int getBut() const;
        void setBut(int );
};
  protected:
    Case *terrain;
    int largeur, hauteur; // Nombre de cases en largeur et en hauteur
    int nombreJoueur;     //Nombre de joueurs (1 ou 2)
  public:
    Pacman pacman1;
    Pacman pacman2;
    list<Fantome> fantomes;         // list de fantome
    list<pointvieImg> pointvie[2];  //list de pointvie pour afficher le point de vie sur l'ecran
    list<gommes> listgommes;        //list de pacGommes
    list<bonusVie> listbonusVie;    //list de gomme qui permet recuperer une vie

  public:
    Jeu();
    Jeu(const Jeu &)=delete;
    ~Jeu();

    Jeu &operator=(const Jeu &)=delete;

    bool init();
    void evolue();

    // Retourne les dimensions (en nombre de cases)
    int getNbCasesX() const;
    int getNbCasesY() const;

    // Retourne la case à une position donnée
    Case getCase(int, int) const;

    // Indique si la case à une position donnée existe et est vide
    // (Pacman ou les fantomes peuvent l'occuper)
    bool posValide(int, int) const;

    // Déplace Pacman dans une direction (si la case à atteindre est valide)
    bool deplacePacman(Pacman &, Direction);
    // set et get nombre de joueur
    void setNombreJoueur(int n){nombreJoueur = n;}
    int getNombreJoueur() const{return nombreJoueur;}

};

#endif
