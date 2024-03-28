import java.lang.Math;
import java.util.Scanner;

class Main {
    public static int montyHall (int numOfRuns){
        int wins = 0, losses = 0;

        for (int i = 0; i < numOfRuns; i++){
            int prizeDoor = (int) (Math.random() * 3) + 1;
            int chooseDoor = (int) (Math.random() * 3) + 1;
            int removeDoor = 0;
            for (int j = 1; j < 4; j++){
                if (j != prizeDoor && j != chooseDoor) {
                    removeDoor = j;
                    break;
                }
            }
            for (int j = 1; j < 4; j++){
                if (j != removeDoor && j != chooseDoor){
                    chooseDoor = j;  
                    break;
                }
                
            }
            
            if (chooseDoor == prizeDoor) wins++;
            else losses++;
        }

        int winRate = (int)((double) wins/(wins + losses) * 100);
        return winRate;
       
    }
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        System.out.println("Input number of runs");
        int runs = input.nextInt();

        System.out.println("Win Rate: " + montyHall(runs) + "%");

        input.close();
    }
}

