#pragma once

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <thread>

namespace Cherenkov {

	struct ProfileResult {
		std::string Name;
		long long	Start, End;
		uint32_t	Thread;
	};

	struct InstSession {
		std::string Name;
	};

	class Instrumentor {
		InstSession* m_Session;
		std::ofstream m_Output;
		int m_Count;

	public:
		Instrumentor() : m_Session{ nullptr }, m_Count{ 0 } {
			
		}

		void begin(const std::string& name, const std::string& filepath = "results.json") {
			m_Output.open(filepath);
			writeHeader();
			m_Session = new InstSession{ name };
		}

		void end() {
			writeFooter();
			m_Output.close();
			delete m_Session;
			m_Session = nullptr;
			m_Count = 0;
		}

		void writeProfile(const ProfileResult& result) {
			if (m_Count++ > 0) m_Output << ", ";

			std::string name = result.Name;
			std::replace(name.begin(), name.end(), '"', '\'');

			m_Output << "{";
			m_Output << "\"cat\":\"function\",";
			m_Output << "\"dur\":" << (result.End - result.Start) << ',';
			m_Output << "\"name\":\"" << name << "\",";
			m_Output << "\"ph\":\"X\",";
			m_Output << "\"pid\":0,";
			m_Output << "\"tid\":" << result.Thread << ',';
			m_Output << "\"ts\":" << result.Start;
			m_Output << "}";
			
			m_Output.flush();
		}

		void writeHeader() {
			m_Output << "{\"other\":{},\"traceEvents\": [";
			m_Output.flush();
		}

		void writeFooter() {
			m_Output << "]}";
			m_Output.flush();
		}

		static Instrumentor& get() {
			static Instrumentor instance;
			return instance;
		}
	};

	class Timer {
		const char* m_Name;
		std::chrono::time_point<std::chrono::steady_clock> m_Start;
		bool m_Stopped;

	public:
		Timer(const char* name) : m_Name{ name }, m_Stopped{ false } {
			m_Start = std::chrono::high_resolution_clock::now();
		}

		~Timer() {
			if (!m_Stopped) stop();
		}

		void stop() {
			auto end = std::chrono::high_resolution_clock::now();

			long long start_milliseconds = std::chrono::time_point_cast<std::chrono::microseconds>(m_Start).time_since_epoch().count();
			long long end_milliseconds = std::chrono::time_point_cast<std::chrono::microseconds>(end).time_since_epoch().count();

			uint32_t tID = std::hash<std::thread::id>{}(std::this_thread::get_id());
			Instrumentor::get().writeProfile({ m_Name, start_milliseconds, end_milliseconds, tID });
			//float_t duration = (end_milliseconds - start_milliseconds) * 0.001f;
			//std::cout << "[" << m_Name << "] Duration: " << duration << "ms\n";
			m_Stopped = true;
		}
	};
}

#define CK_PROFILE 1
#if CK_PROFILE
#define CK_PROFILE_BEGIN(name, filepath) ::Cherenkov::Instrumentor::get().begin(name, filepath)
#define CK_PROFILE_END() ::Cherenkov::Instrumentor::get().end()
#define CK_PROFILE_SCOPE(name) ::Cherenkov::Timer timer##__LINE__(name);
#define CK_PROFILE_FUNCTION() CK_PROFILE_SCOPE(__FUNCSIG__)
#else
#define CK_PROFILE_BEGIN(name, filepath)
#define CK_PROFILE_END()
#define CK_PROFILE_SCOPE(name)
#define CK_PROFILE_FUNCTION()
#endif