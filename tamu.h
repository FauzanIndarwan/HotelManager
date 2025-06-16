#pragma once
#include <string>

class Tamu {
private:
    int idTamu;
    std::string nama;
    std::string kontak;

public:
    Tamu(std::string nama, std::string kontak);
    // Getter methods
    int getId() const;
    std::string getNama() const;
    std::string getKontak() const;
    void setId(int id);
};