#pragma once
#include "Rolebase.h"
#include "UtilStr.h"

class CAnimationBlendRotate;
class CAnimationBlendDual;
class CObjectParticles;
class CWorldEffect;
class CObjectMeshSkinned;

class CFPSRole :public CRoleBase
{
public:
	CFPSRole(void);
	virtual ~CFPSRole(void);
	virtual int  Init(int nRoleID, const char* strCharFile);
	virtual void	Update(float ifps);


protected:
	virtual void		OnKeyFrame(_ActionCallback_KeyFrame* pKeyInfo);
	virtual void		OnActionComplete(_ActionCallback_Complete* pActInfo);
protected:
	CAnimationBlendRotate*		m_pStand[2];
	CAnimationBlendRotate*		m_pFire[2];
	CAnimationBlendDual*		m_pRun[2];

	int						m_nFire;
	float					m_fAniCoolingTime;//������������ȴʱ��
	float					m_fAniNowCoolingTime;
	float					m_fSudCoolingTime;//��ǹ������ȴʱ��
	float					m_fSudNowCoolingTime;
	float					m_fEmitCoolingTime;//�����ӵ���ȴʱ��
	float					m_fEmitNowCoolingTime;
};

