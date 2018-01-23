/*Дана очень длинная последовательность целых чисел длины n.
 * Требуется вывести в отсортированном виде её наименьшие k элементов.
 * Последовательность может не помещаться в память. Время работы O(n * log(k)).
 * Доп. память O(k). Использовать слияние.
*/

#include <iostream>
#include <vector>
#include <algorithm>



void my_merge(std::vector<int> & data, std::vector<int> & result, int k) {

    std::vector<int> buffer;
    std::sort(data.begin(), data.end());

    int i = 0;
    int j = 0;

    while (i < result.size() && j < data.size()) {

        if (result[i] < data[j]) {
            buffer.push_back(result[i]);
            ++i;
        }
        else {
            buffer.push_back(data[j]);
            ++j;
        }
    }

    if (i == result.size()) {
        for (j; j < data.size(); ++j) {
            buffer.push_back(data[j]);
        }
    }
    else {

        for (i; i < result.size(); ++i) {
            buffer.push_back(result[i]);
        }
    }

    result = std::move(std::vector<int>(buffer.begin(), buffer.begin() + k));
}


//result - отсортированный массив из k чисел
int main() {

    long int n = 0;
    int k = 0;

    std::cin >> n;
    std::cin >> k;

    std::vector<int> data;
    std::vector<int> result;

    for (int i = 0; i < n; ++i) {
        int obj = 0;
        std::cin >> obj;
        data.push_back(obj);

        //считываем k символов, сортируем, мержим с result,
        //записываем в result первые k символов нового массива (полученный размер <= 2 * k)
        if ((i + 1) % k == 0 || i == n - 1) {
            my_merge(data, result, k);
            data.clear();
        }

    }

    for (int j = 0; j < result.size(); ++j)
        std::cout << result[j] << " ";


    return 0;
}