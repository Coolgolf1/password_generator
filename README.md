# Safe Password Generator

A secure and customizable password generator written in C++. This program allows you to create strong passwords with adjustable lengths, customizable character options and a password history.

## Features
- Generate passwords from **8 to 64 characters** in length.
- Choose between different character sets:
  - Easily readable characters (avoiding ambiguous symbols like `0` and `O` and `l` `1`).
  - Include or exclude **symbols** (`!@#$%^&*()` etc.).
  - Include or exclude **uppercase letters**.
- Ensures high security by generating **random** and **unpredictable** passwords.
- Lightweight and fast execution.

## Installation
Ensure you have a C++ compiler installed (e.g., g++ for Linux/macOS or MinGW for Windows). Clone or download the repository and compile the program:

```sh
 g++ -o password_generator password_generator.cpp
```

## Usage
Run the program and specify your password preferences:

```sh
 ./password_generator
```

You will be prompted to choose the length, character options, and whether to include symbols and uppercase letters.

## Security Note
This generator uses C++'s **random device** to ensure the highest level of randomness. However, for highly sensitive environments, consider using a password manager or cryptographic libraries.

## License
This project is open-source under the **MIT License**. Feel free to contribute or modify it for your needs!

## Contributing
Pull requests and suggestions are welcome. If you find a bug or have an improvement idea, open an issue in the repository.

---
Enjoy secure and customizable passwords! 🔒
