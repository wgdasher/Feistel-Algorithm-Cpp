#ifndef FEISTEL_H
#define FEISTEL_H

#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <string>
#include <cstdint>
#include "poly.h"

namespace feistel_16
{
    void process(const std::string& inName, const std::string& outName, const std::string& key, bool decrypting);
}

#endif