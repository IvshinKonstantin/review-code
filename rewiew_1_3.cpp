#include "rewiew_1_3.h"

// FIX_ME: Использование using namespace std; (против правил Google Style Guide)
// старый код: using namespace std;
// новый код: (using namespace std; удалено, используется префикс std::)
#include <climits>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

// FIX_ME: Использование pow для целых чисел (риск потери точности)
// старый код: double all = pow(K, N);
// новый код:
// Функция для безопасного возведения в степень (целые числа)
long long SafePower(int base, int exponent) {
  long long result = 1;
  for (int i = 0; i < exponent; ++i) {
    // FIX_ME: Отсутствие проверки на переполнение
    if (result > LLONG_MAX / base) {
      std::cerr << "Предупреждение: обнаружено переполнение при возведении в степень!"
                << std::endl;
      return LLONG_MAX;
    }
    result *= base;
  }
  return result;
}

// Функция для подсчета чисел с 4 или более подряд идущими нулями
double CountNumbersWithFourPlusZeros(int num_digits, int base) {
  // FIX_ME: Использование магических чисел
  // старый код: vector<vector> dp(N + 1, vector(5, 0));
  //            for (int j = 0; j < 4; j++) {
  //            dp[i][4] — количество чисел, где уже было 4+ подряд идущих нулей
  // новый код:
  const int kMaxConsecutiveZeros = 4;
  const int kStateSize = kMaxConsecutiveZeros + 1;  // Состояния: 0,1,2,3,4+

  // FIX_ME: Длина строки превышает 80 символов
  // старый код: vector<vector> dp(N + 1, vector(5, 0));
  // новый код:
  // dp[i][j] - количество чисел длины i, заканчивающихся на j подряд идущих нулей
  // dp[i][kMaxConsecutiveZeros] - числа, в которых уже есть 4+ нулей подряд
  std::vector<std::vector<long long>> dp(
      num_digits + 1, std::vector<long long>(kStateSize, 0));

  // FIX_ME: Неправильная обработка первой цифры (не может быть нулем для N-значных чисел)
  // старый код: dp[1][0] = K - 1; // Любая цифра кроме нуля
  //            dp[1][1] = 1; // Только ноль
  // новый код:
  // Первая цифра не может быть нулем (иначе число будет короче)
  dp[1][0] = base - 1;  // Любая ненулевая цифра
  dp[1][1] = 0;         // Ноль не может быть первой цифрой

  // FIX_ME: Неправильное форматирование (открывающая скобка на отдельной строке)
  // FIX_ME: Использование постфиксного инкремента (лучше префиксный)
  // старый код: for (int i = 2; i <= N; i++) { for (int j = 0; j < 4; j++) {
  // новый код:
  // Заполнение таблицы динамического программирования
  for (int i = 2; i <= num_digits; ++i) {
    // Добавление ненулевых цифр к любому состоянию (прерывает последовательность нулей)
    for (int j = 0; j < kMaxConsecutiveZeros; ++j) {
      dp[i][0] += dp[i - 1][j] * (base - 1);
    }

    // Добавление нуля для удлинения последовательностей нулей
    dp[i][1] += dp[i - 1][0];
    dp[i][2] += dp[i - 1][1];
    dp[i][3] += dp[i - 1][2];

    // Числа, в которых уже есть 4+ нулей, могут добавлять любую цифру
    dp[i][kMaxConsecutiveZeros] += dp[i - 1][3];
    dp[i][kMaxConsecutiveZeros] += dp[i - 1][kMaxConsecutiveZeros] * base;
  }

  // FIX_ME: Отладочный вывод внутри вычислительной функции
  // старый код: double count = dp[N][4]; cout <<"Количество чисел, содержащих болше 3 нулей подряд: "<< count << endl; return count;
  // новый код:
  return static_cast<double>(dp[num_digits][kMaxConsecutiveZeros]);
}

// Основная функция решения задачи
void SolveTask() {
  // FIX_ME: Использование cin/cout без учета ввода-вывода из файлов (по условию задачи)
  // старый код: cout<<"Система счисления: ";cin >> K; cout<<"Количество разрядов: ";cin >> N;
  // новый код:
  std::ifstream input_file("input.txt");
  std::ofstream output_file("output.txt");

  // FIX_ME: Отсутствие проверки открытия файлов
  if (!input_file.is_open()) {
    std::cerr << "Ошибка открытия входного файла input.txt!" << std::endl;
    return;
  }

  if (!output_file.is_open()) {
    std::cerr << "Ошибка открытия выходного файла output.txt!" << std::endl;
    input_file.close();
    return;
  }

  int num_digits, base;
  // FIX_ME: Отсутствие проверки корректности чтения данных
  if (!(input_file >> base >> num_digits)) {
    std::cerr << "Ошибка чтения данных из файла!" << std::endl;
    input_file.close();
    output_file.close();
    return;
  }

  // FIX_ME: Отсутствие проверки граничных условий
  // старый код: cout<<"Система счисления: ";cin >> K; cout<<"Количество разрядов: ";cin >> N;
  // новый код:
  // Проверка корректности входных параметров
  if (base < 2 || base > 10) {
    std::cerr << "Ошибка: основание системы счисления должно быть от 2 до 10!"
              << std::endl;
    input_file.close();
    output_file.close();
    return;
  }

  if (num_digits <= 1 || num_digits >= 20) {
    std::cerr << "Ошибка: количество разрядов должно быть 1 < N < 20!"
              << std::endl;
    input_file.close();
    output_file.close();
    return;
  }

  if (num_digits + base >= 26) {
    std::cerr << "Ошибка: N + K должно быть < 26!" << std::endl;
    input_file.close();
    output_file.close();
    return;
  }

  input_file.close();

  // Вычисление общего количества возможных чисел
  long long total_numbers = SafePower(base, num_digits);

  // Вычисление количества чисел с 4+ подряд идущими нулями
  double valid_count = CountNumbersWithFourPlusZeros(num_digits, base);

  // Вычисление результата как вещественного числа (для избежания переполнения)
  double result = valid_count / static_cast<double>(total_numbers);

  // FIX_ME: Вывод результата без форматирования (по условию нужен вещественный ответ)
  // старый код: cout << result << endl;
  // новый код:
  // Вывод результата с требуемой точностью
  output_file << std::fixed << std::setprecision(10) << result << std::endl;

  output_file.close();
  // Вывод результата в консоль (для информативности, не по условию задачи)
  std::cout << "Файл input.txt содержит: основание K = " << base
            << ", количество разрядов N = " << num_digits << std::endl;
  std::cout << "Результат: " << result << ", записан в файл output.txt" << std::endl;
}
