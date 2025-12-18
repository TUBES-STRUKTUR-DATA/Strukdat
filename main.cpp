#include "library.h"
#include "library.cpp"
#include <iostream>
#include <string>
#include <conio.h>
#include <cstdlib> // Untuk fungsi rand() dan srand()
#include <ctime>   // Untuk fungsi time()
using namespace std;

int main()
{
    srand(time(0));
    UserNode *users = nullptr;

    const int ADMIN_ID = 90000001;
    const string ADMIN_USER = "Admin123";
    const string ADMIN_PASS = "Admin123";

    bool loggedIn = false;
    int role = 0;

    while (true)
    {
        if (!loggedIn)
        {
            cout << "\n--- SELAMAT DATANG DI SKIN LIBRARY ---";
            cout << "\n1. Login\n2. Register\n3. Exit\nPilih: ";
            int c;
            cin >> c;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Input tidak valid.\n";
                continue;
            }

            if (c == 1)
            {
                string idStr, pass;
                int id;

                cout << "ID: ";
                cin >> idStr;

                bool valid = true;
                id = 0;

                for (char ch : idStr)
                {
                    if (!isdigit(ch))
                    {
                        valid = false;
                        break;
                    }
                    id = id * 10 + (ch - '0');
                }

                cout << "Password: ";
                pass = getPassword();

                if (!valid)
                {
                    cout << "Login gagal.\n";
                    continue;
                }

                if (id == ADMIN_ID && pass == ADMIN_PASS)
                {
                    loggedIn = true;
                    role = 1;
                }
                else
                {
                    UserNode *u = searchUser(users, id);
                    if (u && u->data.password == pass)
                    {
                        loggedIn = true;
                        role = 2;
                    }
                    else
                    {
                        cout << "Login gagal.\n";
                    }
                }
            }
            else if (c == 2)
            {
                User u;
                cout << "Username: ";
                cin >> u.username;

                do
                {
                    u.id = rand() % 900000 + 100000;
                } while (searchUser(users, u.id));

                cout << "ID Anda: " << u.id << endl;

                do
                {
                    cout << "Password (min 8): ";
                    u.password = getPassword();
                } while (u.password.length() < 8);

                users = insertUser(users, u);
                cout << "Registrasi sukses.\n";
            }

            else if (c == 3)
            {
                cout << "Terima kasih telah menggunakan Skin Library!\n";
                break;
            }
            else
            {
                cout << "Pilihan tidak valid.\n";
                continue;
            }
        }

        else if (role == 1)
        {
            while (true)
            {
                cout << "\n--- ADMIN SKIN LIBRARY ---\n";
                cout << "1. Tambah Skin\n";
                cout << "2. Hapus Skin\n";
                cout << "3. Tampilkan Skin\n";
                cout << "4. Cari Skin\n";
                cout << "5. Skin Serupa\n";
                cout << "6. Kembali\n";
                cout << "Pilih: ";

                int c;
                cin >> c;

                if (c == 1)
                    addSkin();
                else if (c == 2)
                    deleteSkin();
                else if (c == 3)
                    showSkins();
                else if (c == 4)
                    searchSkin();
                else if (c == 5)
                    similarSkin();
                else if (c == 6)
                {
                    if (confirmBackAdmin())
                    {
                        loggedIn = false;
                        role = 0;
                        break;
                    }
                }
            }
        }

        else if (role == 2)
        {
            int userId;

            while (true)
            {
                cout << "\n--- MENU USER ---\n";
                cout << "1. Lihat Semua Skin\n";
                cout << "2. Simpan Skin ke Koleksi\n";
                cout << "3. Cari Skin (Hero)\n";
                cout << "4. Cari Skin (Rarity)\n";
                cout << "5. Lihat Koleksi Skin\n";
                cout << "6. Gunakan Skin\n";
                cout << "7. Logout\n";
                cout << "Pilih: ";

                int c;
                cin >> c;

                if (c == 1)
                    showSkins();
                else if (c == 2)
                    addSkinToUser(userId);
                else if (c == 3)
                    searchSkinByHero();
                else if (c == 4)
                    searchSkinByRarity();
                else if (c == 5)
                    showUserSkins(userId);
                else if (c == 6)
                    useUserSkin(userId);
                else if (c == 7)
                {
                    loggedIn = false;
                    role = 0;
                    break;
                }
            }
        }
    }
    return 0;
}