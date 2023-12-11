#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream ifs("5x5.in",ios::in);
    char buffer[256] = {0};

    if (!ifs.is_open()) {
        cout << "Failed to open file.\n";
        return 1; // EXIT_FAILURE
    }

    ifs.read(buffer, sizeof(buffer));
    cout << buffer;
    ifs.close();
    return 0;
}