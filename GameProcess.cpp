#include "GameProcess.h"
#include "Object.h"
#include "Engine.h"
#include "World.h"
#include "App.h"
#include "ToolsCamera.h"
#include "ControlsApp.h"
#include "MathLib.h"
#include "Game.h"
#include "Editor.h"



using namespace MathLib;

CGameProcess::CGameProcess(void)
{

}

CGameProcess::~CGameProcess(void)
{

}
int CGameProcess::Init()
{
	g_Engine.pFileSystem->CacheFilesFormExt("char");
	g_Engine.pFileSystem->CacheFilesFormExt("node");
	g_Engine.pFileSystem->CacheFilesFormExt("smesh");
	g_Engine.pFileSystem->CacheFilesFormExt("sanim");

	g_Engine.pWorld->LoadWorld("data/scene/terrain/test/test.world");
	//g_Engine.pWorld->LoadWorld("data/scene/terrain/cj/cj.world"); 
	g_Engine.pControls->SetKeyPressFunc(KeyPress);
	g_Engine.pControls->SetKeyReleaseFunc(KeyRelease);

	m_pRole = new CFPSRoleLocal();
	m_pRole->Init(10001, "data/role/hero/FpsRole/fps.char");		//���ؽ�ɫ��Դ

	m_pRole->SetActorPosition(vec3(0, 0, 0));	//���ý�ɫ��ʼλ�á����Ŵ���Ϊԭ�㣬��ά����ϵvec3������
	m_pSkillSystem = new CSkillSystem(this);
	m_pCameraBase = new CCameraBase();
	m_pCameraBase->SetEnabled(1);
	g_pSysControl->SetMouseGrab(1);

	m_pStarControl = new CStarControl();
	m_pRayControl = new CRayControl();

	return 1;
}

int CGameProcess::ShutDown()			//�ر���Ϸ����
{
	delete m_pRole;
	delete m_pSkillSystem;
	delete m_pCameraBase;
	delete m_pStarControl;
	delete m_pRayControl;

	DelAllListen(); 
	return 0;
}

int CGameProcess::Update()
{

	return 0;
}
