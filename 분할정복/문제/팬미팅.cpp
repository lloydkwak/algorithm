#include<iostream>
#include<string>
#include<vector>
using namespace std;

//c: 테스트 케이스 수
int c;

//각 자리 곱한 값의 합
vector<int> multiply(const vector<int>& a, const vector<int>& b){
    vector<int> c(a.size() + b.size() + 1, 0);
    for(int i = 0; i < a.size(); ++i){
        for(int j = 0; j < b.size(); ++j){
            c[i + j] += a[i] * b[j];
        }
    }
    return c;
}

//큰자리 자연수를 나타네는 두 수열 a,b에 대하여 a += b * (10^k) 구현
void addTo(vector<int>& a, const vector<int>& b, int k){
    if (a.size() < b.size() + k)
    a.resize(b.size() + k, 0);
    
    for (int i = 0; i < b.size(); ++i){
        a[i + k] += b[i];
    }
}

//큰자리 자연수를 나타네는 두 수열 a,b에 대하여 a -= b; 구현 (a>=b)
void subFrom(vector<int>& a, const vector<int>& b){
    for (int i = 0; i < b.size(); ++i){
        a[i] -= b[i];
    }
}

vector<int> karatsuba(const vector<int>& a, const vector<int>& b){
    //b가 a 보다 자릿수가 큰경우 서로 바꿈꿈
    if(a.size() < b.size()) karatsuba(b, a);
    
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
    vector<int> z2 = karatsuba(a1, b1);
    //z0 = a0*b0
    vector<int> z0 = karatsuba(a0, b0);
    //a0 = a0+a1, b0 = b0+b1
    addTo(a0, a1, 0); addTo(b0, b1, 0);
    //z1 = (a0*b0) - z0 - z2;
    vector<int> z1 = karatsuba(a0, b0);
    subFrom(z1, z0); subFrom(z1, z2);

    //카라츠비 공식으로 a, b 곱하기
    vector<int> ret;
    addTo(ret, z0, 0);
    addTo(ret, z1, mid);
    addTo(ret, z2, mid*2);

    return ret;
}

//모든 멤버가 포옹하는 경우의 수를 계산하는 함수
int allHugs(string& members, const string& fans){
    int nm = members.size(), nf = fans.size();
    //주어진 성별에 대한 정보를 정수(남:1, 여:0)으로 표현
    vector<int> m(nm), f(nf);

    //m은 원소들은 뒤집고 f는 그대로 둔다
    for(int i = 0; i < nm; ++i){
        m[i] = (members[i]=='M');
    }
    for(int i = 0; i < nf; ++i){
        f[i] = (fans[nf-i-1]=='M');
    }

    //karatsuba 알고리즘을 이용(자리 올림 생략)
    vector<int> c = karatsuba(f, m);
    //ret: 모든 멤버가 포옹하는 총 횟수
    int ret = 0;
    for(int i = nm - 1; i < nf; ++i){
        if(c[i] == 0) ++ret;
    }
    return ret;
}

int main(){
    cin >> c;
    for(int i = 0; i < c; i++){
        string members, fans;
        cin >> members;
        cin >> fans;
        cout << allHugs(members, fans) << endl;
    }
    return 0;
}