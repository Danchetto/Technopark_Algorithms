//обход двоичного дерева post-order

#include <iostream>
#include <stack>
#include <cassert>


class node {

public:

    int value;
    node * left;
    node * right;

    node() : value(0), left(nullptr), right(nullptr) {}

    node(int obj) : value(obj), left(nullptr), right(nullptr) {}

    node(int obj, node * l, node* r) : value(obj), left(l), right(r) {}

    node(const node & obj) = delete;

    node(const node && obj) = delete;

    ~node(){
        delete left;
        delete right;
    }
};


class binary_tree {

public:

    node * root;

    binary_tree() : root(nullptr) {}

    binary_tree(node * obj) : root(obj) {}

    binary_tree(const binary_tree & obj) = delete;

    binary_tree(const binary_tree && obj) = delete;

    void insert(int obj);

    void post_order(node * root);

};


void binary_tree::insert(int obj) {

    if (root == nullptr) {
        root = new node(obj);
        return;
    }

    node * pi = root;

    while (1) {

        if (obj > pi->value) {
            if (pi->right == nullptr) {
                node * k = new node(obj, nullptr, nullptr);
                pi->right = k;
                return;
            }

            pi = pi->right;
        }

        if (obj <= pi->value) {
            if (pi->left == nullptr) {
                node * k = new node(obj, nullptr, nullptr);
                pi->left = k;
                return;
            }

            pi = pi->left;
        }
    }

}


//обход post-order
void binary_tree::post_order(node * root) {

    if (!root)
        return;

    std::stack<node *> stack_1;
    std::stack<node *> stack_2;
    stack_1.push(root);

    while (!stack_1.empty()) {
        node * buf = stack_1.top();
        stack_2.push(buf);
        stack_1.pop();

        if (buf->left != nullptr)
            stack_1.push(buf->left);
        if (buf->right != nullptr)
            stack_1.push(buf->right);
    }

    while (!stack_2.empty()) {
        std::cout <<  stack_2.top()->value << " ";
        stack_2.pop();
    }
}


int main() {

    int n = 0;

    std::cin >> n;

    assert(n <= 10000);

    binary_tree data;

    for (int i = 0; i < n; ++i) {
        int obj = 0;
        std::cin >> obj;
        data.insert(obj);
    }

    data.post_order(data.root);

    return 0;
}