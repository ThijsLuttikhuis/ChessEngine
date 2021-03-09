cmake_minimum_required(VERSION 3.14)
project(ChessEngine)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "-O0")

set(INCLUDE_ENGINE
        engines/Engine.cpp
        engines/Engine.h

        # a human player
        engines/player/Player.cpp
        engines/player/Player.h

        # random moves
        engines/random/RandomEngine.cpp
        engines/random/RandomEngine.h
        )

set(INCLUDE_UTILITIES
        utilities/CountLegalMoves.cpp
        utilities/CountLegalMoves.h
        )

set(INCLUDE_CHESSBOARD
        chessboard/Board.cpp
        chessboard/Board.h

        # types of pieces
        chessboard/pieces/JumpPiece.cpp
        chessboard/pieces/JumpPiece.h
        chessboard/pieces/SlidePiece.cpp
        chessboard/pieces/SlidePiece.h

        # pieces
        chessboard/pieces/Piece.cpp
        chessboard/pieces/Piece.h
        chessboard/pieces/Pawn.cpp
        chessboard/pieces/Pawn.h
        chessboard/pieces/Knight.cpp
        chessboard/pieces/Knight.h
        chessboard/pieces/Bishop.cpp
        chessboard/pieces/Bishop.h
        chessboard/pieces/Rook.cpp
        chessboard/pieces/Rook.h
        chessboard/pieces/Queen.cpp
        chessboard/pieces/Queen.h
        chessboard/pieces/King.cpp
        chessboard/pieces/King.h
        )

set(INCLUDE_ALL
        ${INCLUDE_CHESSBOARD}
        ${INCLUDE_UTILITIES}
        ${INCLUDE_ENGINE}
        )

add_executable(chessEngine main.cpp ${INCLUDE_ALL})
add_executable(count count.cpp ${INCLUDE_ALL})
add_executable(randomVsRandom random.cpp ${INCLUDE_ALL})
