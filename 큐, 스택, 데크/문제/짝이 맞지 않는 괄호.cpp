#include<iostream>
#include<string>
#include<stack>
using namespace std;

//c : 테스트 케이스 수(<=50), str: 주어지는 문자열
int c;
string str;

const string open("({["), close(")}]");

bool matched(){
    stack<char> paper;
    for(int i = 0; i < str.size(); ++i){
        //find는 없으면 -1 반환, 있으면 위치 반환
        if(open.find(str[i]) != -1) paper.push(str[i]);
        else {
            if(paper.empty()) return false;
            if(open.find(paper.top()) != close.find(str[i])) return false;
            paper.pop();
        }
    }
    return paper.empty();
}

int main() {
    cin >> c;
    for(int i = 0; i < c; ++i){
        cin >> str;
        if(matched()) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
	return 0;
}