#include<iostream>
#include<map>
#include<stack>
using namespace std;

using KeyType = int;

//c : 테스트 케이스 수(<= 50), n : 배열의 길이(<= 50,000), move : 움직인 횟수 저장 배열
int c, n, moved[50001], ans[50001];

//트립 노드 구현
struct Node {
    KeyType key;
    int priority, size;
    Node *left, *right;
    
    //생성자
    Node(const KeyType& _key) 
    : key(_key), priority(rand()), size(1), left(NULL), right(NULL) 
    {}

    //left, right, size 세팅
    void setLeft(Node* newLeft) { left = newLeft; colcSize(); }
    void setRight(Node* newRight) { right = newRight; colcSize(); }
    void colcSize(){
        size = 1;
        if(left) size += left->size;
        if(right) size += right->size;
    }
};

//root를 루트로 하는 트립을 key를 기준으로 나눔
using NodePair = pair<Node*, Node*>;
NodePair split(Node* root, KeyType key){
    if(root == NULL) return NodePair(NULL, NULL);
    //root->key가 key 보다 작으면 오른쪽 서브트리를 자른다
    if(root->key < key){
        NodePair rightSub = split(root->right, key);
        root->setRight(rightSub.first);
        return NodePair(root, rightSub.second);
    }
    //root->key가 key 보다 크거나 같으면 왼쪽 서브트리를 자른다
    NodePair leftSub = split(root->left, key);
    root->setLeft(leftSub.second);
    return NodePair(leftSub.first, root);
}

//root를 루트로 하는 트립에 node 삽입후 root 반환
Node* insert(Node* root, Node* node){
    if(root == NULL) return node;
    //priority 비교를 통해 부모/자식 선택
    if(root->priority < node->priority){
        NodePair splitted = split(root, node->key);
        node->setLeft(splitted.first);
        node->setRight(splitted.second);
        return node;
    }
    else if(node->key < root->key){
        root->setLeft(insert(root->left, node));
    }
    else {
        root->setRight(insert(root->right, node));
    }
    return root;
}

//트립 a, b 합치기(max(a) < min(b))
Node* merge(Node* a, Node* b) {
    if(a == NULL) return b;
    if(b == NULL) return a;
    if(a->priority < b->priority) {
        b->setLeft(merge(a, b->left));
        return b;
    }
    a->setRight(merge(a->right, b));
    return a;
}

//root를 루트로 하는 트립에서 key를 지우고 결과 트립의 루트 반환
Node* erase(Node* root, KeyType key) {
    if(root == NULL) return root;
    //root를 지우고 양 서브트리를 합친 뒤 반환
    if(root->key == key) {
        Node* ret = merge(root->left, root->right);
        delete root;
        return ret;
    }
    if(key < root->key) root->setLeft(erase(root->left, key));
    else root->setRight(erase(root->right, key));
    return root;
}

//root를 루트로 하는 트립 중에서 k번째 원소 반환
Node* kth(Node* root, int k){
    //왼쪽 서브트리 크기 계산
    int leftSize = 0;
    if(root->left != NULL) leftSize = root->left->size;
    if(k <= leftSize) return kth(root->left, k);
    if(k == leftSize + 1) return root;
    return kth(root->right, k - leftSize - 1);
}

void solve(){
    Node* condidates = NULL;
    for(int i = 1; i <= n; ++i){
        condidates = insert(condidates, new Node(i));
    }
    for(int i = n - 1; i >= 0; --i){
        Node* k = kth(condidates, i + 1 - moved[i]);
        ans[i] = k->key;
        condidates = erase(condidates, k->key);
    }
}

int main(){
    cin >> c;
    for(int i = 0; i < c; ++i){
        cin >> n;
        for(int j = 0; j < n; ++j){
            cin >> moved[j];
        }
        solve();
        for(int j = 0;  j < n; ++j)
            cout << ans[j] << ' ';
        cout << endl;
    }
}