#include "Engine.h"
#include "Game.h"
#include "ObjectDummy.h"
#include "BodyRigid.h"
#include "BodyDummy.h"



#ifdef MEMORY_INFO
#define new new(__FILE__, __LINE__) 
#endif // MEMORY_INFO

using namespace MathLib;

/*
*/
#define ACTOR_BASE_IFPS             (1.0f / 60.0f)
#define ACTOR_BASE_CLAMP            89.9f
#define ACTOR_BASE_COLLISIONS       4

/*
*/


CActorBase::CActorBase()
{
	m_vUp = vec3(0.0f, 0.0f, 1.0f);
	m_pObject = new CObjectDummy();
	m_pDummy = new CBodyDummy();
	m_pShape = new CShapeCapsule(1.0f, 1.0f);

	m_nFlush = 0;
	m_vPosition = Vec3_zero;
	m_vVelocity = Vec3_zero;
	m_fPhiAngle = 0.0f;			//��б��		��άƽ������ϵ�У�ֱ����Y������ķ�����X������֮��ļн�
	m_fThetaAngle = 0.0f;			//��λ�ǣ��������������뵱ǰ��������˳ʱ���߹��ĽǶ�

	for (int i = 0; i < NUM_STATES; i++)
	{
		m_pStates[i] = 0;
		m_pTimes[i] = 0.0f;
	}

	m_pDummy->SetEnabled(1);
	m_pObject->SetBody(NULL);
	m_pObject->SetBody(m_pDummy);
	m_pShape->SetBody(NULL);
	m_pShape->SetBody(m_pDummy);

	m_pObject->SetWorldTransform(Get_Body_Transform());
	m_pShape->SetRestitution(0.0f);
	m_pShape->SetCollisionMask(2);

	SetEnabled(1);
	SetViewDirection(vec3(0.0f, 1.0f, 0.0f));
	SetCollision(1);

	SetCollisionRadius(0.3f);
	SetCollisionHeight(1.0f);
	SetFriction(2.0f);
	SetMinVelocity(2.0f);

}