#include<iostream>
#include<string>
using namespace std;

//c: 테스트 케이스 수(<=50)
int c;

//zip을 압출을 해제하고 바로 뒤집은 뒤 재압축하는 함수
string reverse(string::iterator& now){
    //한 글자를 검사 한 후 한칸 앞으로 옮김
    char head = *now;
    now++;
    //기저 사례: head 가 b 또는 w인 경우
    if(head=='b' || head=='w') return string(1, head);
    //head가 x인 경우 왼위, 오위, 왼밑, 오밑을 모두 재귀를 통해 뒤집기
    string upLeft = reverse(now);
    string upRight = reverse(now);
    string lowLeft = reverse(now);
    string lowRight = reverse(now);
    //뒤집은 그림의 위아래를 바꿈
    return string("x") + lowLeft + lowRight + upLeft + upRight;
}

int main() {
    cin >> c;
    for(int i=0; i<c; ++i){
        //zip: 압축된 그림의 입력값
        string zip;
        cin >> zip;
        string::iterator now = zip.begin();
        cout<< reverse(now) << endl;
    }
	return 0;
}