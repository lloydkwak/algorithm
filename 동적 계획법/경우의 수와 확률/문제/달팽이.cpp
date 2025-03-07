#include<iostream>
#include<string.h>
#include<cmath>
using namespace std;

//c : 테스트 케이스 수(<= 50), n : 우물 높이(<= 1000), m : 장마 기간의 길이(<= 1000)
int c, n, m;

double cache[1001][2001];

//장마 기간 안에 우물을 오를 확률 반환
double climb(int day, int now){
    //기저 사례: 장마 기간이 끝난 경우
    if(day == m) return now >= n ? 1 : 0;

    //memorization
    double& ret = cache[day][now];
    if(ret != -1) return ret;

    ret = 0;
    return ret =  0.75 * climb(day + 1, now + 2) + 0.25 * climb(day + 1, now + 1);
}

int main(){
    cin >> c;
    for(int i = 0; i < c; ++i){
        cin >> n >> m;
        /*
        memset은 바이트 단위로 값을 채움.
        double은 8바이트(64비트)인데, memset(cache, -1, sizeof(cache))은 모든 바이트를 0xFF로 채움.
        이로 인해 cache[][]의 값이 -1이 아니라 **NaN (Not a Number)**으로 설정됨.
        fill_n()을 사용하면 해결 가능
        */
        fill_n(cache, 1001 * 2001, -1.0);
        cout.precision(10);
        cout << fixed << climb(0, 0) << endl;     
    }
}