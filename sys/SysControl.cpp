#include "SysControl.h"
#include "ControlsApp.h"

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
}