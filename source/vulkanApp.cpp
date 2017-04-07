#include "vulkanApp.h"

VulkanApp::VulkanApp(wfOS::WindowContext winContext) 
	: Application(winContext)
{

}

VulkanApp::~VulkanApp()
{

}

bool VulkanApp::OnInit()
{
	if (!createInstance())
		return false;

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

template<typename T>
const char* GetInstancePropertiesName(const T& obj)
{
	return "";
}

template<>
const char* GetInstancePropertiesName(const VkExtensionProperties& obj)
{
	return obj.extensionName;
}

template<>
const char* GetInstancePropertiesName(const VkLayerProperties& obj)
{
	return obj.layerName;
}

template<typename T>
bool checkExtension(std::vector<T> avails, std::vector<const char*> checks)
{
	for (const char* check : checks)
	{
		bool found = false;
		for (VkExtensionProperties avail : avails)
		{
			if (strcmp(check, GetInstancePropertiesName<T>(avail)) == 0)
			{
				found = true;
				break;
			}
		}
		if (!found)
			return false;
	}
	return true;
}

bool VulkanApp::createInstance()
{
	uint32 extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
	std::vector<VkExtensionProperties> extensions(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
	std::cout << "available vulkan extension: " << std::endl;
	for (const auto& extension : extensions)
	{
		std::cout << "\t" << extension.extensionName << std::endl;
	}

	std::vector<const char*> needExtensions = { 
		VK_KHR_SURFACE_EXTENSION_NAME,
		VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
		VK_EXT_DEBUG_REPORT_EXTENSION_NAME };
	if (!checkExtension(extensions, needExtensions))
	{
		wfOS::CreateMessageBox("Required extensions unavailable", "Vulkan::createInstance()", wfOS::MSGBOX_OK);
		return false;
	}

	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Vulkan with LunarG";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledExtensionCount = needExtensions.size();
	createInfo.ppEnabledExtensionNames = needExtensions.data();
	createInfo.enabledLayerCount = 0;

	if (vkCreateInstance(&createInfo, nullptr, instance.replace()) != VK_SUCCESS)
	{
		wfOS::CreateMessageBox("Create instance failure", "Vulkan::createInstance()", wfOS::MSGBOX_OK);
		return false;
	}

	WFDEB_COUT("Instance created");

	return true;
}
