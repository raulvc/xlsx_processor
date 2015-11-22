//
// Created by raul on 11/22/15.
//

#ifndef XLSX_PROCESSOR_MANAGER_H
#define XLSX_PROCESSOR_MANAGER_H

#include <string>
#include <vector>

using namespace std;

class Manager {
    string output;
    int c_line; // min lines criteria until next peak/valley
    double c_f_peak; // [force] min value criteria until next peak
    double c_f_valley; // [force] min value criteria until next valley
    double c_def_peak; // [deformation] min value criteria until next peak
    double c_def_valley; // [deformation] min value criteria until next valley
    vector<string> files; // input files

    void prepare_data();

public:
    Manager(int, char *[]);
    void start();
};


#endif //XLSX_PROCESSOR_MANAGER_H
