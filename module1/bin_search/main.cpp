/*
  Дан отсортированный массив различных целых чисел A[0..n-1] и массив целых чисел B[0..m-1].
  Для каждого элемента массива B[i] найдите минимальный индекс элемента массива A[k], ближайшего по значению к B[i].
  Время работы поиска для каждого элемента B[i]: O(log(k)).
  n ≤ 110000, m ≤ 1000.
 */

#include <iostream>
#include <cassert>

//бинарный поиск с заданными границами
int search(int * data, int begin, int end, int obj) {

    while (begin < end - 1) {
        int middle = (end + begin) / 2;

        if (obj > data[middle]) {
            begin = middle;
        }
        else {
            if (obj < data[middle]) {
                end = middle;
            }
            else {
                return middle;
            }
        }
    }

    //поиск ближайшего соседнего, когда осталось 2 элемента
    if (abs(data[begin] - obj) <= abs(data[end] - obj))
        return begin;
    else
        return end;
}


//поиск большей границы в заданном массиве
int find_edge(int * data, int n, int obj) {

    int end = 1;

    if (data[0] >= obj)
        return 0;

    while (data[end] < obj) {
        end *= 2;
        if (end > n)
            return n - 1;
    }

    return end;
}


int main() {

    int n = 0;
    std::cin >> n;
    assert(n > 0 && n <= 110000);

    auto data = new int [n];
    for (int i = 0; i < n; ++i) {
        std::cin >> data[i];
    }

    int m;
    std::cin >> m;
    assert(m > 0 && m <= 1000);

    //результат записываем в массив
    int * result = new int[m];

    //для каждого элемента из B находим границы и выполняем бинарный поиск
    for (int j = 0; j < m; ++j) {
        int b = 0;
        std::cin >> b;

        int end = find_edge(data, n, b);
        result[j] = search(data, end / 2, end, b);
    }

    for (int k = 0; k < m; ++k) {
        std::cout << result[k] << " ";
    }

    delete[] data;
    delete[] result;

    return 0;
}