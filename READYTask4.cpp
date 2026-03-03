#include <fstream>
#include <iostream>
#include <string>

// Объявление функций
int CalculateExpression(const std::string& str);
int ParseTerm(const std::string& str);
int ParseFactor(const std::string& str);

// Функция для проверки допустимых символов
bool IsValidCharacter(char c) {
    return (c >= '0' && c <= '9') || c == '+' || c == '-' ||
        c == '*' || c == '(' || c == ')';
}

// Парсинг фактора (цифра или выражение в скобках)
int ParseFactor(const std::string& str) {
    if (str.empty()) {
        std::cerr << "Ошибка: пустая строка в ParseFactor!" << std::endl;
        return 0;
    }

    // Если выражение в скобках
    if (str.front() == '(' && str.back() == ')') {
        // Проверка на сбалансированность скобок
        int balance = 0;
        for (size_t i = 0; i < str.size() - 1; ++i) {
            if (str[i] == '(') ++balance;
            if (str[i] == ')') --balance;
            if (balance == 0 && i < str.size() - 2) {
                std::cerr << "Ошибка: несбалансированные скобки!" << std::endl;
                return 0;
            }
        }
        // Рекурсивно вычисляем выражение внутри скобок
        return CalculateExpression(str.substr(1, str.size() - 2));
    }

    // Если это число
    try {
        return std::stoi(str);
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка преобразования строки в число: " << str << std::endl;
        return 0;
    }
}

// Парсинг терма (содержит операторы умножения)
int ParseTerm(const std::string& str) {
    int i = str.size() - 1;
    int level = 0;
    int pos = -1;
    const char kMultiplicationOperator = '*';

    // Поиск оператора умножения с учетом приоритета
    while (i >= 0) {
        if (str[i] == ')') ++level;
        if (str[i] == '(') --level;
        if (level == 0 && str[i] == kMultiplicationOperator) {
            pos = i;
            break;
        }
        --i;
    }

    // Если оператор умножения не найден
    if (pos == -1) {
        return ParseFactor(str);
    }

    // Рекурсивно вычисляем левую и правую части
    return ParseTerm(str.substr(0, pos)) *
        ParseFactor(str.substr(pos + 1));
}

// Парсинг выражения (содержит операторы сложения и вычитания)
int CalculateExpression(const std::string& str) {
    int i = str.size() - 1;
    int level = 0;
    int pos = -1;

    // Поиск оператора сложения или вычитания с учетом приоритета
    while (i >= 0) {
        if (str[i] == ')') ++level;
        if (str[i] == '(') --level;
        if (level == 0 && (str[i] == '-' || str[i] == '+')) {
            pos = i;
            break;
        }
        --i;
    }

    // Если оператор не найден, это терм
    if (pos == -1) {
        return ParseTerm(str);
    }

    char op = str[pos];
    if (op == '+') {
        return CalculateExpression(str.substr(0, pos)) +
            ParseTerm(str.substr(pos + 1));
    }
    else if (op == '-') {
        return CalculateExpression(str.substr(0, pos)) -
            ParseTerm(str.substr(pos + 1));
    }
    else {
        std::cerr << "Ошибка: неизвестный оператор '" << op << "'!" << std::endl;
        return 0;
    }
}

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

    std::cout << "Результат вычисления записан в файл output.txt" << std::endl;
    return 0;
}