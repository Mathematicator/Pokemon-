/*
 *       _   _  _  _  _    ___  _  _  _____ _   _  _  _  _ 
 *      | \_/ |/ \| \| |  | o \/ \| |// __|| \_/ |/ \| \| |
 *      | \_/ ( o ) \\ |  |  _( o )  (| _| | \_/ ( o ) \\ |
 *      |_| |_|\_/|_|\_|  |_|  \_/|_|\\___||_| |_|\_/|_|\_|
 *      
                  Par: Lebbat badreddine
 */

#include "Drug.h"


// constructeur param�trique
CDrug::CDrug(string name, bool sechageTerrain, bool guerisonBrulure)
{
	m_name = name;
	m_type = Drug;
	m_used = false;

	m_sechageTerrain = sechageTerrain;
	m_guerisonBrulure = guerisonBrulure;
}



void CDrug::DrugGuerisonBrulure(CMonster *monster)
{
	// objet utilis�e
	m_used = true;

	// gu�rison br�lure
	if (monster->getEtat().brule == true)
		monster->setBrule(false);

	printf("\n Utilisation de %s pour guerir les brulures de %s !", m_name.c_str(), monster->getName().c_str());
}
//La fonctin qui assure le s�chage de terrain
void CDrug::DrugSechageTerrain(CTerrain *terrain)
{
	// si un objet est utilis� elle renvoie la valeur true
	m_used = true;

	// on s�che le terrian  si il a �t� inod� ou pas 
	if (terrain->getInnonde() == true)
		terrain->setInnonde(false);

	printf("\n Utilisation de %s pour secher le terrain !", m_name.c_str());
}

// m�thode a pour but d'utiliser l'objet choisi 
void CDrug::useObject(CTerrain *terrain, CMonster *monster)
{
	// un objet de gu�rison de brulure agit de cette fa�on
	if (m_guerisonBrulure == true)
		CDrug::DrugGuerisonBrulure(monster);

	// un objet de sechage de terrain agit de cette mani�re
	if (m_sechageTerrain == true)
		CDrug::DrugSechageTerrain(terrain);
}



// une m�thode qui a pour but de gu�rir les brulures 
void CDrug::printObject()
{
	printf("\n Nom : %s", m_name.c_str());
	printf("\n Type : %s", nameTypeObject[m_type].c_str());

	if (m_guerisonBrulure)
		printf("\n Guerison brulure ? : OUI");
	else
		printf("\n Guerison brulure ? : NON");

	if (m_sechageTerrain)
		printf("\n Seche le terrain ? : OUI");
	else
		printf("\n Seche le terrain ? : NON");
}

type_object CDrug::getType()
{
	return m_type;
}

// destructeur 
CDrug::~CDrug()
{

}