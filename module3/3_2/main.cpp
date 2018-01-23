/*Вычислить количество узлов в самом широком слое декартового дерева и количество узлов в
 * самом широком слое наивного дерева поиска. Вывести их разницу. Разница может быть отрицательна.
 * */

#include <iostream>
#include <queue>
#include <cassert>


class node {

public:

    int value;
    node * left;
    node * right;


    node() : left(nullptr), right(nullptr) {}

    node(int obj) : value(obj), left(nullptr), right(nullptr) {}

    node(int obj, node * l, node * r) : value(obj), left(l), right(r) {}

    node(const node & obj) = delete;

    node(const node && obj) = delete;

    ~node() {
        delete left;
        delete right;
    }
};


class binary_tree {

public:

    node * root;

    int size;

    binary_tree() : root(nullptr), size(0) {}

    binary_tree(node * obj) : root(obj), size(0) {}

    binary_tree(const binary_tree & obj) = delete;

    binary_tree(const binary_tree && obj) = delete;

    void insert(int obj);

    int max_width();

};


void binary_tree::insert(int obj) {

    size++;

    if (root == nullptr) {
        root = new node(obj);
        return;
    }

    node * pi = root;

    while (1) {

        if (obj >= pi->value) {
            if (pi->right == nullptr) {
                node * k = new node(obj);
                pi->right = k;
                return;
            }

            pi = pi->right;
        }

        else {
            if (pi->left == nullptr) {
                node * k = new node(obj);
                pi->left = k;
                return;
            }

            pi = pi->left;
        }
    }
}



//модернизированный поиск в ширину
int binary_tree::max_width() {

    std::queue<std::pair<node *, int>> data;
    data.push(std::pair<node *, int>(root, 0));

    int result = 0;

    //вектор, в котором хранятся размеры слоев
    std::vector<int> layers(size, 0);

    while (!data.empty()) {
        node * buf = data.front().first;
        int current_layer = data.front().second;
        data.pop();
        if (buf->left)
            data.push(std::pair<node *, int>(buf->left, current_layer + 1));

        if (buf->right)
            data.push(std::pair<node *, int>(buf->right, current_layer + 1));

        layers[current_layer]++;

    }

    for (auto & obj : layers) {
        if (obj > result)
            result = obj;
    }

    return result;
}


////##############################################################################
class pair_node {

public:

    std::pair<int, int> value;
    pair_node * left;
    pair_node * right;


    pair_node() : left(nullptr), right(nullptr) {}

    pair_node(const std::pair<int, int> & obj) : value(obj), left(nullptr), right(nullptr) {}

    pair_node(const std::pair<int, int> & obj, pair_node * l, pair_node * r) : value(obj), left(l), right(r) {}

    pair_node(const pair_node & obj) = delete;

    pair_node(const pair_node && obj) = delete;

    ~pair_node() {
        delete left;
        delete right;
    }
};



class treapy {

public:

    pair_node * root;

    int size;

    treapy() : root(nullptr), size(0) {}

    treapy(pair_node * obj) : root(obj), size(0) {}

    treapy(const treapy & obj) = delete;

    treapy(const treapy && obj) = delete;

    void split(pair_node * current_node, std::pair<int, int> obj, pair_node* & left, pair_node* & right);

    void insert(std::pair<int, int> obj);

    int max_width();

};



void treapy::split(pair_node *current_node, std::pair<int, int> obj, pair_node *&left, pair_node *&right) {

    if (current_node == nullptr) {
        left = nullptr;
        right = nullptr;
    }

    else if (current_node->value.first <= obj.first) {
        split(current_node->right, obj, current_node->right, right);
        left = current_node;
    }

    else {
        split(current_node->left, obj, left, current_node->left);
        right = current_node;
    }
}



void treapy::insert(std::pair<int, int> obj) {

    size++;

    if (root == nullptr) {
        root = new pair_node(obj);
        return;
    }

    pair_node * pi = root;
    pair_node * prev = nullptr;

    while (1) {

        if (pi->value.second < obj.second) {
            pair_node * left;
            pair_node * right;
            split(pi, obj, left, right);
            pair_node * new_obj = new pair_node(obj, left, right);

            if (pi == root) {
                root = new_obj;
                return;
            }

            if (new_obj->value.first >= prev->value.first)
                prev->right = new_obj;
            else
                prev->left = new_obj;
            return;
        }

        if (obj.first >= pi->value.first) {

            if (pi->right == nullptr) {
                pair_node * k = new pair_node(obj);
                pi->right = k;
                return;
            }
            prev = pi;
            pi = pi->right;
        }

        else {
            if (pi->left == nullptr) {
                pair_node * k = new pair_node(obj);
                pi->left = k;
                return;
            }

            prev = pi;
            pi = pi->left;
        }
    }

}



//модернизированный поису в ширину на куреве
int treapy::max_width() {

    std::queue<std::pair<pair_node *, int>> data;
    data.push(std::pair<pair_node *, int>(root, 0));

    int result = 0;

    //вектор, в котором хранятся размеры слоев
    std::vector<int> layers(size, 0);

    while (!data.empty()) {
        pair_node * buf = data.front().first;
        int current_layer = data.front().second;
        data.pop();
        if (buf->left)
            data.push(std::pair<pair_node *, int>(buf->left, current_layer + 1));

        if (buf->right)
            data.push(std::pair<pair_node *, int>(buf->right, current_layer + 1));

        layers[current_layer]++;
    }

    for (auto & obj : layers) {
        if (obj > result)
            result = obj;
    }

    return result;
}



int main() {

    treapy a;
    binary_tree b;

    int n = 0;

    std::cin >> n;

    assert(n < 1000000);

    for (int i = 0; i < n; ++i) {

        int x = 0;
        int y = 0;
        std::cin >> x >> y;
        a.insert(std::pair<int, int>(x, y));
        b.insert(x);
    }

    std::cout << a.max_width() - b.max_width();

    return 0;
}