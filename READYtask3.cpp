#include <climits>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

// Функция для безопасного возведения в степень (целые числа)
long long SafePower(int base, int exponent) {
    long long result = 1;
    for (int i = 0; i < exponent; ++i) {
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
    const int kMaxConsecutiveZeros = 4;
    const int kStateSize = kMaxConsecutiveZeros + 1;  // Состояния: 0,1,2,3,4+

    // dp[i][j] - количество чисел длины i, заканчивающихся на j подряд идущих нулей
    // dp[i][kMaxConsecutiveZeros] - числа, в которых уже есть 4+ нулей подряд
    std::vector<std::vector<long long>> dp(
        num_digits + 1, std::vector<long long>(kStateSize, 0));

    // Первая цифра не может быть нулем (иначе число будет короче)
    dp[1][0] = base - 1;  // Любая ненулевая цифра
    dp[1][1] = 0;         // Ноль не может быть первой цифрой

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

    return static_cast<double>(dp[num_digits][kMaxConsecutiveZeros]);
}

void SolveTask() {
    std::ifstream input_file("input.txt");
    std::ofstream output_file("output.txt");

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
    if (!(input_file >> base >> num_digits)) {
        std::cerr << "Ошибка чтения данных из файла!" << std::endl;
        input_file.close();
        output_file.close();
        return;
    }

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

    // Вывод результата с требуемой точностью
    output_file << std::fixed << std::setprecision(10) << result << std::endl;

    output_file.close();
}

int main() {
    setlocale(LC_ALL, "russian");
    SolveTask();
    return 0;
}