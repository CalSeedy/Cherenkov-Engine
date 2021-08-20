#include "ckpch.h"
#include "Serializer.h"

#include "Components.h"

#include <fstream>
#include <filesystem>
#include <sstream>
#include <yaml-cpp/yaml.h>

#include "../../Spectrum/src/Defaults/Defaults.h"

namespace YAML {

	template<>
	struct convert<glm::vec3> {

		static Node encode(const glm::vec3& vec) {
			Node node;
			node.push_back(vec.x);
			node.push_back(vec.y);
			node.push_back(vec.z);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec3& vec) {
			if (!node.IsSequence() || node.size() != 3) return false;

			vec.x = node[0].as<float>();
			vec.y = node[1].as<float>();
			vec.z = node[2].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec4> {

		static Node encode(const glm::vec4& vec) {
			Node node;
			node.push_back(vec.x);
			node.push_back(vec.y);
			node.push_back(vec.z);
			node.push_back(vec.w);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec4& vec) {
			if (!node.IsSequence() || node.size() != 4) return false;

			vec.x = node[0].as<float>();
			vec.y = node[1].as<float>();
			vec.z = node[2].as<float>();
			vec.w = node[3].as<float>();
			return true;
		}
	};
}



namespace Cherenkov {

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& vec) {
		out << YAML::Flow;
		out << YAML::BeginSeq << vec.x << vec.y << vec.z << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& vec) {
		out << YAML::Flow;
		out << YAML::BeginSeq << vec.x << vec.y << vec.z << vec.w << YAML::EndSeq;
		return out;
	}

	Serializer::Serializer(const Ref<Scene>& scene) :m_Scene{ scene } {}

	static void checkDir(const std::filesystem::path& path) {
		if (!(std::filesystem::exists(path.parent_path()))) std::filesystem::create_directory(path.parent_path());
	}

	template<typename T, typename Func>
	static void serializeComponent(YAML::Emitter& out, Entity& entity, const std::string& title, Func function) {
		if (entity.has<T>()) {
			out << YAML::Key << title;
			out << YAML::BeginMap;
			T& comp = entity.get<T>();
			function(out, comp);
			out << YAML::EndMap;
		}
	}

	static void serializeEntity(YAML::Emitter& out, Entity& ent) {
		out << YAML::BeginMap;
		out << YAML::Key << "Entity ID" << YAML::Value << "864872648263";

		serializeComponent<NameComp>(out, ent, "NameComp", [](YAML::Emitter& out, auto& comp) {
			out << YAML::Key << "Name" << YAML::Value << comp.Name;
		});

		serializeComponent<CameraComp>(out, ent, "CameraComp", [](YAML::Emitter& out, auto& comp) {
			out << YAML::Key << "Camera" << YAML::BeginMap;
			out << YAML::Key << "Type" << YAML::Value << (uint32_t)comp.Camera.getType();
			out << YAML::Key << "Aspect Ratio" << YAML::Value << comp.Camera.getAspectRatio();
			out << YAML::Key << "Orthographic Size" << YAML::Value << comp.Camera.getOrthographicSize();
			out << YAML::Key << "Orthographic Near" << YAML::Value << comp.Camera.getOrthographicNear();
			out << YAML::Key << "Orthographic Far" << YAML::Value << comp.Camera.getOrthographicFar();
			out << YAML::Key << "Perspective FOV" << YAML::Value << comp.Camera.getPerspectiveFOV();
			out << YAML::Key << "Perspective Near" << YAML::Value << comp.Camera.getPerspectiveNear();
			out << YAML::Key << "Perspective Far" << YAML::Value << comp.Camera.getPerspectiveFar();
			out << YAML::EndMap;

			out << YAML::Key << "Fixed" << YAML::Value << comp.fixedAspectRatio;
		});

		serializeComponent<TransformComp>(out, ent, "TransformComp", [](YAML::Emitter& out, auto& comp) {
			out << YAML::Key << "Position" << YAML::Value << comp.Position;
			out << YAML::Key << "Rotation" << YAML::Value << comp.Rotation;
			out << YAML::Key << "Scale" << YAML::Value << comp.Scale;
		});

		serializeComponent<SpriteComp>(out, ent, "SpriteComp", [](YAML::Emitter& out, auto& comp) {
			out << YAML::Key << "Colour" << YAML::Value << comp.Colour;
			//out << YAML::Key << "Texture" << YAML::Value << "None";
		});

		serializeComponent<ScriptComp>(out, ent, "ScriptComp", [](YAML::Emitter& out, auto& comp) {
			out << YAML::Key << "Name" << YAML::Value << comp.Name;
			out << YAML::Key << "Path" << YAML::Value << comp.Path.string();
			out << YAML::Key << "Language" << YAML::Value << (uint32_t)comp.Language;
			out << YAML::Key << "Instance" << YAML::Value << "86529365364595692";
		});

		out << YAML::EndMap;
	}

	void Serializer::serialize(const std::filesystem::path& path)	{
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << m_Scene->m_Name;
		std::string primary = (m_Scene->cameraCount() > 0) ? m_Scene->getPrimaryCamera().get<NameComp>().Name : "";
		out << YAML::Key << "Primary" << YAML::Value << primary;
		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
		m_Scene->m_Registry.each([&](auto entID) {
			Entity ent = { entID, m_Scene.get() };
			if (!ent) return;

			serializeEntity(out, ent);
		});
		out << YAML::EndSeq;
		out << YAML::EndMap;

		checkDir(path);
		std::ofstream fileOut(path);
		fileOut << out.c_str();
	}

	bool Serializer::deserialize(const std::filesystem::path& path) {

		YAML::Node data = YAML::LoadFile(path.string());
		if (!data["Scene"])	return false;
		std::string sceneName = data["Scene"].as<std::string>();
		CK_CORE_INFO("Deserializing scene '{0}'", sceneName);
		std::string primaryCam = data["Primary"].as<std::string>();
		bool hasSetPrimaryCam = false;
		auto& entities = data["Entities"];
		if (entities){
			for (auto& entity : entities) {
			
				uint64_t uuid = entity["Entity ID"].as<uint64_t>();
				std::string name;
				auto& nameComp = entity["NameComp"];
				if (nameComp) name = nameComp["Name"].as<std::string>();

				CK_CORE_INFO("Deserializing Entity {0}, aka: '{1}'", uuid, name);
				Entity newEntity = m_Scene->createEntity(name);
				auto& transformComp = entity["TransformComp"];
				if (transformComp) {
					auto& transform = newEntity.get<TransformComp>();
					transform.Position = transformComp["Position"].as<glm::vec3>();
					transform.Rotation = transformComp["Rotation"].as<glm::vec3>();
					transform.Scale = transformComp["Scale"].as<glm::vec3>();
				}

				auto& cameraComp = entity["CameraComp"];
				if (cameraComp) {
					auto& comp = newEntity.add<CameraComp>();
					
					auto& camera = cameraComp["Camera"];
					comp.Camera.setType((ProjectionType)camera["Type"].as<uint32_t>());
					
					auto aspect = camera["Aspect Ratio"].as<float>();
					
					auto orthoS = camera["Orthographic Size"].as<float>();
					auto orthoN = camera["Orthographic Near"].as<float>();
					auto orthoF = camera["Orthographic Far"].as<float>();
					
					auto perspFOV = camera["Perspective FOV"].as<float>();
					auto perspN = camera["Perspective Near"].as<float>();
					auto perspF = camera["Perspective Far"].as<float>();

					comp.Camera.setProperties(aspect, orthoS, orthoN, orthoF, perspFOV, perspN, perspF);
					comp.fixedAspectRatio = cameraComp["Fixed"].as<bool>();
					
					if (!hasSetPrimaryCam && !std::strcmp(primaryCam.c_str(), "")) {
						if (!std::strcmp(primaryCam.c_str(), name.c_str())) {
							m_Scene->setPrimaryCamera(newEntity);
							hasSetPrimaryCam = true;
						}
					}
				}

				auto& spriteComp = entity["SpriteComp"];
				if (spriteComp) {
					auto& comp = newEntity.add<SpriteComp>();
					comp.Colour = spriteComp["Colour"].as<glm::vec4>();
				}

				auto& scriptComp = entity["ScriptComp"];
				if (scriptComp){
					auto language = (ScriptLanguage)scriptComp["Language"].as<uint32_t>();
					auto& comp = newEntity.add<ScriptComp>(language);

					comp.Name = scriptComp["Name"].as<std::string>();
					comp.Path = std::filesystem::path(scriptComp["Path"].as<std::string>());
					
					if (!std::strcmp(comp.Path.string().c_str(), "Default_Empty")) comp.bind<EmptyScript>();
					else if (!std::strcmp(comp.Path.string().c_str(), "Default_SimpleMovement")) comp.bind<SimpleMovement>();
					else CK_CORE_ASSERT(false);
					
				}
			}
		}
		return true;
	}

	void Serializer::serializeRuntime(const std::filesystem::path& path) {
		CK_CORE_ASSERT(false, "Not implemented");
	}

	bool Serializer::deserializeRuntime(const std::filesystem::path& path) {
		CK_CORE_ASSERT(false, "Not implemented");
		return false;
	}

}
