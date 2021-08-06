#pragma once
#include <Cherenkov.h>

namespace Cherenkov {

	class EntityProperties {
		Ref<Scene> m_Ctx;

	public:
		EntityProperties() = default;
		EntityProperties(const Ref<Scene>& context);

		void setContext(const Ref<Scene>& context);

		void onImGuiDraw();
		void drawAddComponents(Entity& entity);
		void drawComponents(Entity& entity);
		void drawCameraControls(Entity& camera);
	};
}
