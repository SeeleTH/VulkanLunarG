#pragma once
#include "waifu\wfmacro.h"
#include "waifu\wfos.h"

class Application
{
public:
	Application(wfOS::WindowContext winContext)
		: m_windowContext(winContext)
	{}

	virtual ~Application(){}

	virtual bool OnInit(){ return true; }
	virtual bool OnUpdate(const float elapsetime = 0.f){ return true; }
	virtual bool OnDestroy(){ return true; }
private:
	wfOS::WindowContext m_windowContext;
};