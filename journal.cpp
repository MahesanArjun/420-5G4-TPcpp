#include <fstream>
#include <iostream>
#include <ctime>
#include <iomanip>

#include "journal.h"

using namespace std;

// Constructor
Journal::Journal(const string& fileName) : fileName(fileName) {}



void Journal::log(const string& action, const string& details) {
    ofstream file(fileName, ios::app);
    if (!file.is_open()) {
        cout << "Erreur : Impossible d'écrire dans le journal " << fileName << ".\n";
        return;
    }

    time_t now = time(nullptr);
    file << put_time(localtime(&now), "%Y-%m-%d %H:%M:%S")
         << " - [" << action << "] " << details << "\n";
}