#pragma once

#include <glm/glm.hpp>

namespace Cherenkov::Maths {

	bool decomposeMat4(const glm::mat4& matrix, glm::vec3& translation, glm::vec3& rotation, glm::vec3& scale);

}
