/*
 Дано натуральное число N. Представить N в виде A + B, так, что НОД(A, B) максимален, A ≤ B. Вывести A и B.
 Если возможно несколько ответов - вывести ответ с минимальным A.
 n ≤ 107.
 */

#include <iostream>
#include <cassert>

//достаточно найти максимальный делитель
std::size_t max_del(std::size_t n) {

    if (n % 2 == 0) {
        return n / 2;
    }
    else {  //встретим минимальный делитель i - возвращаем n/i (максимальный делитель)
        for (std::size_t i = 2; i*i < n; ++i) {
            if (n % i == 0)
                return n / i;
        }
    }

    return 1;
}


int main() {
    std::size_t n = 0;
    std::cin >> n;

    assert(n <= 10000000);

    std::size_t res = max_del(n);

    std::cout << res << " " << n - res;

    return 0;
}