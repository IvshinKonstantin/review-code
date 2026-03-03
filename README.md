//FIX_ME: Использование using namespace std; (против правил Google Style Guide)

//старый код
using namespace std;

//новый код
// (using namespace std; удалено, используется префикс std::)


//FIX_ME: Неинформативные имена переменных (должны быть lower_case_with_underscores)

//старый код
vector<vector<int>> docka(N, vector<int>(N));
vector< vector<int>> dp(N, vector<int>(N, 0));
int x = 0, y = 0;

//новый код
std::vector<std::vector<int>> board(N, std::vector<int>(N));
std::vector<std::vector<int>> max_sum(N, std::vector<int>(N, 0));
int row = 0, col = 0;


//FIX_ME: Отсутствие проверки открытия файлов

//старый код
ifstream input("a.txt");
ofstream output("b.txt");

//новый код
std::ifstream input_file("a.txt");
std::ofstream output_file("b.txt");

if (!input_file.is_open()) {
  std::cerr << "Ошибка открытия входного файла a.txt!" << std::endl;
  return 1;
}

if (!output_file.is_open()) {
  std::cerr << "Ошибка открытия выходного файла b.txt!" << std::endl;
  return 1;
}


//FIX_ME: Отсутствие проверки корректности чтения данных

//старый код
input >> N;

for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
        input >> docka[i][j];
    }
}

//новый код
if (!(input_file >> size)) {
  std::cerr << "Ошибка чтения размера доски!" << std::endl;
  return 1;
}

if (size <= 1 || size >= 80) {
  std::cerr << "Некорректный размер доски! Должен быть 1 < N < 80" << std::endl;
  return 1;
}

for (int i = 0; i < size; ++i) {
  for (int j = 0; j < size; ++j) {
    if (!(input_file >> board[i][j])) {
      std::cerr << "Ошибка чтения значения монеты в позиции [" << i << "][" << j << "]!" << std::endl;
      return 1;
    }
    if (board[i][j] < 1 || board[i][j] > 100) {
      std::cerr << "Некорректное достоинство монеты! Должно быть от 1 до 100" << std::endl;
      return 1;
    }
  }
}


//FIX_ME: Использование магических чисел

//старый код
if (board[i][j] < 1 || board[i][j] > 100)

//новый код
const int kMinCoinValue = 1;
const int kMaxCoinValue = 100;

if (board[i][j] < kMinCoinValue || board[i][j] > kMaxCoinValue)


//FIX_ME: Неправильное форматирование скобок (открывающая скобка должна быть на той же строке)

//старый код
for (int i = N - 1; i >= 0; --i) 
{
    for (int j = N - 1; j >= 0; --j) 
    {

//новый код
for (int i = size - 1; i >= 0; --i) {
  for (int j = size - 1; j >= 0; --j) {


//FIX_ME: Неправильные отступы (нужно 2 пробела, не табуляция)

//старый код
    int N;
    input >> N;
    
    // Используем вектор векторов для представления доски
    vector<vector<int>> docka(N, vector<int>(N));

//новый код
  int size;
  input_file >> size;
  
  // Создание доски с монетами
  std::vector<std::vector<int>> board(size, std::vector<int>(size));


//FIX_ME: Ошибка в логике восстановления пути (перепутаны направления)

//старый код
if (x == N - 1) { // можем двигаться только вверх
    path.push_back('L');
    y++;
}
else if (y == N - 1) { // можем двигаться только влево
    path.push_back('U');
    x++;
}
else if (dp[x + 1][y] > dp[x][y + 1]) { // двигаться вверх
    path.push_back('L');
    y++;
}
else { 
    path.push_back('U'); // двигаться влево
    x++;
}

//новый код
// Король начинает в левом верхнем углу (0,0) и идет в правый нижний (size-1, size-1)
while (row < size - 1 || col < size - 1) {
  if (row == size - 1) {
    // Достигли нижней границы, можем двигаться только вправо
    path.push_back('L');  // L - движение влево (по условию)
    col++;
  } else if (col == size - 1) {
    // Достигли правой границы, можем двигаться только вниз
    path.push_back('U');  // U - движение вверх (по условию)
    row++;
  } else if (max_sum[row + 1][col] > max_sum[row][col + 1]) {
    // Движение вниз дает большую сумму
    path.push_back('U');  // U - движение вверх
    row++;
  } else {
    // Движение вправо дает большую сумму
    path.push_back('L');  // L - движение влево
    col++;
  }
}


//FIX_ME: Использование cout/cerr без учета локализации

//старый код
cout << "Ошибка открытия файла!" << endl;

//новый код
std::cerr << "Ошибка открытия входного файла a.txt!" << std::endl;


//FIX_ME: Длина строки превышает 80 символов

//старый код
vector<vector<int>> docka(N, vector<int>(N));

//новый код
std::vector<std::vector<int>> board(size, 
                                    std::vector<int>(size));


//FIX_ME: Отсутствие проверки граничных условий при восстановлении пути

//старый код
while (x < N - 1 || y < N - 1) {

//новый код
// Проверяем, что не вышли за границы доски
while ((row < size - 1 || col < size - 1) && 
       row < size && col < size) {


//FIX_ME: Использование постфиксного инкремента (лучше префиксный)

//старый код
for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
        input >> docka[i][j];
    }
}
x++;
y++;

//новый код
for (int i = 0; i < size; ++i) {
  for (int j = 0; j < size; ++j) {
    input_file >> board[i][j];
  }
}
++row;
++col;


//FIX_ME: Отсутствие закрытия файлов при ошибках

//старый код
if (!input_file.is_open()) {
  std::cerr << "Ошибка открытия файла!" << std::endl;
  return 1;
}

//новый код
if (!input_file.is_open()) {
  std::cerr << "Ошибка открытия входного файла a.txt!" << std::endl;
  if (output_file.is_open()) {
    output_file.close();
  }
  return 1;
}
