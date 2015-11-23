//
// Created by raul on 11/22/15.
//

#include <sstream>
#include "DataRow.h"

DataRow::DataRow(double force, double time, double code, long segment, double fall)
        : force(force), time(time), code(code),
          segment(segment), fall(fall) { }

string DataRow::to_csv_row() {
    ostringstream stream;
    stream << force << ", " << time << ", " << code << ", " << stringify(def1) << ", " << stringify(def2) <<
    ", " << stringify(def3) << ", " << stringify(def4) << ", " << fall << ", " << segment << endl;
    return stream.str();
}

string DataRow::stringify(double d) {
    return (d == 0) ? "" : to_string(d);
}
