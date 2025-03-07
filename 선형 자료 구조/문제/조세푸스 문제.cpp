#include<iostream>
#include<list>
using namespace std;

//c : 테스트 케이스 수(<=50), n : 인원(<=20000), k : 다음 순서(n, k <= 1000)
int c, n, k;

void josephus(){
    //리스트
    list<int> survive;
    //리스트 채우기
    for(int i = 1; i <= n; ++i){
        survive.push_back(i);
    }
    //삭제할 위치 포인터 생성
    list<int>::iterator kill = survive.begin();
    while(n > 2){
        //erase()는 지운 원소의 다음 원소 반환
        kill = survive.erase(kill);
        if(kill == survive.end()) kill = survive.begin();
        --n;
        //kill k-1 만큼 이동 O(NK) ==> 최적화 : (k-1) % mod N 만큼 이동동 O(N^2), dp를 이용한 풀이도 존재 O(n)
        for(int i = 0; i < (k-1) % n; ++i){
            ++kill;
            if(kill == survive.end()) kill = survive.begin();
        }
    }
    cout << survive.front() << " " << survive.back() << endl;
}

int main() {
    cin >> c;
    for(int i = 0; i < c; ++i){
        cin >> n >> k;
        josephus();
    }
	return 0;
}