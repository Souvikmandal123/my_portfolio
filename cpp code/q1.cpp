#include <bits/stdc++.h>
using namespace std;
void solve(vector<int>powers,int &teamAPower,int &teamBPower,int N){
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
}
bool myComp(int a, int b){
return abs(a) > abs(b) || (abs(a) == abs(b) && a > b);
}
int main() {
    int N;
    cin >> N;
    vector<int> powers(N); 
    for (int i = 0; i < N; i++) { cin >> powers[i];
    }    
    int teamAPower = 0;
    int teamBPower = 0;
    sort(powers.begin(), powers.end(),myComp);
    solve(powers,teamAPower,teamBPower,N);
    int powerDifference = abs(teamAPower - teamBPower);
    cout << powerDifference << endl; 
    return 0;
}