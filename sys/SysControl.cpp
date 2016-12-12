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
	g_Engine.pApp->SetMouseShow(0);			

	SetControlMode(CONTROL_KEYBORAD_MOUSE);

	m_pTest3DUI = new CObjectGui(2.0f, 1.0f, "data/core/gui/");
	m_pTest3DUI->SetMouseShow(0);		
	m_pTest3DUI->SetBackground(1);		
	m_pTest3DUI->SetBackgroundColor(vec4(1.0f, 0.0f, 0.0f, 1.0f));

	m_pTest3DUI->SetScreenSize(800, 400);
	m_pTest3DUI->SetControlDistance(1000.0f);	
	m_pTest3DUI->CreateMaterial("gui_base");	 //show in game	


	m_pTest3DUI->SetWorldTransform(Translate(0.0f, 0.0f, 2.0f) * MakeRotationFromZY(vec3(0.0f, -1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f)));

	m_pTestMessageLabel = new CWidgetLabel(m_pTest3DUI->GetGui());	//��ʼ�����ֱ�ǩ
	m_pTest3DUI->GetGui()->AddChild(m_pTestMessageLabel, CGui::ALIGN_CENTER);
	m_pTestMessageLabel->SetFontColor(vec4(0.0f, 0.0f, 0.0f, 1.0f));



	m_pTestMessageLabel->SetFontSize(80);		//���������С
	m_pTestMessageLabel->SetFontOutline(1);		//������������
	m_pTestMessageLabel->SetText("�������������\nһ�а���������\n��������ǧ��ѩ\n�Ų��������ﴬ");

	m_nOldMouseX = 0;
	m_nOldMouseY = 0;
}


