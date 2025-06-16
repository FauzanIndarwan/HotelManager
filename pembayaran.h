#pragma once
#include <string>

class Pembayaran {
private:
    int idPembayaran;
    int idReservasi;
    double jumlah;
    std::string tanggalBayar;
    std::string metodePembayaran;

public:
    // Konstruktor bisa ditambahkan sesuai kebutuhan
    Pembayaran(int id, int idRes, double jml, std::string tgl, std::string metode)
        : idPembayaran(id), idReservasi(idRes), jumlah(jml), tanggalBayar(tgl), metodePembayaran(metode) {
    }
};