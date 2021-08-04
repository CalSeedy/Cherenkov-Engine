#pragma once
#include <Cherenkov.h>

namespace Cherenkov {

	class SceneHierarchy {
		Ref<Scene> m_Ctx;
	public:
		SceneHierarchy() = default;
		SceneHierarchy(const Ref<Scene>& context);

		void setContext(const Ref<Scene>& context);

		void onImGuiDraw();

		void drawEntityNode(Entity entity);
	};
}
