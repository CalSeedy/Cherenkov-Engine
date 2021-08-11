#pragma once
#include "Cherenkov/Core/Input.h"

#include "Cherenkov/Scene/ScriptableEntity.h"
#include "Cherenkov/Scene/Components.h"

namespace Cherenkov {

	class SimpleMovement : public ScriptableEntity {
	public:
		void onCreate() {
		}

		void onDestroy() {

		}

		void onUpdate(Timestep dt) {
			float speed = 5.0f;
			bool hasTransform = has<TransformComp>();
			if (hasTransform) {
				auto& transform = get<TransformComp>();

				if (Input::isKeyPressed(Key::W)) {
					transform.Position.y += speed * dt;
				}
				else if (Input::isKeyPressed(Key::S)) {
					transform.Position.y -= speed * dt;
				}
				if (Input::isKeyPressed(Key::A)) {
					transform.Position.x -= speed * dt;
				}
				else if (Input::isKeyPressed(Key::D)) {
					transform.Position.x += speed * dt;
				}
			}
		}

	};

	class EmptyScript : public ScriptableEntity {
	public:
		void onCreate() {
		}

		void onDestroy() {

		}

		void onUpdate(Timestep dt) {
		}

	};

}
