//
// Created by raul on 11/22/15.
//

#include <fstream>
#include <iostream>
#include "Manager.h"

Manager::Manager(int argc, char *argv[]) {
    c_line = stoi(argv[1]);
    c_f_valley = stod(argv[2]);
    c_f_peak = stod(argv[3]);
    c_def_valley = stod(argv[4]);
    c_def_peak = stod(argv[5]);
    for (int index = 6; index < argc; index++) {
        files.push_back(argv[index]);
    }
}

void Manager::start() {
    prepare_data();
}

void Manager::prepare_data() {
    // merging input
    ofstream merged_input("merged_input.csv", ios_base::binary | ios_base::trunc);
    for (vector<string>::iterator it = files.begin(); it != files.end(); ++it) {
        string filepath = *it;
        string base_name =  filepath.substr(filepath.find_last_of("/\\") + 1);
        cout << "Merging file " << base_name << endl;
        ifstream file_input(filepath, ios_base::binary);
        merged_input << file_input.rdbuf();
    }
}
