#include <bits/stdc++.h>
using namespace std;

char *s[]={"I","IV","V","IX","X","XL","L","XC","C"};
int sn[9]={1,4,5,9,10,40,50,90,100};
string a;
char an[5]={'I','V','X','L','C'};
int ans[5];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin>>n;
    int num=n;
    while(num) {
        n=num;
        for (int i=8;i>=0;i--) {
            while (n>=sn[i]) {
                n-=sn[i];
                a+=s[i];
            }
        }
        for (int i=0;i<a.size();i++) {
            for (int j=0;j<5;j++) {
                if (a[i]==an[j]) {
                    ans[j]++;
                }
            }
        }
        num--;
        a.clear();
    }
    for (int i=0;i<5;i++) {
        cout<<ans[i]<<' ';
    }
}
