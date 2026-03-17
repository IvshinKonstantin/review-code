#ifndef REWIEW_1_4_H
#define REWIEW_1_4_H

#include <string>

// Функция для проверки допустимых символов
bool IsValidCharacter(char c);

// Парсинг фактора (цифра или выражение в скобках)
int ParseFactor(const std::string& str);

// Парсинг терма (содержит операторы умножения)
int ParseTerm(const std::string& str);

// Парсинг выражения (содержит операторы сложения и вычитания)
int CalculateExpression(const std::string& str);

#endif // REWIEW_1_4_H