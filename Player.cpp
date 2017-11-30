/*
 *       _   _  _  _  _    ___  _  _  _____ _   _  _  _  _ 
 *      | \_/ |/ \| \| |  | o \/ \| |// __|| \_/ |/ \| \| |
 *      | \_/ ( o ) \\ |  |  _( o )  (| _| | \_/ ( o ) \\ |
 *      |_| |_|\_/|_|\_|  |_|  \_/|_|\\___||_| |_|\_/|_|\_|
 *      
                  Par: Lebbat badreddine
 */

#include "Player.h"



CPlayer::CPlayer()
{

}

void CPlayer::addObject(CObject *Object)
{
	m_TabObjects.push_back(Object);
}


int CPlayer::printObject()
{
	unsigned int i = 0;
	int cpt = 0;		

	printf("\n Objet(s) disponible(s) pour vous :");

	
	for (i = 0; i < m_TabObjects.size(); i++)
	{
		
		if (m_TabObjects[i]->getUsed()==false)
		{
			cpt++;
			
			m_TabObjects[i]->printObject();
			printf("\n==========> Tapez %d pour l'utiliser.. <==========\n", i);
		}
	}

	if (cpt == 0)
		printf("\n Aucun objet disponible !");

	return cpt;
}


vector<CObject *> CPlayer::getObjectTab()
{
	return m_TabObjects;
}


void CPlayer::useObject(int num, CTerrain *terrain, CMonster *monster)
{
	
	if (m_TabObjects[num]->getUsed() == false)
		m_TabObjects[num]->useObject(terrain, monster);
}

void CPlayer::setMonsterTab(vector<CMonster *> Tab)
{
	m_Tabmonstres = Tab;
}

void CPlayer::setObjectTab(vector<CObject*> Tab)
{
	m_TabObjects = Tab;
}

vector<CMonster *> CPlayer::getMonsterTab()
{
	return m_Tabmonstres;
}


// destructeur
CPlayer::~CPlayer()
{
	m_Tabmonstres.clear();
}