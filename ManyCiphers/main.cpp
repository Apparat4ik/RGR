#include "header.h"

void ParseCommand(const string& cmd, Sellection& choice) {
    if (cmd == "1") choice = Sellection::POLIBIUS;
    
    else if (cmd == "2") choice =  Sellection::TRITEMIUS;
    else if (cmd == "3") choice = Sellection::XOR;
    else if (cmd == "0") choice = Sellection::EXIT;
    else choice = Sellection::UNKNOWN;
}

int main(){
    Sellection choice;
    string cmd;
    cout << "ПРОГРАММА ДЛЯ ШИФРОВАНИЯ ФАЙЛОВ" << endl;
    cout << "Какой шифр вы хотите выбрать" << endl;
    cout << "1 - Шифрование через квадрат Полибия" << endl;
    cout << "2 - Шифр Тритемия" << endl;
    cout << "3 - XOR шифрование" << endl;
    cout << "0 - Выход из программы" << endl;
        
    bool run = true;
        
    while (run) {
        cout << "Выберите шифр" << endl;
        cout << ">>> ";
        cin >> cmd;
                
        ParseCommand(cmd, choice);
                
        cout << endl;

        switch (choice) {
            case Sellection::POLIBIUS:
                PolibiusCipher();
                break;
                
            case Sellection::TRITEMIUS:
                TritemiusCipher();
                break;
                
            case Sellection::XOR:
                XorCipher();
                break;
                
            case Sellection::EXIT:
                cout << "Выход из программы..." << endl;
                run = false;
                break;
            
            default:
                cerr << "Такой команды нет" << endl;
                break;
        }
        
        
    }
    return 0;
}


