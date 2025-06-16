#pragma once
#include <string>

class Layanan {
private:
    int idLayanan;
    std::string namaLayanan;
    double harga;

public:
    Layanan(int id, std::string nama, double hrg)
        : idLayanan(id), namaLayanan(nama), harga(hrg) {
    }

    int getId() const { return idLayanan; }
    std::string getNama() const { return namaLayanan; }
    double getHarga() const { return harga; }
};