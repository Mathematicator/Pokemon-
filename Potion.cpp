/*
 *       _   _  _  _  _    ___  _  _  _____ _   _  _  _  _ 
 *      | \_/ |/ \| \| |  | o \/ \| |// __|| \_/ |/ \| \| |
 *      | \_/ ( o ) \\ |  |  _( o )  (| _| | \_/ ( o ) \\ |
 *      |_| |_|\_/|_|\_|  |_|  \_/|_|\\___||_| |_|\_/|_|\_|
 *      
                  Par: Lebbat badreddine
 */

#include "Potion.h"



CPotion::CPotion(string name, float lifeRecup, float attackValue) 
{
	m_name = name;
	m_type = Potion;
	m_used = false;
	
	m_attackValue = attackValue;
	m_lifeRecup = lifeRecup;
}


void CPotion::PotionLifeRecupe(CMonster *Monster)
{
	
	m_used = true;
		
	
	Monster->setPointVie(Monster->getPoinVie() + m_lifeRecup);

	printf("\n %s ! %.2f points de vie ajoutes !", Monster->getName().c_str(), m_lifeRecup);
}


void CPotion::PotionAttackValue(CMonster *Monster)
{
	
	m_used = true;

	
	Monster->setDefense(Monster->getDefense() + m_attackValue);

	printf("\n %s ! %.2f points d'attack ajoutes !", Monster->getName().c_str(), m_attackValue);
}


void CPotion::printObject()
{
	printf("\n Nom : %s", m_name.c_str());
	printf("\n Type : %s", nameTypeObject[m_type].c_str());
	printf("\n Vie bonus : %.1f", m_lifeRecup);
	printf("\n Attack Bonus : %.1f",m_attackValue);
}

void CPotion::useObject(CTerrain *terrain, CMonster *monster)
{
	CPotion::PotionAttackValue(monster);
	CPotion::PotionLifeRecupe(monster);
}


type_object CPotion::getType()
{
	return m_type;
}

CPotion::~CPotion()
{

}