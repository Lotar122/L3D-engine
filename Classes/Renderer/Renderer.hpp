#pragma once

#include <iostream>
#include "Classes/Engine/Engine.Structs.InData.hpp"
#include "nihil-standard/nstd.hpp"
#include "Classes/Buffer/Buffer.hpp"

namespace nihil::graphics {
	class Engine;
	class Scene;

	class Renderer {
		friend class Engine;
	public:
		Renderer(Engine* _engine);
		~Renderer();

		//Draw
		void Draw();

		nstd::OBJ* objobject;
	private:
		/*
		* @brief Creates a swapchain
		*
		* @param createInfo - config creation info
		* @return inforamtion to create the swapchain
		*/
		SwapchainConfiguration CreateSwapchainConfiguration(SwapchainConfigCreateInfo createInfo);
		/*
		* @brief Creates a swapchain
		*
		* @param createInfo - information for the creation of the swapchain
		* @return None
		*/
		void CreateSwapchain(SwapchainConfiguration createInfo);
		/*
		* @brief Creates a swapchain
		*
		* @param createInfo - inforamtion to create the swapchain
		* @return None
		*/
		void CreateImageViews();
		//sets up the basic pipeline
		void PipelineSetup();
		//creates the shader module
		void CreateShaderModule(std::string filepath, vk::Device device, vk::ShaderModule** ppShaderModule);
		//records draw commands
		void recordDrawCommands(vk::CommandBuffer& commandBuffer, uint32_t imageIndex);
		//destroy the swapchain
		void destroySwapchain();
		//create the flow-control
		void createSyncObjects();
		//create framebuffers
		void createFrameBuffers();
		//create depthbuffers
		void createDepthBuffers();
		//make frame commandbuffers
		void createFrameCommandBuffers();
		//make main commandbuffer
		void createMainCommandBuffer();
		//make commandpools
		void createCommandPools();
		//reacreate swapchain
		void RecreateSwapchain();

		uint32_t findMemoryType(uint32_t typeFilter, vk::MemoryPropertyFlags properties);

		QueueFamilyIndices famind;
		std::vector<uint32_t> uniqueFAMIND;

		vk::Queue graphicsQueue;
		vk::Queue presentQueue;

		SwapChainSupportDetails support;
		vk::SurfaceFormatKHR surfaceFormat;
		vk::PresentModeKHR presentMode;
		vk::SwapchainCreateInfoKHR swapCreateInfo;

		std::vector<vk::AttachmentDescription> renderPassAttachments;

		SwapChainBundle swapchainBundle{};

		uint32_t imageCount;

		vk::ShaderModule* vertexShader = NULL;
		vk::ShaderModule* fragmentShader = NULL;

		vk::PipelineLayout layout;
		vk::RenderPass renderPass;
		vk::Pipeline pipeline;

		vk::CommandPool commandPool;
		vk::CommandBuffer commandBuffer;

		vk::Viewport viewport = {};
		vk::Rect2D scissor = {};

		uint32_t maxFramesInFlight, frameNumber;

		Engine* engine;

		//VertexBuffer
		Buffer<float, vk::BufferUsageFlagBits::eVertexBuffer>* vertexBuffer;
		Buffer<uint32_t, vk::BufferUsageFlagBits::eIndexBuffer>* indexBuffer;

		SwapchainConfiguration swapchainConfiguration;
	};
}