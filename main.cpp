#include <iostream>
#include <string>
#include "feistel.h"

static void usage(const char* prog) {
    std::cerr << "ERROR, incorrect arguments\n"
              << "Usage: " << prog << " <input_file> <output_file> <key> <\"e\"|\"d\">\n";
}

int main(int argc, char* argv[]) {
    const char* prog = (argc > 0) ? argv[0] : "feistel";
    if (argc != 5) { usage(prog); return 1; }

    const std::string inName  = argv[1];
    const std::string outName = argv[2];
    const std::string key     = argv[3];
    const std::string mode    = argv[4];

    bool decrypting;
    if      (mode == "e") decrypting = false;
    else if (mode == "d") decrypting = true;
    else { std::cerr << "ERROR, mode must be \"e\" or \"d\"\n"; usage(prog); return 1; }

    try {
        feistel_16::process(inName, outName, key, decrypting);
    } catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << "\n";
        return 1;
    }
    return 0;
}