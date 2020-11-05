// Задание ЛР3 (Вариант 4)
// На основе трёх равно размерных массивов A, B и C (длины N) функция возвращает сумму значений,
// полученных таким образом: если Ai четно: Bi + Ci, иначе Bi - Ai, неравных 1.

// Задание ЛР4
// Модифицировать программу, составленную по Заданию 1 в Л.Р. №3, используя синхронизацию вместо редукции.
// Измерять время работы программы для тех же значений параметров, что были использованы при выполнении Л.Р. №3.
// Результаты сравнить и занести в отчёт.

// Задание ЛР5
// Модифицировать программы, составленные в Л.Р. №№3,4, распределив вычислительную нагрузку по секциям (как минимум двумя способами).
// Измерять время работы программы для тех же значений параметров, что были использованы при выполнении Л.Р. №3.
// Результаты сравнить и занести в отчёт.

// Задание ЛР6_1
// Модифицировать программы, составленные в Л.Р. №№3,4, используя переменные семафорного типа.
// Измерять время работы программы для тех же значений параметров, что были использованы при выполнении Л.Р. №3.
// Результаты сравнить и занести в отчёт.

// Задание ЛР6_2
// Модифицировать программы, составленные в Л.Р. №№3,4, используя методы барьерной синхронизации.
// Измерять время работы программы для тех же значений параметров, что были использованы при выполнении Л.Р. №3

#include <omp.h>
#include <iostream>
#include <ctime>

void printArr(int * arr, int size){
  for (int i = 0; i < size; i++)
    std::cout << arr[i] << " ";
  std::cout << std::endl;
}

int main(int argc, char *argv[]) {
  int N = (argc == 2) ? atoi(argv[1]) : 10000;

  srand(time(NULL));

  double begin, end;
  int* A = new int[N];
  int* B = new int[N];
  int* C = new int[N];

  for (int i = 0; i < N; i++){
    A[i] = rand() % 100;
    B[i] = rand() % 100;
    C[i] = rand() % 100;
  }

  int total = 0;
  int i, r;

  // ЗАДАНИЕ 1

  omp_lock_t lock;
  omp_init_lock(&lock);

  begin = omp_get_wtime();
  #pragma omp parallel shared(total, A, B, C) private(i, r)
  #pragma omp for
  for (i = 0; i < N; i++){
    if (A[i] % 2) r = B[i] - A[i]; // нечётное
    else r = B[i] + C[i]; // четное

    omp_set_lock(&lock);
    total += (r != 1) ? r : 0;
    omp_unset_lock(&lock);
  }
  end = omp_get_wtime();
  std::cout << "Semaf_Total (" << N << ") = " << total << " Time: " << end - begin << std::endl;
  omp_destroy_lock(&lock);

  // ЗАДАНИЕ 2

  int* R = new int[N];
  total = 0;

  begin = omp_get_wtime();
  #pragma omp parallel
  {
    #pragma omp for private(i)
    for (i = 0; i < N; i++){
      if (A[i] % 2) R[i] = B[i] - A[i]; // нечётное
      else R[i] = B[i] + C[i]; // четное
      if (R[i] == 1) R[i] = 0;
    }
    #pragma omp barrier
    #pragma omp master
    {
       for (int j = 0; j < N; j++)
         total += R[j];
     }
  }
  end = omp_get_wtime();
  std::cout << "Barr_Total (" << N << ") = " << total << " Time: " << end - begin << std::endl;

   return 0;
}
