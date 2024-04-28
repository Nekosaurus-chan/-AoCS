#include <iostream>
#include <mmintrin.h>

#pragma GCC target("mmx")

int main()
{
    __m64 a = _mm_set_pi8(8, 7, 6, 5, 4, 3, 2, 1);
    __m64 b = _mm_set_pi8(-1, -2, -3, -4, -5, -6, -7, -8);
    __m64 cHigh = _mm_set_pi16(-8, -7, -6, -5);
    __m64 cLow = _mm_set_pi16(-4, -3, -2, -1);
    __m64 dHighHigh = _mm_set_pi32(1, 2);
    __m64 dHighLow = _mm_set_pi32(3, 4);
    __m64 dLowHigh = _mm_set_pi32(5, 6);
    __m64 dLowLow = _mm_set_pi32(7, 8);

    // F[i] = (A[i] + B[i]) * C[i] - D[i]
    // 1. A[i] + B[i]
    __m64 res = _mm_adds_pi8(a, b);
    int8_t* resArray = (int8_t*)&res;
    __m64 resLow = _mm_set_pi16(resArray[3], resArray[2], resArray[1], resArray[0]);
    __m64 resHigh = _mm_set_pi16(resArray[7], resArray[6], resArray[5], resArray[4]);

    // 2. (A[i] + B[i]) * C[i]
    // Low
    __m64 resMulLowLowHigh = _mm_mulhi_pi16(resLow, cLow);
    __m64 resMulLowLowLow = _mm_mullo_pi16(resLow, cLow);
    __m64 resLowLow = _mm_unpacklo_pi16(resMulLowLowLow, resMulLowLowHigh);
    __m64 resLowHigh = _mm_unpackhi_pi16(resMulLowLowLow, resMulLowLowHigh);

    // High
    __m64 resMulHighLowHigh = _mm_mulhi_pi16(resHigh, cHigh);
    __m64 resMulHighLowLow = _mm_mullo_pi16(resHigh, cHigh);
    __m64 resHighLow = _mm_unpacklo_pi16(resMulHighLowLow, resMulHighLowHigh);
    __m64 resHighHigh = _mm_unpackhi_pi16(resMulHighLowLow, resMulHighLowHigh);

    // 3. (A[i] + B[i]) * C[i] - D[i]
    __m64 resFinalLowLow = _mm_sub_pi32(resLowLow, dLowLow);
    __m64 resFinalLowHigh = _mm_sub_pi32(resLowHigh, dLowHigh);
    __m64 resFinalHighLow = _mm_sub_pi32(resHighLow, dHighLow);
    __m64 resFinalHighHigh = _mm_sub_pi32(resHighHigh, dHighHigh);

    // Output
    int32_t* arrLowLow = (int32_t*)&resFinalLowLow;
    int32_t* arrLowHigh = (int32_t*)&resFinalLowHigh;
    int32_t* arrHighLow = (int32_t*)&resFinalHighLow;
    int32_t* arrHighHigh = (int32_t*)&resFinalHighHigh;

    std::cout << "Result:\n";

    for (size_t i = 0; i < 2; i++)
    {
        std::cout << arrLowLow[i] << " " << arrLowHigh[i] << " " << arrHighLow[i] << " " << arrHighHigh[i] << " ";
    }

    std::cout << std::endl;
    return 0;
}