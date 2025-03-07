#include<iostream>
#include<string.h>
#include<limits>
using namespace std;

//c: 테스트 케이스 수(<= 50), n, m: 수열의 크기(<= 100)
//s1, s2: 수열
int c, n, m;
int s1[101], s2[101];
//범위가 32비트 정수이므로 최소는 64비트로 설정
const long long NEGINF = numeric_limits<long long>::min();

//cache : 합친 LIS의 최대 길이 저장
int cache[101][101];

int jlis(int idx1, int idx2){
    //memrization
    int& ret = cache[idx1 + 1][idx2 + 1];
    if(ret != -1){
        return ret;
    }

    //s1[idx1], s2[idx2] 는 이미 포함이므로 ret은 2
    ret = 2;
    //현재 합친 LIS에서 가장 큰 원소를 구함
    long long a = (idx1 == -1 ? NEGINF : s1[idx1]);
    long long b = (idx2 == -1 ? NEGINF : s2[idx2]);
    long long maxNum = max(a, b);

    for(int i = idx1 + 1; i < n; ++i){
        if(maxNum < s1[i]){
            ret = max(ret, 1 + jlis(i, idx2));
        }
    }
    for(int i = idx2 + 1; i < m; ++i){
        if(maxNum < s2[i]){
            ret = max(ret, 1 + jlis(idx1 , i));
        }
    }
    return ret;
}

int main() {
    cin >> c;
    for(int i = 0; i < c; ++i){
        cin >> n >> m;
        memset(s1, 0, sizeof(s1));
        memset(s2, 0, sizeof(s2));
        memset(cache, -1, sizeof(cache));
        for(int j = 0; j < n; j++){
            cin >> s1[j];
        }
        for(int j = 0; j < m; j++){
            cin >> s2[j];
        }
        cout << jlis(-1, -1)-2 << endl;
    }
    return 0;
}