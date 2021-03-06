/* MODUL TABEL INTEGER */
/* Versi II : dengan banyaknya elemen didefinisikan secara eksplisit,
   memori tabel dinamik */

/* Tugas Kelas Algoritma & Struktur Data */
/* Name1	: Fadhil Imam Kurnia - 13615146 */
/* Name2 	: Muhammad Hilmi Asyrofi - 13515083 */
/* File 	: array.c */
/* Date 	: 8 September 2016 */

#include "array.h"
#include <stdio.h>
#include <stdlib.h>

/* ********** KONSTRUKTOR ********** */
void MakeEmpty (TabInt* T, int maxel)
/* I.S. T sembarang, maxel >= 0 */
/* F.S. Terbentuk tabel T kosong dengan kapasitas maxel+1 */
{

  TI(*T) = (ElType *)malloc((maxel+1)*sizeof(ElType)); /* TI(*T) dialokasi sebesar (maxel + 1) */

  /* Jika pengalokasian memori gagal, maka akan muncul pesan kesalahan alokasi*/
  /* Kemudian akan dilakukan pengalokasian memori kembali hingga berhasil */
  while(TI(*T)==NULL){
    printf("Terjadi kesalahan dalam alokasi memori array.c:21\n");
    printf("Mengulangi alokasi memori ...\n");
    TI(*T) = (ElType *)malloc((maxel+1)*sizeof(ElType));
  }
  MaxEl(*T) = maxel; /* pengalokasian memori berhasil dan diperoleh ukuran alokasi memori */
  Neff(*T) = 0;
}

void Dealokasi (TabInt *T)
/* I.S T terdefinisi;
	 F.S TI(T) dikembalikan ke sistem, MaxEl(T)=0; Neff(T)=0;
*/
{
  free(TI(*T)); /* Pengembalian memori ke sistem */
  MaxEl(*T)=0;
  Neff(*T)=0;
}

void AddContainer (TabInt *T)
/* I.S T terdefinisi;
	 F.S TI(T) bertambah alokasi memorinya untuk 1 data bertipe ElType;
*/
{
  /* Penambahan satu alokasi memori dari TI(*T) */
  TI(*T) = (ElType *)realloc(TI(*T),(MaxEl(*T)+1)*sizeof(ElType));

  /* Jika alokasi memori gagal, maka akan muncul pesan kesalahan */
  if(TI(*T)==NULL){
    printf("Terjadi kesalahan dalam alokasi memori array.c:47\n");
  }
  else {
    MaxEl(*T)++; /* Alokasi memori berhasil */
  }
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int NbElmt (TabInt T)
/* Mengirimkan banyaknya elemen efektif tabel */
/* Mengirimkan nol jika tabel kosong */
/* *** Daya tampung container *** */
{
  return Neff(T);
}

int MaxNbEl (TabInt T)
/* Mengirimkan maksimum elemen yang dapat ditampung oleh tabel */
{
  return MaxEl(T);
}

/* *** Selektor INDEKS *** */
IdxType GetFirstIdx (TabInt T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T pertama */
{
  return IdxMin;
}

IdxType GetLastIdx (TabInt T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T terakhir */
{
  return Neff(T);
}

/* ********** Test Indeks yang valid ********** */
boolean IsIdxValid (TabInt T, IdxType i)
/* Mengirimkan true jika i adalah indeks yang valid utk ukuran tabel */
/* yaitu antara indeks yang terdefinisi utk container*/
{
  return ( i>=IdxMin && i<=MaxEl(T) );
}

boolean IsIdxEff (TabInt T, IdxType i)
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk tabel */
/* yaitu antara FirstIdx(T)..LastIdx(T) */
{
  return ( i>=GetFirstIdx(T) && i<=GetLastIdx(T) );
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean IsEmpty (TabInt T)
/* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */
{
  return ( Neff(T)==0 );
}

/* *** Test tabel penuh *** */
boolean IsFull (TabInt T)
/* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */
{
  return ( Neff(T)==MaxEl(T) );
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi tabel dari pembacaan *** */
void BacaIsi (TabInt * T)
/* I.S. T sembarang */
/* F.S. Tabel T terdefinisi */
/* Proses : membaca banyaknya elemen T dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
/*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= MaxEl(T) */
/*    Jika N tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < N <= MaxNbEl(T){} Lakukan N kali: Baca elemen mulai dari indeks
      IdxMin satu per satu diakhiri enter */
/*    Jika N = 0{} hanya terbentuk T kosong */
{
  /* Kamus */
  IdxType N,i;
  ElType x;

  /* Algoritma */
  do {
    scanf("%d", &N);
  } while ( N<0 || N > MaxEl(*T) );

  MakeEmpty(&(*T),N);
  for (i = IdxMin; i <= N; i++) {
    scanf("%d", &x);
    Elmt(*T,i)=x;
  }

}

void BacaIsiTab (TabInt * T)
/* I.S. T sembarang */
/* F.S. Tabel T terdefinisi */
/* Proses : membaca elemen T sampai dimasukkan nilai -9999 */
/* Dibaca elemen satu per satu dan disimpan mulai dari IdxMin */
/* Pembacaan dihentikan jika pengguna memasukkan nilai -9999 */
/* Jika dari pertama dimasukkan nilai -9999 maka terbentuk T kosong */
{
  /* Kamus */
  IdxType i = IdxMin;
  ElType x;

  /* Algoritma */
  MakeEmpty(&(*T),0);
  do {
    scanf("%d", &x);
    if (x!=(-9999)) {
      AddContainer(&(*T));
      Elmt(*T,i) = x;
      Neff(*T)++;
      i++;
    }
  } while (x!=(-9999));

}

void TulisIsi (TabInt T)
/* Proses : Menuliskan isi tabel dengan traversal */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong : indeks dan elemen tabel ditulis berderet ke bawah */
/*      Jika T kosong : Hanya menulis "Tabel kosong" */
/* Contoh: Jika isi Tabel: [1, 20, 30, 50]
   Maka tercetak di layar:
   [1]1
   [2]20
   [3]30
   [4]50
*/
{
  /* Kamus */
  IdxType i;

  /* Algoritma */
  if (IsEmpty(T)) {
    printf("Tabel kosong\n");
  }else{
    for (i = GetFirstIdx(T); i <= GetLastIdx(T); i++) {
      printf("[%d]%d\n", i, Elmt(T,i));
    }
  }
}

void TulisIsiTab (TabInt T)
/* Proses : Menuliskan isi tabel dengan traversal, tabel ditulis di antara kurung siku{}
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika tabel kosong : menulis [] */
{
  /* Kamus */
  IdxType i;

  /* Algoritma */
  if (IsEmpty(T)) {
    printf("[]");
  }else{
    printf("[%d",Elmt(T,GetFirstIdx(T)));
    for (i = GetFirstIdx(T)+1; i <= GetLastIdx(T); i++) {
      printf(",%d", Elmt(T,i));
    }
    printf("]");
  }
}

/* ********** OPERATOR ARITMATIKA ********** */
/* *** Aritmatika tabel : Penjumlahan, pengurangan, perkalian, ... *** */
TabInt PlusTab (TabInt T1, TabInt T2)
/* Prekondisi : T1 dan T2 berukuran sama dan tidak kosong */
/* Mengirimkan  T1+T2, yaitu setiap elemen T1 dan T2 pada indeks yang sama dijumlahkan */
{
  /* Kamus */
  TabInt T;
  IdxType i;

  /* Algoritma */
  MakeEmpty(&T,NbElmt(T1));
  for (i = IdxMin; i <= GetLastIdx(T1); i++) {
    Elmt(T,i) = Elmt(T1,i) + Elmt(T2,i);
  }
  Neff(T)=Neff(T1);

  return T;
}
TabInt MinusTab (TabInt T1, TabInt T2)
/* Prekondisi : T1 dan T2 berukuran sama dan tidak kosong */
/* Mengirimkan T1-T2, yaitu setiap elemen T1 dikurangi elemen T2 pada indeks yang sama */
{
  /* Kamus */
  TabInt T;
  IdxType i;

  /* Algoritma */
  MakeEmpty(&T,NbElmt(T1));
  for (i = IdxMin; i <= GetLastIdx(T1); i++) {
    Elmt(T,i) = Elmt(T1,i) - Elmt(T2,i);
  }
  Neff(T)=Neff(T1);

  return T;
}

TabInt KaliTab (TabInt T1, TabInt T2)
/* Prekondisi : T1 dan T2 berukuran sama dan tidak kosong */
/* Mengirimkan T1 * T2 dengan definisi setiap elemen dengan indeks yang sama dikalikan */
{
  /* Kamus */
  TabInt T;
  IdxType i;

  /* Algoritma */
  MakeEmpty(&T,NbElmt(T1));
  for (i = IdxMin; i <= GetLastIdx(T1); i++) {
    Elmt(T,i) = Elmt(T1,i) * Elmt(T2,i);
  }
  Neff(T)=Neff(T1);

  return T;
}


TabInt KaliKons (TabInt Tin, ElType c)
/* Prekondisi : Tin tidak kosong */
/* Mengirimkan tabel dengan setiap elemen Tin dikalikan c */
{
  /* Kamus */
  TabInt T;
  IdxType i;

  /* Algoritma */
  MakeEmpty(&T,NbElmt(Tin));
  for (i = IdxMin; i <= GetLastIdx(Tin); i++) {
    Elmt(T,i) = Elmt(Tin,i) * c;
  }
  Neff(T)=Neff(Tin);

  return T;
}


/* ********** OPERATOR RELASIONAL ********** */
/* *** Operasi pembandingan tabel : < =, > *** */
boolean IsEQ (TabInt T1, TabInt T2)
/* Mengirimkan true jika T1 sama dengan T2 yaitu jika ukuran T1 = T2 dan semua elemennya sama */
{
  if (IsEmpty(T1) && IsEmpty(T2))
    return true;
  else if (NbElmt(T1) == NbElmt(T2)) {
    IdxType i = GetFirstIdx(T1);
    while (i < GetLastIdx(T1) && Elmt(T1,i) == Elmt(T2,i))
    i++;
    if (i == GetLastIdx(T1))
    return Elmt(T1,i) == Elmt(T2,i);
    else
    return false;
  } else
  return false;
}


boolean IsLess (TabInt T1, TabInt T2)
/* Mengirimkan true jika T1 < T2, */
/* yaitu : sesuai dg analogi 'Ali' < Badu'{} maka [0, 1] < [2, 3] */

/* ********** SEARCHING ********** */
/* ***  Perhatian : Tabel boleh kosong!! *** */
{
  IdxType i = GetFirstIdx(T1);
  while (i <= GetLastIdx(T1) && i <= GetLastIdx(T2)) {
    if (Elmt(T1,i) != Elmt(T2,i))
    return Elmt(T1,i) < Elmt(T2,i);
    i++;
  }
  return i > GetLastIdx(T1) && i <= GetLastIdx(T2);
}


IdxType Search1 (TabInt T, ElType X)
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = X */
/* Jika tidak ada, mengirimkan IdxUndef */
/* Menghasilkan indeks tak terdefinisi (IdxUndef) jika tabel T kosong */
/* Memakai skema search TANPA boolean */
{
  if (IsEmpty(T))
  return IdxUndef;
  else {
    IdxType i = GetFirstIdx(T);
    while (i <= GetLastIdx(T) && Elmt(T,i) != X)
    i++;
    if (i > GetLastIdx(T))
    return IdxUndef;
    else
    return i;
  }
}


IdxType Search2 (TabInt T, ElType X)
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = X */
/* Jika tidak ada, mengirimkan IdxUndef */
/* Menghasilkan indeks tak terdefinisi (IdxUndef) jika tabel T kosong */
/* Memakai skema search DENGAN boolean Found */
{
  if (IsEmpty(T))
  return IdxUndef;
  else {
    IdxType i = GetFirstIdx(T);
    IdxType idx;
    boolean found = false;
    while (!found && i <= GetLastIdx(T)) {
      found = Elmt(T,i) == X;
      idx = i;
      i++;
    }

    if (found)
    return idx;
    else
    return IdxUndef;
  }
}


boolean SearchB (TabInt T, ElType X)
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan true, jika tidak ada menghasilkan false */
/* Memakai Skema search DENGAN boolean */
{
  boolean found = false;
  IdxType i = GetFirstIdx(T);
  while (!found && i <= GetLastIdx(T))
  found = Elmt(T, i++) == X;
  return found;
}


boolean SearchSentinel (TabInt T, ElType X)
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan true, jika tidak ada menghasilkan false */
/* dengan metoda sequential search dengan sentinel */
/* Untuk sentinel, manfaatkan indeks ke-0 dalam definisi array dalam Bahasa C
   yang tidak dipakai dalam definisi tabel */
{
  Elmt(T,0) = X;
  IdxType i = GetLastIdx(T);
  while (i >= 0 && Elmt(T,i) != X)
    i--;
  return i > 0;
}


/* ********** NILAI EKSTREM ********** */
ElType ValMax (TabInt T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan nilai maksimum tabel */
{
  /* Kamus */
  ElType m = Elmt(T, GetFirstIdx(T));
  IdxType i;

  /* Algoritma */
  for (i = 2; i <= GetLastIdx(T); i++)
    if (Elmt(T,i) > m)
      m = Elmt(T,i);
  return m;
}


ElType ValMin (TabInt T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan nilai minimum tabel */
/* *** Mengirimkan indeks elemen bernilai ekstrem *** */
{
  ElType m = Elmt(T, GetFirstIdx(T));
  IdxType i;
  for (i = 2; i <= GetLastIdx(T); i++)
    if (Elmt(T,i) < m)
      m = Elmt(T,i);
  return m;
}


IdxType IdxMaxTab (TabInt T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks i terkecil dengan nilai elemen merupakan nilai maksimum pada tabel */
{
  IdxType j = GetFirstIdx(T);
  ElType m = Elmt(T, GetFirstIdx(T));
  IdxType i;
  for (i = 2; i <= GetLastIdx(T); i++)
    if (Elmt(T,i) > m) {
      m = Elmt(T,i);
      j = i;
    }
  return j;
}


IdxType IdxMinTab (TabInt T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks i terkecil dengan nilai elemen merupakan nilai minimum pada tabel */
{
  IdxType j = GetFirstIdx(T);
  ElType m = Elmt(T, GetFirstIdx(T));
  IdxType i;
  for (i = 2; i <= GetLastIdx(T); i++)
    if (Elmt(T,i) < m) {
      m = Elmt(T,i);
      j = i;
    }
  return j;
}



/* ********** OPERASI LAIN ********** */
void CopyTab (TabInt Tin, TabInt * Tout)
/* I.S. Tin terdefinisi, Tout sembarang */
/* F.S. Tout berisi salinan dari Tin (elemen dan ukuran identik) */
/* Proses : Menyalin isi Tin ke Tout */
{
  Neff(*Tout) = NbElmt(Tin);
  IdxType i;
  for (i = GetFirstIdx(Tin); i <= GetLastIdx(Tin); i++)
    Elmt(*Tout,i) = Elmt(Tin,i);
}


TabInt InverseTab (TabInt T)
/* Menghasilkan tabel dengan urutan tempat yang terbalik, yaitu : */
/* elemen pertama menjadi terakhir, */
/* elemen kedua menjadi elemen sebelum terakhir, dst.. */
/* Tabel kosong menghasilkan tabel kosong */
{
  TabInt hasil;
  MakeEmpty(&hasil, NbElmt(T));
  Neff(hasil) = Neff(T);

  IdxType i;
  for (i = GetFirstIdx(T); i <= GetLastIdx(T); i++)
    Elmt(hasil,i) = Elmt(T, GetLastIdx(T)-i+GetFirstIdx(T));

  return hasil;
}


boolean IsSimetris (TabInt T)
/* Menghasilkan true jika tabel simetrik */
/* Tabel disebut simetrik jika: */
/*      elemen pertama = elemen terakhir, */
/*      elemen kedua = elemen sebelum terakhir, dan seterusnya */
/* Tabel kosong adalah tabel simetris */
{
  if (IsEmpty(T))
    return true;
  else {
    IdxType i = GetFirstIdx(T);
    IdxType j = GetLastIdx(T);
    while (i < j && Elmt(T,i) == Elmt(T,j)) {
      i++;
      j--;
    }
    return i >= j;
  }
}



/* ********** SORTING ********** */
void MaxSortDesc (TabInt * T)
/* I.S. T boleh kosong */
/* F.S. T elemennya terurut menurun dengan Maximum Sort */
/* Proses : mengurutkan T sehingga elemennya menurun/mengecil */
/*          tanpa menggunakan tabel kerja */
{
  if (!IsEmpty(*T)) {
    IdxType i;
    for (i = GetFirstIdx(*T); i <= GetLastIdx(*T); i++) {
      IdxType j;
      for (j = i + 1; j <= GetLastIdx(*T); j++)
        if (Elmt(*T,i) < Elmt(*T,j)) {
          ElType temp = Elmt(*T,i);
          Elmt(*T,i) = Elmt(*T,j);
          Elmt(*T,j) = temp;
        }
    }
  }
}


void InsSortAsc (TabInt * T)
/* I.S. T boleh kosong */
/* F.S. T elemennya terurut menaik dengan Insertion Sort */
/* Proses : mengurutkan T sehingga elemennya menaik/membesar */
/*          tanpa menggunakan tabel kerja */
{
  if (!IsEmpty(*T)) {
    IdxType i;
    for (i = GetFirstIdx(*T); i <= GetLastIdx(*T); i++) {
      IdxType j = i - 1;
      ElType temp = Elmt(*T, i);
      while (j >= GetFirstIdx(*T) && Elmt(*T,j) > temp) {
        Elmt(*T,j+1) = Elmt(*T,j);
        j--;
      }
      Elmt(*T, j+1) = temp;
    }
  }
}

/* ********** MENAMBAH ELEMEN ********** */
/* *** Menambahkan elemen terakhir *** */
void AddAsLastEl (TabInt * T, ElType X)
/* Proses: Menambahkan X sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong*/
/* F.S. X adalah elemen terakhir T yang baru */
{
  /* Algoritma */
  /* jika tabel penuh -> tambah ukuran container */
  if (Neff(*T)==MaxEl(*T)) {
    AddContainer(&(*T));
  }
  Elmt(*T,GetLastIdx(*T)+1)=X;
  Neff(*T)++;
}
void AddEli (TabInt * T, ElType X, IdxType i)
/* Menambahkan X sebagai elemen ke-i tabel tanpa mengganggu kontiguitas
   terhadap elemen yang sudah ada */
/* I.S. Tabel tidak kosong dan tidak penuh */
/*      i adalah indeks yang valid. */
/* F.S. X adalah elemen ke-i T yang baru */
/* Proses : Geser elemen ke-i+1 s.d. terakhir */
/*          Isi elemen ke-i dengan X */
{
  /* Kamus */
  IdxType ix;


  /* Algoritma */
  /* jika tabel penuh -> tambah ukuran container */
  if (Neff(*T)==MaxEl(*T)) {
    AddContainer(&(*T));
  }

  for (ix = GetLastIdx(*T); ix >= i; ix--) {
    Elmt(*T,(ix+1)) = Elmt(*T,ix);
  }
  Elmt(*T,i)=X;
  Neff(*T)++;

}

/* ********** MENGHAPUS ELEMEN ********** */
void DelLastEl (TabInt * T, ElType * X)
/* Proses : Menghapus elemen terakhir tabel */
/* I.S. Tabel tidak kosong */
/* F.S. X adalah nilai elemen terakhir T sebelum penghapusan, */
/*      Banyaknya elemen tabel berkurang satu */
/*      Tabel T mungkin menjadi kosong */
{
  *X = Elmt(*T, GetLastIdx(*T));
  Neff(*T) -= 1;
}


void DelEli (TabInt * T, IdxType i, ElType * X)
/* Menghapus elemen ke-i tabel tanpa mengganggu kontiguitas */
/* I.S. Tabel tidak kosong, i adalah indeks efektif yang valid */
/* F.S. X adalah nilai elemen ke-i T sebelum penghapusan */
/*      Banyaknya elemen tabel berkurang satu */
/*      Tabel T mungkin menjadi kosong */
/* Proses : Geser elemen ke-i+1 s.d. elemen terakhir */
/*          Kurangi elemen efektif tabel */
{
  IdxType idx;
  *X = Elmt(*T, i);
  for (idx = i+1; idx <= GetLastIdx(*T); idx++)
    Elmt(*T,idx-1) = Elmt(*T,idx);
  Neff(*T) -= 1;
}



/* ********** TABEL DGN ELEMEN UNIK (SETIAP ELEMEN HANYA MUNCUL 1 KALI) ********** */
void AddElUnik (TabInt * T, ElType X)
/* Menambahkan X sebagai elemen terakhir tabel, pada tabel dengan elemen unik */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/*      dan semua elemennya bernilai unik, tidak terurut */
/* F.S. Jika tabel belum penuh, menambahkan X sbg elemen terakhir T,
        jika belum ada elemen yang bernilai X.
		Jika sudah ada elemen tabel yang bernilai X maka I.S. = F.S.
		dan dituliskan pesan "nilai sudah ada" */
/* Proses : Cek keunikan dengan sequential search dengan sentinel */
/*          Kemudian tambahkan elemen jika belum ada */
{
  if (SearchSentinel(*T, X)){
    printf("nilai sudah ada\n");
  }
  else {
    AddAsLastEl(T, X);
  }
}


/* ********** TABEL DGN ELEMEN TERURUT MEMBESAR ********** */
IdxType SearchUrut (TabInt T, ElType X)
/* Prekondisi: Tabel T boleh kosong. Jika tidak kosong, elemen terurut membesar. */
/* Mengirimkan indeks di mana harga X dengan indeks terkecil diketemukan */
/* Mengirimkan IdxUndef jika tidak ada elemen tabel bernilai X */
/* Menghasilkan indeks tak terdefinisi (IdxUndef) jika tabel kosong */
{
  return Search1(T,X);
}


ElType MaxUrut (TabInt T)
/* Prekondisi : Tabel tidak kosong, elemen terurut membesar */
/* Mengirimkan nilai maksimum pada tabel */
{
  return Elmt(T, GetLastIdx(T));
}


ElType MinUrut (TabInt T)
/* Prekondisi : Tabel tidak kosong, elemen terurut membesar */
/* Mengirimkan nilai minimum pada tabel*/
{
  return Elmt(T, GetFirstIdx(T));
}


void MaxMinUrut (TabInt T, ElType * Max, ElType * Min)
/* I.S. Tabel T tidak kosong, elemen terurut membesar */
/* F.S. Max berisi nilai maksimum T;
        Min berisi nilai minimum T */
{
  *Max = MaxUrut(T);
  *Min = MinUrut(T);
}


void Add1Urut (TabInt * T, ElType X)
/* Menambahkan X tanpa mengganggu keterurutan nilai dalam tabel */
/* Nilai dalam tabel tidak harus unik. */
/* I.S. Tabel T boleh kosong, boleh penuh. */
/*      Jika tabel isi, elemennya terurut membesar. */
/* F.S. Jika tabel belum penuh, menambahkan X. */
/*      Jika tabel penuh, maka tabel tetap. */
/* Proses : Search tempat yang tepat sambil geser */
/*          Insert X pada tempat yang tepat tersebut tanpa mengganggu keterurutan */
{
  if (!IsFull(*T)) {
    IdxType i = GetLastIdx(*T);
    while (i >= GetFirstIdx(*T) && Elmt(*T,i) > X) {
      Elmt(*T, i+1) = Elmt(*T,i);
      i--;
    }
    Neff(*T) += 1;
    Elmt(*T,i+1) = X;
  }
}


void Del1Urut (TabInt * T, ElType X)
/* Menghapus X yang pertama kali (pada indeks terkecil) yang ditemukan */
/* I.S. Tabel tidak kosong */
/* F.S. Jika ada elemen tabel bernilai X , */
/*      maka banyaknya elemen tabel berkurang satu. */
/*      Jika tidak ada yang bernilai X, tabel tetap. */
/*      Setelah penghapusan, elemen tabel tetap kontigu! */
/* Proses : Search indeks ke-i dengan elemen ke-i = X. */
/*          Delete jika ada. */
{
  IdxType i = Search1(*T, X);
  ElType tmp;
  if (i != IdxUndef)
    DelEli(T, i, &tmp);
}
