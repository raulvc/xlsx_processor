//
// Created by raul on 11/22/15.
//

#ifndef XLSX_PROCESSOR_PARSER_H
#define XLSX_PROCESSOR_PARSER_H


class Parser {

protected:
    bool searching_peak = true;
    double previous_val = 0;
    double current_val = 0;
    double peak_min;
    double valley_min;
    long c_line;

public:
    bool verify_peak(long current_line);
    void toggle_direction();

    double getCurrent_val() const {
        return current_val;
    }
};


#endif //XLSX_PROCESSOR_PARSER_H
