/* Дан массив неотрицательных целых 64-битных чисел. Количество чисел не больше 1000000.
 * Отсортировать массив методом поразрядной сортировки LSD по байтам.
 */


#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <stdint.h>



//сумма байта с номером "byte"
int byte_sum(uint64_t x, int byte) {
    x = x >> (byte) * 8;
    int sum = 0;
    for (int i = 0; i < 8; ++i) {
        sum += (x & 1) * (1 << i);
        x = x >> 1;
    }

    return sum;
}


//сортировка подсчетом по конкретному байту
void lsd_sort(std::vector<uint64_t> & data, int bytes) {

    int n = data.size();
    int r = 256;

    std::vector<uint64_t> aux(n);

    for (int d = 0; d < bytes; ++d) {
        std::vector<int> count(r + 1);

        //считаем частоту
        for (int i = 0; i < n; ++i)
            count[byte_sum(data[i], d) + 1]++;

        //преобразовываем число вхождений в индексы
        for (int j = 0; j < r; ++j)
            count[j + 1] += count[j];

        //распределим по доп массиву
        for (int i = 0; i < n; ++i)
            aux[count[byte_sum(data[i], d)]++] = data[i];

        std::swap(data, aux);
    }
}



int main() {

    int n = 0;

    std::cin >> n;

    assert(n <= 1000000);

    std::vector<uint64_t> data;

    for (int i = 0; i < n; ++i) {
        uint64_t obj = 0;
        std::cin >> obj;
        data.push_back(obj);
    }

    lsd_sort(data, sizeof(uint64_t));

    for (auto & x : data) {
        std::cout << x << " ";
    }

    return 0;
}