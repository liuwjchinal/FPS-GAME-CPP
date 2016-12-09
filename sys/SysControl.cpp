#include "SysControl.h"
#include "ControlsApp.h"
#include "ControlsXPad360.h"

//�����ƽ̨�ַ�����������
#ifdef _WIN32
#pragma execution_character_set("utf-8")
#endif

using namespace MathLib;

class CSysControlLocal : public CSysControl
{
public:
	CSysControlLocal();
    virtual ~CSysControlLocal();

	virtual void Init();	//��ɫҪ��ʼ������ɫ��Ҫ��ʼ����
	virtual void Update(float ifps);
	virtual void Shutdown();

	virtual int GetState(int state);		//���״̬������״̬������״̬���ӵ�״̬�ȵȡ�
	virtual int ClearState(int state);

	virtual float GetMouseDX();
	virtual float GetMouseDY();

	virtual void SetMouseGrab(int g);		//�����Ƿ���ʾ���
	virtual int GetMouseGrab();			//��ȡ���״̬������ʾ�ػ��ǲ���ʾ��״̬��


	virtual void SetControlMode(ControlMode mode);			//����ģʽ
	virtual ControlMode GetControlMode() const;				//��ȡ����ģʽ

private:
	void Update_Mouse(float ifps);

}