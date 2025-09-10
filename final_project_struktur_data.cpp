#include <iostream>
#include <string>
#include <queue>
#include <limits>
using namespace std;

// STRUCT
struct Kereta {
    string nomorKereta, namaKereta, tujuan, tanggal, jam;
    int harga, kursi;
    Kereta* next;
};

struct Tiket {
    int id;
    string nama;
    string nomorKereta;
    int harga;
};

// LINKED LIST
Kereta* headKereta = NULL;

// QUEUE
queue<Tiket> antrean;

// ARRAY (riwayat pemrosesan tiket)
Tiket riwayat[500];
int jumlahRiwayat = 0;

// GLOBAL
int idCounter = 1;

// Tambah kereta (Linked List)
void tambahKereta(string no, string nama, string tujuan, string tgl, string jam, int harga, int kursi) {
    Kereta* baru = new Kereta{no, nama, tujuan, tgl, jam, harga, kursi, NULL};
    if (!headKereta) headKereta = baru;
    else {
        Kereta* temp = headKereta;
        while (temp->next) temp = temp->next;
        temp->next = baru;
    }
}

// Tampilkan daftar kereta
void tampilKereta() {
    if (!headKereta) { cout << "Belum ada kereta.\n"; return; }
    cout << "\n=== DAFTAR KERETA ===\n";
    Kereta* t = headKereta;
    while (t) {
        cout << "[" << t->nomorKereta << "] " << t->namaKereta 
             << " -> " << t->tujuan
             << " | Rp" << t->harga
             << " | Kursi tersedia: " << t->kursi << endl;
        t = t->next;
    }
}

// Cari kereta (linear)
Kereta* cariKereta(string no) {
    Kereta* t = headKereta;
    while (t) {
        if (t->nomorKereta == no) return t;
        t = t->next;
    }
    return NULL;
}

// Tampilkan antrean
void tampilAntrean() {
    if (antrean.empty()) { cout << "Antrean kosong.\n"; return; }
    cout << "\n=== ANTREAN TIKET ===\n";
    queue<Tiket> temp = antrean;
    while (!temp.empty()) {
        Tiket tk = temp.front(); temp.pop();
        cout << "ID " << tk.id << " | Nama: " << tk.nama
             << " | Kereta: " << tk.nomorKereta
             << " | Rp" << tk.harga << "\n";
    }
}

// Pesan tiket (kursi langsung dikurangi)
void pesanTiket() {
    string noKereta;
    int jml;
    cout << "Masukkan Nomor Kereta: "; cin >> noKereta;
    Kereta* k = cariKereta(noKereta);
    if (!k) { cout << "Kereta tidak ditemukan.\n"; return; }

    cout << "Jumlah tiket yang ingin dipesan: "; cin >> jml;
    if (jml <= 0) { cout << "Jumlah harus > 0.\n"; return; }
    if (jml > k->kursi) { cout << "Jumlah melebihi kursi tersedia (" << k->kursi << ").\n"; return; }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Masukkan nama penumpang untuk tiap tiket.\n";
    for (int i = 1; i <= jml; ++i) {
        string namaPenumpang;
        cout << "  Nama penumpang ke-" << i << ": ";
        getline(cin, namaPenumpang);
        if (namaPenumpang.empty()) { cout << "  Nama tidak boleh kosong. Mohon ulangi.\n"; --i; continue; }

        Tiket t;
        t.id = idCounter++;
        t.nama = namaPenumpang;
        t.nomorKereta = noKereta;
        t.harga = k->harga;
        antrean.push(t);

        // kurangi kursi karena sudah dipesan
        k->kursi--;

        cout << "  -> Tiket dibuat: ID " << t.id << " | " << t.nama << " | Kereta " << t.nomorKereta << "\n";
    }

    cout << jml << " tiket berhasil dipesan.\n";
    cout << "Sisa kursi: " << k->kursi << "\n";
}

// Proses tiket (pindah ke riwayat)
void prosesTiket() {
    if (antrean.empty()) { cout << "Antrean kosong.\n"; return; }

    tampilAntrean();
    int id; cout << "Masukkan ID tiket yang akan diproses: "; cin >> id;

    queue<Tiket> temp;
    bool found = false;
    while (!antrean.empty()) {
        Tiket t = antrean.front(); antrean.pop();
        if (t.id == id) {
            if (jumlahRiwayat < (int)(sizeof(riwayat)/sizeof(riwayat[0]))) {
                riwayat[jumlahRiwayat++] = t;
            }
            cout << "Tiket ID " << t.id << " diproses: Nama " << t.nama
                 << " | Kereta " << t.nomorKereta << " | Total Rp" << t.harga << "\n";
            found = true;
        } else {
            temp.push(t);
        }
    }
    antrean = temp;
    if (!found) cout << "Tiket dengan ID tersebut tidak ditemukan di antrean.\n";
}

// Ubah nama tiket di antrean
void ubahTiket() {
    if (antrean.empty()) { cout << "Antrean kosong.\n"; return; }
    int id; cout << "Masukkan ID tiket yang ingin diubah: "; cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string newName; cout << "Masukkan nama baru: "; getline(cin, newName);
    if (newName.empty()) { cout << "Nama tidak boleh kosong.\n"; return; }

    queue<Tiket> temp;
    bool found = false;
    while (!antrean.empty()) {
        Tiket t = antrean.front(); antrean.pop();
        if (t.id == id) {
            t.nama = newName;
            cout << "Tiket ID " << id << " berhasil diubah nama menjadi: " << newName << "\n";
            found = true;
        }
        temp.push(t);
    }
    antrean = temp;
    if (!found) cout << "Tiket tidak ditemukan di antrean.\n";
}

// Hapus tiket (kursi bertambah kembali)
void hapusTiket() {
    if (antrean.empty()) { cout << "Antrean kosong.\n"; return; }
    int id; cout << "Masukkan ID tiket yang ingin dihapus: "; cin >> id;
    queue<Tiket> temp;
    bool found = false;
    while (!antrean.empty()) {
        Tiket t = antrean.front(); antrean.pop();
        if (t.id == id) {
            Kereta* k = cariKereta(t.nomorKereta);
            if (k) k->kursi++; // kembalikan kursi
            cout << "Tiket ID " << id << " dihapus dari antrean.\n";
            found = true;
        } else temp.push(t);
    }
    antrean = temp;
    if (!found) cout << "Tiket tidak ditemukan di antrean.\n";
}

// Tampilkan riwayat
void tampilRiwayat() {
    if (jumlahRiwayat == 0) { cout << "Belum ada riwayat pemrosesan.\n"; return; }
    cout << "\n=== RIWAYAT TIKET TERPROSES ===\n";
    for (int i = 0; i < jumlahRiwayat; ++i) {
        cout << i+1 << ". ID " << riwayat[i].id << " | " << riwayat[i].nama
             << " | Kereta " << riwayat[i].nomorKereta
             << " | Rp" << riwayat[i].harga << "\n";
    }
}

// Sorting kereta berdasarkan harga
void sortKeretaByHarga() {
    Kereta* arr[100]; int n = 0;
    Kereta* t = headKereta;
    while (t && n < 100) { arr[n++] = t; t = t->next; }

    for (int i = 0; i < n-1; ++i) {
        for (int j = 0; j < n-i-1; ++j) {
            if (arr[j]->harga > arr[j+1]->harga) {
                Kereta* tmp = arr[j]; arr[j] = arr[j+1]; arr[j+1] = tmp;
            }
        }
    }
    cout << "\n=== KERETA (SORT BY HARGA ASCENDING) ===\n";
    for (int i = 0; i < n; ++i) {
        cout << "[" << arr[i]->nomorKereta << "] " << arr[i]->namaKereta << " Rp" << arr[i]->harga
             << " | Kursi: " << arr[i]->kursi << "\n";
    }
}

// Cari tiket di riwayat
void cariTiketDiRiwayat() {
    if (jumlahRiwayat == 0) { cout << "Riwayat kosong.\n"; return; }
    int id; cout << "Masukkan ID tiket yang dicari di riwayat: "; cin >> id;
    for (int i = 0; i < jumlahRiwayat; ++i) {
        if (riwayat[i].id == id) {
            cout << "Tiket ditemukan di riwayat: ID " << riwayat[i].id
                 << " | Nama: " << riwayat[i].nama
                 << " | Kereta: " << riwayat[i].nomorKereta << "\n";
            return;
        }
    }
    cout << "Tiket tidak ditemukan di riwayat.\n";
}

// MAIN
int main() {
    tambahKereta("KA01", "Argo Bromo", "Jakarta", "11-09-2025", "08:00", 300000, 50);
    tambahKereta("KA02", "Matarmaja", "Malang", "11-09-2025", "10:00", 150000, 100);
    tambahKereta("KA03", "Gajayana", "Yogyakarta", "12-09-2025", "09:30", 250000, 70);

    int pilih;
    do {
        cout << "\n=== MENU USER ===\n";
        cout << "1. Lihat Daftar Kereta\n";
        cout << "2. Lihat Antrean Tiket (lihat ID)\n";
        cout << "3. Pesan Tiket\n";
        cout << "4. Proses Tiket\n";
        cout << "5. Ubah Nama Tiket di Antrean\n";
        cout << "6. Hapus Tiket di Antrean\n";
        cout << "7. Tampilkan Riwayat Tiket Terproses\n";
        cout << "8. Sort Kereta by Harga\n";
        cout << "9. Cari Tiket di Riwayat\n";
        cout << "10. Keluar\n";
        cout << "Pilih: "; cin >> pilih;

        switch (pilih) {
            case 1: tampilKereta(); break;
            case 2: tampilAntrean(); break;
            case 3: pesanTiket(); break;
            case 4: prosesTiket(); break;
            case 5: ubahTiket(); break;
            case 6: hapusTiket(); break;
            case 7: tampilRiwayat(); break;
            case 8: sortKeretaByHarga(); break;
            case 9: cariTiketDiRiwayat(); break;
            case 10: cout << "Keluar...\n"; break;
            default: cout << "Pilihan salah.\n";
        }
    } while (pilih != 10);

    return 0;
}
