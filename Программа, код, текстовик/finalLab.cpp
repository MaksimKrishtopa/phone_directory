#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

bool isValidName(const string& name) {
    if (name.empty() || islower(name[0]) || !all_of(name.begin(), name.end(), [](char c) { return isalpha(c) || isspace(c); })) {
        cout << "Некорректное ФИО! Введите ФИО с заглавной буквы и без цифр." << endl;
        return false;
    }
    return true;
}

bool isValidPhoneNumber(const string& phoneNumber) {
    if (phoneNumber.length() != 11 || !all_of(phoneNumber.begin(), phoneNumber.end(), [](char c) { return isdigit(c); })) {
        cout << "Некорректная длина номера телефона или содержит недопустимые символы!" << endl;
        return false;
    }
    return true;
}

void addContact(const string& filename) {
    ofstream file(filename, ios::app);

    if (!file) {
        cout << "Ошибка при открытии файла!" << endl;
        return;
    }

    string fullName;
    cout << "Введите ФИО: ";
    cin.ignore();
    getline(cin, fullName);

    if (!isValidName(fullName)) {
        return;
    }

    string phoneNumber;
    cout << "Введите номер телефона (11 символов): ";
    getline(cin, phoneNumber);

    if (!isValidPhoneNumber(phoneNumber)) {
        return;
    }

    file << fullName << " " << phoneNumber << endl;

    cout << "Контакт успешно добавлен!" << endl;

    file.close();
}

void readContacts(const string& filename) {
    ifstream file(filename);

    if (!file) {
        cout << "Ошибка при открытии файла!" << endl;
        return;
    }

    string line;
    bool contactsExist = false;
    while (getline(file, line)) {
        cout << line << endl;
        contactsExist = true;
    }

    file.close();

    if (!contactsExist) {
        cout << "Здесь пока пусто, добавьте контакты." << endl;
    }
}

void editContact(const string& filename) {
    string search;
    cout << "Введите номер телефона контакта, который нужно отредактировать: ";
    cin.ignore();
    getline(cin, search);

    string fullName;
    cout << "Введите новое ФИО: ";
    getline(cin, fullName);

    if (!isValidName(fullName)) {
        return;
    }

    string phoneNumber;
    cout << "Введите новый номер телефона (11 символов): ";
    getline(cin, phoneNumber);

    if (!isValidPhoneNumber(phoneNumber)) {
        return;
    }

    string confirmation;
    cout << "Введите 'ok', чтобы сохранить изменения: ";
    getline(cin, confirmation);

    if (confirmation == "ok") {
        vector<string> updatedContacts;
        string line;

        ifstream file(filename);
        if (!file) {
            cout << "Ошибка при открытии файла!" << endl;
            return;
        }

        while (getline(file, line)) {
            if (line.find(search) != string::npos) {
                line = fullName + " " + phoneNumber;
            }
            updatedContacts.push_back(line);
        }

        file.close();

        ofstream outFile(filename);
        if (!outFile) {
            cout << "Ошибка при открытии файла!" << endl;
            return;
        }

        for (const string& contact : updatedContacts) {
            outFile << contact << endl;
        }

        outFile.close();

        cout << "Контакт отредактирован!" << endl;
    }
    else {
        cout << "Отмена редактирования контакта." << endl;
    }
}

void deleteContact(const string& filename) {
    string phoneNumber;
    cout << "Введите номер телефона контакта, который нужно удалить: ";
    cin.ignore();
    getline(cin, phoneNumber);

    string confirmation;
    cout << "Введите 'ok', чтобы удалить контакт: ";
    getline(cin, confirmation);

    if (confirmation == "ok") {
        vector<string> updatedContacts;
        string line;

        ifstream file(filename);
        if (!file) {
            cout << "Ошибка при открытии файла!" << endl;
            return;
        }

        bool contactDeleted = false;

        while (getline(file, line)) {
            if (line.find(phoneNumber) == string::npos) {
                updatedContacts.push_back(line);
            }
            else {
                contactDeleted = true;
            }
        }

        file.close();

        if (!contactDeleted) {
            cout << "Контакт с указанным номером телефона не найден!" << endl;
            return;
        }

        ofstream outFile(filename);
        if (!outFile) {
            cout << "Ошибка при открытии файла!" << endl;
            return;
        }

        for (const string& contact : updatedContacts) {
            outFile << contact << endl;
        }

        outFile.close();

        cout << "Контакт удален!" << endl;
    }
    else {
        cout << "Отмена удаления контакта." << endl;
    }
}

void findContactByPhoneNumber(const string& filename) {
    ifstream file(filename);

    if (!file) {
        cout << "Ошибка при открытии файла!" << endl;
        return;
    }

    string phoneNumber;
    cout << "Введите номер телефона для поиска: ";
    cin.ignore();
    getline(cin, phoneNumber);

    if (!isValidPhoneNumber(phoneNumber)) {
        return;
    }

    string line;
    bool contactFound = false;

    while (getline(file, line)) {
        if (line.find(phoneNumber) != string::npos) {
            cout << "Найден контакт: " << line << endl;
            contactFound = true;
        }
    }

    file.close();

    if (!contactFound) {
        cout << "Контакт не найден!" << endl;
    }
}

void sortContacts(const string& filename) {
    ifstream file(filename);
    vector<string> contacts;

    if (!file) {
        cout << "Ошибка при открытии файла!" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        contacts.push_back(line);
    }

    file.close();

    char direction;
    cout << "Выберите направление сортировки (A - возрастание, D - убывание): ";
    cin >> direction;

    if (direction == 'A' || direction == 'a') {
        sort(contacts.begin(), contacts.end());
    }
    else if (direction == 'D' || direction == 'd') {
        sort(contacts.rbegin(), contacts.rend());
    }
    else {
        cout << "Некорректный выбор направления сортировки!" << endl;
        return;
    }

    ofstream outFile(filename);
    if (!outFile) {
        cout << "Ошибка при открытии файла!" << endl;
        return;
    }

    for (const string& contact : contacts) {
        outFile << contact << endl;
    }

    outFile.close();

    cout << "Контакты успешно отсортированы!" << endl;
}

int main() {
    setlocale(LC_CTYPE, "");
    string filename = "contacts.txt";
    int choice;
    while (true) {
        cout << "!========== Меню ==========!" << endl;
        cout << "1. Добавить контакт" << endl;
        cout << "2. Показать все контакты" << endl;
        cout << "3. Редактировать контакт" << endl;
        cout << "4. Удалить контакт" << endl;
        cout << "5. Найти контакт по номеру телефона" << endl;
        cout << "6. Отсортировать контакты" << endl;
        cout << "0. Выход" << endl;  // Changed the exit option to '0'
        cout << "============================" << endl;
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addContact(filename);
            break;
        case 2:
            readContacts(filename);
            break;
        case 3:
            editContact(filename);
            break;
        case 4:
            deleteContact(filename);
            break;
        case 5:
            findContactByPhoneNumber(filename);
            break;
        case 6:
            sortContacts(filename);
            break;
        case 0:  // Added case for exit
            cout << "Программа завершена, до свидания!" << endl;
            return 0;
        default:
            cout << "Некорректный выбор. Попробуйте снова." << endl;
            break;
        }

        cout << endl;
    }

    return 0;
}
