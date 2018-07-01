/*
 * Copyright (C) 2013-2016 Phokham Nonava
 *
 * Use of this source code is governed by the MIT license that can be
 * found in the LICENSE file.
 */

#include "notation.hpp"
#include "file.hpp"
#include "rank.hpp"

#include "gtest/gtest.h"

using namespace goldfish;

TEST(notationtest, test_standard_position
) {
Position position(Notation::to_position(Notation::STANDARDPOSITION));

// Test pawns
for (
auto file
: File::values) {
EXPECT_EQ(+Piece::WHITE_PAWN, position.board[
Square::value_of(file, Rank::R2
)]);
EXPECT_EQ(+Piece::BLACK_PAWN, position.board[
Square::value_of(file, Rank::R7
)]);
}

// Test knights
EXPECT_EQ(+Piece::WHITE_KNIGHT, position.board[Square::B1]);
EXPECT_EQ(+Piece::WHITE_KNIGHT, position.board[Square::G1]);
EXPECT_EQ(+Piece::BLACK_KNIGHT, position.board[Square::B8]);
EXPECT_EQ(+Piece::BLACK_KNIGHT, position.board[Square::G8]);

// Test bishops
EXPECT_EQ(+Piece::WHITE_BISHOP, position.board[Square::C1]);
EXPECT_EQ(+Piece::WHITE_BISHOP, position.board[Square::F1]);
EXPECT_EQ(+Piece::BLACK_BISHOP, position.board[Square::C8]);
EXPECT_EQ(+Piece::BLACK_BISHOP, position.board[Square::F8]);

// Test rooks
EXPECT_EQ(+Piece::WHITE_ROOK, position.board[Square::A1]);
EXPECT_EQ(+Piece::WHITE_ROOK, position.board[Square::H1]);
EXPECT_EQ(+Piece::BLACK_ROOK, position.board[Square::A8]);
EXPECT_EQ(+Piece::BLACK_ROOK, position.board[Square::H8]);

// Test queens
EXPECT_EQ(+Piece::WHITE_QUEEN, position.board[Square::D1]);
EXPECT_EQ(+Piece::BLACK_QUEEN, position.board[Square::D8]);

// Test kings
EXPECT_EQ(+Piece::WHITE_KING, position.board[Square::E1]);
EXPECT_EQ(+Piece::BLACK_KING, position.board[Square::E8]);

EXPECT_EQ(8 * PieceType::PAWN_VALUE
+ 2 * PieceType::KNIGHT_VALUE
+ 2 * PieceType::BISHOP_VALUE
+ 2 * PieceType::ROOK_VALUE
+ PieceType::QUEEN_VALUE
+ PieceType::KING_VALUE,
position.material[Color::WHITE]);
EXPECT_EQ(8 * PieceType::PAWN_VALUE
+ 2 * PieceType::KNIGHT_VALUE
+ 2 * PieceType::BISHOP_VALUE
+ 2 * PieceType::ROOK_VALUE
+ PieceType::QUEEN_VALUE
+ PieceType::KING_VALUE,
position.material[Color::BLACK]);

// Test castling
EXPECT_NE(+Castling::NO_CASTLING, position.
castling_rights &Castling::WHITE_KING_SIDE
);
EXPECT_NE(+Castling::NO_CASTLING, position.
castling_rights &Castling::WHITE_QUEEN_SIDE
);
EXPECT_NE(+Castling::NO_CASTLING, position.
castling_rights &Castling::BLACK_KING_SIDE
);
EXPECT_NE(+Castling::NO_CASTLING, position.
castling_rights &Castling::BLACK_QUEEN_SIDE
);

// Test en passant
EXPECT_EQ(+Square::NO_SQUARE, position.enpassant_square);

// Test active color
EXPECT_EQ(+Color::WHITE, position.active_color);

// Test half move clock
EXPECT_EQ(0, position.halfmove_clock);

// Test full move number
EXPECT_EQ(1, position.

get_fullmove_number()

);
}
