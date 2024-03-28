import java.util.*;

public class TicTacToe {
    
    public static void displayBoard(char[][] board){
        System.out.println("\n   0   1   2 ");
        for (int i = 0; i < 3; i++){
            if (i != 0){
                System.out.println("\n   ————————— ");
            }

            System.out.print(i + " ");
            for (int j = 0; j < 3; j++){
                System.out.print(" " + board[i][j] +  " ");
                if (j != 2){
                    System.out.print("|");
                }
            }
            
        }
        System.out.println();
    }

    public static boolean checkWin(char[][] board, int row, int col, char inputChar){
        //check row
        if (board[row][0] == board[row][1] && board[row][0] == board[row][2]){
            return true;
        }

        //check column
        if (board[0][col] == board[1][col] && board[0][col] == board[2][col]){
            return true;
        }

        //check diagonals
        if (row == col){ 
            if (board[1][1] == board[2][2] && board[1][1] == board[3][3]){
                return true;
            }
        }
        if (row + col == 2){
            if (board[2][0] == board[1][1] && board[2][0] == board[0][2]){
                return true;
            }
        }

        return false;
    }

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        char[][] board = {
            {' ', ' ', ' '},
            {' ', ' ', ' '},
            {' ', ' ', ' '}
        };

        displayBoard(board);
        
        char inputChar = 'X';
        int moveCount = 0;
        while (true) {
            System.out.println("\nEnter row (0-2) and column (0-2)");
            System.out.print("Row: ");
            int row = sc.nextInt();
            System.out.print("Column: ");
            int col = sc.nextInt();
            if (board[row][col] != ' '){
                System.out.println("That ain't right. Try again.");
                continue;
            }
            board[row][col] = inputChar;
            moveCount++;
            displayBoard(board);

            if (checkWin(board, row, col, inputChar)){
                System.out.println("GAME OVER - gotta give it to whoever played " + inputChar);
                break;
            }
            else if (moveCount == 9){
                System.out.println("DRAW!");
                break;
            }
            inputChar = (inputChar == 'X') ? 'O' : 'X';
        }

        sc.close();
    }
}