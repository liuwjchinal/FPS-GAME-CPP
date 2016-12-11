#include "SysControl.h"
#include "ControlsApp.h"
#include "ControlsXPad360.h"
#include "Engine.h"
#include "App.h"


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
	void Update_Keyboard(float ifps);
	void Update_XPad360(float ifps);


	CControlsApp        *m_pControlsApp;		//������Ϸ���ƶ�
	CControlsXPad360    *m_pControlsXPad360;
	ControlMode         m_nControlMode;			//����ģʽ
	
	int                 m_nOldMouseX;			//��һ���������X
	int                 m_nOldMouseY;			//��һ���������Y

	CObjectGui          *m_pTest3DUI;
	CWidgetLabel        *m_pTestMessageLabel;




};



CSysControlLocal::CSysControlLocal()
{

}
CSysControlLocal::~CSysControlLocal()
{

}

void CSysControlLocal::Init()
{
	m_pControlsApp = new CControlsApp;
	m_pControlsXPad360 = new CControlsXPad360(0);


	g_Engine.pApp->SetMouseGrab(0);
	g_Engine.pApp->SetMouseShow(0);			//�Ƿ�����Ϸ��ʱ����ʾ��꣬�����Ƿ�

	m_nOldMouseX = 0;
	m_nOldMouseY = 0;
}


