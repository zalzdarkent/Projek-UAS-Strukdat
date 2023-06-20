#include <iostream>
#include <iomanip>
using namespace std;

struct Kamar
{
    int nomorKamar, hargaPerMalam, lamaMenginap, totalHarga, bayar;
    bool reservasi;
    string WaktuReservasi, tipeKamar, namaPemesan, alamat, nomorTelepon;
    Kamar *next;
};

// salinan kodenya udah beralih di index.cpp ya ges
// nanti pas diclone atau mau di copy paste kodenya ada di index.cpp

void Login()
{
    string username, password;

    system("cls");
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

void TambahKamar(Kamar **head, int nomorKamar, string tipeKamar, int hargaPerMalam)
{
    Kamar *newKamar = new Kamar;
    newKamar->nomorKamar = nomorKamar;
    newKamar->tipeKamar = tipeKamar;

    // Mengatur hargaPerMalam sesuai dengan tipe kamar
    if (tipeKamar == "Single Room")
    {
        newKamar->hargaPerMalam = 400000;
    }
    else if (tipeKamar == "Double Room")
    {
        newKamar->hargaPerMalam = 550000;
    }
    else if (tipeKamar == "Deluxe Room")
    {
        newKamar->hargaPerMalam = 770000;
    }
    else if (tipeKamar == "Suite Room")
    {
        newKamar->hargaPerMalam = 1250000;
    }
    else
    {
        // Tipe kamar tidak valid, hargaPerMalam tetap menggunakan nilai yang diberikan saat pemanggilan fungsi
        newKamar->hargaPerMalam = hargaPerMalam;
    }

    newKamar->reservasi = false;
    newKamar->next = nullptr;

    // Jika daftar kamar masih kosong
    if (*head == nullptr)
    {
        *head = newKamar;
    }
    else
    {
        Kamar *current = *head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = newKamar;
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
        bool adaKamarTersedia = false; // tambahkan variabel boolean ini

        while (current != nullptr)
        {
            if (!current->reservasi)
            {
                adaKamarTersedia = true; // setel variabel ke true jika ada kamar yang tersedia
                cout << "Kamar " << current->nomorKamar << "\t\t";
                cout << current->tipeKamar << "\t\t\t";
                cout << current->hargaPerMalam << endl;
            }
            current = current->next;
        }

        if (!adaKamarTersedia) // tambahkan kondisi ini untuk menampilkan pesan jika semua kamar telah direservasi
        {
            cout << "Semua kamar telah dibooking.\n";
        }
        else
        {
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
                            cout << "\t- Fasilitas: Kasur single, TV, AC, wifi, kamar mandi\n";
                            cout << "\t- Harga: Rp. " << current->hargaPerMalam << endl;
                        }
                        else if (current->tipeKamar == "Double Room")
                        {
                            cout << "\t- Tipe kamar: Double Room\n";
                            cout << "\t- Fasilitas: Kasur double, TV, AC, wifi, kamar mandi\n";
                            cout << "\t- Harga: Rp. " << current->hargaPerMalam << endl;
                        }
                        else if (current->tipeKamar == "Deluxe Room")
                        {
                            cout << "\t- Tipe kamar: Deluxe Room\n";
                            cout << "\t- Fasilitas: Kasur king-size, TV, AC, wifi, kamar mandi, minibar\n";
                            cout << "\t- Harga: Rp. " << current->hargaPerMalam << endl;
                        }
                        else if (current->tipeKamar == "Suite Room")
                        {
                            cout << "\t- Tipe kamar: Suite Room\n";
                            cout << "\t- Fasilitas: Kasur king-size, ruang tamu, TV, AC, wifi, kamar mandi, minibar\n";
                            cout << "\t- Harga: Rp. " << current->hargaPerMalam << endl;
                        }
                        cout << "----------------------------------------------------------\n\n";
                    }
                    current = current->next;
                }
                cout << "Harga sudah termasuk untuk sarapan, makan siang, dan makan malam" << endl;
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

void ReservasiKamar(Kamar *head)
{
    int nomorKamar, lamaMenginap, hargaPerMalam, bayar, totalHarga;
    string WaktuReservasi, namaPemesan, nomorTelepon, alamat;

    cout << "========================Data Kamar========================\n";
    cout << "Kamar\t\tTipe Kamar\t\tHarga Per Malam\n";
    cout << "----------------------------------------------------------\n\n";

    Kamar *current = head;
    bool kamarTersedia = false;
    while (current != nullptr)
    {
        if (!current->reservasi)
        {
            cout << "Kamar " << current->nomorKamar << "\t\t";
            cout << current->tipeKamar << "\t\t\t";
            cout << "Rp. " << fixed << setprecision(2) << current->hargaPerMalam << endl;
            kamarTersedia = true;
        }
        current = current->next;
    }

    if (!kamarTersedia)
    {
        cout << "Tidak ada kamar yang tersedia.\n";
        cout << endl
             << "Tekan enter untuk kembali ke menu...";
        cin.ignore();
        cin.get();
        return;
    }

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

        current = head;
        while (current != nullptr)
        {
            if (current->nomorKamar == nomorKamar && !current->reservasi)
            {
                kamarDitemukan = true;
                cout << "Masukkan waktu reservasi (hari): ";
                cin >> WaktuReservasi;
                cout << "Masukkan nomor telepon: ";
                cin >> nomorTelepon;
                cout << "Masukkan alamat: ";
                cin >> alamat;
                cout << "Masukkan nama pemesan: ";
                cin.ignore();
                getline(cin, namaPemesan);
                cout << "Lama menginap (berapa malam): ";
                cin >> lamaMenginap;
                totalHarga = lamaMenginap * current->hargaPerMalam;
                if (lamaMenginap >= 5)
                {
                    double diskon = 0.15 * totalHarga;
                    totalHarga -= diskon;
                    cout << "Selamat! Anda mendapatkan diskon 15%." << endl;
                    cout << "Total harga setelah diskon: Rp. " << totalHarga << endl;
                }
                cout << "Total harga: Rp. " << totalHarga << endl;
                cout << "Bayar sekarang: Rp. ";
                cin >> bayar;
                if (bayar < totalHarga)
                {
                    system("cls");
                    cout << "Maaf, uang Anda tidak mencukupi." << endl;
                    cout << endl
                         << "Tekan enter untuk kembali ke menu...";
                    cin.ignore();
                    cin.get();
                    return;
                }
                int kembalian;
                kembalian = bayar - totalHarga;
                current->reservasi = true;
                current->WaktuReservasi = WaktuReservasi;
                current->namaPemesan = namaPemesan;
                current->nomorTelepon = nomorTelepon;
                current->alamat = alamat;
                current->bayar = bayar;
                current->lamaMenginap = lamaMenginap;
                current->totalHarga = totalHarga;
                system("cls");
                cout << "Kamar nomor " << current->nomorKamar << " berhasil dipesan pada hari " << current->WaktuReservasi << " oleh " << current->namaPemesan << ".\n";
                cout << "Nomor telepon pemesan: " << current->nomorTelepon << endl;
                cout << "Alamat pemesan: " << current->alamat << endl;
                if (bayar > totalHarga)
                {
                    cout << "Kembalian sebesar: Rp. " << kembalian << endl;
                }
                cout << endl
                     << "Tekan enter untuk kembali ke menu...";
                cin.ignore();
                cin.get();
                return;
            }
            current = current->next;
        }

        char pilihan;
        cout << "Kamar dengan nomor " << nomorKamar << " tidak tersedia atau tidak valid. Apakah Anda ingin mencoba lagi? (y/n): ";
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
    cout << "========================================================================================================================================\n";
    cout << "                                                          Data Reservasi Kamar                                                          \n";
    cout << "========================================================================================================================================\n";
    cout << "No. |   Atas Nama   | Nomor Kamar  |     Tipe Kamar      |  Harga  |  Waktu Reservasi  |  Nomor Telepon |   Alamat  |  Lama Menginap  | \n";
    cout << "----------------------------------------------------------------------------------------------------------------------------------------\n";
    int nomorUrut = 1;
    while (current != nullptr)
    {
        if (current->reservasi)
        {
            cout << setw(3) << nomorUrut << " |";
            cout << setw(14) << current->namaPemesan << " |";
            cout << setw(11) << "Kamar " << current->nomorKamar << " |";
            cout << setw(19) << current->tipeKamar << " |";
            cout << setw(10) << "Rp. " << current->totalHarga << " |";
            cout << setw(15) << current->WaktuReservasi << " |";
            cout << setw(15) << current->nomorTelepon << " |";
            cout << setw(15) << current->alamat << " |";
            cout << setw(15) << current->lamaMenginap << " Malam" << endl;
            TelahReservasi = true;
            nomorUrut++;
        }
        current = current->next;
    }
    if (!TelahReservasi)
    {
        cout << "Tidak ada kamar yang dipesan.\n";
    }
    cout << "=======================================================================================================================================\n";
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

    cout << "========================================================================================================================================\n";
    cout << "                                                          Data Reservasi Kamar                                                          \n";
    cout << "========================================================================================================================================\n";
    cout << "No. |   Atas Nama   | Nomor Kamar  |     Tipe Kamar      |  Harga  |  Waktu Reservasi  |  Nomor Telepon |   Alamat  |  Lama Menginap  | \n";
    cout << "----------------------------------------------------------------------------------------------------------------------------------------\n";
    current = head;
    int nomorUrut = 1;

    while (current != nullptr)
    {
        if (current->reservasi)
        {
            cout << setw(3) << nomorUrut << " |";
            cout << setw(14) << current->namaPemesan << " |";
            cout << setw(12) << "Kamar " << current->nomorKamar << " |";
            cout << setw(21) << current->tipeKamar << " |";
            cout << setw(5) << "Rp. " << current->totalHarga << " |";
            cout << setw(15) << current->WaktuReservasi << " |";
            cout << setw(15) << current->nomorTelepon << " |";
            cout << setw(15) << current->alamat << " |";
            cout << setw(15) << current->lamaMenginap << " Malam" << endl;
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
            cout << "Uang anda akan kami kembalikan dalam waktu 24 jam.\n";
            cout << "Jika uang anda tidak kembali, hubungi call center kami (0812-9089-1345).\n";
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
                    cout << "Uang anda akan kami kembalikan dalam waktu 24 jam." << endl;
                    cout << "Jika uang anda tidak kembali, hubungi call center kami (0812-9089-1345)." << endl;
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

void anggotakelompok()
{
    cout << "========== Anggota Kelompok ==========\n";
    cout << "1. Alif Fadillah Ummar"
         << "             2210631170004" << endl;
    cout << "2. Alustina Suci Manah"
         << "             2210631170" << endl;
    cout << "3. Ari Rizwan"
         << "                      2210631170" << endl;
    cout << "4. Mishel Aulidya"
         << "                  2210631170" << endl;
    cout << "5. Sopian Syauri"
         << "                   2210631170" << endl;
    cout << "6. Tjoargen Christoper Redja"
         << "       2210631170" << endl;
}

int main()
{
    Kamar *DaftarKamar = nullptr;
    TambahKamar(&DaftarKamar, 1, "Single Room", 0);
    TambahKamar(&DaftarKamar, 2, "Double Room", 0);
    TambahKamar(&DaftarKamar, 3, "Deluxe Room", 0);
    TambahKamar(&DaftarKamar, 4, "Suite Room", 0);

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
            anggotakelompok();
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