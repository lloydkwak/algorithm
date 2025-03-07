#include<iostream>
using namespace std;

//1+2+3+...+n을 분할 정복을 통해 반환
int fastSum(int n) {
    //기저 사례: n이 1인 경우
    if(n==1) return 1;
    //n이 홀수인 경우
    if(n%2==1) return fastSum(n-1) + n;
    //1+2+3+...+n을 절반으로 분할하고 병합한 수식
    return 2*fastSum(n/2) + (n/2)*(n/2);
}

int main() {
    //n: 자연수
    int n;
	cin >> n;
    cout << fastSum(n) << endl;
	return 0;
}