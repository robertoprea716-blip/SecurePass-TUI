#include "interface.h"

using namespace std;
using namespace ftxui;

/**
 * @brief Simple XOR-based encryption/decryption.
 * @param text The string to be processed.
 * @param key The XOR key (default 'K').
 * @return string The processed result.
 */
string simpleEncrypt(string text, char key = 'K') {
    string result = text;
    for (size_t i = 0; i < text.size(); i++) result[i] = text[i] ^ key;
    return result;
}

/**
 * @brief Removes leading and trailing whitespace from a string.
 * @param s The input string.
 * @return string The trimmed string.
 */
string cleanInput(string s) {
    if (s.empty()) return s;
    s.erase(0, s.find_first_not_of(" \n\r\t"));
    size_t last = s.find_last_not_of(" \n\r\t");
    if (string::npos != last) s.erase(last + 1);
    return s;
}

/**
 * @brief Entry point for the Password Manager TUI application.
 * @details Handles SQLite initialization, SHA-256 master password verification,
 * and the FTXUI-based terminal interface layout.
 */
int ui() {
    sqlite3* DB;
    if (sqlite3_open("bases_password.db", &DB) != SQLITE_OK) return 1;

    all_password manager;
    bases db_handler;

    sqlite3_exec(DB, "CREATE TABLE IF NOT EXISTS ACOUNTS(SITE TEXT PRIMARY KEY, PASSWORD TEXT);", NULL, NULL, NULL);
    sqlite3_exec(DB, "CREATE TABLE IF NOT EXISTS CONFIG(KEY TEXT PRIMARY KEY, VALUE TEXT);", NULL, NULL, NULL);

    string master_hash = "";
    sqlite3_stmt* stmt_check;
    if (sqlite3_prepare_v2(DB, "SELECT VALUE FROM CONFIG WHERE KEY = 'MASTER_PASSWORD';", -1, &stmt_check, NULL) == SQLITE_OK) {
        if (sqlite3_step(stmt_check) == SQLITE_ROW) {
            master_hash = (const char*)sqlite3_column_text(stmt_check, 0);
        }
    }
    sqlite3_finalize(stmt_check);

    bool este_logat = false;
    string pass_acces_input = "";
    int optiune_selectata = 0;
    string in_site = "", in_pass = "", in_cautare = "", in_stergere = "";

    auto screen = ScreenInteractive::Fullscreen();

    InputOption opt_pass_master;
    opt_pass_master.password = true;
    opt_pass_master.on_enter = [&] {
        string pc = cleanInput(pass_acces_input);
        string input_hash = picosha2::hash256_hex_string(pc);
        if (master_hash == "" || input_hash == master_hash) {
            if (master_hash == "") sqlite3_exec(DB, ("INSERT INTO CONFIG VALUES ('MASTER_PASSWORD', '" + input_hash + "');").c_str(), NULL, NULL, NULL);
            este_logat = true;
            db_handler.upload_DB(DB, manager); 
        }
        else {
            pass_acces_input = ""; 
        }
        };

    Component input_l = Input(&pass_acces_input, "", opt_pass_master);
    Component input_s = Input(&in_site, "Enter site...");
    Component input_p = Input(&in_pass, "Enter password...");
    Component input_search = Input(&in_cautare, "Search by site...");
    Component input_del = Input(&in_stergere, "Site to delete...");

    auto logica_adaugare = [&] {
        if (!in_site.empty() && !in_pass.empty()) {
            string encrypted = simpleEncrypt(in_pass);
            sqlite3_stmt* stmt;
            sqlite3_prepare_v2(DB, "INSERT OR REPLACE INTO ACOUNTS (SITE, PASSWORD) VALUES (?, ?);", -1, &stmt, NULL);
            sqlite3_bind_text(stmt, 1, in_site.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 2, encrypted.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_step(stmt);
            sqlite3_finalize(stmt);
            db_handler.upload_DB(DB, manager); 
            in_site = ""; in_pass = "";
            input_s->TakeFocus();
        }
        };

    auto logica_stergere = [&] {
        if (!in_stergere.empty()) {
            db_handler.delete_acount_DB(DB, in_stergere);
            manager.delete_password(in_stergere);
            in_stergere = "";
            input_del->TakeFocus();
        }
        };

    auto stil_buton_verde = ButtonOption::Animated();
    stil_buton_verde.transform = [](const EntryState& state) {
        auto e = text(state.label) | center | flex;
        if (state.focused) e = e | bgcolor(Color::GreenLight) | color(Color::White) | bold;
        else e = e | bgcolor(Color::RGB(0, 100, 0)) | color(Color::White);
        return e | size(HEIGHT, EQUAL, 3) | size(WIDTH, GREATER_THAN, 25);
        };

    auto stil_buton_rosu = ButtonOption::Animated();
    stil_buton_rosu.transform = [](const EntryState& state) {
        auto e = text(state.label) | center | flex;
        if (state.focused) e = e | bgcolor(Color::Red) | color(Color::White) | bold;
        else e = e | bgcolor(Color::RGB(150, 0, 0)) | color(Color::White);
        return e | size(HEIGHT, EQUAL, 3) | size(WIDTH, GREATER_THAN, 25);
        };

    Component btn_save = Button(" Save Account ", logica_adaugare, stil_buton_verde);
    Component btn_gen = Button(" Generate Password ", [&] {
        in_pass = manager.create_new_password();
        input_p->TakeFocus();
        }, stil_buton_verde);
    Component btn_del = Button(" Confirm Deletion ", logica_stergere, stil_buton_rosu);

    vector<string> entries = { " ADDING ", " SEARCH ", " DELETE ", " EXIT " };
    MenuOption menu_style;
    menu_style.entries_option.transform = [](const EntryState& state) {
        Element e = text(state.label);
        if (state.focused) e = e | color(Color::GreenLight) | bold;
        else e = e | color(Color::White) | bold;
        return e;
        };

    Component meniu = Menu(&entries, &optiune_selectata, menu_style);

    auto main_renderer = Renderer(Container::Vertical({
        input_l,
        Container::Horizontal({
            meniu,
            Container::Tab({
                Container::Vertical({input_s, input_p, btn_gen, btn_save}),
                Container::Vertical({input_search}),
                Container::Vertical({input_del, btn_del}),
                Container::Vertical({})
            }, &optiune_selectata)
        })
        }), [&] {
            if (!este_logat) {
                auto login_box = vbox({
                    text(" ENTER MASTER PASSWORD ") | bold | hcenter | color(Color::Green),
                    separatorLight(),
                    hbox({ filler(), input_l->Render() | size(WIDTH, EQUAL, 25) | borderRounded | color(Color::White) | bold, filler() }),
                    }) | borderRounded | color(Color::White) | size(WIDTH, EQUAL, 45) | bgcolor(Color::RGB(0, 0, 0));

                return vbox({ filler(), hbox({ filler(), login_box, filler() }), filler() }) | bgcolor(Color::RGB(0, 0, 0)) | flex;
            }

            Element content;
            if (optiune_selectata == 0) { 
                content = vbox({
                    text(" Add Account ") | color(Color::Green) | bold,
                    separatorLight(),
                    hbox({ text(" Site:     ") | size(WIDTH, EQUAL, 12), input_s->Render() | flex }) | borderRounded | color(Color::White),
                    hbox({ text(" Password: ") | size(WIDTH, EQUAL, 12), input_p->Render() | flex }) | borderRounded | color(Color::White),
                    filler(),
                    hbox({ filler(), btn_gen->Render(), text("    "), btn_save->Render(), filler() }),
                    filler()
                    });
            }
            else if (optiune_selectata == 1) { 
                string site_cautat = cleanInput(in_cautare);
                string rez = manager.search_password(site_cautat);
                bool gasit = !(site_cautat.empty() || rez == "" || rez == " " || rez == "Password not found!");

                content = vbox({
                    text(" Password Search ") | color(Color::Green) | bold,
                    separatorLight(),
                    hbox({ text(" Site: "), input_search->Render() | flex }) | borderRounded | color(Color::White),
                    separatorLight(),
                    vbox({
                        text(" Found Password: ") | color(Color::GrayLight) | center,
                        text(gasit ? rez : "Site not found") | bold | color(gasit ? Color::GreenLight : Color::Red) | center | borderRounded | size(WIDTH, EQUAL, 40) | hcenter
                    }) | center | flex
                    });
            }
            else if (optiune_selectata == 2) { 
                content = vbox({
                    text(" Delete Account ") | color(Color::Green) | bold,
                    separatorLight(),
                    hbox(text(" Site: "), input_del->Render() | flex) | borderRounded | color(Color::White),
                    filler(),
                    hbox({ filler(), btn_del->Render(), filler() }),
                    filler()
                    });
            }

            auto main_layout = hbox({
                meniu->Render() | size(WIDTH, EQUAL, 18) | borderRounded | color(Color::White),
                content | flex | borderRounded | color(Color::White)
                }) | borderRounded | color(Color::White) | flex;

            return vbox({ main_layout }) | bgcolor(Color::RGB(0, 0, 0)) | flex;
        });

    auto final_component = CatchEvent(main_renderer, [&](Event event) {
        if (optiune_selectata == 3 && este_logat) {
            screen.ExitLoopClosure()();
            return true;
        }
        return false;
        });

    screen.Loop(final_component);

    sqlite3_close(DB);
    return 0;
}