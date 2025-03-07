#include<iostream>
#include<vector>
#define INF 987654321
using namespace std;

//c: 테스트 케이스 수
int c;
//스위치 별로 연결된 시계, 1이면 연결
const bool linked[10][16]{
    {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1},
    {1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1},
    {0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0}
};

//모든 시계가 12시를 가르치는지 여부 확인
bool checkAll(vector<int>& clock){
    for(int i=0; i<16; ++i){
        if(clock[i] != 12) return false;
    }
    return true;
}

//스위치를 누르면 시계의 시간 변경
void change(vector<int>& clock, int swtch){
    for(int i=0; i<16; ++i){
        if(linked[swtch][i]){
            clock[i] += 3;
            if(clock[i]==15) clock[i] = 3;
        }
    }
}

//모든 시계를 12시로 맞추기 위해 스위치를 눌러야하는 최소 횟수를 구하는 재귀함수
int minCount(vector<int>& clock, int swtch){
    //기저 사례: 모든 스위치를 3번 이상 눌러본 경우
    if(swtch==10) return checkAll(clock) ? 0 : INF;

    //현재 스위치 눌러보기
    int ret=INF;
    //스위치를 4번 누르면 누리지 않은 것과 같으므로 4번 이하만 누른다
    //i: 현재 스위치를 누른 횟수
    for(int i=0; i<4; ++i){
        ret = min(ret, i + minCount(clock, swtch + 1));
        change(clock, swtch);
    }
    return ret;
}

int main() {
	cin >> c;
    for(int i=0; i<c; ++i){
        //시계 별로 가르치는 시간 입력
        vector<int> clock;
        for(int j=0; j<16; ++j){
            int time;
            cin >> time;
            clock.push_back(time);
        }
        int ans = minCount(clock, 0);
        if(ans==INF) cout << -1 << endl;
        else cout << ans << endl;
    }
	return 0;
}