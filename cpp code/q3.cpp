#include <bits/stdc++.h>
using namespace std;
int main() {
    int N;
    cin >> N;
    vector powers(N); 
    for (int i = 0; i < N; i++) { cin >> powers[i];
    }    
    int teamAPower = 0;
    int teamBPower = 0;
    sort(powers.begin(), powers.end(), [](int a, int b) {
        return abs(a) > abs(b) || (abs(a) == abs(b) && a > b);
    });   
    bool ironmanTurn = true;    
    for (int i = 0; i < N; i++) {
        if (ironmanTurn) {
            teamAPower += powers[i];
        }
        else {
            teamBPower += powers[i];
        }
        ironmanTurn = !ironmanTurn;
    }    
    int powerDifference = abs(teamAPower - teamBPower);
    cout << powerDifference << endl; 
   return 0;
}