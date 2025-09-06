#include "header.h"
#include <random>

random_device rd;
mt19937 gen(rd());

void xor_encrypt_decrypt(const string& inputFile, const string& outputFile, const string& key) {
    ifstream InFile(inputFile, ios::binary);
    ofstream OutFile(outputFile, ios::binary);
    
    if (!InFile.is_open() || !OutFile.is_open()) {
        throw runtime_error("Ошибка открытия файлов!, Проверьте существует ли входной файл или выставите на него нужные разрешения");
    }
    
    if (InFile.peek() == InFile.eof()){
        throw runtime_error("Ошибка! Файл пуст");
    }
    
    char ch;
    int index = 0;
    
    while (InFile.get(ch)){
        char encCh = ch ^ key[index % key.size()];
        index++;
        OutFile.put(static_cast<unsigned char>(encCh));
    }

    InFile.close();
    OutFile.close();
}

string key_generation(int range){
    ofstream mk_file("master_key.txt", ios::binary);
    
    string key;
    uniform_int_distribution<> dis(32, 126);
    for (int i = 0; i < range; i++){
        key += static_cast<unsigned char>(dis(gen));
    }
    mk_file << key;
    mk_file.close();
    return key;
}


void XorCipher() {
    cout << "XOR шифрование" << endl;
    string inputFile, outputFile, key;
    int choice, key_range;
    bool run = true;
    
    cout << "Выберите что вы хотите сделать" << endl;
    cout << "1 - Шифрование файла" << endl;
    cout << "2 - Расшифрование файла" << endl;
    cout << "0 - Назад в меню" << endl;
    cout << "Выбор: ";
    
    try {
        while (run) {
            cout << " >>> ";
            cin >> choice;
            switch (choice) {
                case 1:
                    cout << "Введите путь к файлу для шифрования: ";
                    cin >> inputFile;
                    cout << "Введите имя файла куда вы хотите вывести результат: ";
                    cin >> outputFile;
                    cout << "Введите длину вашего ключа: ";
                    cin >> key_range;
                    
                    if (key_range <= 0 || cin.fail()){
                        cerr << "Длина ключа должна быть положительным числом" << endl;
                    }
                    
                    key = key_generation(key_range);
                    cout << "Ключ сгенерирован в файл master_key.txt" << endl;
                            
                    cout << "Ваш ключ шифрования: " << key << endl;
                            
                    xor_encrypt_decrypt(inputFile, outputFile, key);
                            
                    cout << "Файл зашифрован" << endl;
                    break;
                            
                case 2:
                    cout << "Введите путь к файлу для расшифрования: ";
                    cin >> inputFile;
                    cout << "Введите имя файла куда вы хотите вывести результат: ";
                    cin >> outputFile;
                    cout << "Введите ключ для шифрования: ";
                    getline(cin, key);
                    getline(cin, key);
                            
                    if (key.empty()) {
                        throw runtime_error("Ошибка: Ключ не может быть пустым");
                    }

                    xor_encrypt_decrypt(inputFile, outputFile, key);
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
    } catch (const exception& ss) {
        cerr << ss.what() << endl;
    }
}
