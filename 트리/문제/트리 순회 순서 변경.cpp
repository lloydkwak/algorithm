#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

//c : 테스트 케이스 수(<= 100), n : 노드 수(<= 100)
int c, n;

//구간에 맞게 나눈 배열 반환
vector<int> slice(const vector<int>& v, int start, int end){
    return vector<int>(v.begin() + start, v.begin() + end);
}

void printPostorder(const vector<int>& preorder, const vector<int>& inorder){
    const int N = preorder.size();
    //기저 사례: 트리가 비었있을때
    if(preorder.empty()) return;
    //루트 찾기
    const int root = preorder[0];
    //트리 왼쪽 크기 : 중위 탐색 결과에서 root를 찾고 L, R로 나누면 된다
    const int L = find(inorder.begin(), inorder.end(), root) - inorder.begin();
    const int R = N - L - 1;
    //왼쪽, 오른쪽 서부트리 출력 결과 순서대로 출력
    printPostorder(slice(preorder, 1, L + 1), slice(inorder, 0, L));
    printPostorder(slice(preorder, L + 1, N), slice(inorder, L + 1, N));
    //inorder 이므로 root를 마지막으로 출력
    cout << root << ' ';
}

int main(){
    cin >> c;
    for(int i = 0; i < c; ++i){
        cin >> n;
        //preorder : 전위 순환, inorder : 중위 순환, postorder : 후위 순환
        vector<int> preorder, inorder;
        int num;
        for(int j = 0; j < n; ++j){
            cin >> num;
            preorder.push_back(num);
        }
        for(int j = 0; j < n; ++j){
            cin >> num;
            inorder.push_back(num);
        }
        printPostorder(preorder, inorder);
        cout << endl;
    }
    return 0;
}