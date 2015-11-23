//
// Created by raul on 11/22/15.
//

#ifndef XLSX_PROCESSOR_MANAGER_H
#define XLSX_PROCESSOR_MANAGER_H

#include <string>
#include <vector>
#include "ForceParser.h"
#include "DeformationParser.h"

using namespace std;

class Manager {
    string MERGED_FILENAME = "merged_input.csv";
    string output;
    ofstream *writer;
    int c_line; // min lines criteria until next peak/valley
    double c_f_peak; // [force] min value criteria until next peak
    double c_f_valley; // [force] min value criteria until next valley
    double c_def_peak; // [deformation] min value criteria until next peak
    double c_def_valley; // [deformation] min value criteria until next valley
    vector<string> files; // input files
    bool seach_peak_first;

    ForceParser *force_parser;
    vector<DeformationParser *> deformation_parsers;

    void prepare_data();

    void prepare_parsers();

    void parse();

    void parse_deformations(vector<DataRow *> f_cache);

    bool str2bool(const string &v);

    void update_rows(vector<DataRow *> f_cache, vector<double> def_cache, string col);

    void flush_changes(vector<DataRow *> *f_cache);
    

public:
    Manager(int, char *[]);

    void start();

};


#endif //XLSX_PROCESSOR_MANAGER_H
