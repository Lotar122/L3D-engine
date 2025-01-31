#pragma once

#include "nstd/nstd.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vulkan/vulkan.hpp>
#include "Classes/Buffer/Buffer.hpp"

#include "nstd/headers/Memory.hpp"

namespace nihil::graphics {
	class Engine;

	class Model 
	{
	public:
		std::vector<float> vertices;
		std::vector<uint32_t> indices;

		glm::mat4 deafultTransform;

		Engine* engine;

		std::string name = "";
		uint32_t deafultPipeline = 0;
		uint32_t instancedPipeline = 0;
		uint32_t index = 0;

		nstd::OBJ obj;

		nstd::MemoryArena bufferArena = nstd::MemoryArena(
			nstd::CombinedSize<
				Buffer<float, vk::BufferUsageFlagBits::eVertexBuffer>,
				Buffer<uint32_t, vk::BufferUsageFlagBits::eIndexBuffer>
			>::value + 8
		);

		Buffer<float, vk::BufferUsageFlagBits::eVertexBuffer>* vBuffer = NULL;
		Buffer<uint32_t, vk::BufferUsageFlagBits::eIndexBuffer>* iBuffer = NULL;

		Model(Engine* _engine, glm::mat4 _deafultTransform = glm::mat4(1.0f));

		Model(Engine* _engine, const std::string path, glm::mat4 _deafultTransform = glm::mat4(1.0f));

		~Model();

		void Load(const std::string path);

		inline void setInstancedPipeline(uint32_t _pipeline) { instancedPipeline = _pipeline; }
		inline void setDeafultPipeline(uint32_t _pipeline) { deafultPipeline = _pipeline; }
	};
}