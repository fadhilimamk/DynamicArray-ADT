/* MODUL TABEL INTEGER */
/* Versi II : dengan banyaknya elemen didefinisikan secara eksplisit,
   memori tabel dinamik */

/* Tugas Kelas Algoritma & Struktur Data */
/* Name1	: Fadhil Imam Kurnia - 13615146 */
/* Name2 	: Muhammad Hilmi Asyrofi - 13515083 */
/* File 	: marray.c */
/* Date 	: 8 September 2016 */

#include "array.h"
#include <stdio.h>

int main(){
  TabInt T;
  BacaIsiTab(&T);
  TulisIsiTab(T);printf("%d", NbElmt(T));
  printf("\n---------------\n");
  AddAsLastEl(&T,354);
  TulisIsiTab(T);printf("%d", NbElmt(T));
  return 0;
}
