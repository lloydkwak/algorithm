/*
1. isChild() 함수 까지만 구현하고 암시적으로 트리를 구성하여 정답을 찾을 수 있다.

height 함수를 변형하면 됨.

for(int i = 0; i < n; ++i){
    if(isChild(root, i))
        heights.push_back(height(i));
    }

시간은 조금 더 걸린다다
-----------------------------------------------------------------------------------
2. 트리를 잎에서 부터 거꾸로 생성하면 시간 복잡도를 줄일 수 있다(O(n^3) ---> O(n^2))

방법은 나중에 공부부

*/

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

//c : 테스트 케이스 수(<= 100), n : 노드 수(<= 100)
int c, n;
//(x, y) : 성 벽 중심, r : 반지름
int x[101], y[101], r[101];
int longest;

//트리 노드를 표현한 객체체
struct fortress {
    vector<fortress*> children;
};

int sqr(int x){
    return x*x;
}

//a, b 중심 사이의 거리 제곱
int sqrdist(int a, int b){
    return sqr(y[a] - y[b]) + sqr(x[a] - x[b]);
}

//a가 b를 포함 하는지 확인인
bool encloses(int a, int b){
    return r[a] > r[b] && sqrdist(a, b) < sqr(r[a] - r[b]);
}

bool isChild(int parent, int child){
    //포함되지 않은 경우
    if(!encloses(parent, child)) return false;
    //사이에 성벽이 있는 경우
    for(int i = 0; i < n; ++i){
        if(i != parent && i != child && encloses(parent, i) && encloses(i, child))
            return false;
    }
    return true;
}

//root를 루트로 가지는 트리 생성
fortress* getTree(int root){
    fortress* ret = new fortress();
    for(int i = 0; i < n; ++i){
        if(isChild(root, i)){
            ret->children.push_back(getTree(i));
        }
    }
    return ret;
}

//root를 루트로 하는 트리의 높이
int height(fortress* root){
    //각 자식을 루트로 하는 서브트리 높이 계산
    vector<int> heights;
    for(int i = 0; i < root->children.size(); ++i){
        heights.push_back(height(root->children[i]));
    }
    //현재 노드가 잎일 경우
    if(heights.empty()) return 0;
    sort(heights.begin(), heights.end());
    if(heights.size() >= 2){
        longest = max(longest, 2 + heights[heights.size() - 1] + heights[heights.size() - 2]);
    }
    return heights.back() + 1;
}

//두 노드 사이의 가장 긴 경로
int findLongest(fortress* root){
    longest = 0;
    int ret = height(root); //트리의 높이, 구하는 과정에서 longest는 가장긴 잎-잎 거리가 된다.
    return max(ret, longest);
}

int main(){
    cin >> c;
    for(int i = 0; i < c; ++i){
        cin >> n;
        for(int j = 0; j < n; ++j){
            cin >> x[j] >> y[j] >> r[j];
        }
        cout << findLongest(getTree(0)) << endl;
    }
    return 0;
}