//FIX_ME: Использование using namespace std; (против правил Google Style Guide)

//старый код
using namespace std;

//новый код
// (using namespace std; удалено, используется префикс std::)


//FIX_ME: Неинформативное название функции (должно быть lower_case_with_underscores)

//старый код
double Count(int N, int K) {

//новый код
double CountNumbersWithFourPlusZeros(int num_digits, int base) {


//FIX_ME: Неинформативное название функции (должно быть lower_case_with_underscores)

//старый код
void HomeDyn16() {

//новый код
void SolveTask() {


//FIX_ME: Использование магических чисел

//старый код
vector<vector<long long>> dp(N + 1, vector<long long>(5, 0));
for (int j = 0; j < 4; j++) {
dp[i][4] — количество чисел, где уже было 4+ подряд идущих нулей

//новый код
const int kMaxConsecutiveZeros = 4;
const int kStateSize = kMaxConsecutiveZeros + 1; // 5 состояний (0,1,2,3,4+)

std::vector<std::vector<long long>> dp(num_digits + 1, 
                                       std::vector<long long>(kStateSize, 0));
// dp[i][kMaxConsecutiveZeros] — количество чисел, где уже было 4+ подряд идущих нулей


//FIX_ME: Отсутствие проверки граничных условий

//старый код
cout<<"Система счисления: ";cin >> K;
cout<<"Количество разрядов: ";cin >> N;

//новый код
std::cout << "Система счисления (2-10): ";
std::cin >> base;

std::cout << "Количество разрядов (1-20, N+K<26): ";
std::cin >> num_digits;

if (base < 2 || base > 10) {
  std::cerr << "Ошибка: основание системы счисления должно быть от 2 до 10!" 
            << std::endl;
  return;
}

if (num_digits <= 1 || num_digits >= 20) {
  std::cerr << "Ошибка: количество разрядов должно быть 1 < N < 20!" 
            << std::endl;
  return;
}

if (num_digits + base >= 26) {
  std::cerr << "Ошибка: N + K должно быть < 26!" << std::endl;
  return;
}


//FIX_ME: Использование cin/cout без учета ввода-вывода из файлов (по условию задачи)

//старый код
cout<<"Система счисления: ";cin >> K;
cout<<"Количество разрядов: ";cin >> N;

//новый код
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


//FIX_ME: Неправильное форматирование (открывающая скобка на отдельной строке)

//старый код
for (int i = 2; i <= N; i++) 
{
    for (int j = 0; j < 4; j++) 
    {

//новый код
for (int i = 2; i <= num_digits; ++i) {
  for (int j = 0; j < kMaxConsecutiveZeros; ++j) {


//FIX_ME: Неправильные отступы (нужно 2 пробела)

//старый код
    int N, K;
    cout<<"Система счисления: ";cin >> K;
    cout<<"Количество разрядов: ";cin >> N;

//новый код
  int num_digits, base;
  std::cout << "Система счисления (2-10): ";
  std::cin >> base;
  std::cout << "Количество разрядов (1-20, N+K<26): ";
  std::cin >> num_digits;


//FIX_ME: Отсутствие проверки на переполнение (использование long long, но без проверок)

//старый код
vector<vector<long long>> dp(N + 1, vector<long long>(5, 0));

//новый код
// Используем long long, но добавляем проверку на переполнение
const long long kMaxSafeValue = LLONG_MAX / 2; // Половина максимального значения

// При добавлении проверяем на переполнение
if (dp[i - 1][j] > kMaxSafeValue / (base - 1)) {
  std::cerr << "Внимание: возможно переполнение!" << std::endl;
}


//FIX_ME: Отладочный вывод внутри вычислительной функции

//старый код
double count = dp[N][4]; cout <<"Количество чисел, содержащих болше 3 нулей подряд: "<< count << endl;
return count;

//новый код
double count = static_cast<double>(dp[num_digits][kMaxConsecutiveZeros]);
return count;


//FIX_ME: Использование pow для целых чисел (риск потери точности)

//старый код
double all = pow(K, N);

//новый код
// Функция для безопасного возведения в степень
long long SafePower(int base, int exponent) {
  long long result = 1;
  for (int i = 0; i < exponent; ++i) {
    if (result > LLONG_MAX / base) {
      std::cerr << "Предупреждение: переполнение при возведении в степень!" 
                << std::endl;
      return LLONG_MAX;
    }
    result *= base;
  }
  return result;
}

long long total_numbers = SafePower(base, num_digits);


//FIX_ME: Вывод результата без форматирования (по условию нужен вещественный ответ)

//старый код
cout  << result << endl;

//новый код
double result = count / static_cast<double>(total_numbers);
output_file << std::fixed << std::setprecision(10) << result << std::endl;


//FIX_ME: Длина строки превышает 80 символов

//старый код
vector<vector<long long>> dp(N + 1, vector<long long>(5, 0));

//новый код
std::vector<std::vector<long long>> dp(num_digits + 1, 
                                       std::vector<long long>(kStateSize, 0));


//FIX_ME: Использование постфиксного инкремента (лучше префиксный)

//старый код
for (int i = 2; i <= N; i++) {
for (int j = 0; j < 4; j++) {

//новый код
for (int i = 2; i <= num_digits; ++i) {
  for (int j = 0; j < kMaxConsecutiveZeros; ++j) {


//FIX_ME: Неправильная обработка первой цифры (не может быть нулем для N-значных чисел)

//старый код
dp[1][0] = K - 1;  // Любая цифра кроме нуля
dp[1][1] = 1;      // Только ноль

//новый код
// Для первой цифры: не может быть нулем (иначе число будет короче)
dp[1][0] = base - 1;  // Любая цифра кроме нуля
dp[1][1] = 0;         // Ноль не может быть первой цифрой
