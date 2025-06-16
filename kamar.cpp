#include "kamar.h"

Kamar::Kamar(int no, std::string tipe, double harga, std::string stat)
    : nomorKamar(no), tipeKamar(tipe), hargaPerMalam(harga), status(stat) {
}

int Kamar::getNomorKamar() const { return nomorKamar; }
std::string Kamar::getTipeKamar() const { return tipeKamar; }
double Kamar::getHargaPerMalam() const { return hargaPerMalam; }
std::string Kamar::getStatus() const { return status; }