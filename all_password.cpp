src/
#include "all_password.h"
#include <iostream>
#include <random>

using namespace std;

/**
 * @brief Adds a new account entry to the password collection.
 * @param p A constant reference to a date_Password object containing site and password data.
 */
void all_password::add_acounts(const date_Password& p) {
	vector_password.push_back(p);
}

/**
 * @brief Performs XOR encryption or decryption on a given string.
 * @details Since XOR is a symmetric operation, applying this function a second time
 * with the same key will revert the ciphertext back to plaintext.
 * @param text The string to be processed.
 * @param key The character used as the XOR cipher key (defaults to 'K').
 * @return string The resulting encrypted or decrypted string.
 */
string simpleDEncrypt(string text, char key = 'K') {
	string result = text;
	for (int i = 0; i < text.size(); i++) {
		result[i] = text[i] ^ key;
	}
	return result;
}

/**
 * @brief Searches for a password by site name and returns it in plaintext.
 * @param site The name of the website to look for.
 * @return string The decrypted password if found; otherwise, returns a single space " ".
 */
string all_password::search_password(string site) const {
	for (auto password : vector_password) {
		if (password.get_site() == site) {
			string pass = password.get_password();
			return simpleDEncrypt(pass); // Decrypts the stored password before returning
		}
	}
	return " ";
}

/**
 * @brief Removes a password entry from the vector based on the site name.
 * @details Uses an efficient "swap and pop" method ($O(n)$ complexity).
 * It replaces the target element with the last element in the vector
 * to avoid shifting all subsequent elements.
 * @param site The name of the website entry to be deleted.
 */
void all_password::delete_password(string site) {
	if (vector_password.empty()) return;

	for (size_t i = 0; i < vector_password.size(); ++i) {
		if (vector_password[i].get_site() == site) {
			// Overwrite the current element with the last one
			vector_password[i] = vector_password.back();
			// Remove the last element (which is now a duplicate)
			vector_password.pop_back();
			break;
		}
	}
}

/**
 * @brief Prints all stored entries to the standard output.
 * @note Important: This outputs the passwords exactly as they are stored (usually encrypted).
 */
void all_password::all() const {
	for (auto password : vector_password) {
		cout << password.get_password() << ' ' << password.get_site() << '\n';
	}
}

/**
 * @brief Verifies if a specific site already exists in the database.
 * @param site The name of the website to verify.
 * @return int Returns 1 (true) if the site exists, 0 (false) otherwise.
 */
int all_password::verif(string site) const {
	for (auto password : vector_password) {
		if (password.get_site() == site)
			return 1;
	}
	return 0;
}

/**
 * @brief Generates a cryptographically stronger 9-character random password.
 * @details Utilizes the Mersenne Twister (mt19937) engine and uniform distribution
 * for better randomness compared to the standard rand() function.
 * @return string A randomly generated string containing letters and special characters.
 */
string all_password::create_new_password() {
	string caract = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()";
	random_device rd;
	mt19937 generator(rd()); // Seeded with hardware entropy
	uniform_int_distribution<> distribut(0, (int)caract.size() - 1);

	string password;
	for (int i = 0; i < 9; i++) {
		password += caract[distribut(generator)];
	}

	return password;
}
