#pragma once
#include <string>

class Kamar {
private:
    int nomorKamar;
    std::string tipeKamar;
    double hargaPerMalam;
    std::string status;

public:
    Kamar(int no, std::string tipe, double harga, std::string stat);
    // Getter methods
    int getNomorKamar() const;
    std::string getTipeKamar() const;
    double getHargaPerMalam() const;
    std::string getStatus() const;
};