#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define MAX_BARANG 100
#define MAX_RAK 5

typedef struct {
    int id;
    char nama[50];
    char kategori[30];
    int stok;
    char lokasi[10];
} Barang;

typedef struct Riwayat {
    int idTransaksi;
    int idBarang;
    char namaBarang[50];
    int jumlah;
    char jenis[10];
    char tanggal[20];
    struct Riwayat* next;
} Riwayat;

Barang daftarBarang[MAX_BARANG];
int jumlahBarang = 0;
Riwayat* headRiwayat = NULL;
int idTransaksiCounter = 1001;
char rakGudang[MAX_RAK][MAX_RAK][10];

void menuUtama();
void menuDataBarang();
void menuTataLetakGudang();
void menuTransaksiMasuk();
void menuTransaksiKeluar();
void menuLaporan();
void menuAuthor();

void tambahBarang();
void tampilkanBarang();
void cariBarang();
void ubahBarang();
void hapusBarang();
void urutkanBarang();

void inisialisasiRak();
void tampilkanRak();
void isiRak();

void transaksiMasuk();
void transaksiKeluar();

void tampilkanLaporan();

void catatRiwayat(int idBarang, char* nama, int jumlah, char* jenis);
void tampilkanRiwayat();

void simpanData();
void muatData();

void pressEnter();
void bersihkanBuffer();

int main() {
    muatData();
    inisialisasiRak();
    menuUtama();
    return 0;
}

void pressEnter() {
    printf("\nTekan Enter untuk melanjutkan...");
    getch();
}

void bersihkanBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void menuUtama() {
    int pilihan;
    do {
        system("cls");
        printf("========================================\n");
        printf("     SISTEM MANAJEMEN GUDANG\n");
        printf("========================================\n");
        printf("1. Data Barang\n");
        printf("2. Tata Letak Gudang\n");
        printf("3. Transaksi Barang Masuk\n");
        printf("4. Transaksi Barang Keluar\n");
        printf("5. Laporan Gudang\n");
        printf("6. Riwayat Transaksi\n");
        printf("7. Author\n");
        printf("8. Keluar\n");
        printf("========================================\n");
        printf("Pilih Menu [1-8]: ");
        
        if(scanf("%d", &pilihan) != 1) {
            bersihkanBuffer();
            pilihan = 0;
        }

        switch(pilihan) {
            case 1: menuDataBarang(); break;
            case 2: menuTataLetakGudang(); break;
            case 3: transaksiMasuk(); break;
            case 4: transaksiKeluar(); break;
            case 5: tampilkanLaporan(); break;
            case 6: tampilkanRiwayat(); break;
            case 7: menuAuthor(); break;
            case 8: 
                simpanData();
                printf("Data berhasil disimpan. Terima kasih!\n");
                exit(0); 
                break;
            default: 
                printf("Pilihan tidak valid!\n");
                pressEnter();
        }
    } while(pilihan != 8);
}

void menuDataBarang() {
    int pilihan;
    do {
        system("cls");
        printf("========== MENU DATA BARANG ==========\n");
        printf("1. Tambah Barang\n");
        printf("2. Tampilkan Barang\n");
        printf("3. Cari Barang\n");
        printf("4. Ubah Barang\n");
        printf("5. Hapus Barang\n");
        printf("6. Urutkan Barang\n");
        printf("7. Kembali\n");
        printf("======================================\n");
        printf("Pilih: ");
        
        if(scanf("%d", &pilihan) != 1) {
            bersihkanBuffer();
            pilihan = 0;
        }

        switch(pilihan) {
            case 1: tambahBarang(); break;
            case 2: tampilkanBarang(); break;
            case 3: cariBarang(); break;
            case 4: ubahBarang(); break;
            case 5: hapusBarang(); break;
            case 6: urutkanBarang(); break;
            case 7: return;
            default: 
                printf("Pilihan salah!\n");
                pressEnter();
        }
    } while(pilihan != 7);
}

void menuTataLetakGudang() {
    int pilihan;
    do {
        system("cls");
        printf("======== TATA LETAK GUDANG =========\n");
        printf("1. Visualisasi Rak Gudang\n");
        printf("2. Isi Barang ke Rak\n");
        printf("3. Kembali\n");
        printf("====================================\n");
        printf("Pilih: ");
        
        if(scanf("%d", &pilihan) != 1) {
            bersihkanBuffer();
            pilihan = 0;
        }

        switch(pilihan) {
            case 1: tampilkanRak(); break;
            case 2: isiRak(); break;
            case 3: return;
            default: 
                printf("Pilihan salah!\n");
                pressEnter();
        }
    } while(pilihan != 3);
}

void tambahBarang() {
    system("cls");
    printf("=========== TAMBAH BARANG ============\n");
    if(jumlahBarang >= MAX_BARANG) {
        printf("Gudang penuh! Tidak bisa menambah barang.\n");
        pressEnter();
        return;
    }
    
    printf("ID Barang   : ");
    scanf("%d", &daftarBarang[jumlahBarang].id);
    bersihkanBuffer();
    
    printf("Nama Barang : ");
    fgets(daftarBarang[jumlahBarang].nama, 50, stdin);
    daftarBarang[jumlahBarang].nama[strcspn(daftarBarang[jumlahBarang].nama, "\n")] = 0;
    
    printf("Kategori    : ");
    fgets(daftarBarang[jumlahBarang].kategori, 30, stdin);
    daftarBarang[jumlahBarang].kategori[strcspn(daftarBarang[jumlahBarang].kategori, "\n")] = 0;
    
    printf("Stok Awal   : ");
    scanf("%d", &daftarBarang[jumlahBarang].stok);
    bersihkanBuffer();
    
    printf("Lokasi Rak  : ");
    fgets(daftarBarang[jumlahBarang].lokasi, 10, stdin);
    daftarBarang[jumlahBarang].lokasi[strcspn(daftarBarang[jumlahBarang].lokasi, "\n")] = 0;
    
    jumlahBarang++;
    printf("\nBarang berhasil ditambahkan!\n");
    pressEnter();
}

void tampilkanBarang() {
    system("cls");
    printf("============== DAFTAR BARANG ==============\n");
    if(jumlahBarang == 0) {
        printf("Belum ada data barang.\n");
        pressEnter();
        return;
    }
    
    for(int i=0; i<78; i++) printf("-");
    printf("\n");
    printf("| %-5s | %-20s | %-15s | %-6s | %-10s |\n", "ID", "Nama", "Kategori", "Stok", "Lokasi");
    for(int i=0; i<78; i++) printf("-");
    printf("\n");
    
    for(int i=0; i<jumlahBarang; i++) {
        printf("| %-5d | %-20s | %-15s | %-6d | %-10s |\n", 
            daftarBarang[i].id, daftarBarang[i].nama, daftarBarang[i].kategori, 
            daftarBarang[i].stok, daftarBarang[i].lokasi);
    }
    for(int i=0; i<78; i++) printf("-");
    printf("\n");
    pressEnter();
}

void cariBarang() {
    system("cls");
    printf("============= CARI BARANG =============\n");
    if(jumlahBarang == 0) {
        printf("Belum ada data barang.\n");
        pressEnter();
        return;
    }
    
    int cariID;
    printf("Masukkan ID Barang yang dicari: ");
    scanf("%d", &cariID);
    bersihkanBuffer();
    
    int ketemu = -1;
    for(int i=0; i<jumlahBarang; i++) {
        if(daftarBarang[i].id == cariID) {
            ketemu = i;
            break;
        }
    }
    
    if(ketemu != -1) {
        printf("\nBarang Ditemukan!\n");
        printf("ID       : %d\n", daftarBarang[ketemu].id);
        printf("Nama     : %s\n", daftarBarang[ketemu].nama);
        printf("Kategori : %s\n", daftarBarang[ketemu].kategori);
        printf("Stok     : %d\n", daftarBarang[ketemu].stok);
        printf("Lokasi   : %s\n", daftarBarang[ketemu].lokasi);
    } else {
        printf("\nBarang dengan ID %d tidak ditemukan.\n", cariID);
    }
    pressEnter();
}

void ubahBarang() {
    system("cls");
    printf("============= UBAH BARANG =============\n");
    if(jumlahBarang == 0) {
        printf("Belum ada data barang.\n");
        pressEnter();
        return;
    }
    
    int cariID;
    printf("Masukkan ID Barang yang ingin diubah: ");
    scanf("%d", &cariID);
    bersihkanBuffer();
    
    int ketemu = -1;
    for(int i=0; i<jumlahBarang; i++) {
        if(daftarBarang[i].id == cariID) {
            ketemu = i;
            break;
        }
    }
    
    if(ketemu != -1) {
        printf("Data lama: %s | Stok: %d\n", daftarBarang[ketemu].nama, daftarBarang[ketemu].stok);
        printf("\nMasukkan data baru (tekan enter jika tidak ingin mengubah):\n");
        
        char tempNama[50];
        printf("Nama Baru (%s): ", daftarBarang[ketemu].nama);
        fgets(tempNama, 50, stdin);
        if(strlen(tempNama) > 1) {
            tempNama[strcspn(tempNama, "\n")] = 0;
            strcpy(daftarBarang[ketemu].nama, tempNama);
        }
        
        int tempStok;
        printf("Stok Baru (%d): ", daftarBarang[ketemu].stok);
        if(scanf("%d", &tempStok) == 1) {
            daftarBarang[ketemu].stok = tempStok;
        }
        bersihkanBuffer();
        
        printf("\nData barang berhasil diubah!\n");
    } else {
        printf("Barang dengan ID %d tidak ditemukan.\n", cariID);
    }
    pressEnter();
}

void hapusBarang() {
    system("cls");
    printf("============= HAPUS BARANG =============\n");
    if(jumlahBarang == 0) {
        printf("Belum ada data barang.\n");
        pressEnter();
        return;
    }
    
    int cariID;
    printf("Masukkan ID Barang yang ingin dihapus: ");
    scanf("%d", &cariID);
    bersihkanBuffer();
    
    int ketemu = -1;
    for(int i=0; i<jumlahBarang; i++) {
        if(daftarBarang[i].id == cariID) {
            ketemu = i;
            break;
        }
    }
    
    if(ketemu != -1) {
        for(int i=ketemu; i<jumlahBarang-1; i++) {
            daftarBarang[i] = daftarBarang[i+1];
        }
        jumlahBarang--;
        printf("Barang berhasil dihapus!\n");
    } else {
        printf("Barang dengan ID %d tidak ditemukan.\n", cariID);
    }
    pressEnter();
}

void urutkanBarang() {
    system("cls");
    printf("============= URUTKAN BARANG =============\n");
    if(jumlahBarang == 0) {
        printf("Belum ada data barang.\n");
        pressEnter();
        return;
    }
    
    for(int i=0; i<jumlahBarang-1; i++) {
        for(int j=0; j<jumlahBarang-i-1; j++) {
            if(daftarBarang[j].stok > daftarBarang[j+1].stok) {
                Barang temp = daftarBarang[j];
                daftarBarang[j] = daftarBarang[j+1];
                daftarBarang[j+1] = temp;
            }
        }
    }
    printf("Data berhasil diurutkan berdasarkan stok terendah!\n");
    tampilkanBarang();
}

void inisialisasiRak() {
    for(int i=0; i<MAX_RAK; i++) {
        for(int j=0; j<MAX_RAK; j++) {
            strcpy(rakGudang[i][j], "[Kosong]");
        }
    }
}

void tampilkanRak() {
    system("cls");
    printf("========= VISUALISASI RAK GUDANG =========\n");
    printf("       (Array 2 Dimensi / Matriks 5x5)\n\n");
    
    for(int i=0; i<MAX_RAK; i++) {
        for(int j=0; j<MAX_RAK; j++) {
            printf("+----------");
        }
        printf("+\n");
        for(int j=0; j<MAX_RAK; j++) {
            printf("| %-9s", rakGudang[i][j]);
        }
        printf("|\n");
    }
    for(int j=0; j<MAX_RAK; j++) {
        printf("+----------");
    }
    printf("+\n");
    pressEnter();
}

void isiRak() {
    system("cls");
    printf("============= ISI BARANG KE RAK =============\n");
    int bar, kol;
    char isi[10];
    
    printf("Masukkan Baris Rak (0-4): ");
    scanf("%d", &bar);
    printf("Masukkan Kolom Rak (0-4): ");
    scanf("%d", &kol);
    bersihkanBuffer();
    
    if(bar >= 0 && bar < MAX_RAK && kol >= 0 && kol < MAX_RAK) {
        printf("Masukkan Kode/ID Barang untuk rak ini: ");
        fgets(isi, 10, stdin);
        isi[strcspn(isi, "\n")] = 0;
        
        if(strlen(isi) > 0) {
            strncpy(rakGudang[bar][kol], isi, 9);
            rakGudang[bar][kol][9] = '\0';
            printf("Rak [%d][%d] berhasil diisi dengan: %s\n", bar, kol, rakGudang[bar][kol]);
        }
    } else {
        printf("Posisi rak tidak valid!\n");
    }
    pressEnter();
}

void transaksiMasuk() {
    system("cls");
    printf("========= TRANSAKSI BARANG MASUK =========\n");
    if(jumlahBarang == 0) {
        printf("Belum ada data barang. Silakan tambah barang terlebih dahulu.\n");
        pressEnter();
        return;
    }
    
    tampilkanBarang();
    int cariID, jumlah;
    printf("Masukkan ID Barang: ");
    scanf("%d", &cariID);
    printf("Masukkan Jumlah Masuk: ");
    scanf("%d", &jumlah);
    bersihkanBuffer();
    
    int ketemu = -1;
    for(int i=0; i<jumlahBarang; i++) {
        if(daftarBarang[i].id == cariID) {
            ketemu = i;
            break;
        }
    }
    
    if(ketemu != -1) {
        if(jumlah > 0) {
            daftarBarang[ketemu].stok += jumlah;
            catatRiwayat(cariID, daftarBarang[ketemu].nama, jumlah, "Masuk");
            printf("\nTransaksi berhasil! Stok %s bertambah %d.\n", daftarBarang[ketemu].nama, jumlah);
        } else {
            printf("\nJumlah harus lebih dari 0!\n");
        }
    } else {
        printf("\nBarang dengan ID %d tidak ditemukan.\n", cariID);
    }
    pressEnter();
}

void transaksiKeluar() {
    system("cls");
    printf("========= TRANSAKSI BARANG KELUAR =========\n");
    if(jumlahBarang == 0) {
        printf("Belum ada data barang.\n");
        pressEnter();
        return;
    }
    
    tampilkanBarang();
    int cariID, jumlah;
    printf("Masukkan ID Barang: ");
    scanf("%d", &cariID);
    printf("Masukkan Jumlah Keluar: ");
    scanf("%d", &jumlah);
    bersihkanBuffer();
    
    int ketemu = -1;
    for(int i=0; i<jumlahBarang; i++) {
        if(daftarBarang[i].id == cariID) {
            ketemu = i;
            break;
        }
    }
    
    if(ketemu != -1) {
        if(jumlah > 0) {
            if(daftarBarang[ketemu].stok > 0) {
                if(daftarBarang[ketemu].stok >= jumlah) {
                    daftarBarang[ketemu].stok -= jumlah;
                    catatRiwayat(cariID, daftarBarang[ketemu].nama, jumlah, "Keluar");
                    printf("\nTransaksi berhasil! Stok %s berkurang %d.\n", daftarBarang[ketemu].nama, jumlah);
                } else {
                    printf("\nGagal! Stok tidak mencukupi. Stok tersedia: %d\n", daftarBarang[ketemu].stok);
                }
            } else {
                printf("\nGagal! Stok barang sedang kosong.\n");
            }
        } else {
            printf("\nJumlah harus lebih dari 0!\n");
        }
    } else {
        printf("\nBarang dengan ID %d tidak ditemukan.\n", cariID);
    }
    pressEnter();
}

void tampilkanLaporan() {
    system("cls");
    printf("============== LAPORAN GUDANG ==============\n");
    printf("Laporan Barang dengan Stok Menipis (Stok <= 5):\n\n");
    
    int adaLaporan = 0;
    for(int i=0; i<jumlahBarang; i++) {
        if(daftarBarang[i].stok <= 5) {
            printf("ID: %d | Nama: %-20s | Stok: %d | Lokasi: %s\n", 
                daftarBarang[i].id, daftarBarang[i].nama, daftarBarang[i].stok, daftarBarang[i].lokasi);
            adaLaporan = 1;
        }
    }
    
    if(!adaLaporan) {
        printf("Tidak ada barang dengan stok menipis.\n");
    }
    pressEnter();
}

void catatRiwayat(int idBarang, char* nama, int jumlah, char* jenis) {
    Riwayat* baru = (Riwayat*)malloc(sizeof(Riwayat));
    baru->idTransaksi = idTransaksiCounter++;
    baru->idBarang = idBarang;
    strcpy(baru->namaBarang, nama);
    baru->jumlah = jumlah;
    strcpy(baru->jenis, jenis);
    strcpy(baru->tanggal, "2026-07-07"); 
    baru->next = headRiwayat;
    headRiwayat = baru;
}

void tampilkanRiwayat() {
    system("cls");
    printf("========= RIWAYAT TRANSAKSI (LINKED LIST) =========\n");
    Riwayat* curr = headRiwayat;
    if(curr == NULL) {
        printf("Belum ada riwayat transaksi.\n");
    } else {
        printf("%-5s | %-10s | %-20s | %-8s | %-8s\n", "ID", "Tanggal", "Nama Barang", "Jumlah", "Status");
        for(int i=0; i<70; i++) printf("-");
        printf("\n");
        while(curr != NULL) {
            printf("%-5d | %-10s | %-20s | %-8d | %-8s\n", 
                curr->idTransaksi, curr->tanggal, curr->namaBarang, curr->jumlah, curr->jenis);
            curr = curr->next;
        }
    }
    pressEnter();
}

void simpanData() {
    FILE* fBarang = fopen("data_barang.txt", "w");
    if(fBarang != NULL) {
        fprintf(fBarang, "%d\n", jumlahBarang);
        for(int i=0; i<jumlahBarang; i++) {
            fprintf(fBarang, "%d|%s|%s|%d|%s\n", 
                daftarBarang[i].id, daftarBarang[i].nama, daftarBarang[i].kategori, 
                daftarBarang[i].stok, daftarBarang[i].lokasi);
        }
        fclose(fBarang);
    }
    
    FILE* fRak = fopen("data_rak.txt", "w");
    if(fRak != NULL) {
        for(int i=0; i<MAX_RAK; i++) {
            for(int j=0; j<MAX_RAK; j++) {
                fprintf(fRak, "%s\n", rakGudang[i][j]);
            }
        }
        fclose(fRak);
    }
}

void muatData() {
    FILE* fBarang = fopen("data_barang.txt", "r");
    if(fBarang != NULL) {
        fscanf(fBarang, "%d\n", &jumlahBarang);
        for(int i=0; i<jumlahBarang; i++) {
            fscanf(fBarang, "%d|%[^|]|%[^|]|%d|%[^\n]\n", 
                &daftarBarang[i].id, daftarBarang[i].nama, 
                daftarBarang[i].kategori, &daftarBarang[i].stok, 
                daftarBarang[i].lokasi);
        }
        fclose(fBarang);
    }
    
    FILE* fRak = fopen("data_rak.txt", "r");
    if(fRak != NULL) {
        for(int i=0; i<MAX_RAK; i++) {
            for(int j=0; j<MAX_RAK; j++) {
                fscanf(fRak, "%[^\n]\n", rakGudang[i][j]);
            }
        }
        fclose(fRak);
    }
}

void menuAuthor() {
    system("cls");
    printf("========================================\n");
    printf("              AUTHOR                  \n");
    printf("========================================\n");
    printf("1. Efraim Bias Adisya\n");
    printf("2. Adrian Sinarta Putra Kurniawan\n");
    printf("3. Gunawan Wibisono\n");
    printf("4. Rey Nanda Indra Krisrahmanu\n");
    printf("========================================\n");
    printf("Pesan & Kesan:\n");
    printf("Selama mengikuti kelas Asisten Algoritma & Struktur Data C,\n");
    printf("saya belajar banyak tentang logika pemrograman, pointer,\n");
    printf("dan struktur data. Terima kasih atas bimbingannya!\n");
    printf("========================================\n");
    pressEnter();
}