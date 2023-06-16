#include <iostream>

using namespace std;

// Struct untuk merepresentasikan data kamar
struct Room {
    int nomorKamar;
    bool reservasi;
    Room* next;
};

void Login()
{
    string username, password;

    do
    {
        cout << "Masukkan username: ";
        cin >> username;
        cout << "Masukkan password: ";
        cin >> password;

        if (username.empty() || password.empty())
        {
            cout << "Username dan password harus diisi." << endl;
        }
        else if (username == "admin" && password == "admin")
        {
            system("cls");
            return;
        }
        else
        {
            if (username != "admin" && password != "admin")
            {
                cout << "Username dan password salah." << endl;
            }
            else if (username != "admin")
            {
                cout << "Username salah." << endl;
            }
            else
            {
                cout << "Password salah." << endl;
            }
        }
    } while (true);
}

// Fungsi untuk membuat node kamar baru
Room* BuatKamar(int nomor) {
    Room* newRoom = new Room;
    newRoom->nomorKamar = nomor;
    newRoom->reservasi = false;
    newRoom->next = nullptr;
    return newRoom;
}

// Fungsi untuk menambahkan kamar ke dalam linked list
void TambahKamar(Room*& head, int nomor) {
    if (head == nullptr) {
        head = BuatKamar(nomor);
    } else {
        Room* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = BuatKamar(nomor);
    }
}

// Fungsi untuk menampilkan kamar yang tersedia
void KamarTersedia(Room* head) {
    system("cls");
    if (head == nullptr) {
        cout << "Tidak ada kamar yang tersedia.\n";
    } else {
        cout << "Kamar yang tersedia:\n";
        Room* current = head;
        while (current != nullptr) {
            if (!current->reservasi) {
                cout << "Nomor Kamar: " << current->nomorKamar << "\n";
            }
            current = current->next;
        }
    }
    cout << endl
         << "Tekan enter untuk kembali ke menu...";
    cin.ignore();
    cin.get();
}

// Fungsi untuk melakukan reservasi kamar
void ReservasiKamar(Room* head, int nomor) {
    Room* current = head;
    while (current != nullptr) {
        if (current->nomorKamar == nomor) {
            if (!current->reservasi) {
                current->reservasi = true;
                cout << "Kamar nomor " << current->nomorKamar << " telah berhasil dipesan.\n";
                return;
            } else {
                cout << "Kamar nomor " << current->nomorKamar << " sudah dipesan.\n";
                return;
            }
        }
        current = current->next;
    }
    cout << "Kamar nomor " << nomor << " tidak ditemukan.\n";
    cout << endl
         << "Tekan enter untuk kembali ke menu...";
    cin.ignore();
    cin.get();
}

// Fungsi untuk melihat reservasi kamar
void DataReservasi(Room* head) {
    // 
    bool TelahReservasi = false;
    Room* current = head;
    while (current != nullptr) {
        if (current->reservasi) {
            cout << "Nomor Kamar: " << current->nomorKamar << "\n";
            TelahReservasi = true;
        }
        current = current->next;
    }
    if (!TelahReservasi) {
        cout << "Tidak ada kamar yang dipesan.\n";
    }
}

// Fungsi untuk membatalkan reservasi kamar
void BatalkanReservasi(Room* head, int nomor) {
    // 
    Room* current = head;
    while (current != nullptr) {
        if (current->nomorKamar == nomor) {
            if (current->reservasi) {
                current->reservasi = false;
                cout << "Reservasi untuk kamar nomor " << current->nomorKamar << " berhasil dibatalkan.\n";
                return;
            } else {
                cout << "Kamar nomor " << current->nomorKamar << " tidak dalam status dipesan.\n";
                return;
            }
        }
        current = current->next;
    }
    cout << "Kamar nomor " << nomor << " tidak ditemukan.\n";
}

// Fungsi utama (main)
int main() {
    Room* roomList = nullptr;

    // Menambahkan beberapa kamar ke dalam linked list
    TambahKamar(roomList, 101);
    TambahKamar(roomList, 102);
    TambahKamar(roomList, 103);
    TambahKamar(roomList, 104);

    Login();

    int pilih;
    int nomorKamar;

    while (true) {
        system("cls");
        cout << "========== Sistem Reservasi Hotel ==========\n";
        cout << "1. Lihat Kamar yang Tersedia\n";
        cout << "2. Reservasi Kamar\n";
        cout << "3. Lihat Reservasi\n";
        cout << "4. Batalkan Reservasi\n";
        cout << "5. Keluar\n";
        cout << "Pilihan Anda: ";
        cin >> pilih;

        switch (pilih) {
            case 1:
                
                KamarTersedia(roomList);
                break;
            case 2:
                system("cls");
                cout << "Masukkan nomor kamar yang ingin dipesan: ";
                cin >> nomorKamar;
                ReservasiKamar(roomList, nomorKamar);
                break;
            case 3:
                
                DataReservasi(roomList);
                break;
            case 4:
                
                cout << "Masukkan nomor kamar yang ingin dibatalkan: ";
                cin >> nomorKamar;
                BatalkanReservasi(roomList, nomorKamar);
                break;
            case 5:
                
                cout << "Terima kasih! Sampai jumpa.";
                exit(0);
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
                break;
        }
        cout << "\n";
    }

    return 0;
}
