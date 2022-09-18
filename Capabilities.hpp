
#pragma once

#include "Requirements.HPP"

static int cpuCaps() noexcept {
	int Size{ SE_0, }, Iter{ SE_0, }; ::std::bitset < 32 > Avx1{ }, Avx2{ };
	::std::vector < ::std::array < int, 4 > > Data{ }; ::std::array < int, 4 > Info{ };
	::__cpuid(Info.data(), SE_0), Size = Info[SE_0];
	for (Iter = SE_0; Iter < (Size + SE_1); Iter = (Iter + SE_1)) ::__cpuidex(Info.data(), Iter, SE_0), Data.emplace_back(Info);
	if (Size > SE_0) {
		Avx1 = Data[SE_1][SE_2]; if (Size > SE_6) Avx2 = Data[SE_7][SE_1];
	} return Avx2[SE_5] ? SE_2 : (Avx1[SE_28] ? SE_1 : SE_0);
}
