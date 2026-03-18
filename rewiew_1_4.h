#ifndef REWIEW_1_4_H
#define REWIEW_1_4_H

// FIX_ME: Отсутствие прототипов функций в начале файла
// FIX_ME: Неинформативные имена функций
// старый код: int calc(string str); int element(string str); int term(string str);
// новый код:

#include <string>

// FIX_ME: Передача строки по значению вместо константной ссылки (неэффективно)
// старый код: int calc(string str); int element(string str); int term(string str);
// новый код:

// FIX_ME: Неинформативные имена функций (должны быть lower_case_with_underscores)
// Функция для проверки допустимых символов
bool IsValidCharacter(char c);

// FIX_ME: Комментарии, объясняющие рекурсивный алгоритм
// Рекурсивный парсер для вычисления арифметических выражений
// Грамматика:
// <выражение> ::= <терм> | <выражение> + <терм> | <выражение> - <терм>
// <терм> ::= <фактор> | <терм> * <фактор>
// <фактор> ::= <цифра> | ( <выражение> )

// Парсинг фактора (цифра или выражение в скобках)
int ParseFactor(const std::string& str);

// Парсинг терма (содержит операторы умножения)
int ParseTerm(const std::string& str);

// Парсинг выражения (содержит операторы сложения и вычитания)
int CalculateExpression(const std::string& str);

#endif  // REWIEW_1_4_H
