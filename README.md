# 📄 License

This project is open source and free to use.
---------------------------------------------------
# 📚 Learning Goals

This project demonstrates:

  - XOR encryption/decryption
  - Authentication systems
  - Dynamic memory allocation
  -  File I/O operations
  - String manipulation
  - Security concepts

# 🔐 Password Manager

A simple command-line password manager written in C with XOR encryption and master password authentication.

## ✨ Features

- 🔑 Master password setup on first run
- 🔐 XOR encryption for stored passwords
- ➕ Add password entries (website, username, password)
- 👁️ View saved passwords (decrypted)
- 🗑️ Delete password entries
- 💾 Save to encrypted file
- 📂 Load from encrypted file
- 🔄 Dynamic memory allocation (unlimited entries)

## 🛠️ Planned Features

- [] Edit existing entries
- [ ] Password generator
- [ ] Search by website
- [ ] Export to CSV
- [ ] Stronger encryption (AES)

## 📋 Requirements

- GCC compiler
- Linux/Unix or Windows

## 🚀 How to Compile

```bash
gcc -Wall -Wextra -o password_manager main.c
```
🏃 How to Run
```bash
./password_manager
```
# 📝 Usage
First Run
```text

No master password found. Create one:
Enter master password: ********
✅ Master password created!
```

# Login
```text

Enter master password: ********
✅ Access granted!
```

# Main Menu
```text

===== PASSWORD MANAGER =====
1. Add Password
2. View Passwords
3. Delete Password
4. Save to File
5. Load from File
6. Exit
============================
```
# 🔒 Security

Passwords are encrypted using XOR cipher before being saved to disk.
```text

Encryption: password ^ key = encrypted
Decryption: encrypted ^ key = password
```
# 📁 File Format

Passwords are saved in passwords.txt (encrypted):
```text

Website|Username|EncryptedPassword
```
