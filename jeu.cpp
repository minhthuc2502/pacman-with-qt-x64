#include "jeu.h"
#include <iostream>
#include <assert.h>
#include<list>

Fantome::Fantome()
{
    posX = 0; posY = 0;
    dir = BAS;
}

int Fantome::getPosX() const
{
    return posX;
}

int Fantome::getPosY() const
{
    return posY;
}

void Fantome::setPosX(int x) {
    posX = x;
}

void Fantome::setPosY(int y){
    posY = y;
}

void Fantome::setDir(Direction d)
{
    dir = (Direction) d;
}

int Jeu::Pacman::getPacmanVie() const
{
    return pointVie;
}
void Jeu::Pacman::setPacmanVie(int s)
{
    pointVie = s;
}

int Jeu::Pacman::getBut() const
{
   return but;
}

void Jeu::Pacman::setBut(int b)
{
    but = b;
}


Direction Jeu::Pacman::getPacmanDir() const
{
    return dirPacman;
}

void Jeu::Pacman::setPacmanDir(Direction d)
{
    dirPacman = d;
}

int Jeu::Pacman::getPacmanX() const
{
    return posPacmanX;
}

int Jeu::Pacman::getPacmanY() const
{
    return posPacmanY;
}

Jeu::Jeu()
{
    terrain = NULL;
    largeur = 0; hauteur = 0;
    pacman1.but = 0;
    pacman1.pointVie = 0 ;
}

Jeu::~Jeu()
{
    if (terrain!=NULL)
        delete[] terrain;
}

bool Jeu::init()
{
    int viePacman = 5;
    pacman1.but  = 0;
    pacman1.dirPacman = DROITE;
	int x, y;
	list<Fantome>::iterator itFantome;

	const char terrain_defaut[17][21] = {
	    "....................",
	    "....................",
		"####################",
		"#.+......##......+.#",
		"#.#####..##...####.#",
		"#........##........#",
		"#..........+.......#",
		"#......#....#......#",
		"#......#...##......#",
		"#####..#..+.#..#####",
		"#......##...#......#",
		"#......#....#......#",
		"#......+...........#",
		"#..................#",
		"#.....#......#.....#",
		"#+....#......#....+#",
        "####################"
    };

	largeur = 20;
	hauteur = 17;

	terrain = new Case[largeur*hauteur];

	for(y=2;y<hauteur;++y)
		for(x=0;x<largeur;++x)
            if (terrain_defaut[y][x]=='#')
                terrain[y*largeur+x] = MUR;
            else if(terrain_defaut[y][x]=='+')
                terrain[y*largeur+x] = BONUSVIE;
            else
                terrain[y*largeur+x] = VIDE;

    fantomes.resize(10);

	for (itFantome=fantomes.begin(); itFantome!=fantomes.end(); itFantome++)
    {
        do {
            x = rand()%largeur;
            y = rand()%(hauteur-2) + 2;
        } while (terrain[y*largeur+x]!=VIDE);

        itFantome->posX = x;
        itFantome->posY = y;
        itFantome->dir = (Direction)(rand()%4);
    }

    do {
        x = rand()%largeur;
        y = rand()%(hauteur-2) + 2;
    } while (terrain[y*largeur+x]!=VIDE);

    pacman1.posPacmanX = x,
    pacman1.posPacmanY = y;
    pacman1.pointVie = viePacman;

    // Initialiser le list de point de vie de pacman1
    int PositionX_firstPointVie = 300;
	int PositionY_firstPointVie = 0;
    pointvie[0].resize(5);
	list<pointvieImg>:: iterator itpointvieImg;
	for (itpointvieImg = pointvie[0].begin(); itpointvieImg!= pointvie[0].end(); itpointvieImg++)
    {
        PositionX_firstPointVie += 32;
        itpointvieImg->setPosX(PositionX_firstPointVie);
        itpointvieImg->setPosY(PositionY_firstPointVie);
    }

    // initialiser la position des gommes
    if(!listgommes.empty())
    {
        list<gommes>::iterator itgommes;
        for(itgommes = listgommes.begin();itgommes!= listgommes.end(); itgommes++)
            listgommes.erase(itgommes);
    }
    gommes myGommes;
    for (int y=2;y<getNbCasesY();y++)
        for (int x=0;x<getNbCasesX();x++)
            if (getCase(x,y)==VIDE)
            {
                myGommes.setPosX(x);
                myGommes.setPosY(y);
                listgommes.push_back(myGommes);
            }
    //initialiser le bonus vie
    list<bonusVie> :: iterator itbonusVie;
    listbonusVie.resize(7);
    itbonusVie = listbonusVie.begin();
    for(y=2;y<hauteur;++y)
		for(x=0;x<largeur;++x)
            if(terrain[y*largeur+x] == BONUSVIE)
            {
                itbonusVie->setPosX(x);
                itbonusVie->setPosY(y);
                itbonusVie++;
            }

    if(nombreJoueur == 2)
    {
        pacman2.but = 0;
        pacman2.dirPacman = DROITE;
        do {
            x = rand()%largeur;
            y = rand()%(hauteur-2) + 2;
        } while (terrain[y*largeur+x]!=VIDE);

        pacman2.posPacmanX = x,
        pacman2.posPacmanY = y;
        pacman2.pointVie = viePacman;
        // Initialiser le list de point de vie de pacman2
        int PositionX_firstPointVie2 = 300;
        int PositionY_firstPointVie2 = 32;
        pointvie[1].resize(5);
        for (itpointvieImg = pointvie[1].begin(); itpointvieImg!= pointvie[1].end(); itpointvieImg++)
        {
            PositionX_firstPointVie2 += 32;
            itpointvieImg->setPosX(PositionX_firstPointVie2);
            itpointvieImg->setPosY(PositionY_firstPointVie2);
        }
    }
    return true;
}

void Jeu::evolue()
{
    int testX, testY;
	list<Fantome>::iterator itFantome;

    int depX[] = {-1, 1, 0, 0};
    int depY[] = {0, 0, -1, 1};

    for (itFantome=fantomes.begin(); itFantome!=fantomes.end(); itFantome++)
    {
        testX = itFantome->posX + depX[itFantome->dir];
        testY = itFantome->posY + depY[itFantome->dir];

        if (terrain[testY*largeur+testX]==VIDE || terrain[testY*largeur+testX]== BONUSVIE)
        {
            itFantome->posX = testX;
            itFantome->posY = testY;
        }
        else
            // Changement de direction
            itFantome->dir = (Direction)(rand()%4);
    }
}

int Jeu::getNbCasesX() const
{
    return largeur;
}

int Jeu::getNbCasesY() const
{
    return hauteur;
}

Case Jeu::getCase(int x, int y) const
{
    assert(x>=0 && x<=largeur && y>=0 && y<=hauteur);
    return terrain[y*largeur+x];
}

bool Jeu::posValide(int x, int y) const
{
    return (x>=0 && x<largeur && y>=0 && y<hauteur && (terrain[y*largeur+x]==VIDE || terrain[y*largeur+x]==BONUSVIE));
}

bool Jeu::deplacePacman(Pacman &p , Direction dir)
{
    int depX[] = {-1, 1, 0, 0};
    int depY[] = {0, 0, -1, 1};
    int testX, testY;

    testX = p.posPacmanX + depX[dir];
    testY = p.posPacmanY + depY[dir];

    if (posValide(testX, testY))
    {
        p.posPacmanX = testX;
        p.posPacmanY = testY;
        return true;
    }
    else
        return false;
}



