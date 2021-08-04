#pragma once
#include <Cherenkov.h>

namespace Cherenkov {

	class EntityProperties {
		Ref<Scene> m_Ctx;

		void decomposeTransform(const glm::mat4& transform, glm::vec3& position, glm::vec3& rotation, glm::vec3& scale);
		void recalculateTransformation(glm::mat4& transform, const glm::vec3& position, glm::vec3& rotation, glm::vec3& scale);
	public:
		EntityProperties() = default;
		EntityProperties(const Ref<Scene>& context);

		void setContext(const Ref<Scene>& context);

		void onImGuiDraw();

		void drawComponents(Entity entity);
	};
}
