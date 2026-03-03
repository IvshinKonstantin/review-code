#include <fstream>
#include <iostream>
#include <vector>

const int kMinCoinValue = 1;
const int kMaxCoinValue = 100;

int main() {
    setlocale(LC_ALL, "russian");

    std::ifstream input_file("a.txt");
    std::ofstream output_file("b.txt");

    if (!input_file.is_open()) {
        std::cerr << "Ошибка открытия входного файла a.txt!" << std::endl;
        return 1;
    }

    if (!output_file.is_open()) {
        std::cerr << "Ошибка открытия выходного файла b.txt!" << std::endl;
        input_file.close();
        return 1;
    }

    int size;
    if (!(input_file >> size)) {
        std::cerr << "Ошибка чтения размера доски!" << std::endl;
        input_file.close();
        output_file.close();
        return 1;
    }

    if (size <= 1 || size >= 80) {
        std::cerr << "Некорректный размер доски! Должен быть 1 < N < 80" << std::endl;
        input_file.close();
        output_file.close();
        return 1;
    }

    // Создание доски с монетами
    std::vector<std::vector<int>> board(size, std::vector<int>(size));

    // Чтение доски из файла
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (!(input_file >> board[i][j])) {
                std::cerr << "Ошибка чтения значения монеты в позиции [" << i << "]["
                    << j << "]!" << std::endl;
                input_file.close();
                output_file.close();
                return 1;
            }
            if (board[i][j] < kMinCoinValue || board[i][j] > kMaxCoinValue) {
                std::cerr << "Некорректное достоинство монеты! Должно быть от "
                    << kMinCoinValue << " до " << kMaxCoinValue << std::endl;
                input_file.close();
                output_file.close();
                return 1;
            }
        }
    }

    input_file.close();

    // Вектор для хранения максимальных сумм
    std::vector<std::vector<int>> max_sum(size, std::vector<int>(size, 0));

    // Начальная позиция (правый нижний угол)
    max_sum[size - 1][size - 1] = board[size - 1][size - 1];

    // Заполнение таблицы максимальных сумм
    for (int i = size - 1; i >= 0; --i) {
        for (int j = size - 1; j >= 0; --j) {
            if (i < size - 1) {
                int candidate = max_sum[i + 1][j] + board[i][j];
                if (candidate > max_sum[i][j]) {
                    max_sum[i][j] = candidate;
                }
            }
            if (j < size - 1) {
                int candidate = max_sum[i][j + 1] + board[i][j];
                if (candidate > max_sum[i][j]) {
                    max_sum[i][j] = candidate;
                }
            }
        }
    }

    // Максимальная сумма монет
    int max_coin_sum = max_sum[0][0];
    output_file << max_coin_sum << std::endl;

    // Восстановление пути
    std::vector<char> path;
    int row = 0;
    int col = 0;

    // Король начинает в левом верхнем углу (0,0) и идет в правый нижний (size-1, size-1)
    while (row < size - 1 || col < size - 1) {
        if (row == size - 1) {
            // Достигли нижней границы, можем двигаться только вправо
            path.push_back('L');  // L - движение влево (по условию)
            ++col;
        }
        else if (col == size - 1) {
            // Достигли правой границы, можем двигаться только вниз
            path.push_back('U');  // U - движение вверх (по условию)
            ++row;
        }
        else if (max_sum[row + 1][col] > max_sum[row][col + 1]) {
            // Движение вниз дает большую сумму
            path.push_back('U');  // U - движение вверх
            ++row;
        }
        else {
            // Движение вправо дает большую сумму
            path.push_back('L');  // L - движение влево
            ++col;
        }
    }

    // Вывод пути в файл
    for (char move : path) {
        output_file << move;
    }
    output_file << std::endl;

    output_file.close();

    return 0;
}