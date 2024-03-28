#include <iostream>
#include <stdlib.h>

int montyHall(){
    int prizeDoor = rand() % 3 + 1;
    int chooseDoor = rand() % 3 + 1;
    int removeDoor = 0;
    for (int j = 1; j < 4; j++){
        if (j != prizeDoor && j != chooseDoor) {
            removeDoor = j;
            break;
        }
    }
    for (int j = 1; j < 4; j++){
        if (j != removeDoor && j != chooseDoor) {
            chooseDoor = j;
            break;
        }
    }
       

    return chooseDoor == prizeDoor;
       
}

double winrate(int it){
    double wins = 0, losses;
    for (int i = 0; i < it; i++){
        if (montyHall()) wins++;
        else losses++;

        if (i % 10000 == 0){
            printf("\rPercent: %f%%    Win Rate: %f%%", (double)i/it * 100, wins/(wins + losses) * 100);
            fflush(stdout);
        }
        if (i == it - 1){
            printf("\rPercent: 100%%    Win Rate: %f%%", wins/(wins + losses) * 100);
            fflush(stdout);
        }
    }

    return wins/(wins + losses) * 100;

}

int main(){
    std::cout << "Input number of runs\n";

    int runs;
    std::cin >> runs;
    std::cout << "\n";
    double winRate = winrate(runs);

    std::cout << "\n\nFinal Win Rate: " << (int)(winRate + 0.5) << "%";
}