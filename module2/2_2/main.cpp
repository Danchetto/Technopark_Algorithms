/*
 * Для сложения чисел используется старый компьютер. Время, затрачиваемое на нахождение суммы двух чисел равно их сумме.
 * Таким образом для нахождения суммы чисел 1,2,3 может потребоваться разное время, в зависимости от порядка вычислений.
 * ((1+2)+3) -> 1+2 + 3+3 = 9 ((1+3)+2) -> 1+3 + 4+2 = 10 ((2+3)+1) -> 2+3 + 5+1 = 11
 * Требуется написать программу, которая определяет минимальное время, достаточное для вычисления суммы заданного набора чисел.
 * */



#include <iostream>
#include <vector>


class Heap {

public:
    std::vector<int> data;

    friend std::ostream& operator<<(std::ostream& out, const Heap & obj);

    Heap() {}

    Heap(const std::vector<int> & obj) :  data(obj) {
        build_heap();
    }

    Heap(const Heap & obj) = delete;

    Heap(const Heap && obj) = delete;

    void sift_up(int index);

    int my_sum();

    int extract_min();

    ~Heap() {}


private:
    void build_heap();
    void sift_down(int index);
};



void Heap::sift_down(int index) {

    int left = 2 * index + 1;
    int right = 2 * index + 2;

    int smallest = index;
    if (left < data.size() && data[left] < data[index])
        smallest = left;

    if (right < data.size() && data[right] < data[smallest])
        smallest = right;

    if (smallest != index) {
        std::swap(data[index], data[smallest]);
        sift_down(smallest);
    }
}



void Heap::sift_up(int index) {

    while (index > 0) {
        int parent = (index - 1 ) / 2;

        if (data[index] >= data[parent])
            return;

        std::swap(data[index], data[parent]);
        index = parent;
    }
}



void Heap::build_heap() {

    for (int i = data.size() / 2 - 1; i >= 0 ; --i) {
        sift_down(i);
    }
}



int Heap::extract_min() {

    int buf = data[0];
    if (data.size() > 0)
        data.erase(data.begin());

    build_heap();

    return buf;
}


//вытаскиваем 2 мин элемента, сумму добавляем к результату и добавляем в кучу
int Heap::my_sum() {

    int result = 0;

    while (data.size() > 1) {

        int buf = extract_min();
        buf += extract_min();
        result += buf;

        if (data.size() == 0)
            break;

        data.push_back(buf);
        sift_up(data.size() - 1);
    }

    return result;
}



std::ostream& operator<<(std::ostream &out, const Heap & obj) {

    for (auto & item : obj.data)
        out << item << " ";

    return out;
}



int main() {

    int n = 0;

    std::cin >> n;

    std::vector<int> data;

    for (int i = 0; i < n; ++i) {
        int obj = 0;
        std::cin >> obj;
        data.push_back(obj);
    }

    Heap q(data);

    std::cout << q.my_sum();

    return 0;
}