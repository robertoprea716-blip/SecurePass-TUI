#include "data_bases.h"

/**
 * @brief Loads all data from the SQLite database into the application's memory.
 * @details This function executes a SQL SELECT query to fetch sites and passwords.
 * Each retrieved row is converted into a 'date_Password' object and added to the local vector.
 * * @param DB Pointer to the active SQLite database connection.
 * @param new_acounts Reference to the 'all_password' object where data will be stored in RAM.
 */
void bases::upload_DB(sqlite3* DB, all_password& new_acounts) {
	string sql = "SELECT SITE, PASSWORD FROM ACOUNTS";
	sqlite3_stmt* stmt;

	int result = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);

	if (result == SQLITE_OK) {
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			string site_db = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
			string password_db = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));

			date_Password new_acount(password_db, site_db);
			new_acounts.add_acounts(new_acount);
		}
	}
	sqlite3_finalize(stmt);
}

/**
 * @brief Deletes a specific account from the database based on the site name.
 * @details Note: This uses string concatenation for the query. While functional,
 * it is susceptible to SQL Injection if the 'site' input is not sanitized.
 * * @param DB Pointer to the database connection.
 * @param site The name of the website entry to be removed from the ACCOUNTS table.
 */
void bases::delete_acount_DB(sqlite3* DB, string site) {
	string del = "DELETE FROM ACOUNTS WHERE SITE = '" + site + "';";
	sqlite3_exec(DB, del.c_str(), NULL, NULL, NULL);
}

/**
 * @brief Wipes all records from the ACCOUNTS table.
 * @details Effectively empties the database while keeping the table structure intact.
 * Use with caution as this operation is irreversible.
 * * @param DB Pointer to the database connection.
 */
void bases::delete_all(sqlite3* DB) {
	string delete_all = "DELETE FROM ACOUNTS;";
	sqlite3_exec(DB, delete_all.c_str(), NULL, NULL, NULL);
}