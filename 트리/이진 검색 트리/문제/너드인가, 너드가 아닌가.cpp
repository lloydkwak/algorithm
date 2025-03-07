#include<iostream>
#include<map>
using namespace std;

//c : 테스트 케이스 수(<= 50), n : 신청한 인원(<= 50,000)
int c, n;
map<int, int> participant;

//포함 여부 확인
bool included(int x, int y){
    //p가 x보다 큰 사람 중에 가장 작은 사람
    map<int, int>::iterator it = participant.lower_bound(x);
    //오른쪽에 점이 없는 경우
    if(it == participant.end()) return false;
    //오른쪽에 있는 점의 q가 y 보다 크면 (x, y)는 포함된다
    return y < it->second; 
}

//안에 포함된 사람의 삭제
void removeInclude(int x, int y){
    map<int, int>::iterator it = participant.lower_bound(x);
    //p가 x보다 작은 사람이 없는 경우
    if(it == participant.begin()) return;
    //왼쪽에 있는 첫번째 점으로 이동
    --it;
    //외쪽에 점들을 모두 확인한다
    while(true){
        //왼쪽 점의 q가 y 보다 크면 break;(이미 더 작은 값들은 삭제됨)
        if(it->second > y) break;
        //왼쪽에 점이 더 없는 경우
        if(it == participant.begin()){
            participant.erase(it);
            break;
        }
        //이전 점으로 옮기고 it을 삭제
        else {
            //erase를 하면 반복자는 무효화 된다. 따라서 미리 저장 후 조작.
            map<int, int>::iterator jt = it;
            --jt;
            participant.erase(it);
            it = jt;
        }
    }
}

//참가자 추가가
int add(int x, int y){
    //다른 사람에게 포함된 경우
    if(included(x, y)) return participant.size();
    //다른 사람을 포함 하는 경우
    removeInclude(x, y);
    participant[x] = y;
    return participant.size();
}

int main(){
    cin >> c;
    for(int i = 0; i < c; ++i){
        cin >> n;
        //p : 푼 문제 수, q : 먹을 라면 그릇(p,q <= 100,000)
        int p, q;
        int ans = 0;
        participant.clear();
        for(int j = 0; j < n; ++j){
            cin >> p >> q;
            ans += add(p, q);
        }
        cout << ans << endl;
    }
}