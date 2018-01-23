//Реализовать хэш-таблицу с методом разрешения коллизий - двойное хэширование

#include <iostream>
#include <vector>


#define HASH1 17
#define HASH2 73


unsigned int my_hash(const std::string & key, int bound) {

    unsigned int hash = 0;
    for (auto & x : key)
        hash = (hash * HASH1 + x) % bound;
    return hash;
}

unsigned int my_second_hash(const std::string & key, int bound) {

    unsigned int hash = 0;
    for (auto & x : key)
        hash = (hash * HASH2 + x) % bound;

    return ((hash << 1) + 1) % bound;
}



//элемент хэш-таблицы
struct hash_node {

    hash_node(const std::string &data) : _data(data), is_deleted(false) {}

    std::string _data;
    bool is_deleted;
};



using vector_t = std::vector<hash_node *>;


class hash_table {

public:

    explicit hash_table(int max_size);
    ~hash_table();
    // Проверка наличия ключа в хеш-таблице.
    bool has( const std::string & key ) const;
    // Добавление ключа. Возвращает false, если ключ уже есть в хеш-таблице, повторно его не добавляет.
    bool add( const std::string & key );
    // Удаление ключа. Возвращает false, если ключа нет в хеш-таблице.
    bool remove( const std::string & key );
    // Перехэширование.
    void resize();


private:

    vector_t data;
    unsigned int current_size;
};



hash_table::hash_table(int max_size) : data(max_size, nullptr), current_size(0) {}

hash_table::~hash_table() {
    for (auto & obj : data)
        delete obj;
}



void hash_table::resize() {

    vector_t buf = data;
    data.clear();
    data.resize(buf.size() * 2, nullptr);

    for (const auto & obj: buf) {
        if (obj != nullptr && !obj->is_deleted)
            add(obj->_data);
    }
}



bool hash_table::add(const std::string & key) {

    if ((double)current_size / (double)data.size() >= 0.75) {
        this->resize();
    }

    int hash = my_hash(key, data.size());
    const int second_hash =  my_second_hash(key, data.size());

    int index = -1;

    int i = 0;
    while (data[hash] != nullptr && i < data.size()) {

        if (data[hash]->_data == key && !data[hash]->is_deleted) {
            return false;
        }

        // поиск места для вставки (удаленные места)
        if (data[hash]->is_deleted && index < 0) {
            index = hash;
        }

        hash = (hash + second_hash) % data.size();

        ++i;
    }

    if (index >= 0) {
        data[index]->_data = key;
        data[index]->is_deleted = false;
    }

    else {
        data[hash] = new hash_node(key);
    }

    ++current_size;
    return true;
}



bool hash_table::remove(const std::string & key) {

    int hash = my_hash(key, data.size());
    const int second_hash =  my_second_hash(key, data.size());

    size_t i = 0;
    while (data[hash] != nullptr && i < data.size()) {

        if (data[hash]->_data == key && !data[hash]->is_deleted) {
            data[hash]->is_deleted = true;
            --current_size;
            return true;
        }

        hash = (hash + second_hash) % data.size();
        ++i;
    }

    return false;
}


bool hash_table::has(const std::string & key) const {

    int hash = my_hash(key, data.size());
    const int second_hash =  my_second_hash(key, data.size());

    size_t i = 0;

    while (data[hash] != nullptr && i < data.size()) {

        if (data[hash]->_data == key && !data[hash]->is_deleted)
            return true;

        hash = (hash + second_hash) % data.size();
        ++i;
    }

    return false;
}



int main() {

    hash_table table(8);

    char command = 0;
    std::string key;
    while (std::cin >> command >> key) {
        switch (command) {
            case '?':
                std::cout << (table.has(key) ? "OK" : "FAIL") << std::endl;
                break;
            case '+':
                std::cout << (table.add(key) ? "OK" : "FAIL") << std::endl;
                break;
            case '-':
                std::cout << (table.remove(key) ? "OK" : "FAIL") << std::endl;
                break;
        }
    }

    return 0;
}