#pragma once
#include "wfmacro.h"

namespace wfTime
{
	class FrameTimer
	{
	public:
		FrameTimer();

		void Update(bool bUpdateVirtual = true);
		void UpdateBy(uint64 u64Ticks, bool bUpdateVirtual = true);

		uint64 GetCurMicros() const { return m_u64CurMicros; }
		uint64 GetDeltaMicros() const { return m_u64DeltaMicros; }
		float GetDeltaFloat() const { return m_f32DeltaFloat; }

	protected:
		double   m_dSecondsPerCount;
		uint64   m_u64CurTime;
		uint64   m_u64LastTime;
		uint64   m_u64LastRealTime;

		uint64   m_u64CurMicros;
		uint64   m_u64DeltaMicros;
		float    m_f32DeltaFloat;
	};
}