#ifndef JOURNAL_H
#define JOURNAL_H

#include <string>

using namespace std;

class Journal {
private:
    string fileName;

public:
    // Constructors
    Journal(const string& fileName);

    // Add a line to the journal: "date heure - [ACTION] details"
    void log(const string& action, const string& details);
};

#endif