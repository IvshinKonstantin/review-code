#include <iostream>
#include <fstream>
#include <vector>

#include "rewiew_1_1.h"

int main() {
  setlocale(LC_ALL, "russian");

  // FIX_ME: Отсутствие проверки открытия файла
  // старый код: ifstream input("t.txt");
  // новый код:
  std::ifstream input_file("t.txt");

  // FIX_ME: Отсутствие проверки открытия файла (продолжение)
  if (!input_file.is_open()) {
    // FIX_ME: Использование cout для ошибок (нужно cerr)
    // старый код: cout << "Ошибка открытия файла!" << endl;
    // новый код:
    std::cerr << "Ошибка открытия файла t.txt!" << std::endl;
    // FIX_ME: Отсутствие кода возврата при ошибках
    return 1;
  }

  int num_items, min_required_weight;
  // FIX_ME: Отсутствие проверки корректности чтения данных
  // старый код: input >> N >> Z;
  // новый код:
  if (!(input_file >> num_items >> min_required_weight)) {
    std::cerr << "Ошибка чтения N и Z из файла!" << std::endl;
    input_file.close();
    return 1;
  }

  // FIX_ME: Неэффективное чтение данных (использование push_back)
  // старый код: vector<int> weights; for (...) { input >> value; weights.push_back(value); }
  // новый код:
  std::vector<int> weights(num_items);
  std::vector<int> taxes(num_items);

  // Считываем веса предметов
  for (int i = 0; i < num_items; ++i) {
    if (!(input_file >> weights[i])) {
      std::cerr << "Ошибка чтения веса предмета " << i + 1 << "!" << std::endl;
      input_file.close();
      return 1;
    }
  }

  // Считываем налоговое бремя предметов
  for (int i = 0; i < num_items; ++i) {
    if (!(input_file >> taxes[i])) {
      std::cerr << "Ошибка чтения налога предмета " << i + 1 << "!" << std::endl;
      input_file.close();
      return 1;
    }
  }

  input_file.close();

  // FIX_ME: Неправильное именование функции
  FindMinTaxSubset(min_required_weight, weights, taxes);

  // FIX_ME: Отсутствие кода возврата при ошибках
  return 0;
}
