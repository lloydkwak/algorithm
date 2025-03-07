#include<iostream>
#include<vector>
using namespace std;

//O(n^2) 큰수 곱셈

//자릿수 올림
void normalize(vector<int>& num){
    num.push_back(0);
    for(int i = 0; i < num.size(); ++i){
        if(num[i]<0){
            int borrow = (abs(num[i]) + 9) / 10;
            num[i+1] -= borrow;
            num[i] += borrow/10;
        } else {
            num[i+1] += num[i]/10;
            num[i] = num[i]%10;
        }
    }
    while(num.size() > 1 && num.back() == 0) num.pop_back();
}
//각 자리 곱한 값의 합
vector<int> multiply(const vector<int>& a, const vector<int>& b){
    vector<int> c(a.size()+b.size()+1, 0);
    for(int i = 0; i < a.size(); ++i){
        for(int j = 0; j < b.size(); ++j){
            c[i+j] += a[i]*b[j];
        }
    }
    normalize(c);
    return c;
}

//카르츠바 알고리즘
/*
a = {a1*10^(n/2)} + a0, b = {b1*10^(n/2)} + b0
a * b = (a1*b1)*10^n + (a1*b0 + b1*a0)+10^(n/2) + a0*b0   ===> O(n^2)

z0 = a0*b0
z1 = a1*b0 + a0*b1 = (a0+a1)*(b0+b1) -z0 -z1
z2 = a1*b1

a * b = z2*10^n + z1*10^(n/2) +z0   ===> 곱하기 횟수를 4번에서 3번으로 줄임 O(n^lg3)
*/

//큰자리 자연수를 나타네는 두 수열 a,b에 대하여 a += b * (10^k) 구현
void addTo(vector<int>& a, const vector<int>& b, int k){
    if (a.size() < b.size() + k)
    a.resize(b.size() + k, 0);
    
    for (int i = 0; i < b.size(); i++){
        a[i + k] += b[i];
    }
    
    normalize(a);
}

//큰자리 자연수를 나타네는 두 수열 a,b에 대하여 a -= b; 구현 (a>=b)
void subFrom(vector<int>& a, const vector<int>& b){
    for (int i = 0; i < b.size(); i++){
        a[i] -= b[i];
    }
    normalize(a);
}

vector<int> karatusba(const vector<int>& a, const vector<int>& b){
    //b가 a 보다 자릿수가 큰경우 서로 바꿈꿈
    if(a.size() < b.size()) karatusba(b, a);
    
    //기저 사례1: a 또는 b가 비어있는 경우
    if(a.size() == 0 || b.size() == 0) return vector<int> ();
    //기저 사례2: a가 짧은 경우(a<=50) O(n^2) 알고리즘으로 해결
    if(a.size() <= 50) return multiply(a, b);
    
    //a, b를 a(자릿수가 큰수)를 기준으로 절반 자리와 나머지로 분리
    int mid = a.size() / 2;
    vector<int> a0(a.begin(), a.begin() + mid);
    vector<int> a1(a.begin() + mid, a.end());
    vector<int> b0(b.begin(), b.begin() + min<int>(b.size(), mid));
    vector<int> b1(b.begin() + min<int>(b.size(), mid), b.end());

    //z2 = a1*b1
    vector<int> z2 = karatusba(a1, b1);
    //z0 = a0*b0
    vector<int> z0 = karatusba(a0, b0);
    //a0 = a0+a1, b0 = b0+b1
    addTo(a0, a1, 0); addTo(b0, b1, 0);
    //z1 = (a0*b0) - z0 - z2;
    vector<int> z1 = karatusba(a0, b0);
    subFrom(z1, z0); subFrom(z1, z2);

    //카라츠비 공식으로 a, b 곱하기
    vector<int> ret;
    addTo(ret, z0, 0);
    addTo(ret, z1, mid);
    addTo(ret, z2, mid*2);

    return ret;
}