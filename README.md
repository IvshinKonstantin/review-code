//FIX_ME: Использование using namespace std; (против правил Google Style Guide)

//старый код
using namespace std;

//новый код
// (using namespace std; удалено, используется префикс std::)


//FIX_ME: Отсутствие прототипов функций в начале файла

//старый код
int calc(string str);
int element(string str)
// (определение функции до ее использования)

//новый код
// Объявление всех функций в начале файла
int CalculateExpression(const std::string& str);
int ParseTerm(const std::string& str);
int ParseFactor(const std::string& str);


//FIX_ME: Передача строки по значению вместо константной ссылки (неэффективно)

//старый код
int calc(string str);
int element(string str);
int term(string str);

//новый код
int CalculateExpression(const std::string& str);
int ParseFactor(const std::string& str);
int ParseTerm(const std::string& str);


//FIX_ME: Неинформативные имена функций (должны быть lower_case_with_underscores)

//старый код
int calc(string str);
int element(string str);
int term(string str);

//новый код
int CalculateExpression(const std::string& str);
int ParseFactor(const std::string& str);
int ParseTerm(const std::string& str);


//FIX_ME: Отсутствие проверки на пустую строку

//старый код
int element(string str)
{
    if (str[0] == '(' && str[str.size() - 1] == ')')

//новый код
int ParseFactor(const std::string& str)
{
    if (str.empty()) {
        std::cerr << "Ошибка: пустая строка!" << std::endl;
        return 0;
    }
    if (str[0] == '(' && str[str.size() - 1] == ')')


//FIX_ME: Отсутствие проверки на корректность скобок

//старый код
if (str[0] == '(' && str[str.size() - 1] == ')')
    return calc(str.substr(1, str.size() - 2));

//новый код
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
    return CalculateExpression(str.substr(1, str.size() - 2));
}


//FIX_ME: Использование индексации без проверки границ

//старый код
if (str[0] == '(' && str[str.size() - 1] == ')')
return stoi(str);

//новый код
if (str.front() == '(' && str.back() == ')')
// Проверка, что строка не пуста перед вызовом stoi
if (str.empty()) {
    std::cerr << "Ошибка: пустая строка в ParseFactor!" << std::endl;
    return 0;
}
try {
    return std::stoi(str);
} catch (const std::exception& e) {
    std::cerr << "Ошибка преобразования строки в число: " << str << std::endl;
    return 0;
}


//FIX_ME: Неправильное форматирование (открывающая скобка на отдельной строке)

//старый код
int term(string str)
{
    int i = str.size() - 1;

//новый код
int ParseTerm(const std::string& str) {
    int i = str.size() - 1;


//FIX_ME: Использование магических символов без комментариев

//старый код
if (level == 0 && str[i] == '*')

//новый код
const char kMultiplicationOperator = '*';
// Поиск оператора умножения с учетом приоритета
if (level == 0 && str[i] == kMultiplicationOperator)


//FIX_ME: Использование постфиксного инкремента (лучше префиксный)

//старый код
i--;
level++;

//новый код
--i;
++level;


//FIX_ME: Длина строки превышает 80 символов

//старый код
return calc(str.substr(0, pos)) + term(str.substr(pos + 1));

//новый код
return CalculateExpression(str.substr(0, pos)) + 
       ParseTerm(str.substr(pos + 1));


//FIX_ME: Отсутствие обработки некорректных операторов

//старый код
if (ch == '+')
    return calc(str.substr(0, pos)) + term(str.substr(pos + 1));
if (ch == '-')
    return calc(str.substr(0, pos)) - term(str.substr(pos + 1));
return 0;

//новый код
if (ch == '+') {
    return CalculateExpression(str.substr(0, pos)) + 
           ParseTerm(str.substr(pos + 1));
} else if (ch == '-') {
    return CalculateExpression(str.substr(0, pos)) - 
           ParseTerm(str.substr(pos + 1));
} else {
    std::cerr << "Ошибка: неизвестный оператор '" << ch << "'!" << std::endl;
    return 0;
}


//FIX_ME: Использование cin/cout без учета ввода-вывода из файлов (по условию задачи)

//старый код
cout << "Программа считает значение выражения которое вы введете" << endl;
string str;
cout << "Введите выражение: ";
getline(cin, str);

//новый код
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


//FIX_ME: Отсутствие проверки на недопустимые символы в выражении

//старый код
// (отсутствует проверка)

//новый код
// Функция для проверки допустимых символов
bool IsValidCharacter(char c) {
    return (c >= '0' && c <= '9') || c == '+' || c == '-' || 
           c == '*' || c == '(' || c == ')';
}

// Проверка выражения на недопустимые символы
for (char c : expression) {
    if (!IsValidCharacter(c)) {
        std::cerr << "Ошибка: недопустимый символ '" << c << "' в выражении!" 
                  << std::endl;
        input_file.close();
        output_file.close();
        return 1;
    }
}


//FIX_ME: Отсутствие комментариев, объясняющих рекурсивный алгоритм

//старый код
// (минимальные комментарии)

//новый код
// Рекурсивный парсер для вычисления арифметических выражений
// Грамматика:
//   <выражение> ::= <терм> | <выражение> + <терм> | <выражение> - <терм>
//   <терм> ::= <фактор> | <терм> * <фактор>
//   <фактор> ::= <цифра> | ( <выражение> )


//FIX_ME: Отсутствие закрытия файлов при ошибках

//старый код
return 1; // просто возврат кода ошибки

//новый код
input_file.close();
output_file.close();
return 1;


//FIX_ME: Неправильные отступы (нужно 2 пробела)

//старый код
    int i = str.size() - 1;
    int level = 0;
    int pos = -1;

//новый код
  int i = str.size() - 1;
  int level = 0;
  int pos = -1;
