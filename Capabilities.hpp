
#pragma once

class CPUCapabilities
{
public:

    class CPUCapabilitiesInternal;

public:

    static const CPUCapabilitiesInternal CPUCapabilitiesHandler;

public:

    static constexpr __forceinline const bool hasAVX(void) noexcept
    {
        return CPUCapabilitiesHandler.m_bsAvx[SE_28];
    }

    static constexpr __forceinline const bool hasAVX2(void) noexcept
    {
        return CPUCapabilitiesHandler.m_bsAvx2[SE_5];
    }

public:

    class CPUCapabilitiesInternal
    {
    public:

        __forceinline const CPUCapabilitiesInternal(void) noexcept : \
            m_nSize{ SE_0, }, m_nIter{ SE_0, }, m_bsAvx{ SE_0, }, m_bsAvx2{ SE_0, }, m_vecData{ }, m_arrInfo{ }
        {
            ::__cpuid(m_arrInfo.data(), SE_0), m_nSize = m_arrInfo[SE_0];

            for (m_nIter = SE_0; m_nIter < (m_nSize + SE_1); m_nIter = (m_nIter + SE_1))
                ::__cpuidex(m_arrInfo.data(), m_nIter, SE_0), m_vecData.emplace_back(m_arrInfo);

            if (m_nSize > SE_0)
            {
                m_bsAvx = m_vecData[SE_1][SE_2];

                if (m_nSize > SE_6)
                    m_bsAvx2 = m_vecData[SE_7][SE_1];
            }
        }

public:

        int m_nSize{ SE_0, }, m_nIter{ SE_0, };

        ::std::bitset < 32 > m_bsAvx{ SE_0, }, m_bsAvx2{ SE_0, };

        ::std::vector < ::std::array < int, 4 > > m_vecData{ };

        ::std::array < int, 4 > m_arrInfo{ };
    };
};

const ::CPUCapabilities::CPUCapabilitiesInternal CPUCapabilities::CPUCapabilitiesHandler{ };
