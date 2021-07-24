#pragma once

namespace Cherenkov {
	class Timestep {
		float_t m_Time;

	public:
		Timestep(float_t time = 0.0f) : m_Time{ time } {

		}

		operator float() const { return m_Time; }

		float_t getSeconds() const { return m_Time; }
		float_t getMilliseconds() const { return m_Time * 1000.0f; }
		float_t toFPS() const { return 1.0f / m_Time; }
		
	};

}