#include<iostream>
#include<queue>
using namespace std;

//c : 테스트 케이스 수(<=50), n : 인원(<=20000), k : 다음 순서(n, k <= 1000)
int c, n, k;

void josephus(){
    //큐
    queue<int> survive;
    //큐 채우기
    for(int i = 1; i <= n; ++i){
        survive.push(i);
    }
    //삭제할 위치 포인터 생성
    while(n > 2){
        //맨앞 원소 삭제
        survive.pop();
        --n;
        //맨앞 원소를 제일 뒤로 옮김
        for(int i = 0; i < k-1; ++i){
            int tmp = survive.front();
            survive.pop();
            survive.push(tmp);
        }
    }
    if(survive.front() < survive.back())
        cout << survive.front() << " " << survive.back() << endl;
    else cout << survive.back() << " " << survive.front() << endl;
}

int main() {
    cin >> c;
    for(int i = 0; i < c; ++i){
        cin >> n >> k;
        josephus();
    }
	return 0;
}

//리스트를 활용하는 방식이 최적화 하기에 더 좋음