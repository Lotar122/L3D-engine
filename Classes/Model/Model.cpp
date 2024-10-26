#include "Model.hpp"
#include "Classes/Engine/Engine.hpp"
#include "nstd/nstd.hpp"

#include <new>
#include <cstdlib>

namespace nihil::graphics {
	Model::Model(Engine* _engine, glm::mat4 _deafultTransform)
	{
		engine = _engine;
		deafultTransform = _deafultTransform;
		name = "./resources/models/cube.obj";

		obj.Load("./resources/models/cube.obj", nstd::LoadBinObj::DontCare, engine->app->screenRatio);

		vertices = obj.verticesRender;
		indices = obj.indicesRender;

		vBuffer = new (bufferArena.allocate<Buffer<float, vk::BufferUsageFlagBits::eVertexBuffer>>()) Buffer<float, vk::BufferUsageFlagBits::eVertexBuffer>(engine, vertices);
		iBuffer = new (bufferArena.allocate<Buffer<uint32_t, vk::BufferUsageFlagBits::eIndexBuffer>>()) Buffer<uint32_t, vk::BufferUsageFlagBits::eIndexBuffer>(engine, indices);
	}
	Model::Model(Engine* _engine, const std::string path, glm::mat4 _deafultTransform)
	{
		engine = _engine;
		deafultTransform = _deafultTransform;
		name = path;

		//std::cout << &engine->app->screenRatio << std::endl;
		std::cout<<"Loading the model"<<std::endl;
		obj.Load(path, nstd::LoadBinObj::DontCare, engine->app->screenRatio);
		std::cout<<"Loading Finished"<<std::endl;

		vertices = obj.verticesRender;
		indices = obj.indicesRender;

		Buffer<float, vk::BufferUsageFlagBits::eVertexBuffer>* vbp = bufferArena.allocate<Buffer<float, vk::BufferUsageFlagBits::eVertexBuffer>>();
		std::cout<<"Allocating a new vBuffer "<<vbp<<std::endl;
		vBuffer = new (vbp) Buffer<float, vk::BufferUsageFlagBits::eVertexBuffer>(engine, vertices);

		Buffer<uint32_t, vk::BufferUsageFlagBits::eIndexBuffer>* ibp = bufferArena.allocate<Buffer<uint32_t, vk::BufferUsageFlagBits::eIndexBuffer>>();
		std::cout<<"Allocating a new iBuffer "<<ibp<<std::endl;
		iBuffer = new (ibp) Buffer<uint32_t, vk::BufferUsageFlagBits::eIndexBuffer>(engine, indices);
		std::cout<<"Allocation finished"<<std::endl;
	}

	Model::~Model()
	{
		vBuffer->~Buffer();
		iBuffer->~Buffer();

		bufferArena.free();
	}

	//, Buffer<InstanceData, vk::BufferUsageFlagBits::eVertexBuffer>* _instanceBuffer

	void Model::Load(const std::string path)
	{
		obj.Load(path, nstd::LoadBinObj::DontCare, engine->app->screenRatio);

		vertices = obj.verticesRender;
		indices = obj.indicesRender;
		name = path;

		if (vBuffer != NULL && iBuffer != NULL)
		{
			vBuffer->~Buffer();
			iBuffer->~Buffer();
		}

		bufferArena.reset();

		vBuffer = new (bufferArena.allocate<Buffer<float, vk::BufferUsageFlagBits::eVertexBuffer>>()) Buffer<float, vk::BufferUsageFlagBits::eVertexBuffer>(engine, vertices);
		iBuffer = new (bufferArena.allocate<Buffer<uint32_t, vk::BufferUsageFlagBits::eIndexBuffer>>()) Buffer<uint32_t, vk::BufferUsageFlagBits::eIndexBuffer>(engine, indices);
	}
}
