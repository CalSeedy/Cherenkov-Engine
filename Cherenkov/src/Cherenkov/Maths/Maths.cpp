#include "ckpch.h"
#include "Maths.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>

namespace Cherenkov::Maths {

	bool decomposeMat4(const glm::mat4& matrix, glm::vec3& translation, glm::vec3& rotation, glm::vec3& scale) {
		
		using namespace glm;

		mat4 localMatrix(matrix);

		if (epsilonEqual(localMatrix[3][3], static_cast<float>(0), epsilon<float>())) return false;

		if ( epsilonNotEqual(localMatrix[0][3], static_cast<float>(0), epsilon<float>()) || epsilonNotEqual(localMatrix[1][3], static_cast<float>(0), epsilon<float>()) || epsilonNotEqual(localMatrix[2][3], static_cast<float>(0), epsilon<float>())) {
		
			localMatrix[0][3] = localMatrix[1][3] = localMatrix[2][3] = static_cast<float>(0);
		}

		translation = vec3(localMatrix[3]);
		localMatrix[3] = vec4(0, 0, 0, localMatrix[3].w);

		vec3 Row[3];

		for (length_t i = 0; i < 3; ++i)
			for (length_t j = 0; j < 3; ++j)
				Row[i][j] = localMatrix[i][j];

		scale.x = length(Row[0]);
		Row[0] = detail::scale(Row[0], static_cast<float>(1));
		scale.y = length(Row[1]);
		Row[1] = detail::scale(Row[1], static_cast<float>(1));
		scale.z = length(Row[2]);
		Row[2] = detail::scale(Row[2], static_cast<float>(1));

		rotation.y = asin(-Row[0][2]);
		if (cos(rotation.y) != 0) {
			rotation.x = atan2(Row[1][2], Row[2][2]);
			rotation.z = atan2(Row[0][1], Row[0][0]);
		} else {
			rotation.x = atan2(-Row[2][0], Row[1][1]);
			rotation.z = 0;
		}

		return true;
	}
}
