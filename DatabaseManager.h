#pragma once

#include <jdbc/mysql_driver.h>
#include <jdbc/mysql_connection.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/prepared_statement.h>
#include <jdbc/cppconn/resultset.h>

#include "Tamu.h"
#include "Pembayaran.h"
#include "Layanan.h"
#include "Kamar.h"
#include <vector>
#include <memory>

class DatabaseManager {
private:
    sql::Driver* driver;
    std::unique_ptr<sql::Connection> con;

public:
    DatabaseManager();
    ~DatabaseManager();
    void connect(const std::string& host, const std::string& user, const std::string& pass, const std::string& db);

    // Operasi CRUD
    int tambahTamu(const Tamu& tamu);
    std::vector<Kamar> getSemuaKamar();
    bool buatReservasi(int idTamu, int nomorKamar, const std::string& checkIn, const std::string& checkOut);
    std::vector<Layanan> getAllLayanan();
    bool tambahLayananKeReservasi(int idReservasi, int idLayanan, int jumlah, const std::string& catatan);
    bool catatPembayaran(int idReservasi, double jumlah, const std::string& metode);
};