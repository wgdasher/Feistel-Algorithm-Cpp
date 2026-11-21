#include "feistel.h"

static int m = 0x11B;

void feistel_16::process(const std::string& inName, const std::string& outName,
                         const std::string& key, bool decrypting) {
    if (key.empty()) throw std::invalid_argument("key must not be empty");
    const size_t rounds = key.size();          // <-- key length IS the round count

    std::ifstream in(inName, std::ios::binary);
    if (!in) throw std::runtime_error("could not open " + inName);
    std::vector<uint8_t> data((std::istreambuf_iterator<char>(in)),
                               std::istreambuf_iterator<char>());
    in.close();

    for (size_t i = 0; i + 1 < data.size(); i += 2) {
        uint8_t L = data[i];
        uint8_t R = data[i + 1];
        for (size_t r = 0; r < rounds; ++r) {
            size_t idx = decrypting ? (rounds - 1 - r) : r;
            uint8_t k = static_cast<uint8_t>(key[idx]);
            uint8_t newR = L ^ poly::multiply_galois(R, k, m);
            L = R;
            R = newR;
        }
        data[i]     = R;      // final swap
        data[i + 1] = L;
    }
    // odd trailing byte passes through untouched — see note

    std::ofstream out(outName, std::ios::binary);
    if (!out) throw std::runtime_error("could not open " + outName);
    out.write(reinterpret_cast<const char*>(data.data()),
              static_cast<std::streamsize>(data.size()));
    
}