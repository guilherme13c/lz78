#pragma once

#include <getopt.h>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

#define COMPRESS 0
#define DECOMPRESS 1

struct cl_args {
    string input_file_name;
    string output_file_name;

    int op;
};

void print_help_message() {
    cout << "Usage:\t./lz78-compress [Options]" << endl;
    cout << "Options:" << endl;
    cout << "\t-c <input_file_name> :\tcompress the given file." << endl;
    cout << "\t-x <input_file_name> :\tdecompress the given file." << endl;
    cout << "\t-o <output_file_name> :\tdefine the output file name. The "
            "default name is the same of the input file."
         << endl;
}

struct cl_args get_execution_options(int argc, char **argv) {
    struct cl_args args;

    string input_file_name;
    string output_file_name;

    int op;
    bool output_defined = false;

    char opt = -1;

    while ((opt = getopt(argc, argv, "c:x:o:")) != -1) {
        switch (opt) {
        case 'c':
            op = COMPRESS;
            input_file_name = string(optarg);
            break;
        case 'o':
            output_file_name = string(optarg);
            output_defined = true;
            break;
        case 'x':
            op = DECOMPRESS;
            input_file_name = string(optarg);
            break;
        case '?':
        default:
            print_help_message();
            abort();
        }
    }

    if (output_defined == false)
        output_file_name =
            input_file_name.substr(0, input_file_name.find_last_of('.'));

    if (op == COMPRESS)
        output_file_name =
            output_file_name.substr(0, output_file_name.find_last_of('.')) +
            ".lz78";
    if (op == DECOMPRESS)
        output_file_name.substr(0, output_file_name.find_last_of('.')) + ".txt";

    args.input_file_name = input_file_name;
    args.output_file_name = output_file_name;
    args.op = op;

    return args;
}
