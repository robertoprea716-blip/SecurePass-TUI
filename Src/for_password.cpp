#include "for_password.h"

/**
 * @brief Constructor for the date_Password class.
 * @details Initializes a new instance of the class with the provided password and site name.
 * The 'this' pointer is used to distinguish between function parameters and the class member variables.
 * * @param p The string representing the password (stored as either plaintext or ciphertext).
 * @param s The string representing the name of the website or service.
 */
date_Password::date_Password(string p, string s) {
	this->password = p;
	this->site = s;
}

/**
 * @brief Retrieves the password stored in the object.
 * @return string The value of the private member variable 'password'.
 */
string date_Password::get_password() {
	return password;
}

/**
 * @brief Retrieves the site name stored in the object.
 * @return string The value of the private member variable 'site'.
 */
string date_Password::get_site() {
	return site;
}