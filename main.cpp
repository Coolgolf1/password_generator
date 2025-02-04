#include <iostream>
#include <random>
#include <cctype>
#include <string>
#include <vector>
#include <variant>
#include <map>
#include <fstream>
#include <set>
#include <ctime>
#include <stdlib.h>

using namespace std;

vector<char> generate_ascii_characters(bool symbols, bool capital_letters, bool readable)
{
    vector<char> characters;
    for (int a = 0; a < 256; ++a)
        if (isprint(char(a)))
        {
            if (readable)
            {
                if (a == 'l' || a == '1' || a == '0' || a == 'O')
                    continue;
            }
            if (!capital_letters && isupper(char(a)))
                continue;

            else if (!symbols && !isalpha(char(a)))
                continue;

            characters.push_back(char(a));
        }
    return characters;
}

char choose_random_character(vector<char> &characters, mt19937 &rng)
{
    uniform_int_distribution<int> dist(0, characters.size() - 1);
    char character;
    character = characters[dist(rng)];
    return character;
}

string generate_password(vector<char> &characters, int length)
{
    random_device rd;
    mt19937 rng(rd());

    string password;
    for (int i = 0; i < length; ++i)
    {
        char character = choose_random_character(characters, rng);
        password += character;
    }
    return password;
}

bool validate_password(string &password, bool symbols, bool capital_letters, bool readable)
{
    bool has_symbol = false;
    bool has_capital = false;
    bool is_readable = true;

    for (const char &character : password)
    {
        if (symbols && !isalnum(character))
        {
            has_symbol = true;
        }

        else if (capital_letters && isupper(character))
        {
            has_capital = true;
        }

        if (readable && (character == 'l' || character == '1' || character == '0' || character == 'O'))
            is_readable = false;
    }

    return (!symbols || has_symbol) && (!capital_letters || has_capital) && (!readable || is_readable);
}

bool ask_input(string type)
{
    bool yes_chosen = false;
    char check;
    bool running_option = true;

    while (running_option)
    {
        cout << "Do you want " << type << "? [y/n]: ";
        cin >> check;
        check = tolower(check);
        if (check == 'y')
        {
            yes_chosen = true;
            running_option = false;
        }
        else if (check == 'n')
        {
            yes_chosen = false;
            running_option = false;
        }
    }

    return yes_chosen;
}

map<string, variant<bool, int>> take_user_inputs()
{
    map<string, variant<bool, int>> inputs;

    bool length_chosen = false;

    while (length_chosen != true)
    {
        int length;
        cout << "Type the password length: ";
        cin >> length;

        if (cin.fail() || length < 8 || length > 64)
        {
            cout << "Invalid input. Please enter an integer in the range [8, 64]." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            length_chosen = true;
            inputs["length"] = length;
        }
    }

    inputs["symbols"] = ask_input("symbols");
    inputs["capital_letters"] = ask_input("capital letters");
    inputs["readable"] = ask_input("easily readable letters");

    return inputs;
}

int read_file()
{
    ifstream file("passwords.txt");
    if (!file.is_open())
    {
        cout << "The passwords file does not exist." << endl;
        return 1;
    }

    string password;
    while (getline(file, password))
    {
        cout << password << endl;
    }
    file.close();
    return 0;
}

int store_password(string &password)
{
    ifstream file("passwords.txt");
    if (!file.is_open())
    {
        ofstream new_file("passwords.txt");
        new_file << password << endl;
        new_file.close();
        cout << "Password saved correctly." << endl;
        return 1;
    }

    string text;
    set<string> passwords;
    while (getline(file, text))
    {
        passwords.insert(text);
    }
    file.close();

    if (passwords.find(password) != passwords.end())
    {
        cout << "This password was already saved.";
        return 0;
    }

    ofstream file_out("passwords.txt", ios::app);
    file_out << password << endl;
    file_out.close();
    cout << "Password saved correctly." << endl;
    return 1;
}

int password_gen_main()
{
    bool check_password = true;
    string password = "";

    map<string, variant<bool, int>> inputs = take_user_inputs();

    int length = get<int>(inputs["length"]);
    bool symbols = get<bool>(inputs["symbols"]);
    bool capital_letters = get<bool>(inputs["capital_letters"]);
    bool readable = get<bool>(inputs["readable"]);

    vector<char> characters = generate_ascii_characters(symbols, capital_letters, readable);

    while (check_password)
    {
        password = generate_password(characters, length);

        check_password = validate_password(password, symbols, capital_letters, readable);
        // if (check_password)
        //     cout << "Generating new password to comply with all requirements." << endl;
    }

    cout << "Your password is: " << password << endl;

    bool save = ask_input("to save your password");
    if (save)
        store_password(password);

    return 0;
}

int main()
{
    bool running = true;
    while (running)
    {
        bool chosen = false;
        int option = 0;
        while (!chosen)
        {
            system("cls");
            cout << "===== Menu =====\n1. Generate New Password\n2. Read Password File\n3. Exit\nChoose an option: ";
            cin >> option;
            if (cin.fail() || option < 1 || option > 3)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else
                chosen = true;
        }
        switch (option)
        {
        case 1:
            password_gen_main();
            system("pause");
            break;
        case 2:
            read_file();
            system("pause");
            break;
        case 3:
            running = false;
            cout << "Thanks for using this password generator." << endl;
            cout << "Made by Coolgolf";
            break;
        }
    }
    return 0;
}
