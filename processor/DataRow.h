//
// Created by raul on 11/22/15.
//

#ifndef XLSX_PROCESSOR_DATAROW_H
#define XLSX_PROCESSOR_DATAROW_H

#include <string>

using namespace std;

class DataRow {

    double force;
    double time;
    double code;
    long segment;
    double def1 = 0;
    double def2 = 0;
    double def3 = 0;
    double def4 = 0;
    double fall;

    string stringify(double);


public:

    DataRow(double force, double time, double code, long segment, double fall);

    string to_csv_row();

    double getForce() const {
        return force;
    }

    void setForce(double force) {
        DataRow::force = force;
    }

    double getTime() const {
        return time;
    }

    void setTime(double time) {
        DataRow::time = time;
    }

    double getCode() const {
        return code;
    }

    void setCode(double code) {
        DataRow::code = code;
    }

    long getSegment() const {
        return segment;
    }

    void setSegment(long segment) {
        DataRow::segment = segment;
    }

    double getDef1() const {
        return def1;
    }

    void setDef1(double def1) {
        DataRow::def1 = def1;
    }

    double getDef2() const {
        return def2;
    }

    void setDef2(double def2) {
        DataRow::def2 = def2;
    }

    double getDef3() const {
        return def3;
    }

    void setDef3(double def3) {
        DataRow::def3 = def3;
    }

    double getDef4() const {
        return def4;
    }

    void setDef4(double def4) {
        DataRow::def4 = def4;
    }

    double getFall() const {
        return fall;
    }

    void setFall(double fall) {
        DataRow::fall = fall;
    }
};


#endif //XLSX_PROCESSOR_DATAROW_H
