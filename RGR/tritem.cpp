#include "header.h"


void process_file(const string& inputFile, const string& outputFile, bool encrypt) {
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
        int result;
        
        if (encrypt) {
            result = (static_cast<unsigned int>(ch) + index) % 256;
        } else {
            result = (static_cast<unsigned int>(ch) - index) % 256;
            if (result < 0) result += 256;
        }
        OutFile.put(static_cast<unsigned char>(result));
        index++;
    }
    
    InFile.close();
    OutFile.close();
    
    cout << "Файл " << (encrypt ? "зашифрован" : "расшифрован") << " успешно!" << endl;
}


void TritemiusCipher() {
    int choice;
    cout << "Шифр Тритемия с mod 256" << endl;
    cout << "1 - Шифрование файла" << endl;
    cout << "2 - Расшифрование файла" << endl;
    cout << "0 - Назад в меню" << endl;
    cout << "Выбор: ";
    string inputFile, outputFile;
    bool run = true;
    
    try {
        while (run) {
            cout << ">>> ";
            cin >> choice;

            switch (choice) {
                case 1:
                    cout << "Введите входной файл: ";
                    cin >> inputFile;
                    cout << "Введите выходной файл: ";
                    cin >> outputFile;
                    process_file(inputFile, outputFile, true);
                    break;
                                
                case 2:
                    cout << "Введите входной файл: ";
                    cin >> inputFile;
                    cout << "Введите выходной файл: ";
                    cin >> outputFile;
                    process_file(inputFile, outputFile, false);
                    break;
                
                case 0:
                    run = false;
                    break;
                                
                default:
                    cerr << "Такой команды нет" << endl;
                    break;
            }
        }
    } catch (exception& ss){
        cerr << ss.what() << endl;
    }
}
