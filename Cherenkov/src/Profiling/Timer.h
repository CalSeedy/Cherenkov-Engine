#pragma once
#include <chrono>
#include <iostream>

namespace Cherenkov {

	template<typename Fn>
	class Timer {
		const char* m_Name;
		std::chrono::time_point<std::chrono::steady_clock> m_Start;
		bool m_Stopped;
		Fn m_Func;

	public:
		Timer(const char* name, Fn&& func) : m_Name{ name }, m_Func{ func }, m_Stopped{ false } {
			m_Start = std::chrono::high_resolution_clock::now();
		}

		~Timer() {
			if (!m_Stopped) stop();
		}

		void stop() {
			auto end = std::chrono::high_resolution_clock::now();

			long long start_milliseconds = std::chrono::time_point_cast<std::chrono::microseconds>(m_Start).time_since_epoch().count();
			long long end_milliseconds = std::chrono::time_point_cast<std::chrono::microseconds>(end).time_since_epoch().count();

			m_Stopped = true;
			float_t duration = (end_milliseconds - start_milliseconds) * 0.001f;
 			//std::cout << "[" << m_Name << "] Duration: " << duration << "ms\n";
			m_Func({ m_Name, duration });
		}
	};
} 

#define PROFILE_SCOPE(name) Cherenkov::Timer timer##__LINE__(name, [&](ProfileResult result) {m_Results.push_back(result); })