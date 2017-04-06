#include "vulkanApp.h"

VulkanApp::VulkanApp(wfOS::WindowContext winContext) 
	: Application(winContext)
{

}

VulkanApp::~VulkanApp()
{

}

bool VulkanApp::OnInitialize()
{
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	std::cout << extensionCount << " extensions supported" << std::endl;

	return true;
}

bool VulkanApp::OnUpdate(const float elapsetime)
{
	return true;
}

bool VulkanApp::OnDestroy()
{
	return true;
}