#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <optional>
#include <set>
#include <cstdint> // Necessary for uint32_t (but works without??)
#include <limits> // Necessary for std::numeric_limits
#include <algorithm> // Necessary for std::clamp
#include <chrono>
#include <array>
#include <unordered_map>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"
#include "Scene.h"
#include "Vertex.h"

namespace VulkanEngine {

	struct FrameData {



	};
	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool isComplete() {
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};
	struct SwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	const uint32_t WIDTH = 1920;//800;
	const uint32_t HEIGHT = 1080;// 600;

	const int MAX_FRAMES_IN_FLIGHT = 2;

	const std::vector<const char*> validationLayers = {
	"VK_LAYER_KHRONOS_validation"
	};

	const std::vector<const char*> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif

	class VKEngine {

	public:
		void run();

	private:

		#pragma region MEMBERS
		///////////////////////////////////
		///////////* EXTERNAL *////////////
		///////////////////////////////////
		Scene* m_Scene;
		Camera* m_Camera;


		///////////////////////////////////
		//////////* GLFW GLOBAL *//////////
		///////////////////////////////////
		GLFWwindow* m_Window;

		///////////////////////////////////
		/////* VULKAN STANDARD SETUP */////
		///////////////////////////////////
		VkInstance m_Instance;
		VkDebugUtilsMessengerEXT m_DebugMessenger;
		VkSurfaceKHR m_Surface;

		VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
		VkDevice m_Device; // LogicalDevice

		VkQueue m_GraphicsQueue;
		VkQueue m_PresentQueue;

		// Swap chain Images
		VkSwapchainKHR m_SwapChain;
		std::vector<VkImage> m_SwapChainImages;
		VkFormat m_SwapChainImageFormat;
		VkExtent2D m_SwapChainExtent;
		std::vector<VkImageView> m_SwapChainImageViews;
		std::vector<VkFramebuffer> m_SwapChainFramebuffers;

		VkRenderPass m_RenderPass;

		// Images that make up individual frames in the SwapChain
		VkImage m_ColorImage;
		VkDeviceMemory m_ColorImageMemory;
		VkImageView m_ColorImageView;
		VkImage m_DepthImage;
		VkDeviceMemory m_DepthImageMemory;
		VkImageView m_DepthImageView;

		// Synchronization Tools
		std::vector<VkSemaphore> m_ImageAvailableSemaphores;
		std::vector<VkSemaphore> m_RenderFinishedSemaphores;
		std::vector<VkFence> m_InFlightFences;

		VkCommandPool m_CommandPool;
		std::vector<VkCommandBuffer> m_CommandBuffers;
		
		uint32_t m_CurrentFrame = 0;
		bool m_FramebufferResized = false;

		VkSampleCountFlagBits m_MsaaSamples = VK_SAMPLE_COUNT_1_BIT;



		//////////////////////////////////
		/////* VULKAN MESH SPECIFIC */////
		//////////////////////////////////

		VkDescriptorPool m_DescriptorPool; // Holds all descriptors; eg. 10x uniformbuffers, 3x images
		VkDescriptorSetLayout m_DescriptorSetLayout; // Shader-Dependent // Describes what kind of Descriptors make up a DSet; e.g. DSetLayout(DSet1) = 1x ubo & 1x image, with ubo binding = 0 and image binding = 1

		// GLOBAL SHADER DATA - e.g. Camera
		std::vector<VkBuffer> m_UniformBuffers;
		std::vector<VkDeviceMemory> m_UniformBuffersMemory;
		std::vector<void*> m_UniformBuffersMapped;
		#pragma endregion

		void initWindow();
		static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

		void initVulkan();
		void mainLoop();
		void cleanup(); //-> Dependent on specific Draw Circumstances ; e.g. PipelineLayout
		///////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////

		///////////////////////////////////
		/////* VULKAN STANDARD SETUP */////
		///////////////////////////////////

#pragma region VULKAN STANDARD SETUP

		void createInstance();
		void pickPhysicalDevice();
		void createLogicalDevice();
		void createSurface();
		void createSwapChain(const VkPhysicalDevice& physicalDevice, const VkDevice& logicalDevice, const VkSurfaceKHR& surface, VkFormat& swaphChainImageFormat, VkExtent2D& swapChainExtent, std::vector<VkImage>& swapChainImages, VkSwapchainKHR& swapChain);
		void createImageViews(const VkDevice& logicalDevice, const VkFormat& swapChainImageFormat, const std::vector<VkImage>& swapChainImages, std::vector<VkImageView>& swapChainImageViews);
		void createRenderPass(const VkPhysicalDevice& physicalDevice, const VkDevice& logicalDevice, const VkFormat& swapChainImageFormat, const VkSampleCountFlagBits& msaaSamples, VkRenderPass& renderPass);
		void createColorResources(const VkDevice& logicalDevice, const VkFormat& swapChainImageFormat, const VkExtent2D& swapChainExtent, const VkSampleCountFlagBits& msaaSamples, VkImageView& colorImageView, VkImage& colorImage, VkDeviceMemory& colorImageMemory);
		void createDepthResources(const VkPhysicalDevice& physicalDevice, const VkDevice& logicalDevice, const VkExtent2D& swapChainExtent, const VkSampleCountFlagBits& msaaSamples, VkImageView& depthImageView, VkImage& depthImage, VkDeviceMemory& depthImageMemory);
		void createFramebuffers(const VkDevice& logicalDevice, const std::vector<VkImageView>& swapChainImageViews, const VkImageView& colorImageView, const VkImageView& depthImageView, const VkRenderPass& renderpass, const VkExtent2D& swapChainExtent, std::vector<VkFramebuffer>& swapChainFramebuffers);
		void createCommandPool(const VkPhysicalDevice& physicalDevice, const VkDevice& logicalDevice, VkCommandPool& commandPool);
		void createSyncObjects(const VkDevice& logicalDevice, const int& maxFramesInFlight, std::vector<VkSemaphore>& imageAvailableSemaphores, std::vector<VkSemaphore>& renderFinishedSemaphores, std::vector<VkFence>& inFlightFences);

#pragma endregion
		

		//////////////////////////////////
		/////* VULKAN SPECIFIC SETUP *////
		//////////////////////////////////
		
#pragma region VULKAN SPECIFIC SETUP

		void createDescriptorSetLayout(const VkDevice& logicalDevice, VkDescriptorSetLayout& descriptorSetLayout);
		void createGraphicsPipeline(const VkDevice& logicalDevice, const VkPrimitiveTopology primitiveTopology, const std::vector<char>& vertShaderCode, const std::vector<char>& fragShaderCode, VkSampleCountFlagBits msaaSamples, const VkDescriptorSetLayout& descriptorSetLayout, const VkRenderPass& renderPass, VkPipelineLayout& pipelineLayout, VkPipeline& graphicsPipeline);
		void createTextureImage(const VkDevice& logicalDevice, const VkCommandPool& commandPool, const std::string& texturePath, uint32_t& mipLevels, VkDeviceMemory& textureImageMemory, VkImage& textureImage);
		void createTextureImageView(const VkDevice& logicalDevice, const VkImage& textureImage, const uint32_t& mipLevels, VkImageView& textureImageView);
		void createTextureSampler(const VkPhysicalDevice& physicalDevice, const VkDevice& logicalDevice, const uint32_t& mipLevels, VkSampler& textureSampler);
		/* LOAD MODEL(s) */
		void createVertexBuffer(const VkDevice& logicalDevice, const VkCommandPool& commandPool, const std::vector<Vertex>& vertices, VkBuffer& vertexBuffer, VkDeviceMemory& vertexBufferMemory);
		void createIndexBuffer(const VkDevice& logicalDevice, const VkCommandPool& commandPool, const std::vector<uint32_t>& indices, VkBuffer& indexBuffer, VkDeviceMemory& indexBufferMemory);
		void createUniformBuffers(const VkDevice& logicalDevice, const int& maxFramesInFlight, VkDeviceSize bufferSize, std::vector<VkBuffer>& uniformBuffers, std::vector<VkDeviceMemory>& uniformBuffersMemory, std::vector<void*>& uniformBuffersMapped);
		void createDescriptorPool(const VkDevice& logicalDevice, const int& maxFramesInFlight, VkDescriptorPool& descriptorPool);
		void createDescriptorSets(const VkDevice& logicalDevice, const int& maxFramesInFlight, const VkDescriptorSetLayout& descriptorSetLayout, const VkDescriptorPool& descriptorPool, const std::vector<VkBuffer>& uniformBuffersGLOBAL, const std::vector<VkBuffer>& uniformBuffersMODEL, const VkImageView& textureImageView, const VkSampler& textureSampler, std::vector<VkDescriptorSet>& descriptorSets);
		void createCommandBuffers(const VkDevice& logicalDevice, const int& maxFramesInFlight, const VkCommandPool& commandPool, std::vector<VkCommandBuffer>& commandBuffers);

		// CUSTOM
		void createUniformBuffersCamera();
		void createUniformBuffersScene(Scene& scene);
		void createTextureDescriptors(Scene& scene);
		void createDescriptorSetsScene(Scene& scene);
		void createVertexIndexBufferSceneModels(Scene& scene);
		void createGraphicsPipelinesScene(Scene& scene);

#pragma endregion


		/////////////////////////////////
		/////////* RENDER LOOP */////////
		/////////////////////////////////

#pragma region RENDER LOOP

		void drawFrame();
			void recreateSwapChain(const VkPhysicalDevice& physicalDevice, const VkDevice& logicalDevice, const VkSurfaceKHR& surface, VkFormat& swapChainImageFormat, VkExtent2D& swapChainExtent, std::vector<VkImage>& swapChainImages, std::vector<VkImageView>& swapChainImageViews, VkSwapchainKHR& swapChain);
			void updateUniformBufferGLOBAL(uint32_t currentImage);
			void updateUniformBufferMODEL(Scene& scene, uint32_t currentImage);
			void recordCommandBuffer(const VkCommandBuffer& commandBuffer, uint32_t imageIndex);
			void drawScene(Scene& scene, const VkCommandBuffer& commandBuffer);
			
#pragma endregion


		////////////////////////////////
		///////* HELPER METHODS *///////
		////////////////////////////////
		
#pragma region HELPER METHODS
		// DEFAULT VULKAN SETUP
		void setupDebugMessenger();
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
		bool checkValidationLayerSupport();
		std::vector<const char*> getRequiredExtensions();
		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
		bool isDeviceSuitable(VkPhysicalDevice device);
		QueueFamilyIndices findQueueFamilies(const VkPhysicalDevice& device);
		bool checkDeviceExtensionSupport(VkPhysicalDevice device);
		SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
		VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
		
		// CUSTOM VULKAN SETUP
		// const
		VkShaderModule createShaderModule(const VkDevice& logicalDevice, const std::vector<char>& code) const;
		VkImageView createImageView(const VkDevice& logicalDevice, const VkImage image, const VkFormat format, const VkImageAspectFlags aspectFlags, const uint32_t& mipLevels) const;

		VkFormat findSupportedFormat(const VkPhysicalDevice& physicalDevice, const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
		VkFormat findDepthFormat(const VkPhysicalDevice& physicalDevice);
		VkCommandBuffer beginSingleTimeCommands(const VkDevice& logicalDevice, const VkCommandPool& commandPool);
		uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
		VkSampleCountFlagBits getMaxUsableSampleCount();
		bool hasStencilComponent(VkFormat format);

		void generateMipmaps(const VkDevice& logicalDevice, const VkCommandPool& commandPool, VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);
		void createImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits numSample, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
		void transitionImageLayout(const VkDevice& logicalDevice, const VkCommandPool& commandPool, VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);
		void copyBuffer(const VkDevice& logicalDevice, const VkCommandPool& commandPool, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
		void copyBufferToImage(const VkDevice& logicalDevice, const VkCommandPool& commandPool, VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
		void endSingleTimeCommands(VkCommandBuffer commandBuffer);
		void createBuffer(const VkDevice& logicalDevice, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
		
		void cleanupSwapChain();
#pragma endregion

	};

}
