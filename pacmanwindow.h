#ifndef PACMANWINDOW_H
#define PACMANWINDOW_H

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>
#include "jeu.h"
#include "pointvie.h"
#include "gomme.h"
class PacmanWindow : public QFrame
{
  protected:
    Jeu jeu;
    QPixmap pixmapPacman_haut,pixmapPacman_bas,pixmapPacman_droite,pixmapPacman_gauche,pixmapPacman2_haut,pixmapPacman2_bas,pixmapPacman2_droite,pixmapPacman2_gauche, pixmapFantome, pixmapMur, pixmapPoint_Vie , pixmapDot,pixmapBonusVie;
    QLabel *butPacman1;
    QLabel *butPacman2;
  public:
    PacmanWindow(QWidget *pParent=0, Qt::WindowFlags flags=0);
    void handleTimer();
    void clickButtonAjouter();      //la fonction handle l'evenement du button-ajouter
    void clickButtonSupprimer();    //la fonction handle l'evenement du button-supprimer
    void collisionHandle();         //la fonction handle la collosion entre pacman et fantome
    void collisionGommeHandle();   //la fonction handle la collosion entre pacman et le gomme
    void collisionPacmanBonusVie();// la fonction handle la collosion entre le pacman et le bonus vie
    void clickButtonSortir();       // la fonction handle le button sortie
    void clickButtonRejouer();      // la fonction handle le button rejouer
    void modeJeu();                 //la fonction pour choisir le nombre de jeu
    void clickButtonUnJoueur();     // handle 1 joueur
    void clickButtonDeuxJoueur();   // handle 2  joueurs
    void afficheBut();              //afficher le nombre de buts des pacmans
  protected:
    void keyPressEvent(QKeyEvent *);
    void paintEvent(QPaintEvent *);

};
class PacmanButton: public QPushButton      //classe fille du QPushButton pour recevoir les evenements lie au clavier
{
  public:
      PacmanButton(QWidget *parent = 0);
  protected:
      void keyPressEvent(QKeyEvent *);
};

#endif
