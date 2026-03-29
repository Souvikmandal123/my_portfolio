#include<bits/stdc++.h>
using namespace std;
bool solve(string seq){
    for(int i=0;i<seq.length();i++){
        for(int j=i+1;j<seq.length();j++){
            if(seq[i]==seq[j]){
                cout<<"New Language Error"<<endl;
                return false;
            }
        }
    }
    return true;
}
int main(){
    string seq;
    string str;
    cin>>seq;
    cin>>str;
    if(solve(seq)!=false){
        string strValue = "";
        for(int i)
    }
}