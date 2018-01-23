/* На числовой прямой окрасили N отрезков. Известны координаты левого и правого концов каждого отрезка (Li и Ri).
 * Найти сумму длин частей числовой прямой, окрашенных ровно в один слой.
 * */


#include <iostream>
#include <vector>
#include <functional>


//структура хранения координат - пара {значение координаты; true -> начало отрезка / false -> конец отрезка}
using vector_t = std::vector<std::pair<int, bool>>;


//сравнение пар по значению координат
struct key_compare {

    bool operator()(const std::pair<int, bool> &obj1, const std::pair<int, bool> &obj2) {

        bool result = obj1.first < obj2.first;
        return result;
    }
};



void sift_down(vector_t & data, int size, int index,
               std::function<bool(std::pair<int, bool>, std::pair<int, bool>)> key_compare) {

    int left = 2 * index + 1;
    int right = 2 * index + 2;

    int smallest = index;
    if (left < size && key_compare(data[index], data[left]))
        smallest = left;

    if (right < size && key_compare(data[smallest], data[right]))
        smallest = right;

    if (smallest != index) {
        std::swap(data[index], data[smallest]);
        sift_down(data, size, smallest, key_compare);
    }
}



void build_heap(vector_t & data, int size,
                std::function<bool(std::pair<int, bool>, std::pair<int, bool>)> key_compare) {

    for (int i = size / 2 - 1; i >= 0 ; --i) {
        sift_down(data, size, i, key_compare);
    }
}



void pyramid_sort(vector_t & data, int n,
                  std::function<bool(std::pair<int, bool>, std::pair<int, bool>)> key_compare) {

    build_heap(data, n, key_compare);

    for (int i = n - 1; i > 0; --i) {
        std::swap(data[0], data[i]);
        sift_down(data, i, 0, key_compare);
    }
}



int main() {

    int n = 0;
    std::cin >> n;
    vector_t data;
    for (int i = 0; i < n; ++i) {
        int a, b = 0;
        std::cin >> a >> b;

        data.push_back(std::pair<int, bool>(a, true));

        data.push_back(std::pair<int, bool>(b, false));
    }


    pyramid_sort(data, 2 * n, key_compare());


    int result = 0;
    int counter = 1;

    for (int j = 1; j < 2 * n; ++j) {
        if (counter == 1)
            result += data[j].first - data[j - 1].first;
        if (data[j].second)
            counter++;
        else
            counter--;
    }

    std::cout << result;

    return 0;
}