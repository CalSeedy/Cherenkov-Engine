#pragma once
#include <filesystem>
#include "Cherenkov/Scene/SceneCamera.h"
#include "Cherenkov/Scene/ScriptableEntity.h"

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace Cherenkov {

	struct TransformComp {
		glm::vec3 Position{ 0.0f };
		glm::vec3 Rotation { 0.0f };
		glm::vec3 Scale { 1.0f };

		TransformComp() = default;
		TransformComp(const TransformComp&) = default;
		TransformComp(const glm::vec3 position) : Position{ position } {}
		TransformComp(const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale) : Position{ position }, Rotation{ rotation }, Scale{ scale } {}

		glm::mat4 getTransform() const { 
			return glm::translate(glm::mat4{ 1.0f }, Position)
				* glm::rotate(glm::mat4{ 1.0f }, Rotation.x, { 1, 0, 0 })* glm::rotate(glm::mat4{ 1.0f }, Rotation.y, { 0, 1, 0 })* glm::rotate(glm::mat4{ 1.0f }, Rotation.z, { 0, 0, 1 }) 
				* glm::scale(glm::mat4{1.0f}, Scale);
		}

		static TransformComp getDefault() { return TransformComp(); }
	};
	
	struct SpriteComp {
		glm::vec4 Colour{ 1.0f };

		SpriteComp() = default;
		SpriteComp(const SpriteComp&) = default;
		SpriteComp(const glm::vec4 rgba) : Colour{ rgba } {}
		SpriteComp(const glm::vec3 rgb) : Colour{ rgb.r, rgb.g, rgb.b, 1.0f } {}
		SpriteComp(float r, float g, float b, float a) : Colour{ r, g, b, a } {}
		SpriteComp(float r, float g, float b) : Colour{ r, g, b, 1.0f } {}

	};

	struct NameComp {
		std::string Name;

		NameComp() = default;
		NameComp(const NameComp&) = default;
		NameComp(const std::string& name) : Name{ name } {}

		operator const char* () { return Name.c_str(); }

	};

	struct CameraComp {

		Cherenkov::SceneCamera Camera;
		bool fixedAspectRatio = false;

		CameraComp() = default;
		CameraComp(const CameraComp&) = default;

	};

	enum class ScriptLanguage {
		Native,
		Cpp,
		Python
	};

	struct ScriptComp {
		
		ScriptLanguage			Language = ScriptLanguage::Native;
		ScriptableEntity*		Instance = nullptr;
		std::string				Name{ "Empty" };
		std::filesystem::path	Path{ "Default" };

		ScriptableEntity*	(*instantiateScript)();
		void				(*destroyScript)(ScriptComp*);

		ScriptComp() = default;
		ScriptComp(ScriptLanguage lang = ScriptLanguage::Native) : Language{ lang } {}

		template<typename T>
		void bind() {
			instantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			destroyScript = [](ScriptComp* script) { delete script->Instance; };
			if (std::is_same_v<T, SimpleMovement>) Path = "Default_SimpleMovement";
			else if (std::is_same_v<T, EmptyScript>) Path = "Default_Empty";
		}

		const char* getLanguage() {
			switch (Language) {
			case ScriptLanguage::Native:	return "C++";
			case ScriptLanguage::Cpp:		return "C++";
			case ScriptLanguage::Python:	return "Python";
			default:						CK_ASSERT(false, "Unknown Scipting Language") return "";
			}
		}
		operator std::filesystem::path() const { return Path; }
		operator std::string() const { return Name; }
	};


}
