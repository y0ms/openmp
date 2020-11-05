// Задание 1(Вариант 4)
// На основе трёх равно размерных массивов A, B и C (длины N) функция возвращает сумму значений,
// полученных таким образом: если Ai четно: Bi + Ci, иначе Bi - Ai, неравных 1.

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
     #pragma omp for private(i, r) reduction(+:total)
     for (i = 0; i < N; i++) {
       if (A[i] % 2) r = B[i] - A[i]; // нечётное
       else r = B[i] + C[i]; // четное
       if (r != 1) total += r;
     }
   }
   end = omp_get_wtime();
   std::cout << "Paral_Total (" << N << ") = " << total << " Time: " << end - begin << std::endl;

   total = 0;
   begin = omp_get_wtime();
   for (i = 0; i < N; i++) {
     if (A[i] % 2) r = B[i] - A[i]; // нечётное
     else r = B[i] + C[i]; // четное
     if (r != 1) total += r;
   }
   end = omp_get_wtime();
   std::cout << "Serial_Total(" << N << ") = " << total << " Time: " << end - begin << std::endl;
   return 0;
}

/* Результаты:
Paral_Total (1000) = 48263 Time: 0.00200003
Serial_Total(1000) = 48263 Time: 0.00100005

Paral_Total (10000) = 484364 Time: 0.00299996
Serial_Total(10000) = 484364 Time: 0.000999987

Paral_Total (100000) = 4935172 Time: 0.00400001
Serial_Total(100000) = 4935172 Time: 0.000999987

Paral_Total (1000000) = 49211309 Time: 0.00600004
Serial_Total(1000000) = 49211309 Time: 0.013

Paral_Total (10000000) = 492254072 Time: 0.028
Serial_Total(10000000) = 492254072 Time: 0.139

Paral_Total (100000000) = 626848349 Time: 0.229
Serial_Total(100000000) = 626848349 Time: 1.312

Paral_Total (1000000000) = 1966335896 Time: 57.476
Serial_Total(1000000000) = 1966335896 Time: 99.985
*/
