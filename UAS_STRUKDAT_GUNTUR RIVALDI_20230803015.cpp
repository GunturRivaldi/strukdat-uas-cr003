#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

struct Produk {
    int id;
    string nama;
    string harga;
    int stok;
};

struct Pengguna {
    string username;
    string password;
};

vector<Produk> produk;
vector<Pengguna> pengguna;

const string ADMIN_USERNAME = "guntur";
const string ADMIN_PASSWORD = "rivaldi123";

void bersihkanBufferMasukan() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int cariProdukById(int id) {
    for (int i = 0; i < produk.size(); ++i) {
        if (produk[i].id == id) {
            return i;
        }
    }
    return -1;
}

int cariPenggunaByUsername(const string& username) {
    for (int i = 0; i < pengguna.size(); ++i) {
        if (pengguna[i].username == username) {
            return i;
        }
    }
    return -1;
}

void tambahProduk() {
    Produk produkBaru;
    cout << "\n--- Tambah Produk ---\n";
    cout << "ID Produk: ";
    while (!(cin >> produkBaru.id)) {
        cout << "ID harus berupa angka. Masukkan lagi: ";
        bersihkanBufferMasukan();
    }
    bersihkanBufferMasukan();
    cout << "Nama Produk: ";
    getline(cin, produkBaru.nama);
    cout << "Harga Produk: ";
    getline(cin, produkBaru.harga);
    cout << "Stok Produk: ";
    while (!(cin >> produkBaru.stok)) {
        cout << "Stok harus berupa angka. Masukkan lagi: ";
        bersihkanBufferMasukan();
    }
    produk.push_back(produkBaru);
    cout << "Produk berhasil ditambahkan!\n";
}

void lihatProduk() {
    cout << "\n--- Lihat Produk ---\n";
    if (produk.empty()) {
        cout << "Tidak ada produk yang tersedia.\n";
    } else {
        for (const auto& prod : produk) {
            cout << "ID: " << prod.id << "\n";
            cout << "Nama: " << prod.nama << "\n";
            cout << "Harga: " << prod.harga << "\n";
            cout << "Stok: " << prod.stok << "\n";
            cout << "------------------------\n";
        }
    }
}

void ubahProduk() {
    int id;
    cout << "\n--- Ubah Produk ---\n";
    cout << "Masukkan ID produk yang akan diubah: ";
    while (!(cin >> id)) {
        cout << "ID harus berupa angka. Masukkan lagi: ";
        bersihkanBufferMasukan();
    }
    int index = cariProdukById(id);
    if (index != -1) {
        Produk& prod = produk[index];
        cout << "Nama Baru (kosongkan jika tidak ingin mengubah): ";
        bersihkanBufferMasukan();
        string namaBaru;
        getline(cin, namaBaru);
        if (!namaBaru.empty()) {
            prod.nama = namaBaru;
        }
        cout << "Harga Baru (kosongkan jika tidak ingin mengubah): ";
        string hargaBaru;
        bersihkanBufferMasukan();
        getline(cin, hargaBaru);
        if (!hargaBaru.empty()) {
            prod.harga = hargaBaru;
        }
        cout << "Stok Baru (0 jika tidak ingin mengubah): ";
        int stokBaru;
        if (cin >> stokBaru && stokBaru != 0) {
            prod.stok = stokBaru;
        }
        cout << "Produk berhasil diubah!\n";
    } else {
        cout << "Produk dengan ID tersebut tidak ditemukan.\n";
    }
}

void hapusProduk() {
    int id;
    cout << "\n--- Hapus Produk ---\n";
    cout << "Masukkan ID produk yang akan dihapus: ";
    while (!(cin >> id)) {
        cout << "ID harus berupa angka. Masukkan lagi: ";
        bersihkanBufferMasukan();
    }
    int index = cariProdukById(id);
    if (index != -1) {
        produk.erase(produk.begin() + index);
        cout << "Produk berhasil dihapus!\n";
    } else {
        cout << "Produk dengan ID tersebut tidak ditemukan.\n";
    }
}

void registrasiPengguna() {
    Pengguna penggunaBaru;
    cout << "\n--- Registrasi Pengguna ---\n";
    cout << "Username: ";
    cin >> penggunaBaru.username;
    if (cariPenggunaByUsername(penggunaBaru.username) != -1) {
        cout << "Username sudah ada. Pilih username lain.\n";
        return;
    }
    cout << "Password: ";
    cin >> penggunaBaru.password;
    pengguna.push_back(penggunaBaru);
    cout << "Registrasi berhasil!\n";
}

void login(bool& isLoggedIn, bool& isAdmin) {
    string username, password;
    cout << "\n--- Login ---\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD) {
        cout << "Login berhasil sebagai admin!\n" << endl;
        isLoggedIn = true;
        isAdmin = true;
    } else if (cariPenggunaByUsername(username) != -1 && pengguna[cariPenggunaByUsername(username)].password == password) {
        cout << "Login berhasil sebagai pengguna!\n" << endl;
        isLoggedIn = true;
        isAdmin = false;
    } else {
        cout << "Login gagal. Periksa username dan password.\n" << endl;
        isLoggedIn = false;
    }
}

int main() {
    int pilihan;
    bool isLoggedIn = false;
    bool isAdmin = false;

    do {
        cout << "\n===== Toko Parabot Guntur =====\n";
        cout << "\nMenu Utama\n";
        if (!isLoggedIn) {
            cout << "1. Login\n";
            cout << "2. Registrasi\n";
        } else {
            cout << "1. Lihat Produk\n";
            cout << "2. Tambah Produk\n";
            cout << "3. Ubah Produk\n";
            cout << "4. Hapus Produk\n";
            cout << "5. Logout\n";
            if (isAdmin) {
                cout << "\n--- Informasi Admin ---\n";
                cout << "Anda memiliki akses untuk menambah dan mengubah produk.\n";
            }
        }
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        while (!(cin >> pilihan)) {
            cout << "Pilihan harus berupa angka. Masukkan lagi: ";
            bersihkanBufferMasukan();
        }

        switch (pilihan) {
            case 1:
                if (!isLoggedIn) {
                    login(isLoggedIn, isAdmin);
                } else {
                    lihatProduk();
                }
                break;
            case 2:
                if (!isLoggedIn) {
                    registrasiPengguna();
                } else if (isAdmin) {
                    tambahProduk();
                } else {
                    cout << "Akses ditolak. Hanya admin yang dapat menambah produk.\n";
                }
                break;
            case 3:
                if (isLoggedIn) {
                    if (isAdmin) {
                        ubahProduk();
                    } else {
                        cout << "Akses ditolak. Hanya admin yang dapat mengubah produk.\n";
                    }
                } else {
                    cout << "Anda harus login terlebih dahulu.\n";
                }
                break;
            case 4:
                if (isLoggedIn) {
                    if (isAdmin) {
                        hapusProduk();
                    } else {
                        cout << "Akses ditolak. Hanya admin yang dapat menghapus produk.\n";
                    }
                } else {
                    cout << "Anda harus login untuk menghapus produk.\n";
                }
                break;
            case 5:
                if (isLoggedIn) {
                    isLoggedIn = false;
                    isAdmin = false;
                    cout << "Logout berhasil.\n" << endl;
                } else {
                    cout << "Anda belum login.\n" << endl;
                }
                break;
            case 0:
                cout << "Keluar dari program.\n" << endl;
                break;
            default:
                cout << "Pilihan tidak valid.\n" << endl;
        }
    } while (pilihan != 0);

    return 0;
}
