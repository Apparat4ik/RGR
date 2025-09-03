#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

// Шифрование/дешифрование файла
void processFile(const string& inputFile, const string& outputFile, bool encrypt) {
    ifstream inFile(inputFile, ios::binary);
    ofstream outFile(outputFile, ios::binary);
    
    if (!inFile.is_open() || !outFile.is_open()) {
        cerr << "Ошибка открытия файлов!" << endl;
        return;
    }
    
    vector<char> buffer((istreambuf_iterator<char>(inFile)),
                       istreambuf_iterator<char>());
    
    for (size_t i = 0; i < buffer.size(); i++) {
        unsigned char c = buffer[i];
        int result;
        
        if (encrypt) {
            result = (static_cast<int>(c) + i) % 256;
        } else {
            result = (static_cast<int>(c) - i) % 256;
            if (result < 0) result += 256;
        }
        
        outFile.put(static_cast<char>(result));
    }
    
    cout << "Файл " << (encrypt ? "зашифрован" : "расшифрован") << " успешно!" << endl;
}

int main() {
    int choice;
    
    cout << "Шифр Тритемия с mod 256" << endl;
    cout << "1 - Шифрование файла" << endl;
    cout << "1 - Расшифрование файла" << endl;
    cout << "Выбор: ";
    cin >> choice;
    cin.ignore(); // Очистка буфера
    
      
    if (choice == 1 || choice == 2) {
        string inputFile, outputFile;
        cout << "Входной файл: ";
        getline(cin, inputFile);
        cout << "Выходной файл: ";
        getline(cin, outputFile);
        
        processFile(inputFile, outputFile, choice == 2);
    }
    
    return 0;
}
