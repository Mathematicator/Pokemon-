/*
 *       _   _  _  _  _    ___  _  _  _____ _   _  _  _  _ 
 *      | \_/ |/ \| \| |  | o \/ \| |// __|| \_/ |/ \| \| |
 *      | \_/ ( o ) \\ |  |  _( o )  (| _| | \_/ ( o ) \\ |
 *      |_| |_|\_/|_|\_|  |_|  \_/|_|\\___||_| |_|\_/|_|\_|
 *      
                  Par: Lebbat badreddine
 */

#include "Object.h"
#include "Monster.h"
#include "terrain.h"

// constructeur paramétrique
CObject::CObject(string name)
{
	m_name = name;
	m_used = false;
}

bool CObject::getUsed()
{
	return m_used;
}

type_object CObject::getType()
{
	return m_type;
}

void CObject::useObject(CTerrain *terrain, CMonster *monster)
{

}

void CObject::printObject()
{

}

CObject::CObject()
{

}

CObject::~CObject()
{

}