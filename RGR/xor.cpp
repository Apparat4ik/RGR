#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


vector<unsigned char> xorEncryptDecrypt(const vector<unsigned char>& data, const string& key) {
    vector<unsigned char> result;
    result.reserve(data.size());
    
    for (size_t i = 0; i < data.size(); ++i) {
        char encryptedChar = data[i] ^ key[i % key.size()];
        result.push_back(encryptedChar);
    }
    
    return result;
}


vector<unsigned char> readFile(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        throw runtime_error("Ошибка: Не удалось открыть файл для чтения: " + filename);
    }
    

    file.seekg(0, ios::end);
    streamsize size = file.tellg();
    file.seekg(0, ios::beg);
    
    vector<unsigned char> buffer(size);
    if (!file.read(reinterpret_cast<char*>(buffer.data()), size)) {  // запись содержимого файла в buffer
        throw runtime_error("Ошибка: Не удалось прочитать файл: " + filename);
    }
    
    file.close();
    return buffer;
}


void writeFile(const string& filename, const vector<unsigned char>& data) {
    ofstream file(filename, ios::binary);
    if (!file.is_open()) {
        throw runtime_error("Ошибка: Не удалось открыть файл для записи: " + filename);
    }
    
    if (!file.write(reinterpret_cast<const char*>(data.data()), data.size())) {
        throw runtime_error("Ошибка: Не удалось записать в файл: " + filename);
    }
    
    file.close();
    cout << "Данные успешно записаны в файл: " << filename << endl;
}

int main() {
    try {
        string inputFilename, key;
  
        cout << "Введите имя файла для шифрования: ";
        cin >> inputFilename;
        
        cout << "Введите ключ для шифрования: ";
        getline(cin, key);
        
        if (key.empty()) {
            throw runtime_error("Ошибка: Ключ не может быть пустым");
        }
        

        cout << "Чтение файла..." << endl;
        vector<unsigned char> originalData = readFile(inputFilename);
        

        cout << "Шифрование..." << endl;
        vector<unsigned char> encryptedData = xorEncryptDecrypt(originalData, key);
        
      
        cout << "Запись результата..." << endl;
        writeFile("cypher.txt", encryptedData);
        
        cout << "Шифрование завершено успешно!" << endl;
    } catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }
    
    return 0;
}
