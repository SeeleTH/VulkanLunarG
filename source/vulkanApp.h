#pragma once
#include "application.h"

#include <string>
#include <vector>
#include <functional>

#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan\vulkan.h>

#include "waifu\wfmacro.h"
#include "waifu\wfassert.h"

template <typename T>
class VDeleter{
public:
	VDeleter() : VDeleter([](T, VkAllocationCallbacks*){}) {}

	VDeleter(std::function<void(T, VkAllocationCallbacks*)> deletef)
	{
		this->deleter = [=](T obj){ deletef(obj, nullptr); };
	}
	VDeleter(const VDeleter<VkInstance>& instance, std::function<void(VkInstance, T, VkAllocationCallbacks*)> deletef)
	{
		this->deleter = [&instance, deletef](T obj){ deletef(instance, obj, nullptr); };
	}
	VDeleter(const VDeleter<VkDevice>& device, std::function<void(VkDevice, T, VkAllocationCallbacks*)> deletef)
	{
		this->deleter = [&device, deletef](T obj) { deletef(device, obj, nullptr); };
	}

	~VDeleter()
	{
		cleanup();
	}

	const T* operator &() const 
	{
		return &object;
	}

	T* replace()
	{
		cleanup();
		return &object;
	}

	operator T() const
	{
		return object;
	}

	void operator=(T rhs)
	{
		if (rhs != object)
		{
			cleanup();
			object = rhs;
		}
	}

	template<typename V>
	bool operator==(V rhs)
	{
		return object == T(rhs);
	}

private:
	T object{ VK_NULL_HANDLE };
	std::function<void(T)> deleter;

	void cleanup()
	{
		if (object != VK_NULL_HANDLE)
		{
			deleter(object);
		}
		object = VK_NULL_HANDLE;
	}
};

class VulkanApp : public Application
{
public:
	VulkanApp(wfOS::WindowContext winContext);

	virtual ~VulkanApp();

	virtual bool OnInit();
	virtual bool OnUpdate(const float elapsetime = 0.f);
	virtual bool OnDestroy();
private:
	bool createInstance();

	VDeleter<VkInstance> instance{ vkDestroyInstance };
};