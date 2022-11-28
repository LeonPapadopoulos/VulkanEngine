//#pragma once
////#include <vulkan/vulkan_core.h>
//#define GLFW_INCLUDE_VULKAN
//#include <GLFW/glfw3.h>
//
//#include <vector>
//
//namespace Vulkan {
//
//	VkInstance instance{};
//	VkDebugUtilsMessengerEXT debugMessenger{};
//
//#ifdef NDEBUG
//	const bool enableValidationLayers = false;
//#else
//	const bool enableValidationLayers = true;
//#endif
//
//	const std::vector<const char*> validationLayers = {
//		"VK_LAYER_KHRONOS_validation"
//	};
//
//	void createInstance();
//	bool checkValidationLayerSupport();
//	std::vector<const char*> getRequiredExtensions();
//	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& debugCreateInfo);
//	VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
//	
//	void setupDebugMessenger();
//	VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
//}
