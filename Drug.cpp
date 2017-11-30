/*
 *       _   _  _  _  _    ___  _  _  _____ _   _  _  _  _ 
 *      | \_/ |/ \| \| |  | o \/ \| |// __|| \_/ |/ \| \| |
 *      | \_/ ( o ) \\ |  |  _( o )  (| _| | \_/ ( o ) \\ |
 *      |_| |_|\_/|_|\_|  |_|  \_/|_|\\___||_| |_|\_/|_|\_|
 *      
                  Par: Lebbat badreddine
 */

#include "Drug.h"


// constructeur paramétrique
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
	// objet utilisée
	m_used = true;

	// guérison brûlure
	if (monster->getEtat().brule == true)
		monster->setBrule(false);

	printf("\n Utilisation de %s pour guerir les brulures de %s !", m_name.c_str(), monster->getName().c_str());
}
//La fonctin qui assure le séchage de terrain
void CDrug::DrugSechageTerrain(CTerrain *terrain)
{
	// si un objet est utilisé elle renvoie la valeur true
	m_used = true;

	// on séche le terrian  si il a été inodé ou pas 
	if (terrain->getInnonde() == true)
		terrain->setInnonde(false);

	printf("\n Utilisation de %s pour secher le terrain !", m_name.c_str());
}

// méthode a pour but d'utiliser l'objet choisi 
void CDrug::useObject(CTerrain *terrain, CMonster *monster)
{
	// un objet de guérison de brulure agit de cette façon
	if (m_guerisonBrulure == true)
		CDrug::DrugGuerisonBrulure(monster);

	// un objet de sechage de terrain agit de cette manière
	if (m_sechageTerrain == true)
		CDrug::DrugSechageTerrain(terrain);
}



// une méthode qui a pour but de guérir les brulures 
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