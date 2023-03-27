// https://www.spoj.com/problems/NDIV/
#include <iostream>
using namespace std;
#include "math.h"

int main(){
    int a,b,n,div,ans;
    cin>>a;
    cin>>b;
    cin>>n;
    ans=0;
    for(int i=a; i<=b; i++){
        div=0;
        for(int j=1; j*j<=i; j++){
            if (i%j==0){
                if (i/j==j){
                   div++;
                }else {
                    div+=2;
                }
            } 
        }
        if (div == n){ ans++;
        }
    }
    cout<< ans;

    return 0;
}
