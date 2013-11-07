#pragma once

#include <memory>
#include "../defines.h"

namespace star
{
	class ScaleSystem
	{
	public:
		~ScaleSystem();

		static std::shared_ptr<ScaleSystem> GetInstance();
		void SetWorkingResolution(int xPixels, int yPixels);
		void SetWorkingResolution(const vec2& pixels);
		const vec2& GetWorkingResolution() const;
		const vec2& GetActualResolution() const;
		float GetScale();
		float GetAspectRatio();
		void CalculateScale();

	private:
		ScaleSystem();

		vec2 m_WorkingRes;
		float m_Scale;
		float m_AspectRatio;
		bool m_bIninitialized;

		static std::shared_ptr<ScaleSystem> m_ScaleSystemPtr;
	};
}
