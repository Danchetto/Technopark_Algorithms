/* k-порядковая статистика, выбор пивота методом медиана трех, проход итераторов с конца массива
 * */


#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>


//получение пивота по методу медиана трех
int median_3(std::vector<int> & data, int left, int right)
{

    std::vector<std::pair<int, int>> arr = {std::pair<int, int>(left, data[left]),
                                            std::pair<int, int>((right + left - 1) / 2, data[(right + left - 1) / 2]),
                                            std::pair<int, int>(right - 1, data[right - 1])};

    std::sort(arr.begin(), arr.end(), [](std::pair<int, int> x, std::pair<int, int> y) {return x.second < y.second;});

    return arr[1].first;
}



int partition(std::vector<int> & data, int left, int right) {

    assert(left < right);

    int pivot_pos = median_3(data, left, right);
    std::swap(data[pivot_pos], data[left]);
    const int& pivot = data[left];

    if (left == right - 1)
        return left;

    int i = right - 1;

    for (; data[i] > pivot && i > left; --i) {}

    int j = i;

    while (j > left) {

        for (; data[j] <= pivot && j > left; --j) {}

        if (j > left) {
            std::swap(data[j], data[i]);
            --j;
            --i;
        }
        else {
            break;
        }
    }

    std::swap(data[i], data[left]);

    return i;
}



int k_stat(std::vector<int> & data, int k) {

    assert(k >= 0 && k < static_cast<int>(data.size()));

    int left = 0;
    int right = static_cast<int>(data.size()); //не включая right

    while(true) {

        int pivot_pos = partition(data, left, right);

        if (pivot_pos == k)
            return data[k];

        if (pivot_pos > k)
            right = pivot_pos;
        else
            left = pivot_pos + 1;
    }
}

int main() {

    int n = 0;
    int k = 0;
    std::cin >> n >> k;

    std::vector<int> data(n);

    for (int i = 0; i < n; ++i)
        std::cin >> data[i];

    std::cout << k_stat(data, k);

    return 0;
}