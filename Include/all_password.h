#ifndef ALL_PASSWORD_H_
#define ALL_PASSWORD_H_

#include "for_password.h"
#include <vector>
#include <random>
#include <string>

using namespace std;

/** * @class all_password
 * @brief Container class for managing a collection of date_Password objects.
 * @details This class acts as an in-memory (RAM) manager, providing
 * functionalities for adding, deleting, searching, and generating passwords.
 */
class all_password {
private:
	vector <date_Password> vector_password;

public:
	void add_acounts(const date_Password& p);

	string search_password(string site) const;

	void delete_password(string site);

	void all() const;

	int verif(string site) const;

	string create_new_password();
};

#endif