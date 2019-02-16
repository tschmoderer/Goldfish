#pragma once

#include <array>
#include "operations.hpp"
#include "bitboard.hpp"

namespace goldfish {

enum Rank {
    RANK_1 = 0, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, NO_RANK
};


ENABLE_FULL_OPERATORS_ON(Rank)

namespace Ranks {

constexpr int VALUES_SIZE = 8;
constexpr std::array<Rank, VALUES_SIZE> values = {
    RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8,
};

inline constexpr bool is_valid(Rank rank) {
    return rank != Rank::NO_RANK;
}

inline constexpr U64 rank_bb(Rank r) {
    return Bitboard::Rank1BB << (8 * r);
}

inline constexpr U64 range(Rank from, Rank to = Rank::NO_RANK) {
    U64 res = rank_bb(from);
    for (; from != to; ++from)
        res |= rank_bb(from);
    return res;
}

}
}



