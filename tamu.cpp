#include "tamu.h"

Tamu::Tamu(std::string n, std::string k) : nama(n), kontak(k), idTamu(0) {}

int Tamu::getId() const { return idTamu; }
std::string Tamu::getNama() const { return nama; }
std::string Tamu::getKontak() const { return kontak; }
void Tamu::setId(int id) { this->idTamu = id; }