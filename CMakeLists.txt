# =================================================================
# Bagian 1: Pengaturan Dasar Proyek
# =================================================================
cmake_minimum_required(VERSION 3.15)
project(HotelManagerCpp VERSION 1.0)

# =================================================================
# Bagian 2: Pengaturan Standar C++
# =================================================================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# =================================================================
# Bagian 3: Mencari Library MySQL Connector/C++ (DENGAN NAMA YANG BENAR)
# =================================================================
# Mencari paket dengan nama "mysql-concpp"
find_package(mysql-concpp REQUIRED)

# Memberikan umpan balik yang jelas apakah library ditemukan atau tidak.
if(mysql-concpp_FOUND)
    message(STATUS "Sukses! Paket 'mysql-concpp' ditemukan.")
else()
    message(FATAL_ERROR "Gagal menemukan paket 'mysql-concpp'.")
endif()

# =================================================================
# Bagian 4: Mendefinisikan File Source Code
# =================================================================
set(SOURCES
    main.cpp
    Tamu.cpp
    Kamar.cpp
    DatabaseManager.cpp
)

# =================================================================
# Bagian 5: Membuat Program & Menghubungkan Library
# =================================================================
add_executable(hotel_manager ${SOURCES} "pembayaran.h")

# Memberitahu compiler untuk mencari file header (.h) di folder utama proyek.
target_include_directories(hotel_manager PUBLIC
    ${PROJECT_SOURCE_DIR}
)

# Memberitahu linker untuk menyambungkan program kita dengan library mysql-concpp.
target_link_libraries(hotel_manager PUBLIC
    mysql::concpp-jdbc
)

message(STATUS "Konfigurasi CMake untuk ${PROJECT_NAME} selesai.")