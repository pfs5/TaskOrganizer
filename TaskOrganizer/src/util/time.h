#pragma once

namespace Time
{
	inline int64_t GetCurrentTimeMilli()
	{
		auto now = std::chrono::system_clock::now().time_since_epoch();
		auto nowMilli = std::chrono::duration_cast<std::chrono::milliseconds>(now);
		return nowMilli.count();
	}
}