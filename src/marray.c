/* MODUL TABEL INTEGER */
/* Versi II : dengan banyaknya elemen didefinisikan secara eksplisit,
   memori tabel dinamik */

/* Tugas Kelas Algoritma & Struktur Data */
/* Name1	: Fadhil Imam Kurnia - 13615146 */
/* Name2 	: Muhammad Hilmi Asyrofi - 13515083 */
/* File 	: marray.c */
/* Date 	: 8 September 2016 */

#include "array.h"
#include "assert.h"
#include <stdio.h>

int main(){
  /* Kamus */
  TabInt T;
  int N;

  /* Algoritma */
  printf("> Test I/O  ...\n");
  printf("Masukkan elemen tabel, akhiri dengan -9999\n");
  BacaIsiTab(&T);
  TulisIsi(T);
  TulisIsiTab(T);printf(" Jumlah :%d\n", NbElmt(T));
  printf("Masukkan jumlah elemen lalu isi tabel\n");
  BacaIsi(&T);
  TulisIsi(T);
  TulisIsiTab(T);printf(" Jumlah :%d\n", NbElmt(T));

  printf("> Test selektor ...\n");
  MakeEmpty(&T,5);
  AddAsLastEl(&T,8);
  assert(GetFirstIdx(T)<=GetLastIdx(T));
  assert(IsIdxValid(T,IdxMin));
  assert(IsIdxEff(T,IdxMin));
  printf("> Test Kosong / Penuh ...\n");
  MakeEmpty(&T,1);
  assert(IsEmpty(T));
  AddAsLastEl(&T,8);
  assert(IsFull(T));
  printf("> Test Operator Aritmatika ...\n");
  TabInt T1,T2;
  MakeEmpty(&T1,5);
  AddAsLastEl(&T1, 5);
  AddAsLastEl(&T1, 2);
  AddAsLastEl(&T1, 4);
  AddAsLastEl(&T1, 3);
  AddAsLastEl(&T1, 1);
  printf("Mencetak T1\n");
  TulisIsiTab(T1);
  printf("\n");

  MakeEmpty(&T2,5);
  AddAsLastEl(&T2, 1);
  AddAsLastEl(&T2, 2);
  AddAsLastEl(&T2, 3);
  AddAsLastEl(&T2, 4);
  AddAsLastEl(&T2, 5);
  printf("Mencetak T2\n");
  TulisIsiTab(T2);
  printf("\n");

  printf("PlusTab\n");
  TulisIsiTab(PlusTab(T1,T2));
  printf("\n");
  printf("\n");


  printf("MinusTab\n");
  TulisIsiTab(MinusTab(T1,T2));
  printf("\n");
  printf("\n");


  printf("KaliTab\n");
  TulisIsiTab(KaliTab(T1,T2));
  printf("\n");
  printf("\n");

  printf("KaliKons\n");
  printf("masukkan konstanta: ");
  ElType cons;
  scanf("%d",&cons);
  TulisIsiTab(KaliKons(T1, cons));
  printf("\n\n");

  printf("> Test Operator Relasional ...\n");
  printf("Apakah T1 dan T2 sama? \n ");
  if (IsEQ(T1,T2))
    printf("Ya");
  else
    printf("Tidak");

  printf("Apakah T1 < T2 ? \n ");
  if (IsLess(T1,T2))
    printf("Ya");
  else
    printf("Tidak");


  printf("> Test Searching ...\n");
  assert(Search1(T1, 0) == IdxUndef);
  assert(Search1(T1, 1) == 5);
  assert(Search1(T1, 5) == 1);
  assert(Search1(T1, 2) == 2);
  assert(Search1(T1, 1) == 5);
  assert(Search1(T1, 6) == IdxUndef);

  assert(Search2(T1, 0) == IdxUndef);
  assert(Search2(T1, 1) == 5);
  assert(Search2(T1, 5) == 1);
  assert(Search2(T1, 2) == 2);
  assert(Search2(T1, 1) == 5);
  assert(Search2(T1, 6) == IdxUndef);

  assert(!SearchB(T1, 0));
  assert(SearchB(T1, 1));
  assert(SearchB(T1, 5));
  assert(SearchB(T1, 2));
  assert(SearchB(T1, 1));
  assert(!SearchB(T1, 6));

  assert(!SearchSentinel(T1, 0));
  assert(SearchSentinel(T1, 1));
  assert(SearchSentinel(T1, 5));
  assert(SearchSentinel(T1, 2));
  assert(SearchSentinel(T1, 1));
  assert(!SearchSentinel(T1, 6));

  printf("> Test Nilai Ekstrem ...\n");
  printf("Nilai maksimum dan minimum dari T1 berturut-turut yaitu %d dan %d\n", ValMax(T1), ValMin(T1));

  printf("> Test Operasi Lain ...\n");
  printf("Dibuat T3 dengan copy T1 kemudian menulsinya\n");
  TabInt T3,T4;
  MakeEmpty(&T3,10);
  MakeEmpty(&T4,10);
  CopyTab(T1,&T3);
  TulisIsiTab(T3);
  printf("\n T3 di-Inverse ke T4\n");
  T4 = InverseTab(T3);
  TulisIsiTab(T4);
  printf("\n");
  printf("Apakah T4 simetris? \n");
  if (IsSimetris(T4))
    printf("Ya\n");
  else
    printf("Tidak \n");
  printf("\n");

  printf("> Test Sorting...\n");
  printf("MaxSortDesc T3\n");
  MaxSortDesc(&T3);
  TulisIsiTab(T3);
  printf("\n");

  printf("InsSortAsc T3\n");
  InsSortAsc(&T3);
  TulisIsiTab(T3);
  printf("\n\n");

  printf("> Test Menambah Elemen...\n");
  printf("Masukkan elemen yang akan ditambah: ");
  ElType x;
  scanf("%d",&x);
  printf("Masukkan indeks elemen yang akan ditambah: ");
  IdxType idx;
  scanf("%d",&idx);
  printf("Menambahkan %d ke indeks %d pada T3", x, idx);
  AddEli(&T3,x,idx);
  TulisIsiTab(T3);
  printf("\n");
  printf("\n");
  printf("\n");

  printf("Menambahkan ke indeks terakhir pada T3");
  AddAsLastEl(&T3,354);
  TulisIsiTab(T3);printf(" Jumlah: %d", NbElmt(T));
  Dealokasi(&T);

  return 0;
}
