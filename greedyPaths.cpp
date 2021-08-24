// mountain paths hw

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
//include "functions.h"

using namespace std;

int MaxVal (const vector< vector<int> >& valsList) {
    int i = 0;
    int j = 0;
    int maxNum = valsList.at(i).at(j);
    for (i = 0; i < valsList.size(); i++) {
        for (j = 0; j < valsList.at(i).size(); j++) {
            if (valsList.at(i).at(j) > maxNum) {
                maxNum = valsList.at(i).at(j);
            }
        }

    }
    return maxNum;
}

int MinVal (const vector< vector<int> >& valsList) {
    int i = 0;
    int j = 0;
    int minNum = valsList.at(i).at(j);
    for (i = 0; i < valsList.size(); i++) {
        for (j = 0; j < valsList.at(i).size(); j++) {
            if (valsList.at(i).at(j) < minNum) {
                minNum = valsList.at(i).at(j);
            }
        }

    }
    return minNum;
}

int GrayShade(int pointVal, int maxPoint, int minPoint) {
    int shadeOfGray = round((((float)(pointVal - minPoint)) / ((float)(maxPoint - minPoint))) * 255);

    return shadeOfGray;
}

int colorPath(const vector< vector<int> >& heightMap, 
            vector< vector<int> >& r, vector< vector<int> >& g, vector< vector<int> >& b, 
            int color_r, int color_g, int color_b, 
            int start_row) {
	
    int dist = 0;
    int c = 0;
    int i = 0;
    int numChoices = 0;
    int fwdDist = 0;
    int fwdUpDist = 0;
    int fwdDownDist = 0;
    int minStep = 0;
    vector <int> pathSteps(0);
    bool bottomRow = true;
    // color start of path
    r.at(start_row).at(c) = color_r;
    g.at(start_row).at(c) = color_g;
    b.at(start_row).at(c) = color_b;

    //find shortest path
    for (c = 0; c < heightMap.size() - 1; c++) {
        // test current spot
        // cout << "current row is: " << start_row << endl;
        // cout << "current column is: " << c << endl;
        
        fwdDist = abs(heightMap.at(start_row).at(c + 1) - heightMap.at(start_row).at(c));
        // cout << "fwdDist = " << fwdDist << endl;
        // current step vector index is i
        numChoices = 0;
        pathSteps.push_back(fwdDist);
        numChoices += 1;
        // if not on last row, add fwd down dist & path option
        if (start_row < heightMap.size() - 1) {
            //cout << "row is: " << start_row << " and size of height vec is: " << heightMap.size() << endl;
            fwdDownDist =  abs(heightMap.at(start_row + 1).at(c + 1) -  heightMap.at(start_row).at(c));
            pathSteps.push_back(fwdDownDist);
            numChoices += 1;
            bottomRow = false;
        }
        // if not on first row, add fwd up dist & path option
        if (start_row > 0) {
            fwdUpDist = abs(heightMap.at(start_row - 1).at(c + 1) -  heightMap.at(start_row).at(c));
            numChoices += 1;
            // if on last row, fwdUp = 2nd path step, otherwise fwdUp = 3rd path step
            pathSteps.push_back(fwdUpDist);
        }
        
        minStep = pathSteps.at(0);
        int choiceNum = 0;           
        for (i = 0; i < pathSteps.size(); i++) {
            if (pathSteps.at(i) < minStep) {
                minStep = pathSteps.at(i);
                choiceNum = i;
            }
        }
        // cout << "minStep is: " << minStep << " and choiceNum is: " << choiceNum << endl;

        if (choiceNum == 0) {
            //move forward
            r.at(start_row).at(c + 1) = color_r;
            g.at(start_row).at(c + 1) = color_g;
            b.at(start_row).at(c + 1) = color_b;

            dist += fwdDist;
        }
        else if (choiceNum == 1 && !bottomRow) {
            //move fwd down
            r.at(start_row + 1).at(c + 1) = color_r;
            g.at(start_row + 1).at(c + 1) = color_g;
            b.at(start_row + 1).at(c + 1) = color_b;

            dist += fwdDownDist;
            start_row += 1;
        }
        else if ((choiceNum == 1 && bottomRow) || (choiceNum == 2 && !bottomRow)) {
            //move fwd up
            r.at(start_row - 1).at(c + 1) = color_r;
            g.at(start_row - 1).at(c + 1) = color_g;
            b.at(start_row - 1).at(c + 1) = color_b;

            dist += fwdUpDist;
            start_row -= 1;
        }

        pathSteps.clear();
        bottomRow = true;
        
        
    }

    //cout << "dist is: " << dist << endl;

	return dist;
}

int main() {
    int numRows = 0;
    int numColumns = 0;
    string fileName = "";

    // enter file info
    cout << "Enter the number of rows: ";
    cin >> numRows;
    if (cin.fail()) {
        cout << "Error: enter an integer value for rows." << endl;
    }
    cout << "Enter the number of colums: ";
    cin >> numColumns;
    if (cin.fail()) {
        cout << "Error: enter an integer value for columns." << endl;
    }
    if (numRows < 1 || numColumns < 1) {
        cout << "Error: enter a positive number of rows and columns." << endl;
        cin >> numRows >> numColumns;
    }
    cout << "Enter the file name: ";
    cin >> fileName;

    cout << "numRows is: " << numRows << " and numColumns is: " << numColumns << endl;

    

    // if (numColumns < 0) {
    //     cout << "Error: enter a positive number of rows and columns." << endl;
    // }


    // if (!isdigit(numRows) || !isdigit(numColumns)) {
    //     cout << isdigit(numRows) << endl;
    //     cout << "Error: enter a numerical value for rows and columns." << endl; 
    // }

    // open file and copy data into vector
    ifstream infs(fileName);
    int fileData = 0;
    vector< vector<int> > fileNums(numRows);

    int r = 0;
    int c = 0;
    cout << endl << "Opening file ..." << endl;
    if (!infs.is_open()) {
        cout << "Error: unable to open file." << endl;
    }
    
    if (infs.is_open()) {
        while (!infs.eof()) {
            for (r = 0; r < numRows; r++) {
                for (c = 0; c < numColumns; c++) {
                    infs >> fileData;
                    // if (infs.fail()) {
                    //     if (infs.bad()) {
                    //         return 1;
                    //     }
                    //     else if (infs.fail()) {
                    //         cout << "Error: invalid data in filestream" << endl;
                    //         infs.clear();
                    //         infs.ignore('\n');
                    //     }
                        
                    // }
                    fileNums.at(r).push_back(fileData);
            }
        }
        if (r != numRows || c != numColumns) {
            cout << "Error: invalid input for rows and columns." << endl;
        }
    }
    }
    // for (r = 0; r < numRows; r++) {
    //     for (c = 0; c < numColumns; c++) {
    //         cout << fileNums.at(r).at(c) << " ";
    //     }
    // }

    // for (r = 0; r < numRows; r++) {
    //     for (c = 0; c < numColumns; c++) {
    //         if (!isdigit(fileNums.at(r).at(c))) {
    //             cout << "Error: non integer in filestream." << endl;
    //                 }
    //         }
    //     }

    cout << endl;

    // find min & max elevation values in file
    int maxElevation = MaxVal(fileNums);
    int minElevation = MinVal(fileNums);
    cout << "File max is: " << maxElevation << endl;
    cout << "File min is: " << minElevation << endl;

    int elevationPoint = 0;
    int grayShadeNum = 0;
    int numElements = numRows * numColumns;
    vector< vector<int> > rGrayVec(numRows);
    vector< vector <int> > gGrayVec(numRows);
    vector< vector <int> > bGrayVec(numRows);
    
    // find grayscale rgb value of elevation points
    for (r = 0; r < numRows; r++) {
        for (c = 0; c < numColumns; c++) {
            elevationPoint = fileNums.at(r).at(c);
            grayShadeNum = GrayShade(elevationPoint,maxElevation,minElevation);
            rGrayVec.at(r).push_back(grayShadeNum);
            gGrayVec.at(r).push_back(grayShadeNum);
            bGrayVec.at(r).push_back(grayShadeNum);
        }
    }

    int i = 0;
    
    // for (r = 0; r < numRows; r++) {
    //     for (c = 0; c < numColumns; c++) {
    //         cout << rGrayVec.at(r).at(c) << " ";
    //     }
    // }

    // call paths func to paint path light blue - RGB (167, 206, 240)
    // create vector to hold dist values
    vector<int> pathDist(numRows);
    int pathCount = 0;
    
    for (pathCount = 0; pathCount < numRows; pathCount++) {
        pathDist.at(pathCount) = colorPath(fileNums, rGrayVec, gGrayVec, bGrayVec, 167, 206, 240, pathCount);

        // cout << pathDist.at(pathCount) << " ";
    }
    

    int minPath = pathDist.at(0);
    int minPathCount = 0;
    for (pathCount = 0; pathCount < numRows; pathCount++) {
        if (pathDist.at(pathCount) < minPath) {
            minPath = pathDist.at(pathCount);
            minPathCount = pathCount;
        }
    }
    
    cout << "shortest path is: " << minPath << " at row: " << minPathCount << endl;

    // paint shortest path darker blue - RGB (0, 101, 152)
    colorPath(fileNums, rGrayVec, gGrayVec, bGrayVec, 0, 101, 152, minPathCount);
    

    string firstLine = "P3";
    string imageFileName = "";
    int maxColor = 255;

    ofstream outfs(fileName + ".ppm");

    if (!outfs.is_open()) {
        cout << "Error: unable to create file." << endl;
    }
    
    r = 0;
    c = 0;
    if (outfs.is_open()) {
        outfs << firstLine << endl;
        outfs << numColumns << " " << numRows << endl;
        outfs << maxColor << endl;
        for (r = 0; r < numRows; r++) {
            for (c = 0; c < numColumns; c++) {
                outfs << rGrayVec.at(r).at(c) << " " << gGrayVec.at(r).at(c) << " " << bGrayVec.at(r).at(c) << "   ";
                //cout << rGrayVec.at(r).at(c) << " " << gGrayVec.at(r).at(c) << " " << bGrayVec.at(r).at(c) << " ";
            }
            outfs << endl; 
        }
    } 



}