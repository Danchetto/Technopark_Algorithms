#include <iostream>
#include <cstring>
#include <stdexcept>
#include <cassert>


class Stack {

private:
    int head;
    int max_size;

    void resize() {
        max_size *= 2;
        auto * buf = new char[size];
        for (int i = 0; i < size; ++i) {
            buf[i] = data[i];
        }

        delete[] data;
        data = new char[max_size];


        for (int i = head; i <= tail; ++i) {
            data[i] = buf[i];
        }

        delete[] buf;
    }

public:
    int tail;
    char * data;
    int size;

    Stack() : size(0), max_size(5), head(0), tail(0) {

        data = new char[5];
    }

    Stack(int n) : size(0), max_size(n), head(0), tail(0) {

        data = new char[n];
    }

    ~Stack() {
        delete[] data;
    }



    void push(char obj) {
//        empty queue
        if (size == 0) {
            size++;
            data[tail] = obj;
            data[head] = obj;
            return;
        }

//        need to allocate more memory
        if (size == max_size)
            resize();
        tail++;

        data[tail] = obj;

        size++;
    }


    char pop() {

        if (size == 0)
            return 0;
        size--;

        if (head == tail)
            return data[head];

        char result = data[tail];

        tail--;

        return result;
    }


    char top () {

        if (size == 0)
            return 0;

        if (head == tail)
            return data[head];

        return data[tail];

    }


    void print() {

        int i = head;
        int s = size;

        while (s > 0) {
            std::cout << data[i];
            ++i;
            --s;
        }

    }


    void reverse_print() {

        int i = tail;
        int s = size;

        while (s > 0) {
            std::cout << data[i];
            --i;
            --s;
        }
    }
};


//интерфейс для обработки последовательностей
class Container {

private:
    bool correct = true;    //состояние последовательности
    Stack stack, before, after;     //3 стэка для составления конечной последовательности
    std::string input;
    std::string brackets = "()[]{}";
    int break_pos = -1;     //позиция, на которой состояние входной последовательности стало некорректным

    //проверка символа перед добавлением в стэк
    void check_symbol(char obj) {

        char pair = brackets[brackets.find_first_of(obj) - 1];

        if (stack.top() == pair) {
            stack.pop();
            if (stack.size + 1 == break_pos + 1) {
                correct = true;
                break_pos = -1;
            }
        }
        else {
            stack.push(obj);
            if (correct)
                before.push(pair);
            else
                throw std::invalid_argument("IMPOSSIBLE");
        }
    }

public:
    Container() = delete;

    Container(Container & obj) = delete;

    Container(Container && obj) = delete;

    Container(std::string input_str) : input(input_str) {}

    //проверка входной послеовательности посимвольно
    bool check() {
        for (int i = 0; i < input.size(); ++i) {

            switch (input[i]) {
                case '}': {
                    check_symbol('}');
                    break;
                }

                case ']' : {
                    check_symbol(']');
                    break;
                }

                case ')' : {
                    check_symbol(')');
                    break;
                }

                default:
                    stack.push(input[i]);
                    if (correct)
                        break_pos = stack.size - 1;
                    correct = false;
                    break;
            }
        }
    }

    
    void make_after() {
        int it = stack.tail;
        int j = stack.size;
        while (j > 0) {
            switch (stack.data[it]) {

                case '{': {
                    after.push('}');
                    break;
                }

                case '[' : {
                    after.push(']');
                    break;
                }

                case '(' : {
                    after.push(')');
                    break;
                }
            }
            --it;
            --j;
        }
    }


    void print() {
        before.reverse_print();
        std::cout << input;
        after.print();
    }


    ~Container() {}
};


int main() {

    std::string input;

    std::cin >> input;

    assert(input.size() <= 800000);

    Container a(input);

    try {
        a.check();
        a.make_after();
        a.print();
    }

    catch (std::invalid_argument & e) {
        std::cout << e.what();
    }

    return 0;
}