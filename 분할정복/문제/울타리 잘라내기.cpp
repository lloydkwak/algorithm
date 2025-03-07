#include<iostream>
#include<vector>
#define INF 987654321
using namespace std;

//c: 테스트 케이스 수(<=50), n: 판자의 수(<=20000)
int c, n;
//hight: 판자의 높이를 저장
vector<int> hight(1, 0);

//l~r 에서 자를 수 있는 가장 큰 직사각형의 넓이를 구하는 재귀 함수
int largestRec(int l, int r){
    //기저 사례: l==r
    if(l==r) return hight[l];

    //왼, 오 구역 나눠서 풀기
    int mid = (l + r) / 2;    
    int ret = max(largestRec(l, mid), largestRec(mid+1, r));

    //구역이 왼, 오 모두 걸치는 경우
    int midLeft = mid, midRight = mid + 1;
    //h: 걸치는 구역에서 가장 낮은 막대의 높이
    int h = min(hight[midLeft], hight[midRight]);
    ret = max(ret, h*2);
    //한칸씩 확장 시키며 더 큰 직사각형 넓이 구하기
    while(midLeft>l || midRight<r){
        //높이가 높은 쪽으로 확장
        if(midLeft>l && (midRight==r || hight[midLeft-1]>hight[midRight+1])){
            --midLeft;
            h = min(h, hight[midLeft]);
        } 
        else {
            ++midRight;
            h = min(h, hight[midRight]);
        }
        //확장한 사각형의 넓이
        ret = max(ret, (midRight-midLeft+1)*h);
    }
    return ret;
}

int main() {
    cin >> c;
    for(int i=0; i<c; ++i){
        cin >> n;
        hight.resize(n, 0);
        for(int j=0; j<n; ++j){
            cin >> hight[j];
        }
        cout << largestRec(0, n-1) << endl;
    }
	return 0;
}