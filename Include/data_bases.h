#ifndef DATA_BASES_H_
#define DATA_BASES_H_

#include <sqlite3.h>
#include "all_password.h"
#include "for_password.h"

/**
 * @class bases
 * @brief Utility class for managing CRUD operations within a SQLite database.
 * @details This class provides functional methods to synchronize in-memory data
 * with the persistent SQL table stored on the disk.
 */
class bases {
public:

	void upload_DB(sqlite3* DB, all_password& v);

	void delete_acount_DB(sqlite3* DB, string site);

	void delete_acount_DB(sqlite3* DB);

	void delete_all(sqlite3* DB);
};

#endif