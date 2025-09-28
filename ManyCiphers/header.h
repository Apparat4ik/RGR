#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>


using namespace std;

enum class Sellection{
    POLIBIUS,
    TRITEMIUS,
    XOR,
    UNKNOWN,
    EXIT
};

void PolibiusCipher();

void TritemiusCipher();

void XorCipher();
