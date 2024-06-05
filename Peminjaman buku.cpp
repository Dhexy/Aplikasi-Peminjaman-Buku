#include <iostream>
#include <string>
#include <cstring>
#include <limits>
#include <conio.h>
#include <ctime>

using namespace std;

string loggedInUser;

struct akun {
    char username[100];
    char password[16];
    int saldo;
    akun *next;
};

struct Book {
    string title;
    string author;
    int year;
    int stock;
    Book* next;
};

Book* head = nullptr;
Book* tail = nullptr;

struct Node
{
    string namaPeminjam;
    string judulBuku;
    tm tanggalPinjam;
    string status;
    tm tanggalKembali;
    Node *next;
    Node *prev;
};

Node* headp = nullptr;
Node* tailp = nullptr;





// bool cekUsername(akun *head, const char *username) {
//     akun *current = head;
//     while (current != NULL) {
//         if (strcmp(current->username, username) == 0) {
//             return true; // Username sudah digunakan
//         }
//         current = current->next;
//     }
//     return false; // Username belum digunakan
// }

bool cekUsername(akun *head, const char *username) {
    akun *current = head;
    while (current != NULL) {
        if (strcmp(current->username, username) == 0) {
            return true; // Username sudah digunakan
        }
        current = current->next;
    }
    return false; // Username belum digunakan
}


void registerUser(akun *&head) {
    akun *newAkun = new akun;

    char cekPassword[16];
    cout << "--------------------Register--------------------" << endl;
    cout << "Masukkan username: ";
    cin >> newAkun->username;

    while (cekUsername(head, newAkun->username)) {
        cout << "Username sudah digunakan, masukkan username lain: ";
        cin >> newAkun->username;
    }

    cout << "Masukkan password (minimal 8 karakter): ";
    cin >> newAkun->password;

    while (strlen(newAkun->password) < 8) {
        cout << "Password minimal 8 karakter" << endl;
        cout << "Masukkan password: ";
        cin >> newAkun->password;
    }

    bool loopPassword = true;
    while (loopPassword) {
        cout << "Masukkan ulang password: ";
        cin >> cekPassword;

        if (strcmp(cekPassword, newAkun->password) != 0) {
            cout << "Password tidak sesuai" << endl;
        } else {
            loopPassword = false;
        }
    }

    newAkun->next = NULL;
    if (head == NULL) {
        head = newAkun;
    } else {
        akun *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newAkun;
    }

    cout << endl << "=================Registrasi Berhasil=================" << endl;
}

void daftarAkun(akun *head) {
    akun *current = head;
    int nomor = 1;
    cout << endl << "------------------Daftar akun------------------" << endl;
    while (current != NULL) {
        cout << "Nomor: " << nomor << endl;
        cout << "Username: " << current->username << endl;
        cout << "Password: " << current->password << endl << endl;
        current = current->next;
        nomor++;
    }
}

void merubahAkun(akun *head, const char* username) {
    char usernameBaru[100];
    char passwordBaru[16];

    akun *current = head;
    while (current != NULL) {
        if (strcmp(username, current->username) == 0) {
            cout << "Masukkan username baru: ";
            cin >> usernameBaru;

            while (cekUsername(head, usernameBaru)) {
                cout << "Username sudah digunakan, masukkan username lain: ";
                cin >> usernameBaru;
            }

            cout << "Masukkan password baru (minimal 8 karakter): ";
            cin >> passwordBaru;

            while (strlen(passwordBaru) < 8) {
                cout << "Password minimal 8 karakter" << endl;
                cout << "Masukkan password baru: ";
                cin >> passwordBaru;
            }

            strcpy(current->username, usernameBaru);
            strcpy(current->password, passwordBaru);
            cout << "Akun berhasil diubah" << endl;

            // Update nilai loggedInUser menjadi username baru
            loggedInUser = usernameBaru;

            return;
        }
        current = current->next;
    }
}

// void hapusAkun(akun *&head, const char* username) {
//     akun *temp = head;
//     akun *prev = NULL;

//     if (temp != NULL && strcmp(temp->username, username) == 0) {
//         head = temp->next;
//         delete temp;
//         cout << "Akun berhasil dihapus" << endl;
//         return;
//     }

//     while (temp != NULL && strcmp(temp->username, username) != 0) {
//         prev = temp;
//         temp = temp->next;
//     }

//     if (temp == NULL) {
//         cout << "Akun tidak ditemukan" << endl;
//         return;
//     }

//     prev->next = temp->next;
//     delete temp;
//     cout << "Akun berhasil dihapus" << endl;
// }

// void hapusAkun(akun *&head, const char* username) {
//     akun *temp = head;
//     akun *prev = nullptr;

//     if (temp != NULL && strcmp(temp->username, username) == 0) {
//         head = temp->next;
//         delete temp;
//         cout << "Akun berhasil dihapus" << endl;
//         return;
//     }

//     while (temp != NULL && strcmp(temp->username, username) != 0) {
//         prev = temp;
//         temp = temp->next;
//     }

//     if (temp == NULL) {
//         cout << "Akun tidak ditemukan" << endl;
//         return;
//     }

//     if (prev != nullptr) {
//         prev->next = temp->next;
//     }

//     delete temp; // Bebaskan memori yang dialokasikan untuk akun yang dihapus
//     cout << "Akun berhasil dihapus" << endl;
// }

void hapusAkun(akun *&head, const char* username) {
    akun *temp = head;
    akun *prev = nullptr;

    if (temp != NULL && strcmp(temp->username, username) == 0) {
        head = temp->next;
        delete temp;
        cout << "Akun berhasil dihapus" << endl;
        return;
    }

    while (temp != NULL && strcmp(temp->username, username) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        cout << "Akun tidak ditemukan" << endl;
        return;
    }

    if (prev != nullptr) {
        prev->next = temp->next;
    }

    delete temp; // Bebaskan memori yang terkait dengan akun yang dihapus
    cout << "Akun berhasil dihapus" << endl;
}



void loginUser(akun *head, string& loggedInUser) {
    char logUser[100];
    char passUser[16];
    char ch;
    int i = 0;

    cout << "--------------------Login--------------------" << endl;

    bool loopLogin = true;
    while (loopLogin) {
        cout << "Masukan username: ";
        cin >> logUser;
        cout << "Masukan password: ";
         while (1) {
        ch = getch();
        if (ch == 13)
            break;
        else if (ch == 8) { 
            if (i > 0) {
                cout << "\b \b"; 
                i--;
            }
        }
        else {
            cout << '*';
            passUser[i] = ch;
            i++;
        }
    }
    passUser[i] = '\0';

        akun *current = head;
        while (current != NULL) {
            if (strcmp(logUser, current->username) == 0 &&
                strcmp(passUser, current->password) == 0) {
                cout << "\n=================Login berhasil=================" << endl;
                loopLogin = false;
                loggedInUser = logUser; // Menyimpan username yang berhasil login
                return;
            }
            current = current->next;
        }
        if (loopLogin) {
            cout << "Username atau password salah" << endl;
        }
    }
}

void HalamanProfil(akun *&head, const string& loggedInUser, bool &loggedIn) {
    char choice;
    while (true) {
        cout << "=== Menu Profil ===" << endl;
        cout << "1. Edit akun" << endl;
        cout << "2. Hapus akun" << endl;
        cout << "3. Kembali" << endl;
        cout << "Pilih menu: ";
        cin >> choice;

        switch (choice) {
            case '1':
                merubahAkun(head, loggedInUser.c_str());
                break;
            case '2':
                hapusAkun(head, loggedInUser.c_str());
                loggedIn =  false;
                return ;
            case '3':
                return; // Kembali ke menu sebelumnya
            default:
                cout << "Pilihan tidak valid" << endl;
                break;
        }
    }
}

//**Profil**

//**Buku**
bool isBookExists(const string& title) {
    Book* current = head;
    while (current != nullptr) {
        if (current->title == title) {
            return true; // Book title already exists
        }
        current = current->next;
    }
    return false; // Book title does not exist
}

void addBook(const string& title, const string& author, int year, int stock) {
    if (isBookExists(title)) {
        cout << "Judul buku sudah ada dalam daftar. Masukkan judul lain.\n";
        return;
    }

    // Create a new Book node
    Book* newBook = new Book;
    newBook->title = title;
    newBook->author = author;
    newBook->year = year;
    newBook->stock = stock;
    newBook->next = nullptr;

    // Insert the new book node into the list
    if (head == nullptr) {
        head = newBook; // First node in the list
        tail = newBook;
    } else {
        tail->next = newBook; // Link previous tail to the new node
        tail = newBook; // Update tail to the new node
    }
    cout << "Buku \"" << title << "\" berhasil ditambahkan ke dalam daftar.\n";
}

void displayBooks() {
    cout << "Daftar Buku:\n";
    int number = 1;
    Book* current = head;
    while (current != nullptr) {
        cout << number << ". " << current->title << " oleh " << current->author << " (" << current->year << ") - Stok: " << current->stock << "\n";
        current = current->next;
        number++;
    }
}

void editBook(const string& title) {
    if (!isBookExists(title)) {
        cout << "Buku dengan judul \"" << title << "\" tidak ditemukan.\n";
        return;
    }

    Book* current = head;

    while (current != nullptr) {
        if (current->title == title) {
            cout << "Buku ditemukan. Silakan masukkan informasi yang ingin diubah:\n";
            int choice;
            cout << "1. Judul buku\n";
            cout << "2. Nama pengarang\n";
            cout << "3. Tahun terbit\n";
            cout << "4. Stok\n";
            cout << "Pilih: ";
            cin >> choice;

            cin.ignore(); // Clear newline character from buffer

            switch (choice) {
                case 1:
                    {
                        string newTitle;
                        cout << "Masukkan judul buku baru: ";
                        getline(cin, newTitle);
                        while (isBookExists(title)) {
                        cout << "Judul buku sudah ada dalam daftar. Masukkan judul lain.\n";
                        cout << "Masukkan judul buku: ";
                        getline(cin, newTitle);
                        break;
                        }
                            current->title = newTitle;
                            cout << "Judul buku berhasil diubah.\n";
                        
                        break;
                    }
                case 2:
                    cout << "Masukkan nama pengarang baru: ";
                    getline(cin, current->author);
                    cout << "Nama pengarang berhasil diubah.\n";
                    break;
                case 3:
                    cout << "Masukkan tahun terbit baru: ";
                    cin >> current->year;
                    cout << "Tahun terbit berhasil diubah.\n";
                    break;
                case 4:
                    cout << "Masukkan stok baru: ";
                    cin >> current->stock;
                    cout << "Stok buku berhasil diubah.\n";
                    break;
                default:
                    cout << "Pilihan tidak valid.\n";
                    break;
            }
            break;
        }
        current = current->next;
    }
}

void deleteBook(const string& title) {
    Book* current = head;
    Book* prev = nullptr;
    bool found = false;

    while (current != nullptr) {
        if (current->title == title) {
            found = true;
            if (prev == nullptr) {
                // If the book to be deleted is the head node
                head = current->next;
            } else {
                prev->next = current->next;
            }

            if (current == tail) {
                // If the book to be deleted is the tail node
                tail = prev;
            }

            delete current;
            cout << "Buku dengan judul \"" << title << "\" berhasil dihapus dari daftar.\n";
            break;
        }
        prev = current;
        current = current->next;
    }

    if (!found) {
        cout << "Buku dengan judul \"" << title << "\" tidak ditemukan.\n";
    }
}

void halamanBuku(bool &loggedIn){
    int choice;

    while (choice!=5){
        cout << "\nMenu Pilihan Buku:\n";
        cout << "1. Tambah Buku Baru\n";
        cout << "2. Tampilkan Daftar Buku\n";
        cout << "3. Ubah Informasi Buku\n";
        cout << "4. Hapus Buku\n";
        cout << "5. Keluar\n";
        cout << "Pilih: ";
        cin >> choice;

        cin.ignore(); // Clear newline character from buffer

        switch (choice) {
            case 1:
                {
                    string title, author;
                    int year, stock;

                    cout << "Masukkan judul buku: ";
                    getline(cin, title);

                    while (isBookExists(title)) {
                        cout << "Judul buku sudah ada dalam daftar. Masukkan judul lain.\n";
                        cout << "Masukkan judul buku: ";
                        getline(cin, title);
                        break;
                    }

                    cout << "Masukkan nama pengarang: ";
                    getline(cin, author);

                    while (true) {
                        cout << "Masukkan tahun terbit: ";

                        // Validate year input using cin.fail()
                        if (cin >> year && !cin.fail()) {
                            break; // Valid integer input
                        } else {
                            // Clear error state and discard non-numeric input
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Masukkan tahun yang valid (format angka)." << endl;
                        }
                    }

                    cout << "Masukkan stok buku: ";
                    cin >> stock;

                    addBook(title, author, year, stock);
                    break;
                }
            case 2:
                displayBooks();
                break;
            case 3:
                {
                    string title;
                    cout << "Masukkan judul buku yang ingin diubah: ";
                    getline(cin, title);
                    editBook(title);
                    break;
                }
            case 4:
                {
                    string title;
                    cout << "Masukkan judul buku yang ingin dihapus: ";
                    getline(cin, title);
                    deleteBook(title);
                    break;
                }
            case 5:
                
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
                break;
        }
    } 
    
    
}
//**End Buku**

//**Peminjaman**

void lihatPeminjaman(Node *headp)
{
    cout << "Daftar Peminjam:" << endl;
    Node *current = headp;
    int i = 1;
    while (current != nullptr)
    {
        time_t waktuPinjam = mktime(&current->tanggalPinjam);
        cout << i << ". ";
        cout << "Nama: " << current->namaPeminjam << endl;
        cout << "Judul: " << current->judulBuku << endl;
        cout << "Tanggal Peminjaman: " << ctime(&waktuPinjam) << endl;
        cout << "Status: " << current->status << "\n"
             << endl;
        current = current->next;
        i++;
    }
}



    void displayBookList() {
        cout << "Daftar Buku:\n";
        int number = 1;
        Book* current = head;
        while (current != nullptr) {
            cout << number << ". " << current->title << " oleh " << current->author << " (" << current->year << ") - Stok: " << current->stock << "\n";
            current = current->next;
            number++;
        }
        
    
    }

 void peminjamanBuku(Node *&headp)
{
    time_t now = time(0);
    Node *newNode = new Node;
    cout << "Masukan Nama Anda: ";
    cin >> newNode->namaPeminjam;

    displayBooks(); // Tampilkan daftar buku

    int nomorBuku;
    cout << "Masukkan nomor buku yang ingin dipinjam: ";
    cin >> nomorBuku;

    Book* currentBook = head; // Menggunakan head (head dari linked list Book)

    int count = 1;
    while (currentBook != nullptr && count < nomorBuku) {
        currentBook = currentBook->next;
        count++;
    }

    if (currentBook == nullptr) {
        cout << "Nomor buku tidak valid." << endl;
        return;
    }

    // Mengisi informasi peminjaman buku
    newNode->judulBuku = currentBook->title;
    cout << "Judul Buku: " << newNode->judulBuku << endl;

    struct tm *p = gmtime(&now);
    p->tm_hour = 0;
    p->tm_min = 0;
    p->tm_sec = 0;

    newNode->status = "Dipinjam";
    newNode->tanggalPinjam = *p;
    newNode->next = nullptr; // Setelah node baru ditambahkan, node selanjutnya harus nullptr karena akan menjadi node terakhir.
    newNode->prev = nullptr; // Karena kita menggunakan double linked list, atur pointer prev ke nullptr.

    if (headp == nullptr) // Jika list kosong, node baru adalah kepala.
    {
        headp = newNode;
    }
    else
    {
        Node *temp = headp;
        while (temp->next != nullptr) // Cari node terakhir.
        {
            temp = temp->next;
        }
        temp->next = newNode; // Tambahkan node baru setelah node terakhir.
        newNode->prev = temp; // Atur pointer prev dari node baru ke node sebelumnya.
    }

    cout << "Peminjaman Berhasil Ditambahkan" << endl;
}




void ubahPeminjaman(Node *headp)
{
    cout << "Daftar Peminjam:" << endl;
    Node *current = headp;
    int i = 1;
    while (current != nullptr)
    {
        cout << i << ". ";
        cout << "Nama: " << current->namaPeminjam << endl;
        cout << "Judul: " << current->judulBuku << endl;
        current = current->next;
        i++;
    }

    cout << "Masukkan nomor peminjaman yang ingin anda ubah: ";
    int nomorPeminjaman;
    cin >> nomorPeminjaman;

    current = headp;
    int count = 1;
    while (current != nullptr && count < nomorPeminjaman)
    {
        current = current->next;
        count++;
    }

    if (current == nullptr)
    {
        cout << "Nomor peminjaman tidak valid." << endl;
        return;
    }

    cout << "Nama Sebelumnya: " << current->namaPeminjam << endl;

    cout << "Masukkan Nama Baru: ";
    cin >> current->namaPeminjam;

    displayBooks(); // Tampilkan daftar buku
    int nomorBuku;
    cout << "Masukkan nomor buku yang baru: ";
    cin >> nomorBuku;

    Book* currentBook = head; // Menggunakan head (head dari linked list Book)
    count = 1;
    while (currentBook != nullptr && count < nomorBuku) {
        currentBook = currentBook->next;
        count++;
    }

    if (currentBook == nullptr) {
        cout << "Nomor buku tidak valid." << endl;
        return;
    }

    // Mengubah informasi buku yang dipinjam
    current->judulBuku = currentBook->title;
    cout << "Judul Buku Baru: " << current->judulBuku << endl;

    cout << "Peminjaman Berhasil Diubah";
}



void hapusPeminjaman(Node *&headp)
{
    cout << "Daftar Peminjam:" << endl;
    Node *current = headp;
    int i = 1;
    while (current != nullptr)
    {
        cout << i << ". ";
        cout << "Nama: " << current->namaPeminjam << endl;
        cout << "Judul: " << current->judulBuku << endl;
        current = current->next;
        i++;
    }

    cout << "Masukan nomor buku yang ingin anda hapus: ";
    int nomorBuku;
    cin >> nomorBuku;

    current = headp;
    int count = 1;
    while (current != nullptr && count < nomorBuku)
    {
        current = current->next;
        count++;
    }

    if (current == nullptr)
    {
        cout << "Nomor buku tidak valid." << endl;
        return;
    }

    if (current->prev != nullptr)
    {
        current->prev->next = current->next;
    }
    else
    {
        headp = current->next;
    }

    if (current->next != nullptr)
    {
        current->next->prev = current->prev;
    }

    delete current;
    cout << "Peminjaman berhasil dihapus" << endl;
}


void halamanPeminjaman()
{
    // Inisialisasi langsung untuk membuat data dummy
    

    while (true)
    {
        cout << "Menu:" << endl;
        cout << "1. Lihat Daftar Peminjam" << endl;
        cout << "2. Menambah Peminjaman Buku" << endl;
        cout << "3. Mengubah Peminjaman Buku" << endl;
        cout << "4. Hapus Peminjaman Buku" << endl;
        cout << "5. Keluar" << endl;

        cout << "Masukan Pilihan Anda:";
        int pilihPeminjaman;
        cin >> pilihPeminjaman;

        switch (pilihPeminjaman)
        {
        case 1:
            cout << "Anda memilih untuk melihat buku" << endl;
            lihatPeminjaman(headp);
            break;
        case 2:
            cout << "Anda memilih untuk menambah peminjaman buku" << endl;
            peminjamanBuku(headp);
            break;
        case 3:
            cout << "Anda memilih untuk mengubah peminjaman buku" << endl;
            ubahPeminjaman(headp);
            break;
        case 4:
            cout << "Anda memilih untuk menghapus peminjaman buku" << endl;
            hapusPeminjaman(headp);
            break;
        case 5:
            cout << "Anda telah keluar dari program" << endl;
            // Bersihkan memori linked list sebelum keluar dari program
            return;
        default:
            cout << "Pilihan tidak valid. Silakan pilih lagi." << endl;
        }
    }
}

//**Pengembalian**
void pengembalianBuku(Node *&headp)
{
    cout << "Daftar Buku yang Sedang Dipinjam:" << endl;
    Node *current = headp;
    int i = 1;
    while (current != nullptr)
    {
        cout << i << ". ";
        cout << "Nama: " << current->namaPeminjam << endl;
        cout << "Judul: " << current->judulBuku << endl;
        cout << "Tanggal Pinjam: " << asctime(&current->tanggalPinjam) << endl;
        if (current->status == "Dipinjam") {
            cout << "Status: " << current->status << endl;
        }
        cout << endl;
        current = current->next;
        i++;
    }

    cout << "Masukkan nomor buku yang ingin anda kembalikan: ";
    int nomorPeminjaman;
    cin >> nomorPeminjaman;

    current = headp;
    int count = 0;
    while (current != nullptr && count < nomorPeminjaman - 1)
    {
        current = current->next;
        count++;
    }

    if (current == nullptr || current->status != "Dipinjam")
    {
        cout << "Nomor peminjaman tidak valid atau buku tidak sedang dipinjam." << endl;
        return;
    }

    cout << "Apakah Anda yakin ingin mengembalikan buku ini? (y/n): ";
    char confirm;
    cin >> confirm;
    if (confirm != 'y')
    {
        cout << "Pengembalian dibatalkan." << endl;
        return;
    }

    time_t now = time(0);
    struct tm *p = gmtime(&now);
    p->tm_hour = 0;
    p->tm_min = 0;
    p->tm_sec = 0;

    double seconds = difftime(now, mktime(&current->tanggalPinjam));
    int days = seconds / (60 * 60 * 24);

    double denda = 0;
    if (days > 7) {
        current->status = "Terlambat Dikembalikan";
        denda = 500 * (days - 7);
        cout << "Anda terlambat mengembalikan buku selama " << days << " hari." << endl;
        cout << "Denda yang harus Anda bayar: Rp " << denda << endl;
    } else if (days <= 0) {
        current->status = "Dikembalikan";
        cout << "Buku berhasil dikembalikan." << endl;
        return;
    } else {
        current->status = "Dikembalikan";
    }

    cout << "Apakah Anda yakin ingin mengembalikan buku ini? (y/n): ";
    cin >> confirm;
    if (confirm != 'y')
    {
        cout << "Pengembalian dibatalkan." << endl;
        return;
    }

    // Hapus node dari linked list
    if (headp == current) {
        headp = current->next;
    } else {
        Node *temp = headp;
        while (temp->next != current)
        {
            temp = temp->next;
        }
        temp->next = current->next;
    }

    delete current;

    cout << "Buku berhasil dikembalikan." << endl;
    if (denda > 0) {
        cout << "Silakan membayar denda sebesar Rp " << denda << "." << endl;
    }
}
//**Pengembalian**

//**End Peminjaman**


void HalamanAkun(akun *head, const string& loggedInUser, bool &loggedIn) {
    int choice;
    
    while (loggedIn) {
        cout << "=== Menu ===" << endl;
        cout << "1. Profil" << endl;
        cout << "2. Buku" << endl;
        cout << "3. Peminjaman" << endl;
        cout << "4. Pengembalian" << endl;
        cout << "5. Logout" << endl;
        cout << "Pilihan Anda: ";
        cin >> choice;
        if (loggedIn=false){
            return ;
        }

        switch (choice) {
            case 1:
                cout << "Ini Halaman Profil" << endl;
                HalamanProfil(head, loggedInUser, loggedIn);
                break;
            case 2:
                cout << "Ini Halaman Buku" << endl;
                halamanBuku(loggedIn);
                loggedIn=true;
                break;
            case 3:
                cout << "Ini Halaman Peminjaman" << endl;
                halamanPeminjaman();
                loggedIn=true;
                break;
            case 4:
                cout << "Ini Halaman Pengembalian" << endl;
                loggedIn=true;
                pengembalianBuku(headp);
                break;
            case 5:
                cout << "Anda berhasil logout" << endl;
                return;
            default:
                cout << "Pilihan tidak valid. Silakan pilih lagi." << endl;
                break;
        }
    }
}


int main() {
    Node *dummy1 = new Node{"Dhexy", "Garis Langkah", {0, 0, 0, 1, 1, 122}, "Dipinjam", {}};
    Node *dummy2 = new Node{"Mamat", "Arah Langkah", {0, 0, 0, 1, 7, 122}, "Dipinjam", {}};

    // Menghubungkan data dummy ke dalam linked list
    dummy1->next = dummy2;
    dummy2->prev = dummy1;

    headp = dummy1;
    akun *head = NULL;
    bool loggedIn = false;

    // Menu utama
    while (!loggedIn) {
        int choiceLogin;
        cout << "=== Menu Login ===" << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Exit" << endl;
        cout << "Pilihan Anda: ";
        cin >> choiceLogin;

        switch (choiceLogin) {
            case 1:
                loginUser(head, loggedInUser);
                loggedIn = true;
                HalamanAkun(head, loggedInUser, loggedIn);

                break;
            case 2:
                registerUser(head);
                break;
            case 3:
                cout << "Terima kasih. Sampai jumpa lagi!" << endl;
                return 0;
            default:
                cout << "Pilihan tidak valid. Silakan pilih lagi." << endl;
                break;
        }
    }

    return 0;
}
