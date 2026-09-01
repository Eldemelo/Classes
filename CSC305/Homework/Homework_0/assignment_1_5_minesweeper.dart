import 'dart:math';
import 'dart:io';

class Minesweeper {
  final int rows;
  final int cols;
  final int mines;
  List<List<String>> board;
  List<List<bool>> revealed;

  Minesweeper(this.rows, this.cols, this.mines)
      : board = List.generate(rows, (_) => List.filled(cols, '0')),
        revealed = List.generate(rows, (_) => List.filled(cols, false)) {
    initializeBoard();
  }

  void initializeBoard() {
    placeMines();
    calculateNumbers();
  }

  void placeMines() {
    var random = Random();
    int placedMines = 0;

    while (placedMines < mines) {
      int row = random.nextInt(rows);
      int col = random.nextInt(cols);

      if (board[row][col] != 'M') {
        board[row][col] = 'M';
        placedMines++;
      }
    }
  }

  void calculateNumbers() {
    for (int row = 0; row < rows; row++) {
      for (int col = 0; col < cols; col++) {
        if (board[row][col] == 'M') continue;

        int mineCount = 0;
        for (int i = -1; i <= 1; i++) {
          for (int j = -1; j <= 1; j++) {
            int newRow = row + i;
            int newCol = col + j;
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && board[newRow][newCol] == 'M') {
              mineCount++;
            }
          }
        }
        board[row][col] = mineCount.toString();
      }
    }
  }

  bool revealCell(int row, int col) {
    if (row < 0 || row >= rows || col < 0 || col >= cols || revealed[row][col]) return false;

    revealed[row][col] = true;

    if (board[row][col] == 'M') {
      print('Game Over! You hit a mine.');
      return true;
    }

    if (board[row][col] == '0') {
      for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
          revealCell(row + i, col + j);
        }
      }
    }
    return false;
  }

  void printBoard() {
    for (int row = 0; row < rows; row++) {
      for (int col = 0; col < cols; col++) {
        if (revealed[row][col]) {
          stdout.write(board[row][col] + ' ');
        } else {
          stdout.write('* ');
        }
      }
      print('');
    }
  }
}

void main() {
  var game = Minesweeper(5, 5, 5);
  bool gameOver = false;

  while (!gameOver) {
    game.printBoard();
    print('Enter row and column to reveal (e.g., "2 3"):');
    var input = stdin.readLineSync();
    if (input == null) continue;

    var parts = input.split(' ');
    if (parts.length != 2) {
      print('Invalid input. Please enter two numbers separated by a space.');
      continue;
    }

    int row = int.parse(parts[0]);
    int col = int.parse(parts[1]);

    gameOver = game.revealCell(row, col);
  }

  print('Final Board:');
  game.printBoard();
}