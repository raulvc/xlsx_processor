//
// Created by raul on 11/22/15.
//

#ifndef XLSX_PROCESSOR_FORCEPARSER_H
#define XLSX_PROCESSOR_FORCEPARSER_H

#include "csv.h"
#include "Parser.h"
#include "DataRow.h"

using namespace std;
using namespace io;

class ForceParser : public Parser {

    CSVReader<4> reader;

public:
    ForceParser(string filename, double peak_min, double valley_min, long c_line, bool searching_peak);

    DataRow *read_row(long segment);
};


#endif //XLSX_PROCESSOR_FORCEPARSER_H
