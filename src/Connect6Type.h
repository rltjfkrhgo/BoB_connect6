#ifndef CONNECT6TYPE_H
#define CONNECT6TYPE_H

enum Piece  {EMPTY, BLACK, WHITE};
enum Status {READY, START, BLACK1, BLACK2, WHITE1, WHITE2,
             BLACKWIN, WHITEWIN};

constexpr int BOARDSIZE = 19;

Piece operator!(Piece piece);

#endif // CONNECT6TYPE_H
