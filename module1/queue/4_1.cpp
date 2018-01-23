//Реализовать очередь с динамическим зацикленным буфером.

#include <iostream>
#include <cassert>

class Queue {

public:
    int head;
    int tail;

    int size;
    int max_size;

    Queue() : size(0), max_size(0), head(0), tail(-1) {}

    Queue(int n) : size(0), max_size(n), head(0), tail(-1) {

        data = new int[n];
    }

    Queue(Queue & obj) = delete;

    Queue(Queue && obj) = delete;

    ~Queue() {
        if (data)
            delete[] data;
    }



    void push(int obj) {

        if (size == max_size)
            resize();

        tail = (tail + 1) % max_size;

        data[tail] = obj;

        size++;
    }


    int pop() {

        if (size == 0)
            return -1;

        size--;

        if (head == tail) {
            tail = head - 1;
            return data[head];
        }

        int result = data[head];

        head = (head + 1) % max_size;

        return result;
    }

private:

    int * data;

    void resize() {

        if (max_size == 0) {
            max_size = 2;
            data = new int[max_size];
            return;
        }

        else {
            max_size *= 2;
        }

        //копирование данных в буфер
        int * buf = new int[size];
        for (int i = 0; i < size; ++i) {
            buf[i] = data[i];
        }

        delete[] data;
        data = new int[max_size];

        //перезаписывание данных из буфера
        if (tail > head) {
            for (int i = head; i <= tail; ++i) {
                data[i] = buf[i];
            }
        }

        else {
            head += size;
            for (int i = 0; i <= tail; ++i) {
                data[i] = buf[i];
            }

            for (int i = head; i < max_size; ++i) {
                data[i] = buf[i - size];
            }

        }

        delete[] buf;
    }

};

int main() {
    std::size_t n;
    std::cin >> n;

    assert(0 < n <= 1000000);

    bool result = true;

    Queue q;

    for (int i = 0; i < n; ++i) {
        int a = 0;
        int b = 0;
        std::cin >> a >> b;

        if (a == 3) {
            q.push(b);
        }

        if (a == 2) {
            if (q.pop() != b)
                result = false;
        }

    }

    if (result)
        std::cout << "YES";
    else
        std::cout << "NO";

    return 0;
}