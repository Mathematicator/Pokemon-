/*
 *       _   _  _  _  _    ___  _  _  _____ _   _  _  _  _ 
 *      | \_/ |/ \| \| |  | o \/ \| |// __|| \_/ |/ \| \| |
 *      | \_/ ( o ) \\ |  |  _( o )  (| _| | \_/ ( o ) \\ |
 *      |_| |_|\_/|_|\_|  |_|  \_/|_|\\___||_| |_|\_/|_|\_|
 *      
                  Par Lebbat badreddine
 */

#ifndef	UTILS_H
#define UTILS_H
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <vector>
#include "Monster.h"
#include "Electric.h"
#include "Attack.h"
#include "Water.h"
#include "Rock.h"
#include "terrain.h"
#include "Fire.h"
#include "Grass.h"
#include "Plant.h"
#include "Insect.h"
#include "time.h"
#include "Player.h"
#include "Object.h"
#include "Potion.h"
#include "Drug.h"
#include <string>





/**************** Prototype fonctions **********************/
int gagner(vector<CMonster *> Tabmonstres, int joueur);
char jouer(CMonster *monster, CPlayer *JoueurCourant, int joueur, CMonster *ennemi, CPlayer *JoueurEnnemi, CTerrain *terrain_p);


void affichageFichier(string const nomFichier);
float frand_a_b(float a, float b);
CElectric* lecture_Elec(ifstream *fichier, string nomMonstre);
//CWater* lecture_Water(ifstream *fichier, string nomMonstre, CTerrain *terrain);
CFire* lecture_Fire(ifstream *fichier, string nomMonstre);
CInsect* lecture_Insect(ifstream *fichier, string nomMonstre);
CPlant* lecture_Plant(ifstream *fichier, string nomMonstre);
CRock* lecture_Rock(ifstream *fichier, string nomMonstre);
CMonster* constructor(ifstream *fichier, string nomMonstre, string type, CTerrain *terrain);
string rechercheMonster(ifstream *fichier, string str_tosearch);
vector<CMonster*> InitMonster(int joueur, ifstream *fichier, CTerrain *terrain, vector<CMonster *> Tabmonstres, int cpt, int nbMonstre);
vector<CMonster*> createMonstre(int joueur, string const nomFichier, string nomfichierAttack, CTerrain *terrain, int nbMonstre, int NbAttack);

int AffichageMonstre(vector<CMonster *> Tabmonstres, int joueur);
CMonster* choixMonstre(int joueur, vector<CMonster *> Tabmonstres);
void 
Game(CPlayer *Joueur1, CPlayer *Joueur2, CTerrain *terrain);
CAttack* AttackFill(ifstream *fichier, type_a monType, vector<CAttack *> m_attack);

CObject* ObjectFill(ifstream *fichier, type_object monType);
vector<CObject*> createTabObjet(string const nomFichier, int NbObject);
void CommencerLeJeu(CPlayer *Joueur1, CPlayer *Joueur2, CTerrain *terrain);
/***********************************************************/


#endif