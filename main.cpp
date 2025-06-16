#include <iostream>
#include "DatabaseManager.h"
#include "Tamu.h"
#include <vector>

void tampilkanMenu() {
    std::cout << "\n===== Sistem Manajemen Hotel =====" << std::endl;
    std::cout << "1. Lihat Semua Kamar" << std::endl;
    std::cout << "2. Tambah Tamu & Buat Reservasi" << std::endl;
    std::cout << "3. Tambah Layanan ke Reservasi" << std::endl;
    std::cout << "4. Catat Pembayaran" << std::endl;
    std::cout << "5. Keluar" << std::endl;
    std::cout << "Pilih opsi: ";
}

int main() {
    DatabaseManager db;
    db.connect("tcp://127.0.0.1:3306", "root", "", "hotel_db");

    int pilihan;
    do {
        tampilkanMenu();
        std::cin >> pilihan;

        if (pilihan == 1) {
            std::vector<Kamar> kamar = db.getSemuaKamar();
            std::cout << "\n--- Daftar Kamar ---" << std::endl;
            for (const auto& k : kamar) {
                std::cout << "No: " << k.getNomorKamar()
                    << ", Tipe: " << k.getTipeKamar()
                    << ", Harga: " << k.getHargaPerMalam()
                    << ", Status: " << k.getStatus() << std::endl;
            }
        }
        else if (pilihan == 2) {
            std::string nama, kontak, checkIn, checkOut;
            int nomorKamar;

            std::cout << "Masukkan nama tamu: ";
            std::cin.ignore();
            std::getline(std::cin, nama);
            std::cout << "Masukkan kontak tamu: ";
            std::getline(std::cin, kontak);

            Tamu tamuBaru(nama, kontak);
            int idTamuBaru = db.tambahTamu(tamuBaru);

            if (idTamuBaru > 0) {
                std::cout << "Tamu berhasil ditambahkan dengan ID: " << idTamuBaru << std::endl;
                std::cout << "Masukkan nomor kamar yang ingin dipesan: ";
                std::cin >> nomorKamar;
                std::cout << "Masukkan tanggal Check-In (YYYY-MM-DD): ";
                std::cin >> checkIn;
                std::cout << "Masukkan tanggal Check-Out (YYYY-MM-DD): ";
                std::cin >> checkOut;

                if (db.buatReservasi(idTamuBaru, nomorKamar, checkIn, checkOut)) {
                    std::cout << "Reservasi berhasil dibuat!" << std::endl;
                }
                else {
                    std::cout << "Gagal membuat reservasi." << std::endl;
                }
            }
            else {
                std::cout << "Gagal menambahkan tamu." << std::endl;
            }
        }
        else if (pilihan == 3) {
            int idReservasi, idLayanan, jumlah;
            std::string catatan;

            std::cout << "--- Tambah Layanan ---" << std::endl;
            std::cout << "Masukkan ID Reservasi: ";
            std::cin >> idReservasi;

            std::cout << "\nDaftar Layanan Tersedia:" << std::endl;
            std::vector<Layanan> layananTersedia = db.getAllLayanan();
            for (const auto& layanan : layananTersedia) {
                std::cout << "ID: " << layanan.getId() << ", Nama: " << layanan.getNama()
                    << ", Harga: " << layanan.getHarga() << std::endl;
            }

            std::cout << "Pilih ID Layanan: ";
            std::cin >> idLayanan;
            std::cout << "Masukkan Jumlah: ";
            std::cin >> jumlah;
            std::cout << "Masukkan Catatan (opsional): ";
            std::cin.ignore();
            std::getline(std::cin, catatan);

            if (db.tambahLayananKeReservasi(idReservasi, idLayanan, jumlah, catatan)) {
                std::cout << "Layanan berhasil ditambahkan ke reservasi!" << std::endl;
            }
            else {
                std::cout << "Gagal menambahkan layanan." << std::endl;
            }

        }
        else if (pilihan == 4) {
            int idReservasi;
            double jumlah;
            std::string metode;

            std::cout << "--- Catat Pembayaran ---" << std::endl;
            std::cout << "Masukkan ID Reservasi: ";
            std::cin >> idReservasi;
            std::cout << "Masukkan Jumlah Pembayaran: ";
            std::cin >> jumlah;
            std::cout << "Masukkan Metode Pembayaran (misal: Tunai, Kartu Kredit): ";
            std::cin.ignore();
            std::getline(std::cin, metode);

            if (db.catatPembayaran(idReservasi, jumlah, metode)) {
                std::cout << "Pembayaran berhasil dicatat!" << std::endl;
            }
            else {
                std::cout << "Gagal mencatat pembayaran." << std::endl;
            }
        }

    } while (pilihan != 5);

    std::cout << "Terima kasih telah menggunakan sistem." << std::endl;

    return 0;
}