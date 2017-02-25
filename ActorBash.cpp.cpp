#include "Engine.h"
#include "Game.h"
#include "ObjectDummy.h"
#include "BodyRigid.h"
#include "BodyDummy.h"
#include "Physics.h"
#include "ShapeCapsule.h"
#include "ActorBase.h"
#include "Visualizer.h"
#include "sys/SysControl.h"


using namespace MathLib;

#ifdef MEMORY_INFO
#define new new(__FILE__, __LINE__) 
#endif // MEMORY_INFO

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
	m_fPhiAngle = 0.0f;			//倾斜角		二维平面坐标系中，直线向Y周延伸的方向与X轴正向之间的夹角
	m_fThetaAngle = 0.0f;			//方位角，正北方那条线与当前线条按照顺时针走过的角度


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
	SetMaxVelocity(4.0f);
	SetAcceleration(8.0f);
	SetDamping(8.0f);
	SetJumping(1.5f);

	SetGround(0);
	SetCeiling(0);
}


CActorBase::~CActorBase()
{
	m_pDummy->SetObject(NULL);
	delete m_pObject;
	delete m_pDummy;
}

void CActorBase::SetEnabled(int enable)
{
	m_nEnable = enable;
	m_pDummy->SetEnabled(m_nEnable);
}


int CActorBase::IsEnabled() const
{
	return m_nEnable;
}
void CActorBase::Update(float ifps)
{
	if (!m_nEnable)
	{
		return;
	}

	// impulse
	vec3 impulse = vec3_zero;

	// ortho basis
	vec3 tangent, binormal;
	OrthoBasis(m_vUp, tangent, binormal);

	// current basis
	vec3 x = quat(m_vUp, -m_fPhiAngle) * binormal;
	vec3 y = Normalize(Cross(m_vUp, x));
	vec3 z = Normalize(Cross(x, y));

	handle states
		Update_States(1, ifps);

	// old velocity
	float x_velocity = Dot(x, m_vVelocity);
	float y_velocity = Dot(y, m_vVelocity);
	float z_velocity = Dot(z, m_vVelocity);
	// movement
	if (m_pStates[STATE_FORWARD]) impulse += x;
	if (m_pStates[STATE_BACKWARD]) impulse -= x;
	if (m_pStates[STATE_MOVE_LEFT]) impulse += y;
	if (m_pStates[STATE_MOVE_RIGHT]) impulse -= y;
	impulse.normalize();
	//velocity
	if (m_pStates[STATE_RUN])
		impulse *= m_fMaxVelocity;
	else
		impulse *= m_fMinVelocity;
	// jump
	if (m_pStates[STATE_JUMP] == STATE_BEGIN)
	{
		impulse += z * CMathCore::Sqrt(2.0f * 9.8f * m_fJumping) / (m_fAcceleration * ifps);
	}

	// rotate velocity
	if (GetGround())
	{
		m_vVelocity = x * x_velocity + y * y_velocity + z * z_velocity;
	}

	// time
	float time = ifps * g_Engine.pPhysics->GetScale();

	// target velocity
	float target_velocity = Length(vec2(Dot(x, impulse), Dot(y, impulse)));

	// penetration tolerance
	float penetration = g_Engine.pPhysics->GetPenetrationTolerance();
	float penetration_2 = penetration * 2.0f;

	// frozen linear velocity
	float frozen_velocity = g_Engine.pPhysics->GetFrozenLinearVelocity();

	// friction
	float friction = 0.0f;
	if (target_velocity < EPSILON)
	{
		friction = m_fFriction;
	}

	//clear collision flags
	if (GetCollision())
	{
		m_nGround = 0;
		m_nCeiling = 0;
	}
	// movement
	do 
	{
		// adaptive time step
		float ifps = Min(time, ACTOR_BASE_IFPS);
		time -= ifps;

		// save old velocity
		float old_velocity = Length(vec2(Dot(x, m_vVelocity), Dot(y, m_vVelocity)));

		// integrate velocity
		m_vVelocity += impulse * (m_fAcceleration * ifps);
		m_vVelocity += g_Engine.pPhysics->GetGravity() * ifps;

		// damping
		float current_velocity = Length(vec2(Dot(x, m_vVelocity), Dot(y, m_vVelocity)));
		if (target_velocity < EPSILON || current_velocity > target_velocity)
		{
			m_vVelocity = (x * Dot(x, m_vVelocity) + y * Dot(y, m_vVelocity)) * CMathCore::Exp(-m_fDamping * ifps) + z * Dot(z, m_vVelocity);
		}

		// clamp maximum velocity
		current_velocity = Length(vec2(Dot(x, m_vVelocity), Dot(y, m_vVelocity)));
		if (current_velocity > old_velocity)
		{
			if (current_velocity > target_velocity)
			{
				m_vVelocity = (x * Dot(x, m_vVelocity) + y * Dot(y, m_vVelocity)) * target_velocity / current_velocity + z * Dot(z, m_vVelocity);
			}
		}

		// frozen velocity
		int is_frozen = 0;
		if (current_velocity < frozen_velocity)
		{
			m_vVelocity = z * Dot(z, m_vVelocity);
			is_frozen = 1;
		}

		// integrate position
		//m_vPosition += Vec3(m_vVelocity * ifps);

		// world collision
		if (GetCollision())
		{

		}


	}



}