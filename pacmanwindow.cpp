#include <iostream>
#include "pacmanwindow.h"
#include"jeu.h"
#include<string>
#include<sstream>
using namespace std;

PacmanWindow::PacmanWindow(QWidget *pParent, Qt::WindowFlags flags):QFrame(pParent, flags)
{
    // Taille des cases en pixels
    int largeurCase, hauteurCase;

    if (pixmapPacman_droite.load("./data/pacman-right.bmp")==false)
    {
        cout<<"Impossible d'ouvrir pacman-right.png"<<endl;
        exit(-1);
    }
        if (pixmapPacman_gauche.load("./data/pacman-left.bmp")==false)
    {
        cout<<"Impossible d'ouvrir pacman-left.png"<<endl;
        exit(-1);
    }
        if (pixmapPacman_haut.load("./data/pacman-up.bmp")==false)
    {
        cout<<"Impossible d'ouvrir pacman-up.png"<<endl;
        exit(-1);
    }
        if (pixmapPacman_bas.load("./data/pacman-down.bmp")==false)
    {
        cout<<"Impossible d'ouvrir pacman-down.png"<<endl;
        exit(-1);
    }


        if (pixmapPacman2_droite.load("./data/pacman2-right.bmp")==false)
    {
        cout<<"Impossible d'ouvrir pacman2-right.png"<<endl;
        exit(-1);
    }
        if (pixmapPacman2_gauche.load("./data/pacman2-left.bmp")==false)
    {
        cout<<"Impossible d'ouvrir pacman2-left.png"<<endl;
        exit(-1);
    }
        if (pixmapPacman2_haut.load("./data/pacman2-up.bmp")==false)
    {
        cout<<"Impossible d'ouvrir pacman2-up.png"<<endl;
        exit(-1);
    }
        if (pixmapPacman2_bas.load("./data/pacman2-down.bmp")==false)
    {
        cout<<"Impossible d'ouvrir pacman2-down.png"<<endl;
        exit(-1);
    }

    if (pixmapFantome.load("./data/fantome.bmp")==false)
    {
        cout<<"Impossible d'ouvrir fantome.bmp"<<endl;
        exit(-1);
    }

    if (pixmapMur.load("./data/mur.bmp")==false)
    {
        cout<<"Impossible d'ouvrir mur.bmp"<<endl;
        exit(-1);
    }

    if (pixmapPoint_Vie.load("./data/pointVie.bmp")==false)
    {
        cout<<"Impossible d'ouvrir pointVie.bmp"<<endl;
        exit(-1);
    }

    if (pixmapDot.load("./data/dot.bmp") == false)
    {
        cout<<"Impossible d'ouvrir dot.bmp"<<endl;
        exit(-1);
    }

    if(pixmapBonusVie.load("./data/coeur.bmp")==false)
    {
        cout<<"Impossible d'ouvrir coeur.bmp"<<endl;
        exit(-1);
    }
    modeJeu();

    QTimer *timer = new QTimer(this);
    connect(timer, QTimer::timeout, this, PacmanWindow::handleTimer);
    timer->start(100);

    largeurCase = pixmapMur.width();
    hauteurCase = pixmapMur.height();

    resize(jeu.getNbCasesX()*largeurCase, jeu.getNbCasesY()*hauteurCase);

    // Button ajouter
    PacmanButton *btn_ajouter = new PacmanButton(this);
    btn_ajouter->setFixedSize(100,30);
    btn_ajouter->move(0,0);
    btn_ajouter->setText("Ajouter fantome");
    connect(btn_ajouter, PacmanButton::clicked, this, PacmanWindow::clickButtonAjouter);
    // Button supprimer
    PacmanButton *btn_sup = new PacmanButton(this);
    btn_sup->setFixedSize(100,30);
    btn_sup->move(110,0);
    btn_sup->setText("Supprimer fantome");
    connect(btn_sup, QPushButton::clicked, this, PacmanWindow::clickButtonSupprimer);

    // configurer qlabel butPacman1
    butPacman1 = new QLabel(this);// creer
    butPacman1->setGeometry(QRect(QPoint(500, 0), QSize(130, 30)));
    butPacman1->setFont(QFont("Calibri", 20));// Font et size
    butPacman1->setStyleSheet("QLabel { background-color : rgba( 255, 255, 255, 0% ); color : blue; }");//couleur

    //configurer qlabel butPacman2
    butPacman2 = new QLabel(this);// creer
    butPacman2->setGeometry(QRect(QPoint(500, 32), QSize(130, 30)));
    butPacman2->setFont(QFont("Calibri", 20));// Font et size
    butPacman2->setStyleSheet("QLabel { background-color : rgba( 255, 255, 255, 0% ); color : blue; }");//couleur
}

void PacmanWindow::paintEvent(QPaintEvent *)
{
    QMatrix rm;
    QPainter painter(this);
    list<Fantome>::const_iterator itFantome;
    int x, y;

    // Taille des cases en pixels
    int largeurCase, hauteurCase;

    largeurCase = pixmapMur.width();
    hauteurCase = pixmapMur.height();

    // Dessine pac-gommes
    list<gommes>:: iterator itgommes;
	for (itgommes = jeu.listgommes.begin(); itgommes!= jeu.listgommes.end(); itgommes++)
        painter.drawPixmap(itgommes->getPosX()*largeurCase,itgommes->getPosY()*hauteurCase, pixmapDot);
    //dessine bonus vie
    list<bonusVie>:: iterator itbonusVie;
	for (itbonusVie = jeu.listbonusVie.begin(); itbonusVie!= jeu.listbonusVie.end(); itbonusVie++)
        painter.drawPixmap(itbonusVie->getPosX()*largeurCase,itbonusVie->getPosY()*hauteurCase, pixmapBonusVie);
    // Dessine les cases
    for (y=2;y<jeu.getNbCasesY();y++)
        for (x=0;x<jeu.getNbCasesX();x++)
			if (jeu.getCase(x,y)==MUR)
                painter.drawPixmap(x*largeurCase, y*hauteurCase, pixmapMur);

    // Dessine les fantomes
    for (itFantome=jeu.fantomes.begin(); itFantome!=jeu.fantomes.end(); itFantome++)
        painter.drawPixmap(itFantome->getPosX()*largeurCase, itFantome->getPosY()*hauteurCase, pixmapFantome);

	// Dessine Pacman 1
	if(jeu.pacman1.getPacmanDir() == DROITE)
        painter.drawPixmap(jeu.pacman1.getPacmanX()*largeurCase, jeu.pacman1.getPacmanY()*hauteurCase, pixmapPacman_droite);
    else if(jeu.pacman1.getPacmanDir() == GAUCHE)
        painter.drawPixmap(jeu.pacman1.getPacmanX()*largeurCase, jeu.pacman1.getPacmanY()*hauteurCase, pixmapPacman_gauche);
    else if(jeu.pacman1.getPacmanDir() == HAUT)
        painter.drawPixmap(jeu.pacman1.getPacmanX()*largeurCase, jeu.pacman1.getPacmanY()*hauteurCase, pixmapPacman_haut);
    else
        painter.drawPixmap(jeu.pacman1.getPacmanX()*largeurCase, jeu.pacman1.getPacmanY()*hauteurCase, pixmapPacman_bas);
    // dessine Pacman2
    if (jeu.getNombreJoueur() == 2)
    {
        if(jeu.pacman2.getPacmanDir() == DROITE)
            painter.drawPixmap(jeu.pacman2.getPacmanX()*largeurCase, jeu.pacman2.getPacmanY()*hauteurCase, pixmapPacman2_droite);
        else if(jeu.pacman2.getPacmanDir() == GAUCHE)
            painter.drawPixmap(jeu.pacman2.getPacmanX()*largeurCase, jeu.pacman2.getPacmanY()*hauteurCase, pixmapPacman2_gauche);
        else if(jeu.pacman2.getPacmanDir() == HAUT)
            painter.drawPixmap(jeu.pacman2.getPacmanX()*largeurCase, jeu.pacman2.getPacmanY()*hauteurCase, pixmapPacman2_haut);
        else
            painter.drawPixmap(jeu.pacman2.getPacmanX()*largeurCase, jeu.pacman2.getPacmanY()*hauteurCase, pixmapPacman2_bas);
    }

	// Dessine Point de Vie de Pacman
    list<pointvieImg>:: iterator itpointvieImg;
	for (itpointvieImg = jeu.pointvie[0].begin(); itpointvieImg!= jeu.pointvie[0].end(); itpointvieImg++)
    {
        painter.drawPixmap(itpointvieImg->getPosX(),itpointvieImg->getPosY(), pixmapPoint_Vie);
    }
    if(jeu.getNombreJoueur() ==2)
    {
        for (itpointvieImg = jeu.pointvie[1].begin(); itpointvieImg!= jeu.pointvie[1].end(); itpointvieImg++)
        {
            painter.drawPixmap(itpointvieImg->getPosX(),itpointvieImg->getPosY(), pixmapPoint_Vie);
        }
    }

    // Afficher le pacman sur l'ecran pour connaitre quel pacman correspendant a quel point de vie, score
    painter.drawPixmap(250, 0, pixmapPacman_droite);
    if(jeu.getNombreJoueur()==2)
        painter.drawPixmap(250, 32, pixmapPacman2_droite);
}

void PacmanWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key_Left)
    {
        jeu.deplacePacman(jeu.pacman1,GAUCHE);
        jeu.pacman1.setPacmanDir(GAUCHE);
    }
    else if (event->key()==Qt::Key_Right)
    {
        jeu.deplacePacman(jeu.pacman1,DROITE);
        jeu.pacman1.setPacmanDir(DROITE);
    }
    else if (event->key()==Qt::Key_Up)
    {
        jeu.deplacePacman(jeu.pacman1,HAUT);
        jeu.pacman1.setPacmanDir(HAUT);
    }
    else if (event->key()==Qt::Key_Down)
    {
        jeu.deplacePacman(jeu.pacman1,BAS);
        jeu.pacman1.setPacmanDir(BAS);
    }
    //key clavier pour le 2eme pacman
    if (jeu.getNombreJoueur() == 2)
    {
        if (event->key()==Qt::Key_A)
        {
            jeu.deplacePacman(jeu.pacman2,GAUCHE);
            jeu.pacman2.setPacmanDir(GAUCHE);
        }
        else if (event->key()==Qt::Key_D)
        {
            jeu.deplacePacman(jeu.pacman2,DROITE);
            jeu.pacman2.setPacmanDir(DROITE);
        }
        else if (event->key()==Qt::Key_W)
        {
            jeu.deplacePacman(jeu.pacman2,HAUT);
            jeu.pacman2.setPacmanDir(HAUT);
        }
        else if (event->key()==Qt::Key_S)
        {
            jeu.deplacePacman(jeu.pacman2,BAS);
            jeu.pacman2.setPacmanDir(BAS);
        }
    }

    update();
}


void PacmanWindow::handleTimer()
{
    jeu.evolue();
    collisionGommeHandle();
    collisionHandle();
    collisionPacmanBonusVie();
    afficheBut();
    update();
}


void PacmanWindow::clickButtonAjouter()
{
    int largeur = 20;
	int hauteur = 17;
	int x,y;
	Fantome f;
    do {
        x = rand()%largeur;

        y = rand()%(hauteur-2) + 2;
    } while (jeu.getCase(x,y)!=VIDE);

    f.setPosX(x);
    f.setPosY(y);
    f.setDir(Direction(rand()%4));
    jeu.fantomes.push_back(f);
}

void PacmanWindow::clickButtonSupprimer(){
    if(!jeu.fantomes.empty())
        jeu.fantomes.pop_back();
}

PacmanButton::PacmanButton(QWidget *parent): QPushButton(parent){

}
void PacmanButton::keyPressEvent(QKeyEvent *event)
{
    if(parent() != NULL)
        QCoreApplication::sendEvent(parent(),event);
}


void PacmanWindow::collisionHandle()
{
    string resultat;
    ostringstream convert, convert2;
    QString qs;
    QMessageBox msg;
    list<Fantome>:: iterator itFantome;
    for(itFantome=jeu.fantomes.begin(); itFantome!=jeu.fantomes.end(); itFantome++){
        if(jeu.pacman1.getPacmanX() == itFantome->getPosX() && jeu.pacman1.getPacmanY() == itFantome->getPosY()){   // tester la collision
            if(jeu.pacman1.getPacmanVie() > 0){     //tester si le pacman a encore le point de vie
                jeu.pacman1.setPacmanVie(jeu.pacman1.getPacmanVie()-1);
                jeu.pointvie[0].pop_back();
            }
            if(jeu.pacman1.getPacmanVie() == 0)     // si pacman est mort
            {
                convert << jeu.pacman1.getBut();                                 //convert int -> string
                if(jeu.getNombreJoueur() == 2){
                    convert2<< jeu.pacman2.getBut();
                    resultat = "Nombre de buts de Joueur1: " + convert.str() + "\n" + "Nombre de buts de Joueur2: " + convert2.str();
                }
                else
                    resultat = "Nombre de buts de Joueur: " + convert.str();               // contenu du resultat affiche
                qs = QString::fromLocal8Bit(resultat.c_str());           // convert string -> QString
                msg.setText("JEU TERMINE --- Joueur1 est perdu!!");
                msg.setInformativeText(qs);
                //button pour sortir
                QPushButton* Sortir = msg.addButton("Sortir",QMessageBox::ActionRole);
                connect(Sortir, QPushButton::clicked, this, PacmanWindow::clickButtonSortir);
                //button pour rejouer
                QPushButton* Rejouer = msg.addButton("Rejouer",QMessageBox::ActionRole);
                connect(Rejouer, QPushButton::clicked, this, PacmanWindow::clickButtonRejouer);
                msg.exec();
            }
        }
        if(jeu.getNombreJoueur() == 2)
        {
            if(jeu.pacman2.getPacmanX() == itFantome->getPosX() && jeu.pacman2.getPacmanY() == itFantome->getPosY()){
                if(jeu.pacman2.getPacmanVie() > 0)
                {
                    jeu.pacman2.setPacmanVie(jeu.pacman2.getPacmanVie()-1);
                    jeu.pointvie[1].pop_back();
                }
                if(jeu.pacman2.getPacmanVie() == 0)
                {
                    convert << jeu.pacman1.getBut();                                 //convert int -> string
                    convert2<< jeu.pacman2.getBut();
                    resultat = "Nombre de buts de Joueur1: " + convert.str() + "\n" + "Nombre de buts de Joueur2: " + convert2.str();               // contenu du resultat affiche
                    qs = QString::fromLocal8Bit(resultat.c_str());           // convert string -> QString
                    msg.setText("JEU TERMINE --- Joueur2 est perdu!!");
                    msg.setInformativeText(qs);
                    //button pour sortir
                    QPushButton* Sortir = msg.addButton("Sortir",QMessageBox::ActionRole);
                    connect(Sortir, QPushButton::clicked, this, PacmanWindow::clickButtonSortir);
                    //button pour rejouer
                    QPushButton* Rejouer = msg.addButton("Rejouer",QMessageBox::ActionRole);
                    connect(Rejouer, QPushButton::clicked, this, PacmanWindow::clickButtonRejouer);
                    msg.exec();
            }
        }
        }
    }
    update();
}

void PacmanWindow::collisionGommeHandle(){
    string resultat;
    ostringstream convert,convert2;
    QString qs;
    QMessageBox msg;
    list<gommes>:: iterator itgommes;
    for(itgommes= jeu.listgommes.begin(); itgommes!=jeu.listgommes.end(); itgommes++){
        if(jeu.pacman1.getPacmanX() == itgommes->getPosX() && jeu.pacman1.getPacmanY() == itgommes->getPosY()){ // tester la collision
            jeu.listgommes.erase(itgommes);
            jeu.pacman1.setBut(jeu.pacman1.getBut()+10);                                   // 1 gomme == 10 buts(notes)
            if(jeu.listgommes.empty())                                     //verifier si tous les gommes ont mange
            {
                convert << jeu.pacman1.getBut();  //convert int -> string
                if(jeu.getNombreJoueur() == 2)
                {
                    convert2<< jeu.pacman2.getBut();
                    resultat = "Nombre de buts de Joueur1: " + convert.str() + "\n" + "Nombre de buts de Joueur2: " + convert2.str();
                }
                else
                    resultat = "Nombre de buts de Joueur: " + convert.str();                    // contenu du resultat affiche
                qs = QString::fromLocal8Bit(resultat.c_str());             // convert string -> QString
                //QMessageBox::warning(this,"End Game",qs);                  // Afficher le resultat
                msg.setText("JEU TERMINE!!");
                msg.setInformativeText(qs);
                //button pour sortir
                QPushButton* Sortir = msg.addButton("Sortir",QMessageBox::ActionRole);
                connect(Sortir, QPushButton::clicked, this, PacmanWindow::clickButtonSortir);
                //button pour rejouer
                QPushButton* Rejouer = msg.addButton("Rejouer",QMessageBox::ActionRole);
                connect(Rejouer, QPushButton::clicked, this, PacmanWindow::clickButtonRejouer);
                msg.exec();
            }
        }
        if(jeu.getNombreJoueur() == 2)
        {
            if(jeu.pacman2.getPacmanX() == itgommes->getPosX() && jeu.pacman2.getPacmanY() == itgommes->getPosY()){
                jeu.listgommes.erase(itgommes);
                int but2 = jeu.pacman2.getBut()+10;
                jeu.pacman2.setBut(but2);                                   // 1 gomme == 10 buts(notes)
                if(jeu.listgommes.empty())                                     //verifier si tous les gommes ont mange
                {
                    convert << jeu.pacman1.getBut();                                   //convert int -> string
                    convert2<< jeu.pacman2.getBut();
                    resultat ="Nombre de buts de Joueur1: " + convert.str() + "\n" + "Nombre de buts de Joueur2: " + convert2.str();                  // contenu du resultat affiche
                    qs = QString::fromLocal8Bit(resultat.c_str());             // convert string -> QString
                    msg.setText("JEU TERMINE!!");
                    msg.setInformativeText(qs);
                    //button pour sortir
                    QPushButton* Sortir = msg.addButton("Sortir",QMessageBox::ActionRole);
                    connect(Sortir, QPushButton::clicked, this, PacmanWindow::clickButtonSortir);
                    //button pour rejouer
                    QPushButton* Rejouer = msg.addButton("Rejouer",QMessageBox::ActionRole);
                    connect(Rejouer, QPushButton::clicked, this, PacmanWindow::clickButtonRejouer);
                    msg.exec();
            }
        }
        }

    }
}

void PacmanWindow::collisionPacmanBonusVie()
{
    pointvieImg p;
    list<bonusVie> :: iterator itbonusVie;
    list<pointvieImg>::iterator itpointVie;
    for(itbonusVie=jeu.listbonusVie.begin();itbonusVie!=jeu.listbonusVie.end();itbonusVie++)
    {
        if(jeu.pacman1.getPacmanX() == itbonusVie->getPosX() && jeu.pacman1.getPacmanY() == itbonusVie->getPosY()){  //tester si le pacman mange le bonus de la vie
            itpointVie = jeu.pointvie[0].end();
            itpointVie--;
            p.setPosX(itpointVie->getPosX()+32);    // configurer la position d'un point de vie apres manger
            p.setPosY(itpointVie->getPosY());       //  configurer la position d'un point de vie apres manger
            if(jeu.pointvie[0].size()<5)
            {
                jeu.pointvie[0].push_back(p);       // afficher ce point sur l'ecran
                jeu.pacman1.setPacmanVie(jeu.pacman1.getPacmanVie()+1); //augmenter un point de vie de pacman
            }
            jeu.listbonusVie.erase(itbonusVie);
        }
        //faire parreil pour le 2eme pacman
        if(jeu.getNombreJoueur()==2)
        {
            if(jeu.pacman2.getPacmanX() == itbonusVie->getPosX() && jeu.pacman2.getPacmanY() == itbonusVie->getPosY())
            {
                itpointVie = jeu.pointvie[1].end();
                itpointVie--;
                p.setPosX(itpointVie->getPosX()+32);
                p.setPosY(itpointVie->getPosY());
                if(jeu.pointvie[1].size()<5)
                {
                    jeu.pointvie[1].push_back(p);
                    jeu.pacman2.setPacmanVie(jeu.pacman2.getPacmanVie()+1);

                }
                jeu.listbonusVie.erase(itbonusVie);
            }
        }

    }
}

void PacmanWindow::clickButtonSortir()
{
    this->close();
}

void PacmanWindow::clickButtonRejouer()
{
    modeJeu();
    if(jeu.getNombreJoueur()==1)
        butPacman2->setText(QString(""));       //effacer le but affichage du 2eme pacman si il y a just 1 joueur
    update();
}

void PacmanWindow::modeJeu()
{
    QMessageBox msg;
    msg.setText("Nombre de joueurs?");
    msg.setInformativeText("Un joueur-les fleches\nDeux joueurs-les fleches vs AWDS");
    QPushButton* unjoueur = msg.addButton("Un Joueur",QMessageBox::ActionRole);
    connect(unjoueur, QPushButton::clicked, this, PacmanWindow::clickButtonUnJoueur);
    QPushButton* deuxjoueur = msg.addButton("Deux Joueurs",QMessageBox::ActionRole);
    connect(deuxjoueur, QPushButton::clicked, this, PacmanWindow::clickButtonDeuxJoueur);
    msg.exec();
}

void PacmanWindow::clickButtonUnJoueur()
{
    jeu.setNombreJoueur(1);
    jeu.init();
}

void PacmanWindow::clickButtonDeuxJoueur()
{
    jeu.setNombreJoueur(2);
    jeu.init();
}

void PacmanWindow::afficheBut()
{
    butPacman1->setText(QString(("Score : " + to_string(jeu.pacman1.getBut())).c_str()));
    butPacman1->show();
    if(jeu.getNombreJoueur()==2)
    {
        butPacman2->setText(QString(("Score : " + to_string(jeu.pacman2.getBut())).c_str()));
        butPacman2->show();
    }
}
