#include "includes.h"

int main(int argc, char *argv[]) {
    struct cl_args args = get_execution_options(argc, argv);

    if (args.op == COMPRESS) {
        ifstream input_file(args.input_file_name);
        string input = stream_as_string(input_file);

        vector<pair<int, char>> encoded = LZ78::encode(input);

        save_encoded_file(args.output_file_name, encoded);
    }

    else if (args.op == DECOMPRESS) {
        vector<pair<int, char>> encoded =
            read_encoded_file(args.input_file_name);
        string decoded = LZ78::decode(encoded);

        ofstream output_file(args.output_file_name);
        output_file << decoded;
    }

    return 0;
}
