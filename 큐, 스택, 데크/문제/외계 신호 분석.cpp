#include<iostream>
#include<string>
#include<queue>
#include<cmath>
using namespace std;

//c : 테스트 케이스 수(<=50), k : 찾고 싶은 부분수열의 합, n : 신호 길이
int c, k, n;

//난수 생성기(선형 합동 난수 생성기기: LCG)
struct RNG {
    unsigned seed;
    RNG() : seed(1983) {}
    unsigned next() {
        unsigned ret = seed;
        seed = ((seed * 214013u) + 2531011u);
        return ret % 10000 + 1;
    }
};


int analyze(){
    RNG rng;
    queue<int> signal;
    int ret = 0, sum = 0;
    for(int j = 0; j < n; ++j){
        int num = rng.next();
        sum += num;
        signal.push(num);

        //구간의 합이 k 보다 클 때
        while(sum > k){
            sum -= signal.front();
            signal.pop();
        }

        if(sum == k) ++ret;
    }
    return ret;
}

int main() {
    cin >> c;
    for(int i = 0; i < c; ++i){
        cin >> k >> n;
        cout << analyze() << endl;
    }
	return 0;
}