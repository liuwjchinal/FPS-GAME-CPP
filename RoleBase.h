#pragma once
#include "MathLib.h"	//�ⲿ����
#include "UtilStr.h"	//�ⲿ����

class CCreature;
class CAction;
class CInterfaceBase;
class CNavigationFinder;


struct _ActionCallback_KeyFrame;
struct _ActionCallback_Complete;
using namespace MathLib;
class CNode;

class CRoleBase
{
public:
	CRoleBase(void);
	virtual ~CRoleBase(void);
	virtual int	Init(int nRoleID, const char* strCharFile);
	virtual void	Update(float ifps);

private:
}