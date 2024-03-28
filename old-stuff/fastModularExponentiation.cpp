#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

void fastModularExponentiation(int a, int b, int c){
    //convert b to reverse binary array
    std::cout << "\n" << b << " = (";
    int b2 = b;
    int binaryNum[32];
    int i = 0;
    while (b2 > 0) {
        binaryNum[i] = b2 % 2;
        b2 = b2 / 2;
        i++;
    }
    
    for (int j = i - 1; j >= 0; j--) std::cout << binaryNum[j]; // print binary
    std::cout << ")2\n";

    //fast modular exponentiation algorithm
    int x = 1, power = a % c;

    for (int j = 0; j < i; j++){
        if (binaryNum[j] == 1){
            x = (x * power) % c;
        }
        std::cout << "x = " << x;
        for (int k = 0; k < 5 - std::to_string(x).length(); k++) std::cout << " ";
        std::cout << "|  ";

        power = (power * power) % c;
        std::cout << "power = " << power << '\n';
    }

    std::cout << "\n" << a << "^" << b << " (mod" << c << ") = " << x << "\n";
}

int main(){
    std::cout << "Enter a, b, and c in the expression a^b (mod c)" << "\n";
    int a, b, c;
    std::cin >> a >> b >> c;

    fastModularExponentiation(a, b, c);
}
