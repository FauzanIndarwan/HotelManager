#include "DatabaseManager.h"
#include <iostream>

DatabaseManager::DatabaseManager() {
    driver = sql::mysql::get_driver_instance();
}

DatabaseManager::~DatabaseManager() {
    // Koneksi akan ditutup secara otomatis oleh unique_ptr
}

void DatabaseManager::connect(const std::string& host, const std::string& user, const std::string& pass, const std::string& db) {
    try {
        con.reset(driver->connect(host, user, pass));
        con->setSchema(db);
        std::cout << "Koneksi database berhasil!" << std::endl;
    }
    catch (sql::SQLException& e) {
        std::cerr << "Error koneksi database: " << e.what() << std::endl;
        exit(1); // Keluar jika koneksi gagal
    }
}

int DatabaseManager::tambahTamu(const Tamu& tamu) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO tamu(nama, kontak) VALUES(?, ?)"));
        pstmt->setString(1, tamu.getNama());
        pstmt->setString(2, tamu.getKontak());
        pstmt->executeUpdate();

        // Dapatkan ID tamu yang baru dibuat
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT LAST_INSERT_ID()"));
        if (res->next()) {
            return res->getInt(1);
        }
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error saat menambah tamu: " << e.what() << std::endl;
    }
    return 0;
}

bool DatabaseManager::catatPembayaran(int idReservasi, double jumlah, const std::string& metode) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(
            "INSERT INTO hotel_db_pembayaran (id_reservasi, jumlah, tanggal_bayar, metode_pembayaran) VALUES (?, ?, NOW(), ?)"
        ));
        pstmt->setInt(1, idReservasi);
        pstmt->setDouble(2, jumlah);
        pstmt->setString(3, metode);
        pstmt->executeUpdate();
        return true;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error saat mencatat pembayaran: " << e.what() << std::endl;
        return false;
    }
}

std::vector<Kamar> DatabaseManager::getSemuaKamar() {
    std::vector<Kamar> daftarKamar;
    try {
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM kamar"));

        while (res->next()) {
            daftarKamar.emplace_back(
                res->getInt("nomor_kamar"),
                res->getString("tipe_kamar"),
                res->getDouble("harga_per_malam"),
                res->getString("status")
            );
        }
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error saat mengambil data kamar: " << e.what() << std::endl;
    }
    return daftarKamar;
}

std::vector<Layanan> DatabaseManager::getAllLayanan() {
    std::vector<Layanan> daftarLayanan;
    try {
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM hotel_db_layanan"));

        while (res->next()) {
            daftarLayanan.emplace_back(
                res->getInt("id_layanan"),
                res->getString("nama_layanan"),
                res->getDouble("harga")
            );
        }
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error saat mengambil data layanan: " << e.what() << std::endl;
    }
    return daftarLayanan;
}

bool DatabaseManager::tambahLayananKeReservasi(int idReservasi, int idLayanan, int jumlah, const std::string& catatan) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(
            "INSERT INTO hotel_db_reservasi_layanan (id_reservasi, id_layanan, jumlah, catatan) VALUES (?, ?, ?, ?)"
        ));
        pstmt->setInt(1, idReservasi);
        pstmt->setInt(2, idLayanan);
        pstmt->setInt(3, jumlah);
        pstmt->setString(4, catatan);
        pstmt->executeUpdate();
        return true;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error saat menambah layanan ke reservasi: " << e.what() << std::endl;
        return false;
    }
}

bool DatabaseManager::buatReservasi(int idTamu, int nomorKamar, const std::string& checkIn, const std::string& checkOut) {
    try {
        // Mulai transaksi
        con->setAutoCommit(false);

        // 1. Insert ke tabel reservasi
        std::unique_ptr<sql::PreparedStatement> pstmt_res(con->prepareStatement("INSERT INTO reservasi(id_tamu, nomor_kamar, tanggal_check_in, tanggal_check_out) VALUES (?, ?, ?, ?)"));
        pstmt_res->setInt(1, idTamu);
        pstmt_res->setInt(2, nomorKamar);
        pstmt_res->setString(3, checkIn);
        pstmt_res->setString(4, checkOut);
        pstmt_res->executeUpdate();

        // 2. Update status kamar menjadi 'Dipesan'
        std::unique_ptr<sql::PreparedStatement> pstmt_kamar(con->prepareStatement("UPDATE kamar SET status = 'Dipesan' WHERE nomor_kamar = ?"));
        pstmt_kamar->setInt(1, nomorKamar);
        pstmt_kamar->executeUpdate();

        // Commit transaksi
        con->commit();
        con->setAutoCommit(true);
        return true;

    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error saat membuat reservasi: " << e.what() << std::endl;
        con->rollback(); // Batalkan jika terjadi error
        con->setAutoCommit(true);
        return false;
    }
}