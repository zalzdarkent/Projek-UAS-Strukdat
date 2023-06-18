#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#define MAX 100
using namespace std;

struct reservation {
    string nama, alamat, hp, checkin, checkout, tipe_kamar;
    int id, lama, harga_kamar, total_harga, no_kamar,choose;
    char kelamin;
};

struct node {
    reservation data;
    struct node* next;
};

struct stackNode {
    reservation data;
    stackNode* next;
};

struct queueNode {
    reservation data;
    queueNode* next;
};

struct treeNode {
    reservation data;
    treeNode* left;
    treeNode* right;
};

treeNode* createNode(const reservation& data) {
    treeNode* newNode = new treeNode;
    newNode->data = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

bool isEmpty(stackNode* top);
void push(stackNode*& top, reservation data);
void pop(stackNode*& top);
void displayStack(stackNode* top);
void enqueue(queueNode*& front, queueNode*& rear, reservation data);
void dequeue(queueNode*& front, queueNode*& rear);
void displayQueue(queueNode* front);
void menu_reservasi();
void daftar_reservasi();
void batalkan_reservasi();
void checkIn();
void insertNode(treeNode*& root, const reservation& data);
void checkOut();
void displayInOrder(treeNode* root);
void cetakgraph (int n);
void searchpath (int x, int y);

const int MAX_ROOMS = 10;
node* head = nullptr;
int id = 0;
int harga_kamar[5] = { 100000, 200000, 300000, 500000, 800000 };
string tipe_kamar[5] = { "Economy Room", "Standard Room", "Superior Room", "Deluxe Room", "Suite Room" };
int room_available[] = {2,2,2,2,2};
int room_status[10][10];
stackNode* top = nullptr;
queueNode* front = nullptr;
queueNode* rear = nullptr;
treeNode* root = nullptr;
int graph[6][6]={{1,1,0,0,0,0},{1,1,1,0,0,0},{0,1,1,1,0,0},{0,0,1,1,1,0},{0,0,0,1,1,1},{0,0,0,0,1,1}};
int n=6;
int simpul1=0,simpul2=0;

int main() {
    int choice;
    int source, destination, j, i,x,y;
    while (true) {
        system("cls");
        cout << "=======================================================\n";
        cout << "         PROGRAM HOTEL INFORMATIKA - RESERVASI        \n";
        cout << "=======================================================\n";
        cout << " 1. Reservasi Kamar\n";
        cout << " 2. Check-in\n";
        cout << " 3. Check-out\n";
        cout << " 4. Daftar Reservasi Kamar\n";
        cout << " 5. Lihat Daftar Check-in\n";
        cout << " 6. Lihat Daftar Check-out\n";
        cout << " 7. Cetak Denah" << endl;
        cout << " 8. Cari Jalur" << endl;
        cout << " 9. Batalkan Reservasi Kamar\n";
        cout << " 10. Tampilkan Data Reservasi yang Dibatalkan\n";
        cout << " 0. Keluar\n";
        cout << "=======================================================\n";
        cout << " Masukkan Pilihan : ";
        cin >> choice;
        switch (choice) {
        case 0:
            return 0;
        case 1:
            menu_reservasi();
            break;
        case 2:
            system("cls");
            cout << "=========     Check-in     =========\n";
            checkIn();
            break;
        case 3:
            system("cls");
            cout << "=========     Check-out     =========\n";
            checkOut();
            break;
        case 4:
            daftar_reservasi();
            break;
        case 5:
            system("cls");
            cout << "========= Daftar Check-in =========\n";
            displayQueue(front);
            system("pause");
            break;
        case 6:
            system("cls");
            cout << "========= Daftar Check-out =========\n";
            displayInOrder(root);
            system("pause");
            break;
        case 7:
            system("cls");
            cout << "=========     Cetak denah hotel     =========\n";
            cetakgraph(n);
            system("pause");
            break;
        case 8:
            system("cls");
            cout << "=========     Mencari Jalur Terpendek     =========\n";
            cout << "Masukkan Kamar asal   = ";cin >> x;
            cout << "Masukkan Kamar tujuan = ";cin >> y;
            searchpath(x,y);
            system("pause");
            break;
        case 9:
            system("cls");
            cout << "=========     Batalkan Reservasi Kamar     =========\n";
            batalkan_reservasi();
            break;
        case 10:
            system("cls");
            cout << "=========     Data Reservasi yang dibatalkan     =========\n";
            displayStack(top);
            system("pause");
            break;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
            system("pause");
            break;
        }
    }
}
bool isEmpty(stackNode* top) {
    return top == nullptr;
}
void push(stackNode*& top, reservation data) {
    stackNode* newNode = new (std::nothrow) stackNode;  // Use 'std::nothrow' to return a null pointer instead of throwing an exception on failure
    if (newNode == nullptr) {
        cout << "Memory allocation failed for new node.\n";
        return;
    }
    newNode->data = data;
    newNode->next = top;
    top = newNode;
}
void pop(stackNode*& top) {
    if (isEmpty(top)) {
        cout << "Error: Stack is empty. Cannot pop an element.\n";
        return;
    }
    stackNode* temp = top;
    top = top->next;
    delete temp;
}
void displayStack(stackNode* top) {
    if (isEmpty(top)) {
        cout << "Stack is empty.\n";
        return;
    }
    stackNode* temp = top;
    while (temp != nullptr) {
        cout << "ID Pemesan       : " << temp->data.id << endl;
        cout << "Nama Pemesan     : " << temp->data.nama << endl;
        cout << "Alamat           : " << temp->data.alamat << endl;
        cout << "Telp/HP          : " << temp->data.hp << endl;
        cout << "Harga Kamar      : Rp. " << temp->data.harga_kamar << endl;
        cout << "Nomor Kamar      : " << temp->data.no_kamar << endl;
        cout << "Lama Menginap    : " << temp->data.lama << " Hari\n";
        cout << "Tanggal Check in : " << temp->data.checkin << endl;
        cout << "Tanggal Check out: " << temp->data.checkout << endl;
        cout << "Biaya Total      : Rp. " << temp->data.total_harga << endl;
        cout << endl;
        temp = temp->next;
    }
}
void enqueue(queueNode*& front, queueNode*& rear, reservation data) {
    queueNode* newNode = new queueNode;
    newNode->data = data;
    newNode->next = nullptr;
    if (rear == nullptr) {
        front = rear = newNode;
    }
    else {
        rear->next = newNode;
        rear = newNode;
    }
}
void dequeue(queueNode*& front, queueNode*& rear) {
    if (front == nullptr) {
        cout << "Queue is empty.\n";
        return;
    }
    queueNode* temp = front;
    front = front->next;
    if (front == nullptr) {
        rear = nullptr;
    }
    delete temp;
}
void displayQueue(queueNode* front) {
    if (front == nullptr) {
        cout << "Queue is empty.\n";
        return;
    }
    queueNode* temp = front;
    while (temp != nullptr) {
        cout << "ID Pemesan       : " << temp->data.id << endl;
        cout << "Nama Pemesan     : " << temp->data.nama << endl;
        cout << "Alamat           : " << temp->data.alamat << endl;
        cout << "Telp/HP          : " << temp->data.hp << endl;
        cout << "Harga Kamar      : Rp. " << temp->data.harga_kamar << endl;
        cout << "Nomor Kamar      : " << temp->data.no_kamar << endl;
        cout << "Lama Menginap    : " << temp->data.lama << " Hari\n";
        cout << "Tanggal Check in : " << temp->data.checkin << endl;
        cout << "Tanggal Check out: " << temp->data.checkout << endl;
        cout << "Biaya Total      : Rp. " << temp->data.total_harga << endl;
        cout << endl;
        temp = temp->next;
    }
}
void menu_reservasi() {
    system("cls");
    node* newNode = new node;
    int bayar;
    newNode->data.id = id;
    cout << "======================================================\n";
    cout << "         PROGRAM HOTEL INFORMATIKA - RESERVASI        \n";
    cout << "======================================================\n\n";
    cout << " ID Pemesan                : " << id << endl;
    cout << " Nama Pemesan              : ";
    cin >> newNode->data.nama;
    cout << " Telp/HP                   : ";
    cin >> newNode->data.hp;
    cout << " Alamat                    : ";
    cin.ignore();
    getline(cin, newNode->data.alamat);
    cout << "=======================================================\n";
    cout << "             Masukkan Tipe Kamar                         \n";
    cout << "=======================================================\n";
    cout << "  1. Economy Room       |     Rp.100.000                \n";
    cout << "  2. Standard Room      |     Rp.200.000                \n";
    cout << "  3. Superior Room      |     Rp.300.000                \n";
    cout << "  4. Deluxe Room        |     Rp.500.000                \n";
    cout << "  5. Suite Room         |     Rp.800.000                \n";
    cout << "=======================================================\n";
    cout << "  Masukkan Pilihan : ";
    int choose;
    cin >> choose;
    cout << endl << endl;
    if (choose >= 1 && choose <= 5) {
        choose--;
        newNode->data.choose = choose;
        newNode->data.tipe_kamar = tipe_kamar[choose];
        newNode->data.harga_kamar = harga_kamar[choose];
        if (room_available[choose] > 0) {
            int roomNumber = 0;
            for (int i = 0; i < MAX_ROOMS; i++) {
                if (room_status[choose][i] == 0) {
                    room_status[choose][i] = 1;
                    roomNumber = i + 1 +((choose + 1) * 10);
                    room_available[choose]--;
                    break;
                }
            }
            if (roomNumber != 0) {
                newNode->data.no_kamar = roomNumber;
                cout << tipe_kamar[choose] << " berhasil dipilih\n";
                cout << "Harga Kamar    : " << harga_kamar[choose] << endl;
                cout << "Nomor Kamar    : " << roomNumber << endl;
            }
            else {
                cout << "Maaf, kamar " << tipe_kamar[choose] << " sudah penuh.\n";
                cout << "Silahkan pilih tipe kamar lain.\n";
                delete newNode;
                system("pause");
                return;
            }
        }
        else {
            cout << "Maaf, kamar " << tipe_kamar[choose] << " sudah penuh.\n";
            cout << "Silahkan pilih tipe kamar lain.\n";
            delete newNode;
            system("pause");
            return;
        }
    }
    else {
        cout << "Pilihan tidak valid.\n";
        delete newNode;
        return;
    }
    cout << "Lama Menginap  : ";
    cin >> newNode->data.lama;
    cout << "Tanggal Check In [DDMMYYYY]   : ";
    cin >> newNode->data.checkin;
    cout << "Tanggal Check Out [DDMMYYYY]  : ";
    cin >> newNode->data.checkout;
    newNode->data.total_harga = newNode->data.lama * newNode->data.harga_kamar;
    newNode->next = nullptr;
    if (head == nullptr) {
        head = newNode;
    }
    else {
        node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    system("cls");
    cout << "=================================================================================\n";
    cout << "                             Data Pemesanan Kamar                                \n";
    cout << "=================================================================================\n";
    cout << "ID Pemesan           : " << newNode->data.id << endl;
    cout << "Nama Pemesan         : " << newNode->data.nama << endl;
    cout << "Alamat               : " << newNode->data.alamat << endl;
    cout << "Telp/HP              : " << newNode->data.hp << endl;
    cout << "Tipe kamar           : " << newNode->data.tipe_kamar << endl;
    cout << "Harga Kamar          : Rp. " << newNode->data.harga_kamar << endl;
    cout << "Nomor Kamar          : " << newNode->data.no_kamar << endl;
    cout << "Lama Menginap        : " << newNode->data.lama << " Hari\n";
    cout << "Tanggal Check in     : " << newNode->data.checkin << endl;
    cout << "Tanggal Check out    : " << newNode->data.checkout << endl;
    cout << "Biaya Total          : Rp. " << newNode->data.total_harga << endl;
    cout << "Uang yang dibayarkan : Rp. ";
    do{
        cin >> bayar;
        if(newNode->data.total_harga>bayar){
            cout << "Maaf uang yang anda berikan tidak cukup\n";
        }
        else{
            cout << "Uang sisa bayar      : " << bayar-newNode->data.total_harga << endl;
            id++;
            system("pause");
        }
    }while (newNode->data.total_harga>bayar);
}
void daftar_reservasi() {
    system("cls");
    cout << "=======================================================\n";
    cout << "                   Daftar reservasi                    \n";
    cout << "=======================================================\n";
    if (head == nullptr) {
        cout << "\nBelum ada data reservasi.\n";
    }
    else {
        cout << "\nDaftar Semua Reservasi Kamar:\n";
        node* temp = head;
        while (temp != nullptr) {
            cout << "ID Pemesan       : " << temp->data.id << endl;
            cout << "Nama Pemesan     : " << temp->data.nama << endl;
            cout << "Alamat           : " << temp->data.alamat << endl;
            cout << "Telp/HP          : " << temp->data.hp << endl;
            cout << "Harga Kamar      : Rp. " << temp->data.harga_kamar << endl;
            cout << "Nomor Kamar      : " << temp->data.no_kamar << endl;
            cout << "Lama Menginap    : " << temp->data.lama << " Hari\n";
            cout << "Tanggal Check in : " << temp->data.checkin << endl;
            cout << "Tanggal Check out: " << temp->data.checkout << endl;
            cout << "Biaya Total      : Rp. " << temp->data.total_harga << endl << endl;
            temp = temp->next;
        }
    }
    system("pause");
}
void batalkan_reservasi() {
    if (head == nullptr) {
        cout << "Belum ada data reservasi.\n";
        system("pause");
        return;
    }
    int cancel_id;
    cout << "Masukkan ID Pemesan yang ingin dibatalkan: ";
    cin >> cancel_id;
    node* temp = head;
    node* prev = nullptr;
    while (temp != nullptr) {
        if (temp->data.id == cancel_id) {
            push(top, temp->data);
            if (prev == nullptr) {
                head = temp->next;
                delete temp;
                cout << "Reservasi dengan ID " << cancel_id << " berhasil dibatalkan.\n";
                break;
            }
            else {
                prev->next = temp->next;
                delete temp;
                cout << "Reservasi dengan ID " << cancel_id << " berhasil dibatalkan.\n";
                break;
            }
        }
        prev = temp;
        temp = temp->next;
    }
    if (temp == nullptr) {
        cout << "Reservasi dengan ID " << cancel_id << " tidak ditemukan.\n";
    }
    system("pause");
}
void checkIn() {
    int id;
    cout << "Masukkan ID Reservasi: ";
    cin >> id;
    node* temp = head;
    node* prev = nullptr;
    while (temp != nullptr && temp->data.id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == nullptr) {
        cout << "Reservasi dengan ID tersebut tidak ditemukan.\n\n";
        system("pause");
        return;
    }
    reservation data = temp->data;
    enqueue(front, rear, data);
    if (prev == nullptr) {
        head = temp->next;
    }
    else {
        prev->next = temp->next;
    }
    delete temp;
    cout << "Check-in berhasil!\n\n";
    system("pause");
}
void insertNode(treeNode*& root, const reservation& data) {
    if (root == nullptr) {
        root = createNode(data);
    } else {
        if (data.id < root->data.id) {
            insertNode(root->left, data);
        } else {
            insertNode(root->right, data);
        }
    }
}
void checkOut() {
    int id;
    cout << "Masukkan ID Reservasi: ";
    cin >> id;
    queueNode* temp = front;
    queueNode* prev = nullptr;
    while (temp != nullptr && temp->data.id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == nullptr) {
        cout << "Reservasi dengan ID tersebut tidak ditemukan.\n\n";
        system("pause");
        return;
    }
    reservation data = temp->data;
    insertNode(root, temp->data);
    room_status[temp->data.choose][temp->data.no_kamar - 1 -((temp->data.choose + 1) * 10)]=0;
    if (prev == nullptr) {
        front = temp->next;
    }
    else {
        prev->next = temp->next;
    }
    delete temp;
    cout << "Check-out berhasil!\n\n";
    system("pause");
}
void displayInOrder(treeNode* root) {
    if (root != nullptr) {
        displayInOrder(root->left);
        cout << "ID Pemesan       : " << root->data.id << endl;
        cout << "Nama Pemesan     : " << root->data.nama << endl;
        cout << "Alamat           : " << root->data.alamat << endl;
        cout << "Telp/HP          : " << root->data.hp << endl;
        cout << "Harga Kamar      : Rp. " << root->data.harga_kamar << endl;
        cout << "Nomor Kamar      : " << root->data.no_kamar << endl;
        cout << "Lama Menginap    : " << root->data.lama << " Hari" << endl;
        cout << "Tanggal Check in : " << root->data.checkin << endl;
        cout << "Tanggal Check out: " << root->data.checkout << endl;
        cout << "Biaya Total      : Rp. " << root->data.total_harga << endl;
        cout << endl;
        displayInOrder(root->right);
    }
}
void cetakgraph (int n) {
    int i,j;
    cout << "Setiap kamar terhubung dengan kamar lainnya melalui satu lorong\n";
    cout << "Angka 1 pada matriks merepresentasikan bahwa 1 kamar berdekatan dengan kamar lainnya\n\n";
    cout << "  ";
    simpul1=0;
    simpul2=0;
    for (i=0;i<n;i++){
    cout << simpul1++ << " ";
    }
    cout << endl;
    for(i=0;i<n;i++){
    cout << simpul2++<< " ";
    for (j=0;j<n;j++){
        cout << graph[i][j]<< " ";
    }
    cout<< endl;
    }
    cout << "\nsetiap lantai memiliki denah yang sama\ntangga darurat ada di dekat kamar 1 dan 5 di setiap lantai\n\n";
}
void searchpath (int x, int y){
    int source = x;
    int destination = y;
    int visited [MAX] = {0};
    int dist[MAX];
    int parent[MAX];
    for (int i=0;i<n;i++){
        dist[i]= MAX;
        parent[i]=-1;
    }
    dist[source]=0;
    visited[source]=1;
    parent[source]=-1;
    int queue[MAX];
    int front = 0;
    int rear = 0;
    int z = 0;
    queue[rear++]=source;
    while (front != rear){
        int u = queue[front++];
        for (int v=0;v<n;v++){
            if (graph[u][v] && !visited[v]){
                visited[v]=1;
                dist[v]=dist[u]+1;
                parent[v]= u;
                queue[rear++] = v;
            }
        }
    }
    if (!visited[destination]){
        cout << "tidak ada jalur dari " << x << " ke " << y << endl;
    } else{
        cout << "jarak terpendek dari " << x << " ke " << y << " adalah " << dist[destination] << endl;
        cout << "jalur terpendek adalah: " ;
        int u = destination;
        while (u!=-1){
        simpul1=0;
        simpul1+=u;
        cout<<simpul1<< " ";
        u=parent[u];
        }
        cout << endl;
    }
}