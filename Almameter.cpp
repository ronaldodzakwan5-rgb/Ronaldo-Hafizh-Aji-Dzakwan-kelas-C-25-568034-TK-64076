#include <iostream>
#include <string> 
#include <list> // untuk list
#include <limits> // untuk numeric_limits
using namespace std;

// Almameter 
class Almameter {
public:
    Almameter() : size("M"), stock(10) {} // default stock 10
    ~Almameter() {}
    void addStock(int q) { stock += q; } // menambah stock sebanyak q
    void reduceStock(int q) { //kurangi stock jika cukup, kalau tidak tampilkan pesan
        if(q <= stock) stock -= q;
        else cout << "Stock tidak cukup!\n";
    }
    void Print() const { cout << "Size: " << size << ", Stock: " << stock << endl; } // tampilkan ukuran dan jumlah stock
    int getStock() const { return stock; } // mengembalikan jumlah stock almet
private:
    string size;
    int stock;
};

// TakeRecord 
class TakeRecord {
public:
    TakeRecord() : NIM(""), size("") {} // inisialisasi NIM dan size kosong
    ~TakeRecord() {}
    void SetRecord(const string& nim, const string& s) { NIM = nim; size = s; } // menyimpan NIM student dan ukuran Almameter yang diambil
    void PrintRecord() { cout << "NIM: " << NIM << ", Size: " << size << endl; }
private:
    string NIM;
    string size;
};

//  Student 
class Student {
public:
    Student() : hasTaken(false), name(""), NIM("") {} // menandai apakah siswa sudah mengambil Almameter
    ~Student() {}
    string getNIM() const { return NIM; } // mengembalikan NIM student
    void SetData(const string& n, const string& nim) { name = n; NIM = nim; } // menyimpan nama dan NIM
    void Print() const { cout << "Name: " << name << ", NIM: " << NIM << endl; }
private:
    bool hasTaken;
    string name;
    string NIM;
};

// AlmameterRegister 
class AlmameterRegister {
public:
    AlmameterRegister() {}
    ~AlmameterRegister() {}

    void AddStudent() {
        string name, nim;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // bersihkan buffer supaya input sebelumnya tidak mengganggu
        cout << "Masukkan nama student: ";
        getline(cin, name); // menggunakan getline agar bisa ada spasi
        cout << "Masukkan NIM: ";
        getline(cin, nim);
        Student s; s.SetData(name, nim);
        students.push_back(s);
        cout << "Student berhasil ditambahkan!\n";
        Pause(); // panggil Pause untuk menunggu user tekan Enter
    }

    bool CheckStudentNIM(const string& nim) {
        for(auto &s : students) if(s.getNIM() == nim) return true; // Loop setiap student, cek NIM
        return false;
    }

    void DeleteStudent() {
        string nim;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Menghapus student dari list berdasarkan NIM
        cout << "Masukkan NIM yang akan dihapus: "; 
        getline(cin, nim);
        students.remove_if([&](Student &s){ return s.getNIM() == nim; }); 
        cout << "Student berhasil dihapus!\n";
        Pause();
    }

    void EditStudent() { // Cari student berdasarkan NIM. Jika ditemukan, minta input nama dan NIM baru, lalu perbarui datanya 
        string nim;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Masukkan NIM yang akan diedit: ";
        getline(cin, nim);
        for(auto &s : students) {
            if(s.getNIM() == nim) {
                string newName, newNIM;
                cout << "Masukkan nama baru: "; getline(cin, newName);
                cout << "Masukkan NIM baru: "; getline(cin, newNIM);
                s.SetData(newName, newNIM);
                cout << "Data berhasil diperbarui!\n";
                Pause();
                return;
            }
        }
        cout << "Student tidak ditemukan!\n"; // Kalau tidak ketemu tampilkan "Student tidak ditemukan"
        Pause();
    }

    void TakeAlmameter() {
        string nim; int qty;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Masukkan NIM: "; getline(cin, nim);
        if(!CheckStudentNIM(nim)) {  // cek apakah NIM ada di daftar student
            cout << "Student tidak ditemukan!\n"; 
            Pause();
            return; 
        }
        cout << "Masukkan jumlah almameter yang diambil: "; cin >> qty; 
        if(!almameterList.empty()) {
            Almameter &a = almameterList.front();
            if(a.getStock() >= qty) { 
                a.reduceStock(qty); // Kurangi stock jika cukup
                cout << "Berhasil mengambil " << qty << " almameter\n"; 
            } else cout << "Stock tidak cukup!\n";
        } else cout << "Belum ada stock almameter!\n";
        Pause();
    }

    void ViewStock() {
        cout << "Stock Almameter\n"; // menampilkan semua stock Almameter
        if(almameterList.empty()) {
            cout << "Belum ada almameter tersedia.\n";
        } else {
            for(auto &a : almameterList) a.Print();
        }
        Pause();
    }

    void AddStock() {
        int qty;
        cout << "Masukkan jumlah stock yang akan ditambahkan: "; // input jumlah stock baru, tambahkan ke stock pertama di list
        cin >> qty;
        if(!almameterList.empty()) {
            almameterList.front().addStock(qty);
            cout << "Stock berhasil ditambahkan!\n";
        }
        Pause();
    }

private:
    void Pause() {
        cout << "Tekan Enter untuk kembali ke menu..."; // Menunggu user menekan Enter supaya output tidak hilang langsung
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

public:
    list<Almameter> almameterList;
    list<TakeRecord> takerecords;
    list<Student> students;
};

// Controller 
class Controller { // tampilkan pilihan menu. Terima input user, panggil fungsi sesuai pilihan
public:
    Controller() { 
        // Tambahkan stock awal almameter
        Almameter a; 
        inventory.almameterList.push_back(a); 
    }
    ~Controller() {}
    void ShowMenu() {
        cout << "\n=== Menu Almameter ===\n";
        cout << "1. Add Student\n2. Delete Student\n3. Edit Student\n4. View Stock\n5. Take Almameter\n6. Add Stock\n7. Exit\n";
    }
    void HandleInput() {
        int choice; 
        cout << "Pilihan: "; cin >> choice;
        switch(choice) {
            case 1: inventory.AddStudent(); break;
            case 2: inventory.DeleteStudent(); break;
            case 3: inventory.EditStudent(); break;
            case 4: inventory.ViewStock(); break;
            case 5: inventory.TakeAlmameter(); break;
            case 6: inventory.AddStock(); break;
            case 7: exit(0);
            default: cout << "Pilihan salah!\n"; break;
        }
    }
    void Run() { while(true) { ShowMenu(); HandleInput(); } } // oop terus menerus sampai user keluar (exit(0))
private:
    AlmameterRegister inventory;
};

// main 
int main() {
    Controller app;
    app.Run();
    return 0;
}
