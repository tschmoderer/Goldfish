#pragma once

#include <array>
#include "operations.hpp"
#include "bitboard.hpp"

namespace goldfish {

enum File {
    FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, NO_FILE
};


ENABLE_INCR_OPERATORS_ON(File)


namespace Files {

constexpr int VALUES_SIZE = 8;
constexpr std::array<File, VALUES_SIZE> values = {
    FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H
};

inline constexpr bool is_valid(File file) {
    return file != File::NO_FILE;
}

inline U64 file_bb(File f) {
  return Bitboard::FileABB << f;
}

}
}

