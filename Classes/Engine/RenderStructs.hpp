#pragma once
#define GLM_DEPTH_ZERO_TO_ONE
#define GLM_FORCE_LEFT_HANDED
#include <glm/glm.hpp>

#pragma pack(push, 1)
	struct BigObjectData {
		glm::mat4 pre;
		glm::mat4 proj;
		glm::mat4 view;
		glm::mat4 model;
	};

	struct SmallObjectData {
		glm::mat4 pre;
		glm::mat4 proj;
	};
#pragma pack(pop)