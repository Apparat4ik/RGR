#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdint.h>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

string polybius_encrypt(const string& text) {
    vector<uint8_t> codes;
    vector<uint8_t> rows;
    vector<uint8_t> cols;
    
    for (unsigned char c : text) {
        codes.push_back(static_cast<uint8_t>(c));
    }
    
    for (uint8_t code : codes) {
        rows.push_back(code / 16);
        cols.push_back(code % 16);
    }
    
    vector<uint8_t> combined;
    combined.insert(combined.end(), rows.begin(), rows.end());
    combined.insert(combined.end(), cols.begin(), cols.end());
    
    string result;
    for (int i = 0; i < combined.size(); i += 2) {
        if (i + 1 < combined.size()) {
            int new_code = combined[i] * 16 + combined[i + 1];
            result += static_cast<char>(new_code);
        }
    }
    
    return result;
}

string polybius_decrypt(const string& ciphertext) {
    vector<uint8_t> codes;
    
    for (unsigned char c : ciphertext) {
        codes.push_back(static_cast<uint8_t>(c));
    }
    
    vector<uint8_t> coords;
    for (unsigned int code : codes) {
        coords.push_back(code / 16);
        coords.push_back(code % 16);
    }
    
    int n = coords.size() / 2;
    vector<uint8_t> rows(coords.begin(), coords.begin() + n);
    vector<uint8_t> cols(coords.begin() + n, coords.end());
    
    string result;
    for (int i = 0; i < n; i++) {
        int original_code = rows[i] * 16 + cols[i];
        result += static_cast<char>(original_code);
    }
    
    return result;
}

void read_file(const string& filename, string& content) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        throw runtime_error("Ошибка: Не удалось открыть файл '" + filename + "' для чтения");
    }
    
    file.seekg(0, ios::end);
    size_t size = file.tellg();
    file.seekg(0, ios::beg);
    
    content.resize(size);
    file.read(&content[0], size);
    
    file.close();
    cout << "Прочитано " << size << " байт из файла '" << filename << "'" << endl;
}


bool write_file(const string& filename, const string& content) {
    
    ofstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Ошибка: Не удалось открыть файл '" << filename << "' для записи" << endl;
        cerr << "Проверьте права доступа к директории" << endl;
        return false;
    }
    
    file.write(content.c_str(), content.size());
    
    if (!file) {
        cerr << "Ошибка: Не удалось записать данные в файл" << endl;
        file.close();
        return false;
    }
    
    file.close();
    cout << "Записано " << content.size() << " байт в файл '" << filename << "'" << endl;
    return true;
}


int main() {
    cout << "Шифрование методом квадрата Полибия (работа с файлами)" << endl;
    cout << "======================================================" << endl;
    
    int choice;
    cout << "Выберите режим работы:" << endl;
    cout << "1 - Шифрование файла" << endl;
    cout << "2 - Дешифрование файла" << endl;
    cout << "Ваш выбор: ";
    cin >> choice;
    
    string input_file, output_file;
    
    cout << "Введите путь к входному файлу: ";
    cin >> input_file;
    cout << "Введите путь к выходному файлу: ";
    cin >> output_file;
    
    string processed_content;
    string file_content;
    try {
        read_file(input_file, file_content);
        switch (choice) {
            case 1:
                cout << "Шифрование..." << endl;
                processed_content = polybius_encrypt(file_content);
                cout << "Размер данных: " << file_content.size() << " -> " << processed_content.size() << " байт" << endl;
                break;
                    
            case 2:
                cout << "Дешифрование..." << endl;
                processed_content = polybius_decrypt(file_content);
                cout << "Размер данных: " << file_content.size() << " -> " << processed_content.size() << " байт" << endl;
                    
            default:
                cerr << "Ошибка: Неверный выбор режима" << endl;
                break;
        }
            
        write_file(output_file, processed_content);
        
        cout << "Операция завершена успешно!" << endl;
    } catch (exception& ss) {
        cerr << ss.what() << endl;
    }
    return 0;
}
