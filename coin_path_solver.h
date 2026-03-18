#ifndef COIN_PATH_SOLVER_H
#define COIN_PATH_SOLVER_H

#include <vector>
#include <istream>

class CoinPathSolver {
 public:
  CoinPathSolver() = default;

  // Чтение доски из входного потока
  bool ReadBoard(std::istream& input_stream);

  // Вычисление максимальной суммы монет на пути
  void CalculateMaxSum();

  // Получение максимальной суммы
  int GetMaxSum() const;

  // Восстановление пути
  std::vector<char> RestorePath() const;

 private:
  // FIX_ME: Использование магических чисел
  // старый код: if (board[i][j] < 1 || board[i][j] > 100)
  // новый код:
  static const int kMinCoinValue = 1;
  static const int kMaxCoinValue = 100;
  static const int kMaxBoardSize = 79;
  static const int kMinBoardSize = 2;

  int size_ = 0;
  // FIX_ME: Неинформативные имена переменных
  // старый код: vector<vector> docka(N, vector(N)); vector< vector> dp(N, vector(N, 0));
  // новый код:
  std::vector<std::vector<int>> board_;    // доска с монетами
  std::vector<std::vector<int>> max_sum_;  // таблица максимальных сумм

  bool IsValidBoardSize(int size) const;
  bool IsValidCoinValue(int value) const;
};

#endif  // COIN_PATH_SOLVER_H
