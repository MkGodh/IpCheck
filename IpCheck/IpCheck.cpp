#include <algorithm>
#include <iostream>
#include <istream>
#include <string>

using namespace std;

bool octetCheck(string& currentOctet, int& dotCount) {

    bool correct = false;
    for (int i = 0; i < currentOctet.size(); i++) {

        if (currentOctet == "..") {
            return false; // Возвращаем false, если текущий октет содержит две точки
        }
        else if (dotCount > 3) {
            return false;
        }


        if (currentOctet.length() > 3 || currentOctet.length() < 1) {
            return false;
        }
        if (currentOctet[i] >= '0' && currentOctet[i] <= '9') {
            correct = true;
        }
        else {
            return false;

        }
        int num = stoi(currentOctet);
        if (num > 255 || num < 0) {
            correct = false;
            break;
        }
        if (currentOctet[0] == '0' && currentOctet.length() >= 2) {
            correct = false;
            break;
        }
        if (i == currentOctet.size() - 1 && currentOctet[i] == '.') {
            correct = false;
            break;
        }
        if (currentOctet[i] == '.' && currentOctet[i + 1] == '.') {
            correct = false;
            break;
        }
    }
    return correct;
}


string get_adress_part(string ip, int  octetNumber, int& dotCount, int& currentPosition) {

    string currentOctet = "";

    int i = currentPosition;

    while (i < ip.length()) {

        if (ip[i] == '.' && ip[i + 1] == '.') {
            currentOctet = "";
            currentOctet += "..";
            break;
        }

        if (ip[i] == '.') {

            dotCount++;
            currentPosition = i + 1;
            octetCheck(currentOctet, dotCount);
            break;
            currentOctet = "";


        }
        else {
            currentOctet += ip[i]; // Добавляем символ к текущему октету
        }

        i++;
    }
    octetCheck(currentOctet, dotCount);

    return currentOctet;
}


int main() {

    string ip;
    string result;
    int dotCount = 0;
    int currentPosition = 0;


    string currentOctet;

    cout << "Please, input ip adress: "; cin >> ip;
    for (int octetNumber = 0; octetNumber < 4; octetNumber++) {
        currentOctet = get_adress_part(ip, octetNumber, dotCount, currentPosition);
        if (!octetCheck(currentOctet, dotCount)) {
            cout << "Invalid";
            return 1;
        }
    }
    cout << "Valid";

    return 0;
}