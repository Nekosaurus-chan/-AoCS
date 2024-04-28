#include <iostream>
#include <emmintrin.h>

int main() {
    // Исходные массивы A, B, C и D
    __int8_t A[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    __int8_t B[8] = {2, 3, 4, 5, 6, 7, 8, 9};
    __int8_t C[8] = {3, 4, 5, 6, 7, 8, 9, 10};
    __int16_t D[8] = {10, 20, 30, 40, 50, 60, 70, 80};

    // Результаты будут сохранены в массиве F
    __int16_t F[8];

    // Цикл для обработки каждого элемента массива
    for (int i = 0; i < 8; ++i) {
        __m128i a = _mm_cvtsi32_si128(A[i]); // Загрузка A[i] в MMX регистр
        __m128i b = _mm_cvtsi32_si128(B[i]); // Загрузка B[i] в MMX регистр
        __m128i c = _mm_cvtsi32_si128(C[i]); // Загрузка C[i] в MMX регистр
        __m128i d = _mm_cvtsi32_si128(D[i]); // Загрузка D[i] в MMX регистр

        // Вычисление (A[i] + B[i]) * C[i]
        __m128i temp = _mm_mullo_epi16(_mm_adds_epi16(a, b), c);

        // Вычисление (A[i] + B[i]) * C[i] - D[i]
        __m128i result = _mm_subs_epi16(temp, d);

        // Сохранение результата в массив F
        F[i] = _mm_cvtsi128_si32(result);
    }

    // Вывод результатов
    std::cout << "Результаты выражения (A[i] + B[i]) * C[i] - D[i]:" << std::endl;
    for (int i = 0; i < 8; ++i) {
        std::cout << "F[" << i << "] = " << static_cast<int>(F[i]) << std::endl;
    }

    return 0;
}
