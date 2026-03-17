#include "rewiew_1_4.h"
#include <iostream>
#include <string>
#include <exception>

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