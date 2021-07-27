#pragma once

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <thread>

namespace Cherenkov {

	using FloatMicroseconds = std::chrono::duration<double, std::micro>;

	struct ProfileResult {
		std::string					Name;
		FloatMicroseconds			Start;
		std::chrono::microseconds	Elapsed;
		std::thread::id				Thread;
	};

	struct InstSession {
		std::string Name;
	};

	class Instrumentor {
		std::mutex m_Mutex;
		std::ofstream m_Output;
		InstSession* m_Session;

		void writeHeader() {
			m_Output << "{\"other\":{},\"traceEvents\": [{}";
			m_Output.flush();
		}

		void writeFooter() {
			m_Output << "]}";
			m_Output.flush();
		}

		void internalEnd() {
			if (m_Session) {
				writeFooter();
				m_Output.close();
				delete m_Session;
				m_Session = nullptr;
			}
		}

	public:
		Instrumentor() : m_Session{ nullptr } {}

		void begin(const std::string& name, const std::string& filepath = "results.json") {

			std::lock_guard lock(m_Mutex);
			if (m_Session) {
				if (Log::getCoreLogger()) {
					CK_CORE_ERROR("Intrumentor::begin('{0}') called whilst another session ('{1}') is open.", name, m_Session->Name);
				}
				internalEnd();
			}
			m_Output.open(filepath);
			if (m_Output.is_open()) {
				m_Session = new InstSession{ name };
				writeHeader();
			} else {
				if (Log::getCoreLogger()) {
					CK_CORE_ERROR("Instrumentor could not open file '{0}'", filepath);
				}
			}
		}

		void end() {
			std::lock_guard lock(m_Mutex);
			internalEnd();	
		}

		void writeProfile(const ProfileResult& result) {
			std::stringstream json;

			std::string name = result.Name;
			std::replace(name.begin(), name.end(), '"', '\'');

			json << std::setprecision(3) << std::fixed;
			json << ",{";
			json << "\"cat\":\"function\",";
			json << "\"dur\":" << result.Elapsed.count() << ',';
			json << "\"name\":\"" << name << "\",";
			json << "\"ph\":\"X\",";
			json << "\"pid\":0,";
			json << "\"tid\":" << result.Thread << ",";
			json << "\"ts\":" << result.Start.count();
			json << "}";

			std::lock_guard lock(m_Mutex);
			if (m_Session) {
				m_Output << json.str();
				m_Output.flush();
			}
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
			m_Start = std::chrono::steady_clock::now();
		}

		~Timer() {
			if (!m_Stopped) stop();
		}

		void stop() {
			auto end = std::chrono::steady_clock::now();
			auto start = FloatMicroseconds{ m_Start.time_since_epoch() };
			auto elapsed = std::chrono::time_point_cast<std::chrono::microseconds>(end).time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(m_Start).time_since_epoch();

			Instrumentor::get().writeProfile({ m_Name, start, elapsed, std::this_thread::get_id() });
			//float_t duration = (end_milliseconds - start_milliseconds) * 0.001f;
			//std::cout << "[" << m_Name << "] Duration: " << duration << "ms\n";
			m_Stopped = true;
		}
	};

	namespace InstrumentorUtils {

		template <size_t N>
		struct ChangeResult
		{
			char Data[N];
		};

		template <size_t N, size_t K>
		constexpr auto cleanupOutput(const char(&expr)[N], const char(&remove)[K])
		{
			ChangeResult<N> result = {};

			size_t srcIndex = 0;
			size_t dstIndex = 0;
			while (srcIndex < N)
			{
				size_t matchIndex = 0;
				while (matchIndex < K - 1 && srcIndex + matchIndex < N - 1 && expr[srcIndex + matchIndex] == remove[matchIndex])
					matchIndex++;
				if (matchIndex == K - 1)
					srcIndex += matchIndex;
				result.Data[dstIndex++] = expr[srcIndex] == '"' ? '\'' : expr[srcIndex];
				srcIndex++;
			}
			return result;
		}
	}
}

#define CK_PROFILE 1
#if CK_PROFILE
	#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
		#define CK_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__DMC__) && (__DMC__ >= 0x810)
		#define CK_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__FUNCSIG__) || (_MSC_VER)
		#define CK_FUNC_SIG __FUNCSIG__
	#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
		#define CK_FUNC_SIG __FUNCTION__
	#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
		#define CK_FUNC_SIG __FUNC__
	#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
		#define CK_FUNC_SIG __func__
	#elif defined(__cplusplus) && (__cplusplus >= 201103)
		#define CK_FUNC_SIG __func__
	#else
	#define CK_FUNC_SIG "CK_FUNC_SIG unknown!"
	#endif

	#define CK_PROFILE_BEGIN(name, filepath) ::Cherenkov::Instrumentor::get().begin(name, filepath)
	#define CK_PROFILE_END() ::Cherenkov::Instrumentor::get().end()
	#define CK_PROFILE_SCOPE(name) constexpr auto fixedName = ::Cherenkov::InstrumentorUtils::cleanupOutput(name, "__cdecl "); ::Cherenkov::Timer timer##__LINE__(fixedName.Data)
	#define CK_PROFILE_FUNCTION() CK_PROFILE_SCOPE(CK_FUNC_SIG)
#else
	#define CK_PROFILE_BEGIN(name, filepath)
	#define CK_PROFILE_END()
	#define CK_PROFILE_SCOPE(name)
	#define CK_PROFILE_FUNCTION()
#endif