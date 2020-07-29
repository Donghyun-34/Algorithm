/*
	greedy 알고리즘 연습용 문제(백준 2217번. 로프)
	문제 분석 : 주어진 N개의 로프를 사용해서 들 수 있는 최대 무게를 계산.
	해 선택 전략 : 최대 중량 구한 후, 비교를 통한 최대값 도출. 
	접근 방법 : 주어진 로프를 다 사용하지 않아도 된다는 조건이 있었으므로, 내림차순으로 정렬 후 
				순차적으로 들수 있는 최대중량(rope[i]*(i+1))을 비교하였다. 
*/
#include <iostream>
#include <vector>
#include <algorithm> 
using namespace std; 
vector<int> rope;

int compaer(int num){
	int max=0;
	sort(rope.begin(), rope.end(), greater<int>());//내림차순으로 정렬. 
	for(int i=0; i<num; i++){
		if(max<=rope[i]*(i+1))
			max=rope[i]*(i+1);
	}
	/*
		탈출 조건으로 max> rope[i]*(i+1)을 넣으면 결과가 나오지 않았다.
		왜냐하면 rope[i]가 점점 작아져도 i가 커지면 커질수록 rope[i]*(i+1)의 변화도도 커지기 때문이다. 
	*/
	return max;
}

int main(){

	int num=0;
	cin>>num;
	int input;
	for(int i=0; i<num; i++){
		cin>>input;
		rope.push_back(input);
	}
	cout<<compaer(num);
}
