#include "header.h"
#include <stdint.h>


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
            result += static_cast<unsigned char>(new_code);
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
        result += static_cast< unsigned char>(original_code);
    }
    
    return result;
}

void read_file(const string& filename, string& content) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        throw runtime_error("Ошибка: Не удалось открыть файл для чтения");
    }
    
    if (file.peek() == file.eof()){
        throw runtime_error("Ошибка! Файл пуст");
    }
    
    file.seekg(0, ios::end);
    size_t size = file.tellg();
    file.seekg(0, ios::beg);
    
    content.resize(size);
    file.read(&content[0], size);
    
    file.close();
}


void write_file(const string& filename, const string& content) {
    
    ofstream file(filename, ios::binary);
    if (!file.is_open()) {
        throw runtime_error("Ошибка: Не удалось открыть файл для записи");
    }
    
    file.write(content.c_str(), content.size());
    
    file.close();
}


void PolibiusCipher() {
    int choice;
    cout << "Шифрование через квадрат Полибия" << endl;
    cout << "Выберите режим работы:" << endl;
    cout << "1 - Шифрование файла" << endl;
    cout << "2 - Дешифрование файла" << endl;
    cout << "0 - Назад в меню" << endl;
    cout << "Ваш выбор: ";
    
    
    string input_file, output_file;
    string processed_content;
    string file_content;
    bool run = true;
    
    try {
        while (run){
            cout << ">>> ";
            cin >> choice;
            switch (choice) {
                case 1:
                    cout << "Введите путь к входному файлу: ";
                    cin >> input_file;
                    cout << "Введите путь к выходному файлу: ";
                    cin >> output_file;
                    
                    read_file(input_file, file_content);
                    processed_content = polybius_encrypt(file_content);
                    write_file(output_file, processed_content);
                    processed_content.clear();
                    file_content.clear();
                    cout << "Файл зашифрован" << endl;
                    break;
                    
                case 2:
                    cout << "Введите путь к входному файлу: ";
                    cin >> input_file;
                    cout << "Введите путь к выходному файлу: ";
                    cin >> output_file;
                    
                    read_file(input_file, file_content);
                    processed_content = polybius_decrypt(file_content);
                    write_file(output_file, processed_content);
                    processed_content.clear();
                    file_content.clear();
                    cout << "Файл расшифрован" << endl;
                    break;
                    
                case 0:
                    run = false;
                    break;
                    
                default:
                    cerr << "Такой команды нет" << endl;
                    break;
            }
        }
    } catch (exception& ss) {
        cerr << ss.what() << endl;
    }
}
