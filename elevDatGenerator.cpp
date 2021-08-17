// elevation generator
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>


using namespace std;

int main() {
    string fileName = "";
    int numRows = 0;
    int numCols = 0;
    int i = 0;
    int j = 0;
    int randInt = 0;

    cout << "Enter name for elevation file: " << endl;
    cin >> fileName;

    cout << "Enter number of rows: " << endl;
    cin >> numRows;
    cout << "Enter number of columns: " << endl;
    cin >> numCols;

    ofstream outfs(fileName + ".dat");

    if (!outfs.is_open()) {
        cout << "Error: unable to create file." << endl;
    }
    
    if (outfs.is_open()) {
        srand(time(0));
        for (i = 0; i < numRows; i++) {
            for (j = 0; j < numCols; j++) {
                outfs << ((rand()) % 1000) << " ";
            }
            outfs << endl;
        }
        
    }
}