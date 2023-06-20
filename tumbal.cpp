#include <iostream>
#include <iomanip>
using namespace std;

struct Kamar
{
    int nomorKamar;
    int lamaMenginap;
    bool reservasi;
    string WaktuReservasi;
    string nomorHandphone;
    string alamat;
    string tipeKamar;
    int hargaPerMalam;
    string namaPemesan;
    Kamar *next;
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

Kamar *BuatKamar(int nomor)
{
    Kamar *newKamar = new Kamar;
    newKamar->nomorKamar = nomor;
    newKamar->reservasi = false;
    newKamar->WaktuReservasi = "";
    newKamar->next = nullptr;
    return newKamar;
}

void TambahKamar(Kamar *&head, int nomor, const string &tipe, int harga)
{
    if (head == nullptr)
    {
        head = BuatKamar(nomor);
        head->tipeKamar = tipe;
        head->hargaPerMalam = harga;
    }
    else
    {
        Kamar *current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = BuatKamar(nomor);
        current->next->tipeKamar = tipe;
        current->next->hargaPerMalam = harga;
    }
}

void KamarTersedia(Kamar *head, bool showMenu = true)
{
    if (head == nullptr)
    {
        cout << "Tidak ada kamar yang tersedia.\n";
    }
    else
    {
        cout << "========================Data Kamar========================\n";
        cout << "Kamar\t\tTipe Kamar\t\tHarga Per Malam\n";
        cout << "----------------------------------------------------------\n\n";
        Kamar *current = head;
        while (current != nullptr)
        {
            if (!current->reservasi)
            {
                cout << "Kamar " << current->nomorKamar << "\t\t";
                cout << current->tipeKamar << "\t\t\t";
                cout << current->hargaPerMalam << endl;
            }
            current = current->next;
        }

        char pilihan;
        cout << "\nApakah Anda ingin melihat spesifikasi lengkap kamar? (y/n): ";
        cin >> pilihan;

        if (pilihan == 'y' || pilihan == 'Y')
        {
            system("cls");
            cout << "\n===================Spesifikasi Kamar=====================\n";
            current = head;
            while (current != nullptr)
            {
                if (!current->reservasi)
                {
                    cout << "Kamar " << current->nomorKamar << endl;

                    if (current->tipeKamar == "Single Room")
                    {
                        cout << "\t- Tipe kamar: Single Room\n";
                        cout << "\t- Fasilitas: Kasur single, TV, AC, kamar mandi\n";
                        cout << "\t- Harga: " << current->hargaPerMalam << endl;
                    }
                    else if (current->tipeKamar == "Double Room")
                    {
                        cout << "\t- Tipe kamar: Double Room\n";
                        cout << "\t- Fasilitas: Kasur double, TV, AC, kamar mandi\n";
                        cout << "\t- Harga: " << current->hargaPerMalam << endl;
                    }
                    else if (current->tipeKamar == "Deluxe Room")
                    {
                        cout << "\t- Tipe kamar: Deluxe Room\n";
                        cout << "\t- Fasilitas: Kasur king-size, TV, AC, kamar mandi, minibar\n";
                        cout << "\t- Harga: " << current->hargaPerMalam << endl;
                    }
                    else if (current->tipeKamar == "Suite Room")
                    {
                        cout << "\t- Tipe kamar: Suite Room\n";
                        cout << "\t- Fasilitas: Kasur king-size, ruang tamu, TV, AC, kamar mandi, minibar\n";
                        cout << "\t- Harga: " << current->hargaPerMalam << endl;
                    }
                    cout << "----------------------------------------------------------\n";
                }
                current = current->next;
            }
        }
    }

    if (showMenu)
    {
        cout << endl
             << "Tekan enter untuk kembali ke menu...";
        cin.ignore();
        cin.get();
    }
}


//reservasi
void ReservasiKamar(Kamar* head) {
    int nomorKamar;
    string WaktuReservasi;
    string namaPemesan;
    int lamaMenginap;
    string nomorHandphone;
    string alamat;

    cout << "========================Data Kamar========================\n";
    cout << "Kamar\t\tTipe Kamar\t\tHarga Per Malam\n";
    cout << "----------------------------------------------------------\n\n";

    Kamar *current = head;
    bool kamarTersedia = false;
    while (current != nullptr) {
        if (!current->reservasi) {
            cout << "Kamar " << current->nomorKamar << "\t\t";
            cout << current->tipeKamar << "\t\t\t";
            cout << current->hargaPerMalam << endl;
            kamarTersedia = true;
        }
        current = current->next;
    }

    if (!kamarTersedia) {
        cout << "Tidak ada kamar yang tersedia.\n";
        cout << endl << "Tekan enter untuk kembali ke menu...";
        cin.ignore();
        cin.get();
        return;
    }

    bool kamarDitemukan = false;
    while (!kamarDitemukan) {
        cout << "\nMasukkan nomor kamar yang ingin dipesan (0 untuk kembali ke menu): ";
        cin >> nomorKamar;

        if (nomorKamar == 0) {
            cout << endl << "Kembali ke menu..." << endl;
            return;
        }

        current = head;
        while (current != nullptr) {
            if (current->nomorKamar == nomorKamar && !current->reservasi) {
                kamarDitemukan = true;
                cout << "Masukkan hari pemesanan: ";
                cin >> WaktuReservasi;
                cout << "Masukkan lama menginap (Malam): ";
                cin >> lamaMenginap;
                cout << "Masukkan nama pemesan: ";
                cin.ignore();
                getline(cin, namaPemesan);
                cout << "Masukkan nomor handphone: ";
                cin >> nomorHandphone;
                cout << "Masukkan alamat: ";
                cin.ignore();
                getline(cin, alamat);

                current->reservasi = true;
                current->WaktuReservasi = WaktuReservasi;
                current->namaPemesan = namaPemesan;
                current->lamaMenginap = lamaMenginap;
                current->nomorHandphone = nomorHandphone;
                current->alamat = alamat;

                int totalHarga = current->hargaPerMalam * current->lamaMenginap;

                if (current->lamaMenginap > 5) {
                    float diskon = 0.15 * totalHarga;
                    totalHarga -= diskon;
                }

                cout << "Kamar nomor " << current->nomorKamar << " berhasil dipesan pada hari " << current->WaktuReservasi << " atas nama " << current->namaPemesan << " untuk " << current->lamaMenginap << " hari.\n";
                cout << "Nomor handphone: " << current->nomorHandphone << endl;
                cout << "Alamat: " << current->alamat << endl;
                cout << "Total harga: " << totalHarga << endl;
                cout << endl << "Tekan enter untuk kembali ke menu...";
                cin.ignore();
                cin.get();
                return;
            }
            current = current->next;
        }

        char pilihan;
        cout << "Kamar dengan nomor " << nomorKamar << " tidak tersedia atau tidak valid. Apakah Anda ingin mencoba lagi? (y/n): ";
        cin >> pilihan;
        if (pilihan == 'n' || pilihan == 'N') {
            cout << endl << "Kembali ke menu..." << endl;
            return;
        }
    }
}


void DataReservasi(Kamar *head)
{
    bool TelahReservasi = false;
    Kamar *current = head;
    cout << "===============================================================================================\n";
    cout << "                                     Data Reservasi Kamar                                      \n";
    cout << "===============================================================================================\n";
    cout << "No. |   Atas Nama   | Nomor Kamar  |     Tipe Kamar      |  Harga Per Malam  |  Waktu Reservasi\n";
    cout << "-----------------------------------------------------------------------------------------------\n";
    int nomorUrut = 1;
    while (current != nullptr)
    {
        if (current->reservasi)
        {
            cout << setw(3) << nomorUrut << " |";
            cout << setw(14) << current->namaPemesan << " |";
            cout << setw(13) << "Kamar " << current->nomorKamar << " |";
            cout << setw(19) << current->tipeKamar << " |";
            cout << setw(17) << current->hargaPerMalam << " |";
            cout << setw(17) << current->WaktuReservasi << endl;
            TelahReservasi = true;
            nomorUrut++;
        }
        current = current->next;
    }
    if (!TelahReservasi)
    {
        cout << "Tidak ada kamar yang dipesan.\n";
    }
    cout << "===============================================================================================\n";
    cout << endl
         << "Tekan enter untuk kembali ke menu...";
    cin.ignore();
    cin.get();
}

void BatalkanReservasi(Kamar *head)
{
    Kamar *current = head;
    bool found = false;
    int totalReservasi = 0;

    while (current != nullptr)
    {
        if (current->reservasi)
        {
            totalReservasi++;
        }
        current = current->next;
    }

    if (totalReservasi == 0)
    {
        cout << "Tidak ada reservasi yang ditemukan.\n";
        cout << endl
             << "Tekan enter untuk kembali ke menu...";
        cin.ignore();
        cin.get();
        return;
    }

    cout << "====================== Daftar Reservasi ===================================================\n";
    cout << setw(4) << "No. |" << setw(14) << "Atas Nama" << setw(15) << "Nomor Kamar |" << setw(20) << "Tipe Kamar |" << setw(18) << "Harga Per Malam |" << setw(18) << "Waktu Reservasi\n";
    cout << "-------------------------------------------------------------------------------------------\n";
    current = head;
    int nomorUrut = 1;

    while (current != nullptr)
    {
        if (current->reservasi)
        {
            cout << setw(4) << nomorUrut << " |";
            cout << setw(14) << current->namaPemesan << " |";
            cout << setw(13) << "Kamar " << current->nomorKamar << " |";
            cout << setw(18) << current->tipeKamar << " |";
            cout << setw(16) << current->hargaPerMalam << " |";
            cout << setw(18) << current->WaktuReservasi << endl;
            nomorUrut++;
            found = true;
        }
        current = current->next;
    }

    cout << "-------------------------------------------------------------\n";

    if (found)
    {
        int nomorKamar;
        cout << "Masukkan nomor kamar yang ingin dibatalkan (0 untuk membatalkan semua): ";
        cin >> nomorKamar;

        if (nomorKamar == 0)
        {
            current = head;
            while (current != nullptr)
            {
                if (current->reservasi)
                {
                    current->reservasi = false;
                }
                current = current->next;
            }
            cout << "Semua reservasi berhasil dibatalkan.\n";
        }
        else if (nomorKamar > 0 && nomorKamar <= totalReservasi)
        {
            current = head;
            int count = 1;
            while (current != nullptr)
            {
                if (current->reservasi && count == nomorKamar)
                {
                    current->reservasi = false;
                    cout << "Reservasi untuk kamar nomor " << current->nomorKamar << " berhasil dibatalkan.\n";
                    break;
                }
                if (current->reservasi)
                {
                    count++;
                }
                current = current->next;
            }
        }
        else
        {
            cout << "Nomor kamar tidak valid.\n";
        }
    }
    else
    {
        cout << "Tidak ada reservasi yang ditemukan.\n";
    }

    cout << endl
         << "Tekan enter untuk kembali ke menu...";
    cin.ignore();
    cin.get();
}

int main()
{
    Kamar *DaftarKamar = nullptr;
    TambahKamar(DaftarKamar, 1, "Single Room", 100);
    TambahKamar(DaftarKamar, 2, "Double Room", 150);
    TambahKamar(DaftarKamar, 3, "Deluxe Room", 200);
    TambahKamar(DaftarKamar, 4, "Suite Room", 250);

    Login();

    int pilih;
    while (true)
    {
        system("clear");
        cout << "========== Sistem Reservasi Hotel ==========\n";
        cout << "1. Lihat Kamar yang Tersedia\n";
        cout << "2. Reservasi Kamar\n";
        cout << "3. Lihat Reservasi\n";
        cout << "4. Batalkan Reservasi\n";
        cout << "5. Keluar\n";
        cout << "Pilihan Anda: ";
        cin >> pilih;

        switch (pilih)
        {
        case 1:
            system("clear");
            KamarTersedia(DaftarKamar);
            break;
        case 2:
            system("clear");
            ReservasiKamar(DaftarKamar);
            break;
        case 3:
            system("clear");
            DataReservasi(DaftarKamar);
            break;
        case 4:
            system("clear");
            BatalkanReservasi(DaftarKamar);
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
