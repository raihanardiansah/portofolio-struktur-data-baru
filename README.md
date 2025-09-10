# APLIKASI PEMESANAN TIKET KERETA API
Program ini adalah simulasi **aplikasi pemesanan tiket kereta api** sederhana menggunakan C++.
Fitur-fitur yang tersedia dibuat untuk memenuhi final project mata kuliah struktur data dengan syarat penggunaan struct, array, pointer, sorting, searching, queue, dan linked list.

---

## Fitur Utama
- **Daftar Kereta** (Linked List)
- **Pesan Tiket** (ID unik untuk setiap tiket)
- **Antrean Pemrosesan** (Queue)
- **Ubah & Hapus Tiket di Antrean**
- **Proses Tiket** pindah dari antrean ke riwayat
- **Riwayat Tiket** (Array)
- **Sorting Kereta** berdasarkan harga
- **Searching Tiket** berdasarkan ID di riwayat

---

## Struktur Data yang Digunakan
- **Struct** : menyimpan data kereta & tiket  
- **Array** : menyimpan riwayat tiket  
- **Pointer** : untuk linked list kereta  
- **Sorting** : bubble sort kereta berdasarkan harga  
- **Searching** : linear search tiket di riwayat  
- **Queue** : antrean tiket menunggu diproses  
- **Linked List** : daftar kereta

---

## Menu Program
1. Lihat Daftar Kereta  
2. Lihat Antrean Tiket (lihat ID)  
3. Pesan Tiket  
4. Proses Tiket  
5. Ubah Nama Tiket di Antrean  
6. Hapus Tiket di Antrean  
7. Tampilkan Riwayat Tiket Terproses  
8. Sort Kereta by Harga  
9. Cari Tiket di Riwayat  
10. Keluar  

---

## 🚀 Cara Menjalankan
1. Kompilasi program:
   ```bash
   g++ main.cpp -o tiket
2. Jalankan program:
   ./tiket

## Contoh Alur
- Lihat daftar kereta : tampil data kereta.
- Pesan tiket : input nomor kereta + jumlah tiket + nama penumpang.
- Lihat antrean : cek ID tiket yang baru dibuat.
- Proses tiket : masukkan ID tiket untuk dipindah ke riwayat.
- Cek riwayat : tiket akan tampil di daftar riwayat.
