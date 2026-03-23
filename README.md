# TECHNICAL DOCUMENTATION: SECUREPASS TUI

**Author:** Oprea Robert-Andrei  
**Language:** C++17  
**Year:** 2026

---

## 1. Project Abstract
**SecurePass TUI** is an advanced credential management system running exclusively in the terminal. The project was designed to provide a highly secure storage environment, eliminating plaintext vulnerabilities through the use of cryptographic hash functions and symmetric encryption.

---

## 2. Layered System Architecture
To guarantee code scalability and maintainability, the system was designed based on a **Layered Architecture** pattern.

* **Presentation Layer:** Manages user interaction using [FTXUI](https://arthursonzogni.github.io/FTXUI/).
* **Business Logic Layer:** Coordinates CRUD operations in RAM.
* **Data Access Layer:** Interaction with [SQLite3](https://www.sqlite.org/).

<p align="center">
  <img src="https://github.com/user-attachments/assets/6b72be95-9d85-434d-809d-060e16fb64d5" width="600">
</p>

---

## 3. Security and Cryptography Model

### 3.1. Master Authentication (Zero-Knowledge Proof)
Access is restricted by a centralized authentication mechanism using **SHA-256**. Only the resulting hash fingerprint is stored.

<p align="center">
  <img src="https://github.com/user-attachments/assets/2bf3f8ee-bee9-4765-864f-338e355442c5" width="500">
</p>

---

## 4. User Interface Modules

### 4.1. Addition and Generation Module
Uses an internal generation engine to instantly produce secure 9-character strings.

<p align="center">
  <img src="https://github.com/user-attachments/assets/03d4fd99-81b8-47bd-83c9-b16f3a017584" width="500">
</p>

### 4.2. Interactive Search Engine
Optimized for $O(1)$ response time. Displays decrypted passwords or error messages reactively.

### 4.3. Secure Deletion Module
Isolated operation with explicit confirmation to prevent accidental data loss.

<p align="center">
  <img src="https://github.com/user-attachments/assets/9d85-exemplu-stergere" width="500">
</p>

---

## 5. Testing and Quality Assurance (QA)
System integrity is validated through [Google Test (GTest)](https://github.com/google/googletest).

* **Business Logic Testing**
* **Generation Integrity**
* **In-Memory Database Testing**
