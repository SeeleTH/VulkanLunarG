#pragma once
#include "application.h"

#include <vulkan\vulkan.h>

#include "waifu\wfmacro.h"
#include "waifu\wfassert.h"

template <typename T>
class VDeleter{

};

class VulkanApp : public Application
{
public:
	VulkanApp(wfOS::WindowContext winContext);

	virtual ~VulkanApp();

	virtual bool OnInitialize();
	virtual bool OnUpdate(const float elapsetime = 0.f);
	virtual bool OnDestroy();
private:
};