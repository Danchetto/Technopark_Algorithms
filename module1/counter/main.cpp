/*
 * “Считалочка”. В круг выстроено N человек, пронумерованных числами от 1 до N.
 * Будем исключать каждого k-ого до тех пор, пока не уцелеет только один человек.
 * (Например, если N=10, k=3, то сначала умрет 3-й, потом 6-й, затем 9-й, затем 2-й, затем 7-й,
 * потом 1-й, потом 8-й, за ним - 5-й, и потом 10-й. Таким образом, уцелеет 4-й.)
 * Необходимо определить номер уцелевшего.
 * N, k ≤ 10000.
 */

#include <iostream>
#include <cmath>
#include <cassert>


struct Node {
    int number;
    Node * next;

    Node(int n) : number(n),next(nullptr) {}
};

class List {

public:
    Node * head;
    Node * tail;
    std::size_t size;

    List() : head(nullptr), tail(nullptr), size(0) {}

    void push(int n) {

        auto new_node = new Node(n);

        if (size == 0) {
            head = new_node;
            tail = new_node;
        }

        else {
            tail->next = new_node;
            tail = tail->next;
        }

        tail->next = head;

        size++;
    }


    int remove(Node * obj) {

        if (obj == tail)
            head = head->next;

        if (obj->next == tail)
            tail = obj;



        auto buf = obj->next;
        obj->next = obj->next->next;
        buf->next = nullptr;

        int result = buf->number;

        delete obj->next;

        --size;

        return result;
    }


    void print() {
        for (auto it = head; it != tail ; it = it->next) {
            std::cout << it->number << " ";
        }

        std::cout << tail->number << std::endl;
    }


};

int get_alive(List & data, int k) {
    auto it = data.head;
    int counter = 0;
    while (data.size > 1) {

        counter++;

        if (counter == k - 1) {
//            data.remove(it);
            it->next = it->next->next;
            data.size--;
            counter = 0;
        }

        it = it->next;
    }

//    return data.head->number;
    return it->number;
}



int main() {

    int n, k;
    std::cin >> n >> k;

    assert(0 < n <= 10000 && 0 < k <= 10000);

    List data;

    for (int i = 0; i < n; ++i) {
        data.push(i + 1);
    }

    std::cout << get_alive(data, k);

    return 0;
}