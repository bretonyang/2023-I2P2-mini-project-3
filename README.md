# NTHU I2P3 MiniChess AI

## state value function

Assign a material value to each piece.
The state value is the sum of the value of pieces on the board

```h
/** state.hpp */
const int material_value[7] = {0, 2, 6, 7, 8, 20, 1000}; // empty, pawn, rook, knight, bishop, queen, king
```

```cpp
/** state.cpp */

int State::evaluate(){
  // [TODO] design your own evaluation function
  if (game_state == WIN) return INF;

  int value = 0;
  for(int i = 0; i < BOARD_H; i++) {
    for(int j = 0; j < BOARD_W; j++) {
      value += material_value[(int) board.board[player][i][j]];
      value -= material_value[(int) board.board[1 - player][i][j]];
    }
  }
  return value;
}
```

## Minimax tree search
