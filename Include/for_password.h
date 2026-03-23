#ifndef FOR_PASSWORD_H_
#define FOR_PASSWORD_H_

#include <string>

using namespace std;

/**
 * @class date_Password
 * @brief A data model class representing a single account's credentials.
 * @details This class serves as a blueprint for storing a site name and its
 * corresponding password. It follows the encapsulation principle by keeping
 * data members private.
 */
class date_Password {
private:
	string password;

	string site;

public:

	date_Password(string password, string site);

	string get_password();

	string get_site();
};

#endif