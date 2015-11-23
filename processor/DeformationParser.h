//
// Created by raul on 11/22/15.
//

#ifndef XLSX_PROCESSOR_DEFORMATIONPARSER_H
#define XLSX_PROCESSOR_DEFORMATIONPARSER_H

#include "csv.h"
#include "Parser.h"

using namespace std;
using namespace io;

class DeformationParser : public Parser {

    CSVReader<1> reader;
    string col;

public:
    DeformationParser(string filename, string col, double peak_min, double valley_min, long c_line, bool searching_peak);

    double read_row();

    string getCol() const {
        return col;
    }
};


#endif //XLSX_PROCESSOR_DEFORMATIONPARSER_H
