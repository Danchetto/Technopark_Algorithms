// Напишите программу, печатающую набор строк в лексикографическом порядке.


#include <iostream>
#include <vector>
#include <cstring>
#include <functional>
#include <cassert>



//сравнение строк по лексиграфическому отношению порядка
struct string_compare {

    bool operator()(const std::string & obj1, const std::string & obj2) {

        if (obj2.size() < obj1.size())
            return false;

        for (int i = 0; i < obj1.size(); ++i) {

            if (obj1[i] > obj2[i])
                return false;
            if (obj1[i] < obj2[i])
                return true;
        }

        return true;
    }
};


//сортировка вставками
void my_sort(std::vector<std::string> & data, std::function<bool(std::string, std::string)> compare) {

    for (int i = 1; i < data.size(); ++i) {
        for (int j = i - 1; j >= 0 ; --j) {
            if (compare(data[j + 1], data[j]))
                std::swap(data[j + 1], data[j]);
        }
    }
}



int main() {

    std::string n_str;
    getline(std::cin, n_str);

    int n = atoi(n_str.c_str());

    assert(n <= 1000);

    std::vector<std::string> data;

    for (int i = 0; i < n; ++i) {

        std::string obj;
        getline(std::cin, obj);
        data.push_back(obj);
    }

    my_sort(data, string_compare());

    for (auto & x : data) {
        std::cout << x << std::endl;
    }

    return 0;
}