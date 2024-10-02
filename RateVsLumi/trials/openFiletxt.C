#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
using namespace std;

void openFiletxt() {
    string filename = "All_Noisy_strips_ID.txt";
    map<int, vector<int>> dataMap;
    // Get the absolute path
    filesystem::path absolutePath = filesystem::absolute(filename);
    
    // Print the absolute path for debugging
    cout << "Opening file: " << absolutePath << endl;
    
    // Declare an fstream object
    fstream file;

    // Open the file in read mode
    file.open(absolutePath, ios::in);

    // Check if the file was opened successfully
    if (!file.is_open()) {
        cerr << "Error opening the file: " << absolutePath << endl;
        return; // Exit the function if there's an error
    }

    // Read the file line-by-line
    string line;
    while (getline(file, line)) {
        // cout << line << endl;
        istringstream iss(line);
        string element;
        int i = 0;
        int key = 0;
        vector<int> numbers;
        while (getline(iss, element, ',')) {
            if (i==0){
                key = stoi(element);
            }
            else{
                numbers.push_back(stoi(element));
            }
            i++;
            }
        // Insert into the map
        dataMap[key] = numbers;
        cout << endl;
    }

    // Close the file
    file.close();
    
    for (auto it = dataMap.begin(); it != dataMap.end(); ++it) {
        cout << "rpcId found:      " << it->first << endl;
        cout << "   noisy strips:  ";
        for (int i = 0; i < it->second.size(); i++) {
            cout << it->second[i] << " ";
        }
        cout << endl;
    }

    return 0;
}

