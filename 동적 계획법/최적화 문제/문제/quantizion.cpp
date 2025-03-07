#include<iostream>
#include<string.h>
#include<cmath>
#include<algorithm>
using namespace std;

#define INF 987654321

//c: 테스트 케이스 수(<= 50), n: 수열의 길이(<= 100), s : 사용할 수
int c, n, s;
int num[101], pSum[101], pSqSum[101];

//부분합 저장
int precalc(){
    sort(num, num + n);
    pSum[0] = num[0];
    pSqSum[0] = num[0] * num[0];
    for(int i = 1; i < n; ++i){
        pSum[i] = pSum[i-1] + num[i];
        pSqSum[i] = pSqSum[i-1] + num[i] * num[i];
    }
}

//구간에서 최소 오차 제곱의 합 반환
//방정식: (x-a)^2 + (x-b)^2 + ... + (x-?)^2 = (size)x^2 -2(sum)x + sqSum 
int minError(int left, int right){
    //구간에서 부분합
    int sum = pSum[right] - (left == 0 ? 0 : pSum[left - 1]);
    int sqSum = pSqSum[right] - (left == 0 ? 0 : pSqSum[left - 1]);

    //m: 오차 제곱의 합이 최소가 되는 수(2차 방정식 미분을 통해 구할 수 있음)
    int m = int(0.5 + (double)sum / (right-left+1));

    //최소 오차 제곱의 합
    int ret = (right-left+1)*m*m - 2*sum*m + sqSum;
    return ret;
}

int cache[101][11]; 
//양자화를 통한 최소 오차 제곱의 합 반환
int quantization(int from, int parts){
    //기저 사례1: 양자화 끝난 경우
    if(from == n) return 0;
    //기저 사례2: 수가 남았는데 남은 묶음이 없는 경우우
    if(parts == 0) return INF;

    //memorization
    int& ret = cache[from][parts];
    if(ret != -1) return ret;

    ret = INF;
    for(int i = 1; from + i <= n; ++i){
        ret = min(ret, minError(from, from + i - 1) + quantization(from + i, parts - 1));
    }
    return ret;
}

int main() {
    cin >> c;
    for(int i = 0; i < c; ++i){
        cin >> n >> s;
        memset(cache, -1, sizeof(cache));
        for(int j = 0; j < n; ++j){
            cin >> num[j];
        }
        precalc();
        cout << quantization(0, s) << endl;
    }
    return 0;
}