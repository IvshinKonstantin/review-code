#include "rewiew_1_1.h"

// FIX_ME: Использование using namespace std; (против правил Google Style Guide)
// старый код: using namespace std;
// новый код: (using namespace std; удалено, используется префикс std::)
#include <iostream>
#include <vector>
#include <climits>

// FIX_ME: Неправильное именование функции (должно быть lower_case_with_underscores)
// старый код: void knapSack(int W, vector<int>& wt, vector<int>& val) {
// новый код:
void FindMinTaxSubset(int min_weight,
                     const std::vector<int>& weights,
                     const std::vector<int>& taxes) {
  // FIX_ME: Неправильное именование переменных (должны быть lower_case_with_underscores)
  // старый код: int n = wt.size(); int maxWeight = 0;
  // новый код:
  int num_items = weights.size();  // Количество предметов
  int total_weight = 0;  // Максимально возможный вес всех предметов
  
  // Считаем общий вес всех предметов
  for (int w : weights) {
    total_weight += w;
  }

  // FIX_ME: Отсутствие проверки на невозможность достижения минимального веса
  // старый код: (проверка отсутствует)
  // новый код:
  if (total_weight < min_weight) {
    std::cout << "Невозможно достичь минимального веса " << min_weight << std::endl;
    return;
  }

  // FIX_ME: Длина строки превышает 80 символов
  // старый код: vector<vector<bool>> selected(maxWeight + 1, vector<bool>(n, false));
  // новый код:
  // Вектор dp, где dp[w] хранит минимальное налоговое бремя для веса w
  std::vector<int> dp(total_weight + 1, INT_MAX);
  dp[0] = 0;  // Нулевой вес имеет нулевое налоговое бремя

  // Матрица selected, где selected[w][i] = true, если предмет i включен в набор для веса w
  std::vector<std::vector<bool>> selected(total_weight + 1,
                                          std::vector<bool>(num_items, false));

  // FIX_ME: Неправильное форматирование скобок (открывающая скобка должна быть на той же строке)
  // FIX_ME: Постфиксный инкремент вместо префиксного
  // старый код: for (int i = 0; i < n; i++) { for (int w = maxWeight; w >= wt[i]; w--) {
  // новый код:
  // Заполняем dp и selected
  for (int i = 0; i < num_items; ++i) {  // Перебираем все предметы
    // FIX_ME: Постфиксный инкремент вместо префиксного
    for (int w = total_weight; w >= weights[i]; --w) {  // Перебираем все возможные веса
      // Если можно достичь веса (w - weights[i]) и добавление текущего предмета улучшает результат
      if (dp[w - weights[i]] != INT_MAX && 
          dp[w - weights[i]] + taxes[i] < dp[w]) {
        dp[w] = dp[w - weights[i]] + taxes[i];  // Обновляем минимальное налоговое бремя
        selected[w] = selected[w - weights[i]];  // Копируем набор предметов для веса (w - weights[i])
        selected[w][i] = true;  // Добавляем текущий предмет в набор
      }
    }
  }

  // Находим минимальное налоговое бремя для весов >= min_weight
  int min_tax = INT_MAX;
  int best_weight = 0;  // Вес, соответствующий минимальному налоговому бремени
  std::vector<bool> best_selection(num_items, false);  // Набор предметов, дающий минимальное налоговое бремя

  for (int w = min_weight; w <= total_weight; ++w) {  // Перебираем все веса >= min_weight
    if (dp[w] < min_tax) {  // Если найдено лучшее решение
      min_tax = dp[w];  // Обновляем минимальное налоговое бремя
      best_weight = w;  // Запоминаем вес
      best_selection = selected[w];  // Запоминаем набор предметов
    }
  }

  // Вывод результата
  if (min_tax == INT_MAX) {  // Если решение не найдено
    std::cout << "Невозможно достичь минимального веса " << min_weight << std::endl;
  } else {  // Если решение найдено
    std::cout << "Порядковые номера выбранных предметов: ";
    for (int i = 0; i < num_items; ++i) {
      if (best_selection[i]) {
        std::cout << i + 1 << " ";
      }
    }
    std::cout << std::endl;

    // Выводим общий вес и итоговое налоговое бремя
    std::cout << "Общий вес: " << best_weight << " кг" << std::endl;
    std::cout << "Итоговое налогообложение: " << min_tax << std::endl;
  }
}
