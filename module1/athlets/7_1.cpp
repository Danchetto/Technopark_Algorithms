/*
 * В город N приехал цирк с командой атлетов.
 * Они хотят удивить горожан города N — выстроить из своих тел башню максимальной высоты.
 * Башня — это цепочка атлетов, первый стоит на земле, второй стоит у него на плечах, третий стоит на плечах у второго и т.д.
 * Каждый атлет характеризуется силой si (kg) и массой mi (kg).
 * Сила — это максимальная масса, которую атлет способен держать у себя на плечах.
 * К сожалению ни один из атлетов не умеет программировать, так как всю жизнь они занимались физической подготовкой,
 * и у них не было времени на изучение языков программирования. Помогите им, напишите программу, которая определит
 * максимальную высоту башни, которую они могут составить.
 * Известно, что если атлет тяжелее, то он и сильнее: если mi>mj, то si > sj.
 * Атлеты равной массы могут иметь различную силу.
 */



#include <iostream>
#include <vector>
#include <algorithm>


//компаратор пар по первому элемента, затем по второму
bool pairCompare(const std::pair<int, int>& first_elem, const std::pair<int, int>& second_elem) {

    bool result = false;
    result = first_elem.first < second_elem.first;

    if (first_elem.first == second_elem.first)
        result = first_elem.second < second_elem.second;

    return result;
}



//подсчет максимальной высоты башни
int count(std::vector<std::pair<int, int>> & data) {

    //cортировка по возрастанию массы, силы
    std::sort(data.begin(), data.end(), pairCompare);

    int current_mass = 0;
    int height = 0;

    //начиная с верха башни - самого легкого
    for (int i = 0; i < data.size(); ++i) {
        if (data[i].second >= current_mass) {
            height++;
            current_mass += data[i].first;
        }
    }

    return height;
}



int main() {

    std::vector<std::pair<int, int>> data;

    int m = 0;
    int s = 0;

    while (std::cin >> m >> s) {

        std::pair<int, int> athlete(m, s);
        data.push_back(athlete);
    }

    std::cout << count(data);

    return 0;
}