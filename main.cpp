#include "coin_path_solver.h"

#include <iostream>
#include <fstream>

int main() {
  setlocale(LC_ALL, "russian");

  // FIX_ME: Отсутствие проверки открытия файлов
  // старый код: ifstream input("a.txt"); ofstream output("b.txt");
  // новый код: 
  std::ifstream input_file("a.txt");
  std::ofstream output_file("b.txt");

  // FIX_ME: Отсутствие проверки открытия файлов (продолжение)
  // FIX_ME: Отсутствие закрытия файлов при ошибках
  if (!input_file.is_open()) {
    std::cerr << "Ошибка открытия входного файла a.txt!" << std::endl;
    return 1;
  }

  if (!output_file.is_open()) {
    std::cerr << "Ошибка открытия выходного файла b.txt!" << std::endl;
    // FIX_ME: Отсутствие закрытия файлов при ошибках
    input_file.close();
    return 1;
  }

  CoinPathSolver solver;
  if (!solver.ReadBoard(input_file)) {
    std::cerr << "Ошибка чтения данных из файла!" << std::endl;
    // FIX_ME: Отсутствие закрытия файлов при ошибках
    input_file.close();
    output_file.close();
    return 1;
  }

  input_file.close();

  solver.CalculateMaxSum();
  int max_coin_sum = solver.GetMaxSum();
  output_file << max_coin_sum << std::endl;

  std::vector<char> path = solver.RestorePath();
  for (char move : path) {
    output_file << move;
  }
  output_file << std::endl;

  output_file.close();

  return 0;
}
