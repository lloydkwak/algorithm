#include<iostream>
#include<string.h>
#include<vector>
using namespace std;

//c : 테스트 케이스 수(<= 50), n : 마을 수(<= 50), 
//d : 지난 일 수(<= 100), p : 교도소가 있는 마을(<= n) 
//t : 확률을 계산 할 마을의 수, q : 확률을 계산 할 마을
//town : 인접한 마을 정보를 담고있다
int c, n, d, p, t, q;
bool town[51][51];

int countNext[51];

double cache[51][101];
//d 일 후에 q 마을에 있을 확률 반환환
double probability(int start, int day){
    //기저 사례: 목표 날짜가 모두 지난 경우(q에서 반대로 타고 올라와 p로 옴옴)
    if(day == d) return (start == p ? 1.0 : 0.0);
    
    //memorization
    double& ret = cache[start][day];
    if(ret != -1.0) return ret;

    ret = 0.0;
    for(int i = 0; i < n; ++i){
        if(town[start][i]){
            //반대로 가면 countNext[i], 정방향으로 가면 countNext[start]
            ret += probability(i, day + 1) / countNext[i];
        }
    }
    return ret;
}

int main(){
    cin >> c;
    for(int i = 0; i < c; ++i){
        cin >> n >> d >> p;
        memset(countNext, 0, sizeof(countNext));
        for(int j = 0; j < n; ++j){
            for(int k = 0; k < n; ++k){
                cin >> town[j][k];
                if(town[j][k]) ++countNext[j];
            }
        }
        cin >> t;
        /*
        // 목표 q가 다르기 때문에 매번 cache 를 초기화 해줘야 한다. ---> 시간복잡도 높아짐 *t
        for(int j = 0; j < t; ++j){
            fill_n(&cache[0][0], 51 * 101, -1.0);
            cin >> q;
            cout.precision(10);
            cout << fixed << probability(p, 0) << " ";
        }
        */
        //q에서 부터 p로 가는 확률을 계산하면 *t 만큼의 시간 복잡도를 줄일 수 있음
        fill_n(&cache[0][0], 51 * 101, -1.0);
        for(int j = 0; j < t; ++j){
            cin >> q;
            cout.precision(10);
            cout << fixed << probability(q, 0) << " ";
        }
        cout << endl;
    }
}