//
// Created by raul on 11/22/15.
//

#include "DeformationParser.h"

DeformationParser::DeformationParser(string filename, string col, double peak_min, double valley_min, long c_line,
                                     bool searching_peak) : reader(filename) {
    reader.read_header(ignore_extra_column, col);
    this->peak_min = peak_min;
    this->valley_min = valley_min;
    this->c_line = c_line;
    this->col = col;
    this->searching_peak = searching_peak;
}

double DeformationParser::read_row() {
    double deformation;
    bool ok = reader.read_row(deformation);
    previous_val = current_val;
    current_val = deformation;
    return ok ? deformation : 0;
}
