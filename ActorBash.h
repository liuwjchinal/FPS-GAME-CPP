#pragma once
#ifndef __ACTOR_BASE_H__
#define __ACTOR_BASE_H__

#include "Shape.h"
#include "Bounds.h"

class CActorBase
{    
	CActorBase();
	virtual ~CActorBase();

	void SetEnabled(int enable);
	int IsEnabled() const;

	void Update(float ifps);

	// intersection mask
	void SetIntersectionMask(int mask);
	int GetIntersectionMask() const;

	    // collision
    void SetCollision(int collision);
    int GetCollision() const;
        
    // collision mask
    void SetCollisionMask(int mask);
    int GetCollisionMask() const;
        
    // collision radius
    void SetCollisionRadius(float radius);
    float GetCollisionRadius() const;
        
    // collision height
    void SetCollisionHeight(float height);
    float GetCollisionHeight() const;
        
    // maximum friction	���Ħ����ֵ
    void SetFriction(float friction);
    float GetFriction() const;
        
    // minimum velocity	��С�ٶ�
    void SetMinVelocity(float velocity);
    float GetMinVelocity() const;
        
    // maximum velocity ����ٶ�
    void SetMaxVelocity(float velocity);
    float GetMaxVelocity() const;

	// acceleration ���ٶ�
    void SetAcceleration(float acceleration);
    float GetAcceleration() const;
        
    // damping	��б
    void SetDamping(float damping);
    float GetDamping() const;
        
    // jumping ��Ծ
    void SetJumping(float jumping);
    float GetJumping() const;
  
    // view direction ���߳���
    void SetViewDirection(const MathLib::vec3 &direction);
    const MathLib::vec3 &GetViewDirection() const;
    //position λ��
    void SetPosition( const MathLib::vec3 & pos );
    const MathLib::vec3& GetPosition() const;
	



	enum {            //״̬
		STATE_FORWARD = 0,
		STATE_BACKWARD,
		STATE_MOVE_LEFT,
		STATE_MOVE_RIGHT,
		STATE_CROUCH,	//�׷�
		STATE_JUMP,
		STATE_RUN,
		NUM_STATES,
	};



};