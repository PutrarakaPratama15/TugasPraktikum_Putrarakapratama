#include <iostream>
#include <iomanip>

using namespace std;

// Definisi struktur Menu
struct Menu {
    string nama;
    int harga;
};

// Fungsi untuk menampilkan daftar menu
void tampilkanMenu(const Menu daftarMenu[], int size) {
    cout << "selamat datang di restoran Baratie" << endl;
    cout << "------anda bahagia kami tidak--------" << endl << endl;
    cout << "Daftar Menu Restoran:" << endl;
    cout << setw(20) << left << "Menu" << setw(31) << right << "Harga" << endl;
    cout << setfill('-') << setw(51) << "" << setfill(' ') << endl;

    for (int i = 0; i < size; ++i) {
        cout << setw(31) << left << daftarMenu[i].nama << setw(20) << right << daftarMenu[i].harga 
        << endl;
    }
}

// Struktur untuk node dalam linked list
struct Node {
    Menu pesanan;
    Node* next;
};

// Struktur untuk linked list daftar pesanan pelanggan
struct PesananList {
    Node* head;
    Node* tail;
};

// Fungsi untuk membuat node baru dalam linked list
Node* buatNode(Menu pesanan) {
    Node* nodeBaru = new Node;
    nodeBaru->pesanan = pesanan;
    nodeBaru->next = nullptr;
    return nodeBaru;
}

// Fungsi untuk menambahkan pesanan ke linked list
void tambahPesanan(PesananList& list, Menu pesanan) {
    Node* nodeBaru = buatNode(pesanan);
    if (list.head == nullptr) {
        list.head = list.tail = nodeBaru;
    } else {
        list.tail->next = nodeBaru;
        list.tail = nodeBaru;
    }
}

// Fungsi untuk menampilkan seluruh pesanan dari linked list
void tampilkanPesanan(const PesananList& list) {
    Node* current = list.head;
    cout << setw(35) << left << "\nmenu yang dipesan" << setw(10) << right << "jumlah" << endl;
    cout << setfill('-') << setw(50) << "" << setfill(' ') << endl;
    while (current != nullptr) {
        cout << setw(33) << left << current->pesanan.nama << setw(10) << right  
        << current->pesanan.harga << endl;
        current = current->next;
    }
}

// Fungsi untuk menghapus seluruh node dalam linked list
void hapusSemuaNode(PesananList& list) {
    Node* current = list.head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    list.head = list.tail = nullptr;
}

int main() {
    // Inisialisasi daftar menu
    const int jumlahMenu = 8;
    Menu daftarMenu[jumlahMenu] = {
        {"1. gomu gomu no mi", 40000},
        {"2. yami yami no mi", 60000},
        {"3. bara bara no mi", 35000},
        {"4. ope ope no mi", 350000},
        {"5. mera mera no mi", 50000},
        {"6. gura gura no mi", 300000},
        {"7. mero mero no mi", 40000},
        {"8. mochi mochi no mi", 45000}
    };

    // Menampilkan daftar menu
    tampilkanMenu(daftarMenu, jumlahMenu);

    // Memproses pesanan
    int totalHarga = 0;
    char lanjutPesan;
    int uangPelanggan = 0;

    PesananList pesananPelanggan;
    pesananPelanggan.head = pesananPelanggan.tail = nullptr;

    do {
        int nomorMenu, jumlahPesanan;

        cout << "\nMasukkan nomor menu yang dipilih: ";
        cin >> nomorMenu;

        // Periksa apakah nomor menu valid
        if (nomorMenu >= 1 && nomorMenu <= jumlahMenu) {
            cout << "Masukkan jumlah pesanan: ";
            cin >> jumlahPesanan;

            totalHarga += daftarMenu[nomorMenu - 1].harga * jumlahPesanan;

            // Menambahkan pesanan ke linked list
            tambahPesanan(pesananPelanggan, daftarMenu[nomorMenu - 1]);

            cout << "\nLanjutkan pesanan? (y/n): ";
            cin >> lanjutPesan;
        } else {
            cout << "Nomor menu tidak valid. Silakan coba lagi." << endl;
            return 0;
        }
    } while (lanjutPesan == 'y' || lanjutPesan == 'Y');

    // Menampilkan daftar pesanan
    tampilkanPesanan(pesananPelanggan);

    //diskon
   int diskon = 0;

    if (totalHarga > 500000) {
        diskon = 10;
        cout << "\nSelamat anda mendapatkan diskon sebesar 10%" << endl;
    } else if (totalHarga > 200000) {
        diskon = 5;
        cout << "\nSelamat anda mendapatkan diskon sebesar 15%" << endl;
    } else if (totalHarga > 100000) {
        diskon = 3;
        cout << "\nSelamat anda mendapatkan diskon sebesar 3%" << endl;
    }


    // Pajak
    double persentase = 0.10;
    int pajak = totalHarga * persentase;
    cout << "\ntotal sebelum pajak : " << totalHarga <<endl;
    cout << "Pajak: " << pajak << endl;

    // Menampilkan total harga setelah diskon dan pajak
    int totalSetelahDiskon = totalHarga - (totalHarga * diskon / 100);
    int totalSeluruhHarga = totalSetelahDiskon + pajak;

    cout << "total sebelum diskon : " << totalHarga + pajak << endl;
    cout << "diskon : -" << totalHarga * diskon / 100 << endl;
    cout << "Total Seluruh Harga: " << totalSeluruhHarga << endl;
    cout << "Masukkan uang anda: ";
cin >> uangPelanggan;
int kembalian = uangPelanggan - totalSeluruhHarga;

//output jika uang pelanggan kurang
if (uangPelanggan < totalHarga) {
    cout << "Maaf uang anda kurang untuk membeli menu ini." << endl;
} else {
    cout << "Kembalian anda: " << kembalian << endl; // Menampilkan kembalian pelanggan
}

cout << "\nterima kasih telah berbelanja di restoran Baratie"<<endl;
cout << "-------------anda bahagia kami tidak---------------" << endl;
cout << "----------------selamat menikmati------------------";

return 0;

}