//
// Created by raul on 11/22/15.
//

#include <fstream>
#include <iostream>
#include "Manager.h"

Manager::Manager(int argc, char *argv[]) {
    seach_peak_first = str2bool(argv[1]);
    c_line = stoi(argv[2]);
    c_f_valley = stod(argv[3]);
    c_f_peak = stod(argv[4]);
    c_def_valley = stod(argv[5]);
    c_def_peak = stod(argv[6]);
    output = argv[7];
    writer = new ofstream(output, ios_base::trunc);
    // writing headers
    *writer << "forca, tempo, cod, deformacao1, deformacao2, deformacao3, deformacao4, queda, segmento" << endl;
    for (int index = 8; index < argc; index++) {
        files.push_back(argv[index]);
    }
}


bool Manager::str2bool(const string &v) {
    return !v.empty() && atoi(v.c_str()) != 0;
}

void Manager::start() {
    prepare_data();
    prepare_parsers();
    parse();
}

void Manager::parse() {
    cout << "Processing merged file..." << endl;
    long segment = 1;
    long line_counter = 0;
    vector<DataRow *> f_cache;
    while (true) {
        DataRow *row = force_parser->read_row(segment);
        if (row == NULL) {
            break;
        }
        bool is_peak = force_parser->verify_peak(line_counter);
        if (is_peak) {
            parse_deformations(f_cache);
            flush_changes(&f_cache);
            force_parser->toggle_direction();
            segment++;
            line_counter = 0;
        }
        else {
            line_counter++;
        }
        f_cache.push_back(row);
    }
    cout << "Done." << endl;
}

void Manager::flush_changes(vector<DataRow *> *f_cache) {
    for (vector<DataRow *>::iterator it = f_cache->begin(); it != f_cache->end(); ++it) {
        *writer << (*it)->to_csv_row();
    }
    f_cache->clear();
    f_cache->shrink_to_fit();
}

void Manager::parse_deformations(vector<DataRow *> f_cache) {
    for (vector<DeformationParser *>::iterator it = deformation_parsers.begin();
         it != deformation_parsers.end(); ++it) {
        long line_counter = 0;
        vector<double> def_cache;
        DeformationParser *def_parser = *it;
        double queued_value = def_parser->getCurrent_val();
        if (queued_value) {
            def_cache.push_back(queued_value);
        }
        while (true) {
            double row = def_parser->read_row();
            if (!row) {
                break;
            }
            bool is_peak = def_parser->verify_peak(line_counter);
            if (is_peak) {
                update_rows(f_cache, def_cache, def_parser->getCol());
                def_cache.clear();
                def_cache.shrink_to_fit();
                def_parser->toggle_direction();
                break;
            }
            else {
                line_counter++;
                def_cache.push_back(row);
            }
        }
    }
}

void Manager::update_rows(vector<DataRow *> f_cache, vector<double> def_cache, string col) {
    for (vector<DataRow *>::reverse_iterator it = f_cache.rbegin(); it != f_cache.rend(); ++it) {
        double val = def_cache.empty() ? 0 : def_cache.back();
        if (col == "deformacao1") {
            (*it)->setDef1(val);
        }
        else if (col == "deformacao2") {
            (*it)->setDef2(val);
        }
        else if (col == "deformacao3") {
            (*it)->setDef3(val);
        }
        else {
            (*it)->setDef4(val);
        }
        def_cache.pop_back();
    }
}

void Manager::prepare_parsers() {
    force_parser = new ForceParser(MERGED_FILENAME, c_f_peak, c_f_valley, c_line, seach_peak_first);
    deformation_parsers.push_back(
            new DeformationParser(MERGED_FILENAME, "deformacao1", c_def_peak, c_def_valley, c_line, seach_peak_first));
    deformation_parsers.push_back(
            new DeformationParser(MERGED_FILENAME, "deformacao2", c_def_peak, c_def_valley, c_line, seach_peak_first));
    deformation_parsers.push_back(
            new DeformationParser(MERGED_FILENAME, "deformacao3", c_def_peak, c_def_valley, c_line, seach_peak_first));
    deformation_parsers.push_back(
            new DeformationParser(MERGED_FILENAME, "deformacao4", c_def_peak, c_def_valley, c_line, seach_peak_first));
}

void Manager::prepare_data() {
    // merging input
    ofstream merged_input(MERGED_FILENAME, ios_base::binary | ios_base::trunc);
    for (vector<string>::iterator it = files.begin(); it != files.end(); ++it) {
        string filepath = *it;
        string base_name = filepath.substr(filepath.find_last_of("/\\") + 1);
        cout << "Merging file " << base_name << endl;
        ifstream file_input(filepath, ios_base::binary);
        merged_input << file_input.rdbuf();
    }
    cout << "Done." << endl;
}

