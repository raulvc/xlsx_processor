//
// Created by raul on 11/22/15.
//

#include "ForceParser.h"

ForceParser::ForceParser(string filename, double peak_min, double valley_min, long c_line, bool searching_peak)
        : reader(filename) {
    reader.read_header(ignore_extra_column, "forca", "tempo", "cod", "queda");
    this->peak_min = peak_min;
    this->valley_min = valley_min;
    this->c_line = c_line;
    this->searching_peak = searching_peak;
}

DataRow *ForceParser::read_row(long segment) {
    double force;
    double time;
    double code;
    double fall;
    bool ok = reader.read_row(force, time, code, fall);
    previous_val = current_val;
    current_val = force;
    return ok ? new DataRow(force, time, code, segment, fall) : NULL;
}
