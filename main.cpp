#include <iostream>
#include <fstream>
#include <string>
#include "rewiew_1_4.h"

int main() {
    setlocale(LC_ALL, "Russian");

    std::ifstream input_file("input.txt");
    std::ofstream output_file("output.txt");

    if (!input_file.is_open()) {
        std::cerr << "Ошибка открытия входного файла input.txt!" << std::endl;
        return 1;
    }

    if (!output_file.is_open()) {
        std::cerr << "Ошибка открытия выходного файла output.txt!" << std::endl;
        input_file.close();
        return 1;
    }

    std::string expression;
    if (!std::getline(input_file, expression)) {
        std::cerr << "Ошибка чтения выражения из файла!" << std::endl;
        input_file.close();
        output_file.close();
        return 1;
    }

    input_file.close();

    // Проверка выражения на недопустимые символы
    for (char c : expression) {
        if (!IsValidCharacter(c)) {
            std::cerr << "Ошибка: недопустимый символ '" << c << "' в выражении!"
                << std::endl;
            output_file.close();
            return 1;
        }
    }

    // Вычисление выражения
    int result = CalculateExpression(expression);

    // Запись результата в выходной файл
    output_file << result << std::endl;

    output_file.close();
    std::cout << "Выражение из файла: " << expression << std::endl;
    std::cout << "Результат: " << result << " , записан в файл output.txt" << std::endl;
    return 0;
}