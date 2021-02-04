
#pragma once

class CPUCapabilities
{
public:

    class CPUCapabilitiesInternal;

    static constexpr __forceinline const bool hasAVX(void) noexcept
    {
        return CPUCapabilitiesHandler.m_bs1ECX[::std::atoi(XCS("28"))];
    }

    static constexpr __forceinline const bool hasAVX2(void) noexcept
    {
        return CPUCapabilitiesHandler.m_bs7EBX[SE_FIVE];
    }

    static const CPUCapabilitiesInternal CPUCapabilitiesHandler;

    class CPUCapabilitiesInternal
    {
    public:

        __forceinline const CPUCapabilitiesInternal(void) noexcept : \
            m_nIDs{ SE_ZERO, }, m_nIter{ SE_ZERO, }, m_bs1ECX{ SE_ZERO, }, m_bs7EBX{ SE_ZERO, }, m_vecCPUData{ }, m_arrCPUInfo{ }
        {
            ::__cpuid(m_arrCPUInfo.data(), SE_ZERO), m_nIDs = m_arrCPUInfo[SE_ZERO];

            for (m_nIter = SE_ZERO; m_nIter < m_nIDs + SE_ONE; ++m_nIter)
                ::__cpuidex(m_arrCPUInfo.data(), m_nIter, SE_ZERO), m_vecCPUData.emplace_back(m_arrCPUInfo);

            if (m_nIDs > SE_ZERO)
                m_bs1ECX = m_vecCPUData[SE_ONE][SE_TWO];

            if (m_nIDs > SE_SIX)
                m_bs7EBX = m_vecCPUData[SE_SEVEN][SE_ONE];
        }

        int m_nIDs{ SE_ZERO, }, m_nIter{ SE_ZERO, };

        ::std::bitset < 32 > m_bs1ECX{ SE_ZERO, }, m_bs7EBX{ SE_ZERO, };

        ::std::vector < ::std::array < int, 4 > > m_vecCPUData{ };

        ::std::array < int, 4 > m_arrCPUInfo{ };
    };
};

const ::CPUCapabilities::CPUCapabilitiesInternal CPUCapabilities::CPUCapabilitiesHandler{ };
