#ifndef __SYS_CONTROL_H__
#define __SYS_CONTROL_H__

class CSysControl	//�����
{
public:
	// ״̬
	enum {					
		STATE_FORWARD = 0,	//��ǰ
		STATE_BACKWARD,		//���
		STATE_MOVE_LEFT,	//�����ƶ�
		STATE_MOVE_RIGHT,	//�����ƶ�
		STATE_TURN_UP,		//����ת
		STATE_TURN_DOWN,	//����ת
		STATE_TURN_LEFT,	//����ת
		STATE_TURN_RIGHT,	//����ת
		STATE_CROUCH,		//��
		STATE_JUMP,			//��
		STATE_RUN,			//��
		STATE_USE,			
		STATE_FIRE,			//����
		STATE_SAVE,			//����
		STATE_RESTORE,		//�ָ�
		STATE_SCREENSHOT,	//��Ļ����
		STATE_AUX_0,		//�����豸
		STATE_AUX_1,
		STATE_AUX_2,
		STATE_AUX_3,
		STATE_AUX_4,
		STATE_AUX_5,
		STATE_AUX_6,
		STATE_AUX_7,
		STATE_AUX_8,
		STATE_AUX_9,
		STATE_AUX_A,
		STATE_AUX_B,
		STATE_AUX_C,
		STATE_AUX_D,
		STATE_AUX_E,
		STATE_AUX_F,
		NUM_STATES,			
	};
	enum ControlMode		//����ģʽ��ֻ�м����pad���ַ�ʽ
	{
		CONTROL_KEYBORAD_MOUSE,
		CONTROL_XPAD360,
	};
private:

}