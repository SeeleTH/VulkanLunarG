#include "wftime.h"
#include "wfos.h"

namespace wfTime
{
	FrameTimer::FrameTimer()
		: m_u64CurTime(0ULL)
		, m_u64LastTime(0ULL)
		, m_u64CurMicros(0ULL)
		, m_u64DeltaMicros(0ULL)
		, m_f32DeltaFloat(0.f)
	{
		int64 countsPerSec = wfOS::GetOSPerfFreq();
		m_dSecondsPerCount = 1.0 / (double)countsPerSec;
		m_u64LastRealTime = wfOS::GetOSPerfCount();
	}

	void FrameTimer::Update(bool bUpdateVirtual)
	{
		UINT64 u64TimeNow = wfOS::GetOSPerfCount();
		UINT64 u64Delta = u64TimeNow - m_u64LastRealTime;
		m_u64LastRealTime = u64TimeNow;

		UpdateBy(u64Delta, bUpdateVirtual);
	}

	void FrameTimer::UpdateBy(uint64 u64Ticks, bool bUpdateVirtual)
	{
		m_u64LastTime = m_u64CurTime;
		m_u64CurTime += u64Ticks;

		UINT64 u64LastMicros = m_u64CurMicros;
		m_u64CurMicros = static_cast<UINT64>(m_u64CurTime * (m_dSecondsPerCount * 1000000ULL));
		m_u64DeltaMicros = m_u64CurMicros - u64LastMicros;
		m_f32DeltaFloat = m_u64DeltaMicros * static_cast<float>(1.0 / 1000000.0);
	}
}