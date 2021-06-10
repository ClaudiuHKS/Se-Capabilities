
#pragma once

class CPUCapabilities
{
public:

    class CPUCapabilitiesInternal;

    static constexpr __forceinline const bool hasAVX(void) noexcept
    {
        return CPUCapabilitiesHandler.m_bs1ECX[SE_28];
    }

    static constexpr __forceinline const bool hasAVX2(void) noexcept
    {
        return CPUCapabilitiesHandler.m_bs7EBX[SE_5];
    }

    static const CPUCapabilitiesInternal CPUCapabilitiesHandler;

    class CPUCapabilitiesInternal
    {
    public:

        __forceinline const CPUCapabilitiesInternal(void) noexcept : \
            m_nIDs{ SE_0, }, m_nIter{ SE_0, }, m_bs1ECX{ SE_0, }, m_bs7EBX{ SE_0, }, m_vecCPUData{ }, m_arrCPUInfo{ }
        {
            ::__cpuid(m_arrCPUInfo.data(), SE_0), m_nIDs = m_arrCPUInfo[SE_0];

            for (m_nIter = SE_0; m_nIter < (m_nIDs + SE_1); m_nIter = (m_nIter + SE_1))
                ::__cpuidex(m_arrCPUInfo.data(), m_nIter, SE_0), m_vecCPUData.emplace_back(m_arrCPUInfo);

            if (m_nIDs > SE_0)
                m_bs1ECX = m_vecCPUData[SE_1][SE_2];

            if (m_nIDs > SE_6)
                m_bs7EBX = m_vecCPUData[SE_7][SE_1];
        }

        int m_nIDs{ SE_0, }, m_nIter{ SE_0, };

        ::std::bitset < 32 > m_bs1ECX{ SE_0, }, m_bs7EBX{ SE_0, };

        ::std::vector < ::std::array < int, 4 > > m_vecCPUData{ };

        ::std::array < int, 4 > m_arrCPUInfo{ };
    };
};

const ::CPUCapabilities::CPUCapabilitiesInternal CPUCapabilities::CPUCapabilitiesHandler{ };
