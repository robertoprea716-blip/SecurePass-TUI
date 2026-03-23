#include <gtest/gtest.h>
#include "all_password.h"
using namespace testing;

// 1. Testăm adăugarea și metoda verif
TEST(PasswordManager, TestVerificareSite) {
    all_password manager;
    date_Password cont("parola123", "google.com");

    manager.add_acounts(cont);

    EXPECT_EQ(manager.verif("google.com"), 1);
    EXPECT_EQ(manager.verif("yahoo.ro"), 0);
}

// 2. Testăm generarea parolei (lungimea de 9 caractere)
TEST(PasswordManager, TestLungimeGenerare) {
    all_password manager; // ADAUGĂ ACEASTĂ LINIE AICI
    string p = manager.create_new_password();
    EXPECT_EQ(p.length(), 9);
}

// 3. Testăm logica de XOR (Criptare/Decriptare)
TEST(PasswordManager, TestXOR) {
    all_password manager;
    string parola_simpla = "abc";
    date_Password cont(parola_simpla, "site_test");
    manager.add_acounts(cont);

    // search_password ar trebui să aplice simpleDEncrypt (XOR cu 'K')
    string rezultat = manager.search_password("site_test");

    // Calculăm manual ce ar trebui să fie "abc" ^ 'K'
    string asteptat = "abc";
    for (char& c : asteptat) c ^= 'K';

    EXPECT_EQ(rezultat, asteptat);
}