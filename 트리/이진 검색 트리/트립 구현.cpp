#include<iostream>
using namespace std;

using KeyType = int;
//트립의 한 노드를 저장
struct Node {
    //노드에 저장된 원소
    KeyType key;
    //이 노드의 우선순위(priority)
    //이 노드를 루트로 하는 서브트리 크기(size)
    int priority, size;
    //두 자식 노드의 포인터
    Node *left, *right;
    //생성자에서 난수 우선순위를 생성, size와 left/right 초기화
    Node(const KeyType& _key) : key(_key), priority(rand()), size(1), left(NULL), right(NULL) {}
    void setLeft(Node* newLeft) { left = newLeft; calcSize(); }
    void setRight(Node* newRight) { right = newRight; calcSize(); }
    //size 멤버 갱신
    void calcSize() {
        size = 1;
        if(left) size += left->size;
        if(right) size += right->size;
    }
};

//priority를 통해 균형 잡힌 트리를 생성한다.
//size를 노드마다 갱신하여 k번째 원소를 찾는 연산이나 x보다 작은 원소를 세는 연산을 쉽게 구현할 수 있다.


using NodePair = pair<Node*, Node*>;
//root를 루트로 하는 트립을 key를 기준으로 나눈다
NodePair split(Node* root, KeyType key){
    if(root == NULL) return NodePair(NULL, NULL);
    //루트가 key 미만이면 오른쪽 서브트리를 쪼갠다
    if(root->key < key){
        NodePair rightSub = split(root->right, key);
        root->setRight(rightSub.first);
        return NodePair(root, rightSub.second);
    }
    //루트가 key 이하이면 왼쪽 서브트리를 쪼갠다
    NodePair leftSub = split(root->left, key);
    root->setLeft(leftSub.second);
    return NodePair(leftSub.first, root);
}

//root를 루트로 하는 트립에 새 노드 node 삽입
//삽입 후 루트 반환
Node* insert(Node* root, Node* node){
    if(root == NULL) return node;
    //node가 루트를 대체. 해당 서브트리를 반으로 자름
    //각각 자손으로 한다.
    if(root->priority < node->priority){
        NodePair splitted = split(root, node->key);
        node->setLeft(splitted.first);
        node->setRight(splitted.second);
        return node;
    }
    else if(node->key < root->key){
        root->setLeft(insert(root->left, node));
    } else{
        root->setRight(insert(root->right, node));
    }
    return root;
}

/*
트립의 루트를 가르키는 포인터 root가 있을 때, 새 값 value 추가
root = insert(root, new Node(value));
*/

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