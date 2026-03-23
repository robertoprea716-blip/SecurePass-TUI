# TECHNICAL DOCUMENTATION: SECUREPASS TUI

**Author:** Oprea Robert-Andrei  
**Language:** C++17  
**Year:** 2026

---

## 1. Project Abstract 
**SecurePass TUI** is an advanced credential management system running exclusively in the terminal (Terminal User Interface). The project was designed to provide a highly secure storage environment, eliminating plaintext vulnerabilities through the use of cryptographic hash functions and symmetric encryption. The application combines the robust data persistence offered by [SQLite3](https://www.sqlite.org/) with a modern and reactive UI design, built upon the [FTXUI](https://arthursonzogni.github.io/FTXUI/) library.

---

## 2. Layered System Architecture 
To guarantee code scalability and maintainability, the system was designed based on a **Layered Architecture** pattern. This strict decoupling ensures the separation of business logic from the user interface and data manipulation.

* **Presentation Layer (`interface.h/cpp`):** Exclusively manages user interaction, rendering visual components, and capturing events (keyboard/mouse).
* **Business Logic Layer (`all_password.h/cpp`):** Coordinates CRUD operations in volatile memory (RAM) and implements the high-entropy password generation algorithm.
* **Data Access Layer (`data_bases.h/cpp`):** Abstracts the interaction with the SQLite3 engine, managing transactions, SQL queries (Prepared Statements), and data mapping.
* **Domain Layer (`for_password.h/cpp`):** Defines the fundamental and immutable data structures (`date_Password`).

<p align="center">
  <img src="https://github.com/user-attachments/assets/6b72be95-9d85-434d-809d-060e16fb64d5" width="600">
</p>

---

## 3. Security and Cryptography Model 
Data security is the core of this application, implemented across two distinct levels:

### 3.1. Master Authentication (Zero-Knowledge Proof) 
Access to the database is restricted by a centralized authentication mechanism. During the initial setup, the user defines a Master Password. This password is processed using the **SHA-256** algorithm (via *Picosha2*). Only the resulting hash fingerprint is stored in the database, meaning the system operates with zero knowledge of the user's actual plaintext password.

<p align="center">
  <img src="https://github.com/user-attachments/assets/2bf3f8ee-bee9-4765-864f-338e355442c5" width="500">
</p>

### 3.2. Persistent Data Encryption (XOR Cipher)
To prevent database inspection (attacks on the `bases_password.db` file stored on disk), credentials pass through a symmetric **XOR encryption** filter before being sent to the SQL `INSERT` clause. Upon retrieval from the database (`SELECT`), the process is reversed to load the data in plaintext into secure RAM.

---

## 4. User Interface (Functional Terminal UI)
The interface was developed using [FTXUI](https://arthursonzogni.github.io/FTXUI/) (Functional Terminal User Interface), a modern C++ library that employs a declarative model similar to the DOM used in web development.

### 4.1. Addition and Generation Module
The registration form utilizes `Input` components to capture user data. The integration of the "Generate Password" button employs an internal generation engine to instantly produce secure 9-character strings, updating the interface state reactively.

<p align="center">
  <img src="https://github.com/user-attachments/assets/c05f0063-4ec9-41a9-8c6b-01ff0f09461c" width="500">
</p>

### 4.2. Interactive Search Engine 
The search functionality has been optimized to provide an $O(1)$ response time. As the user types characters into the search field, the `Renderer` component re-evaluates the logical state and displays the decrypted password, or a prominently color-coded error message.

<p align="center">
  <img src="https://github.com/user-attachments/assets/1e5b714a-219c-4919-a66f-8fb2b62d1637" width="500">
</p>

### 4.3. Secure Deletion Module
To prevent accidental data loss, the deletion operation ("Drop") is isolated within a separate tab and requires explicit confirmation of the identifier (site), triggering a cascading deletion from both RAM and disk.

<p align="center">
  <img src="https://github.com/user-attachments/assets/c3c232d1-3947-454a-97f1-22ad65834250" width="500">
</p>

---

## 5. Testing and Quality Assurance (QA) 
System integrity is validated through a suite of unit tests built on the Google Test(GTest) framework. The suite covers:

* **Business Logic Testing:** Validation of insertions, retrievals, and deletion operations (`AddAndVerify`, `DeleteAccount`).
* **Generation Integrity:** Verification of entropy rigor and length limits (`PasswordGenerationLength`).
* **In-Memory Database Testing:** Simulation of SQL transactions directly in RAM (`:memory:`) to isolate tests from disk I/O.

---

## 6. Technologies, Dependencies, and Methodology

* **Language:** **C++17** (Modern standard, utilizing `std::vector`, lambda expressions, and managed pointers).
* **Database Engine:** **[SQLite3](https://www.sqlite.org/)** (Serverless, transactional).
* **TUI Graphics:** **[FTXUI](https://arthursonzogni.github.io/FTXUI/)**, created by Arthur Sonzogni.
* **Cryptography:** Header-only **Picosha2** library for SHA-256.
* **AI Assistance:** During the development process, Artificial Intelligence (LLM) was utilized as a pair-programming tool for code refactoring (DRY principles), generating templates for unit tests (GTest), and the technical structuring of this documentation.
