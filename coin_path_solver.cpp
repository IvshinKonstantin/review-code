#include "coin_path_solver.h"

#include <iostream>
#include <vector>

bool CoinPathSolver::IsValidBoardSize(int size) const {
  return size > kMinBoardSize && size < kMaxBoardSize;
}

bool CoinPathSolver::IsValidCoinValue(int value) const {
  return value >= kMinCoinValue && value <= kMaxCoinValue;
}

bool CoinPathSolver::ReadBoard(std::istream& input_stream) {
  // FIX_ME: Отсутствие проверки корректности чтения данных
  // старый код: input >> N;
  // новый код:
  if (!(input_stream >> size_)) {
    std::cerr << "Ошибка чтения размера доски!" << std::endl;
    return false;
  }

  // FIX_ME: Отсутствие проверки корректности чтения данных (продолжение)
  if (!IsValidBoardSize(size_)) {
    std::cerr << "Некорректный размер доски! Должен быть "
              << kMinBoardSize << " < N < " << kMaxBoardSize << std::endl;
    return false;
  }

  // FIX_ME: Длина строки превышает 80 символов
  // старый код: vector<vector> docka(N, vector(N));
  // новый код:
  // Создание доски с монетами
  board_.assign(size_, std::vector<int>(size_, 0));

  // FIX_ME: Отсутствие проверки корректности чтения данных (продолжение)
  // FIX_ME: Использование постфиксного инкремента
  // старый код: for (int i = 0; i < N; ++i) { for (int j = 0; j < N; ++j) { input >> docka[i][j]; } }
  // новый код:
  for (int i = 0; i < size_; ++i) {
    for (int j = 0; j < size_; ++j) {
      if (!(input_stream >> board_[i][j])) {
        std::cerr << "Ошибка чтения значения монеты в позиции ["
                  << i << "][" << j << "]!" << std::endl;
        return false;
      }
      // FIX_ME: Использование магических чисел
      if (!IsValidCoinValue(board_[i][j])) {
        std::cerr << "Некорректное достоинство монеты! Должно быть от "
                  << kMinCoinValue << " до " << kMaxCoinValue << std::endl;
        return false;
      }
    }
  }

  return true;
}

void CoinPathSolver::CalculateMaxSum() {
  // Вектор для хранения максимальных сумм
  max_sum_.assign(size_, std::vector<int>(size_, 0));

  // Начальная позиция (правый нижний угол)
  max_sum_[size_ - 1][size_ - 1] = board_[size_ - 1][size_ - 1];

  // FIX_ME: Неправильное форматирование скобок
  // FIX_ME: Неправильные отступы
  // старый код: for (int i = N - 1; i >= 0; --i) { for (int j = N - 1; j >= 0; --j) {
  // новый код:
  for (int i = size_ - 1; i >= 0; --i) {
    for (int j = size_ - 1; j >= 0; --j) {
      if (i < size_ - 1) {
        int candidate = max_sum_[i + 1][j] + board_[i][j];
        if (candidate > max_sum_[i][j]) {
          max_sum_[i][j] = candidate;
        }
      }
      if (j < size_ - 1) {
        int candidate = max_sum_[i][j + 1] + board_[i][j];
        if (candidate > max_sum_[i][j]) {
          max_sum_[i][j] = candidate;
        }
      }
    }
  }
}

int CoinPathSolver::GetMaxSum() const {
  return max_sum_[0][0];
}

std::vector<char> CoinPathSolver::RestorePath() const {
  std::vector<char> path;
  // FIX_ME: Неинформативные имена переменных
  // старый код: int x = 0, y = 0;
  // новый код:
  int row = 0;
  int col = 0;

  // FIX_ME: Ошибка в логике восстановления пути (перепутаны направления)
  // старый код: if (x == N - 1) { // можем двигаться только вверх
  //            path.push_back('L'); y++; } ...
  // новый код:
  // Король начинает в левом верхнем углу (0,0)
  // и идет в правый нижний (size-1, size-1)
  
  // FIX_ME: Отсутствие проверки граничных условий при восстановлении пути
  // старый код: while (x < N - 1 || y < N - 1) {
  // новый код:
  while ((row < size_ - 1 || col < size_ - 1) &&
         row < size_ && col < size_) {
    if (row == size_ - 1) {
      // Достигли нижней границы, можем двигаться только вправо
      path.push_back('L');  // L - движение влево (по условию)
      // FIX_ME: Использование постфиксного инкремента
      // старый код: y++;
      // новый код:
      ++col;
    } else if (col == size_ - 1) {
      // Достигли правой границы, можем двигаться только вниз
      path.push_back('U');  // U - движение вверх (по условию)
      // FIX_ME: Использование постфиксного инкремента
      ++row;
    } else if (max_sum_[row + 1][col] > max_sum_[row][col + 1]) {
      // Движение вниз дает большую сумму
      path.push_back('U');  // U - движение вверх
      // FIX_ME: Использование постфиксного инкремента
      ++row;
    } else {
      // Движение вправо дает большую сумму
      path.push_back('L');  // L - движение влево
      // FIX_ME: Использование постфиксного инкремента
      ++col;
    }
  }

  return path;
}
