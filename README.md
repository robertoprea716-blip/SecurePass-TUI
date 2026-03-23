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

* **Presentation Layer (`interface.h/cpp`):** Exclusively manages user interaction, rendering visual components.
* **Business Logic Layer (`all_password.h/cpp`):** Coordinates CRUD operations in volatile memory (RAM).
* **Data Access Layer (`data_bases.h/cpp`):** Abstracts the interaction with the SQLite3 engine.
* **Domain Layer (`for_password.h/cpp`):** Defines the fundamental data structures.

<p align="center">
  <img src="https://github.com/user-attachments/assets/6b72be95-9d85-434d-809d-060e16fb64d5" width="600">
</p>

---

## 3. Security and Cryptography Model
Data security is the core of this application, implemented across two distinct levels:

### 3.1. Master Authentication (Zero-Knowledge Proof)
Access to the database is restricted by a centralized authentication mechanism. During the initial setup, the user defines a Master Password. This password is processed using the **SHA-256** algorithm.

<p align="center">
  <img src="https://github.com/user-attachments/assets/2bf3f8ee-bee9-4765-864f-338e355442c5" width="500">
</p>

### 3.2. Persistent Data Encryption (XOR Cipher)
To prevent database inspection, credentials pass through a symmetric **XOR encryption** filter before being sent to the SQL `INSERT` clause.

---

## 4. User Interface ([FTXUI](https://arthursonzogni.github.io/FTXUI/))
The interface was developed using a declarative model similar to the DOM used in web development.

### 4.1. Addition and Generation Module
The registration form utilizes `Input` components to capture user data and an internal generation engine for secure 9-character strings.

<p align="center">
  <img src="https://github.com/user-attachments/assets/03d4fd99-81b8-47bd-83c9-b16f3a017584" width="500">
</p>

### 4.2. Interactive Search Engine
Optimized for $O(1)$ response time. Displays decrypted passwords or error messages reactively.

<p align="center">
  <img src="https://github.com/user-attachments/assets/1e5b714a-219c-4919-a66f-8fb2b62d1637" width="500">
</p>

### 4.3. Secure Deletion Module
To prevent accidental data loss, the deletion operation ("Drop") requires explicit confirmation of the identifier (site).

<p align="center">
  <img src="https://github.com/user-attachments/assets/c3c232d1-3947-454a-97f1-22ad65834250" width="500">
</p>

---

## 5. Testing and Quality Assurance (QA)
System integrity is validated through a suite of unit tests built on the [Google Test (GTest)](https://github.com/google/googletest) framework.

* **Business Logic Testing:** Validation of insertions, retrievals, and deletions.
* **Generation Integrity:** Verification of entropy rigor and length limits.
* **In-Memory Database Testing:** Simulation of SQL transactions directly in RAM.

---

## 6. Technologies and Methodology

* **Language:** **C++17** (utilizing `std::vector` and lambda expressions).
* **Database Engine:** **SQLite3** (Serverless, transactional).
* **TUI Graphics:** **FTXUI**, created by Arthur Sonzogni.
* **AI Assistance:** Artificial Intelligence (LLM) was utilized as a pair-programming tool for code refactoring and technical structuring.
