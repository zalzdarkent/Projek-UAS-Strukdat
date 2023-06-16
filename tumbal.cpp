#include <iostream>
#include <iomanip>
using namespace std;

struct Kamar
{
    int nomorKamar;
    bool reservasi;
    string WaktuReservasi;
    string tipeKamar;
    int hargaPerMalam;
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
                // cout << "-------------------------------------\n";
            }
            current = current->next;
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

void ReservasiKamar(Kamar *head)
{
    KamarTersedia(head, false);

    int nomorKamar;
    string WaktuReservasi;

    bool kamarDitemukan = false;
    while (!kamarDitemukan)
    {
        cout << "\nMasukkan nomor kamar yang ingin dipesan (0 untuk kembali ke menu): ";
        cin >> nomorKamar;

        if (nomorKamar == 0)
        {
            cout << endl
                 << "Kembali ke menu..." << endl;
            return;
        }

        Kamar *current = head;
        while (current != nullptr)
        {
            if (current->nomorKamar == nomorKamar)
            {
                if (!current->reservasi)
                {
                    kamarDitemukan = true;
                    cout << "Masukkan waktu reservasi (hari): ";
                    cin >> WaktuReservasi;
                    current->reservasi = true;
                    current->WaktuReservasi = WaktuReservasi;
                    cout << "Kamar nomor " << current->nomorKamar << " berhasil dipesan pada hari " << current->WaktuReservasi << ".\n";
                    cout << endl
                         << "Tekan enter untuk kembali ke menu...";
                    cin.ignore();
                    cin.get();
                    return;
                }
                else
                {
                    cout << "Kamar nomor " << current->nomorKamar << " sudah dipesan.\n";
                    break;
                }
            }
            current = current->next;
        }

        char pilihan;
        cout << "Kamar nomor " << nomorKamar << " tidak ditemukan." << endl;
        cout << "Apakah Anda ingin memesan kamar lain? (y/n): ";
        cin >> pilihan;

        if (pilihan == 'n' || pilihan == 'N')
        {
            cout << endl
                 << "Tekan enter untuk kembali ke menu...";
            cin.ignore();
            cin.get();
            return;
        }
    }
}

void DataReservasi(Kamar *head)
{
    bool TelahReservasi = false;
    Kamar *current = head;
    cout << "================================================================================\n";
    cout << "                               Data Reservasi Kamar                             \n";
    cout << "================================================================================\n";
    cout << "No. |  Nomor Kamar  |     Tipe Kamar      |  Harga Per Malam  |  Waktu Reservasi\n";
    cout << "--------------------------------------------------------------------------------\n";
    int nomorUrut = 1;
    while (current != nullptr)
    {
        if (current->reservasi)
        {
            cout << setw(3) << nomorUrut << " |";
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
    cout << "=================================================================================\n";
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

    cout << "====================== Daftar Reservasi ======================\n";
    cout << setw(4) << "No. |" << setw(15) << "Nomor Kamar |" << setw(20) << "Tipe Kamar |" << setw(18) << "Harga Per Malam |" << setw(18) << "Waktu Reservasi\n";
    cout << "-------------------------------------------------------------\n";
    current = head;
    int nomorUrut = 1;

    while (current != nullptr)
    {
        if (current->reservasi)
        {
            cout << setw(4) << nomorUrut << " |";
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
        system("cls");
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
            system("cls");
            KamarTersedia(DaftarKamar);
            break;
        case 2:
            system("cls");
            ReservasiKamar(DaftarKamar);
            break;
        case 3:
            system("cls");
            DataReservasi(DaftarKamar);
            break;
        case 4:
            system("cls");
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