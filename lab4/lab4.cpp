// Задание ЛР3 (Вариант 4)
// На основе трёх равно размерных массивов A, B и C (длины N) функция возвращает сумму значений,
// полученных таким образом: если Ai четно: Bi + Ci, иначе Bi - Ai, неравных 1.

// Задание ЛР4
// Модифицировать программу, составленную по Заданию 1 в Л.Р. №3, используя синхронизацию вместо редукции.
// Измерять время работы программы для тех же значений параметров, что были использованы при выполнении Л.Р. №3.
// Результаты сравнить и занести в отчёт.

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

  begin = omp_get_wtime();
   #pragma omp parallel shared(A, B, C)
   {
     #pragma omp for private(i, r)
     for (i = 0; i < N; i++) {
       if (A[i] % 2) r = B[i] - A[i]; // нечётное
       else r = B[i] + C[i]; // четное

       if (r != 1)
          #pragma omp atomic
            total += r;

     }
   }
   end = omp_get_wtime();
   std::cout << "Atomic_Total (" << N << ") = " << total << " Time: " << end - begin << std::endl;

   total = 0;
   begin = omp_get_wtime();
    #pragma omp parallel shared(A, B, C)
    {
      #pragma omp for private(i, r)
      for (i = 0; i < N; i++) {
        if (A[i] % 2) r = B[i] - A[i]; // нечётное
        else r = B[i] + C[i]; // четное

        if (r != 1)
           #pragma omp critical
           if (r != 1)
             total += r;

      }
    }
    end = omp_get_wtime();
    std::cout << "Critic_Total (" << N << ") = " << total << " Time: " << end - begin << std::endl;

   //printArr(A,N);
   //printArr(B,N);
   //printArr(C,N);
   return 0;
}
