/*Дано N кубиков. Требуется определить каким количеством способов можно выстроить из этих кубиков пирамиду.
Каждый вышележащий слой пирамиды должен быть не больше нижележащего.
N ≤ 200.
*/


#include <iostream>
#include <vector>
#include <cassert>

std::size_t count(int n, std::vector<std::vector<std::size_t>> & data) {

    for (int row = 1; row < n; ++row) {

        data[row][0] = 1;
        data[row][row] = 1;

        //рассчет реккурентной формулы (сумма двух высоких пирамид есть высокая пирамида)
        for (int col = 1; col < row; ++col) {

            for (int k = 0; k <= col; ++k) {
                data[row][col] += data[row - col - 1][k];
            }
        }
    }

    std::size_t result = 0;

    //вычисление суммы последней строки - для высоты n
    for (int i = 0; i < n; ++i) {
        result += data[n - 1][i];
    }

    return result;
}


int main() {
    int n = 0;
    std::cin >> n;

    assert(0 < n <= 200);
    //матрица, в которой хранится высота k для i кубиков
    std::vector<std::vector<std::size_t>> data(n, std::vector<std::size_t>(n));

    data[0][0] = 1;

    std::cout << count(n, data) << std::endl;

    return 0;
}