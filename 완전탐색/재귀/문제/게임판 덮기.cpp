#include<iostream>
#include<vector>
#include<string>
using namespace std;


//c: 테스트 케이스의 수(<=30), h: 줄의 수, w: 줄당 칸의 수(1<=h,w<=20), 
//color: 칸 색, countWhite: 흰색 칸 개수
int c, h, w, countWhite;

//가능한 블럭의 모양({y, x})
const int block[4][3][2] = {
	{ { 0, 0 }, { 1, 0 }, { 0, 1 } },
	{ { 0, 0 }, { 0, 1 }, { 1, 1 }},
	{ { 0, 0 }, { 1, 0 }, { 1, 1 }},
	{ { 0, 0 }, { 1, 0 }, { 1, -1 }}
};

//게임보드에 블럭 그리기/지우기, 블럭 설치 가능여부 return
//type: 블럭 모양, delta: 1 그림/-1 지움
bool draw(vector<vector<int>>& gameBoard, int y, int x, int type, int delta){
	bool possible = true;
	for(int i=0; i<3; ++i){
		int ny = y + block[type][i][0];
		int nx = x + block[type][i][1];
        //블럭이 게임보드 범위를 벗어난 경우
		if(ny < 0 || ny >= h || nx < 0 || nx >= w){
            possible = false;
            continue;
        }
        //칸이 이미 사용된 경우
		else if((gameBoard[ny][nx] += delta) > 1) {
            possible = false;
        }
	}
	return possible;
}

//가능한 경우를 세는 재귀함수
int count(vector<vector<int>>& gameBoard){
	//가장 왼쪽 위에 있는 흰칸을 찾는다
	int y = -1, x = -1;
	for(int i=0; i<h; ++i){
		for(int j=0; j<w; ++j){
			if(gameBoard[i][j] == 0){
				y = i;
				x = j;
				break;
			}
		}
		if(y != -1) break;
	}
	//기저 사례: 남은 칸이 없는 경우
	if(y==-1) return 1;
	int ret = 0;
	//현재 위치에서 블럭 설치하기(4가지 형태 모두 시도)
	for(int i=0; i<4; ++i){
		if(draw(gameBoard, y, x, i, 1))
			ret += count(gameBoard);
        //설치한 블럭 지우기
        draw(gameBoard, y, x, i, -1);
	}
	return ret;
}

int main() {	
	cin >> c;
	for(int i=0; i<c; i++){
		cin >> h >> w;
		//게임보드 배열
		vector<vector<int>> gameBoard(h, vector<int>(w,0));
		//흰색 칸의 개수
		countWhite = 0;
		//게임판 입력받기(false는 검정색, true는 흰색)
		for(int j=0; j<h; j++){
			string str;
			cin >> str;
			for(int k=0; k<w; k++){
				if(str[k] == '#') {
					++gameBoard[j][k];
				} 
			}
		}
        if(countWhite%3) {
			cout << 0 << endl;
			continue;
		}
		cout << count(gameBoard) << endl;
	}
	return 0;
}