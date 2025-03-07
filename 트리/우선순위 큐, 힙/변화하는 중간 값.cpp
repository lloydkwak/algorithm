#include<iostream>
#include<queue>
#include<vector>
using namespace std;

struct RNG {
    int seed, a, b;
    RNG(int _a, int _b) : a(_a), b(_b), seed(1983) {}
    int next() {
        int ret = seed;
        seed = ((seed * (long long)a) + b) % 20090711;
        return ret;
    }
};

//c : 테스트 케이스 수(<= 20), n : 수열의 길이(<=200000);
int c, n, a, b;

//수열을 두개로 나눈다.
int solve(RNG rng){
    priority_queue<int, vector<int>, greater<int>> leftHeap;     //내림차순 정렬
    priority_queue<int, vector<int>, less<int>> rightHeap;    //오름차순 정렬
    int ret = 0;
    //minHeap.top()은 항상 maxHeap.top() 보다 항상 커야 한다.
    for(int i = 1; i <= n; ++i){
        if(rightHeap.size() == leftHeap.size()) rightHeap.push(rng.next());
        else leftHeap.push(rng.next());
        if(!leftHeap.empty() && !rightHeap.empty() && leftHeap.top() < rightHeap.top()){
            int a = rightHeap.top(), b = leftHeap.top();
            rightHeap.pop(), leftHeap.pop();
            rightHeap.push(b);
            leftHeap.push(a);
        }
        ret = (ret + rightHeap.top()) % 20090711;
    }
    return ret;
}

int main(){
    cin >> c;
    for(int i = 0; i < c; ++i){
        cin >> n >> a >> b;
        RNG rng(a, b);
        cout << solve(rng) << endl;
    }
}