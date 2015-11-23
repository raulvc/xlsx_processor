//
// Created by raul on 11/22/15.
//

#include "Parser.h"

bool Parser::verify_peak(long current_line) {
    // line criteria
    if (current_line < c_line) {
        return false;
    }
    if (!previous_val || !current_val) {
        return false;
    }
    // peak min criteria
    if (searching_peak && current_val < previous_val) {
        return current_val > peak_min;
    }
    // valley min criteria
    if (!searching_peak && current_val > previous_val) {
        return current_val < valley_min;
    }
    return false;
}

void Parser::toggle_direction() {
    searching_peak = !searching_peak;
}
