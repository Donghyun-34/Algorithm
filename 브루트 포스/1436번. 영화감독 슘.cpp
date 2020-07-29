/*
	브루트 포스 알고리즘 연습용 문제(백준 1436번. 영화감독 슘.) 
	문제 분석 : 단순히 n을 입력 받으면 규칙상 n번째 수를 출력. 
	해 선택 전략 : 단순 누적 계산 + 6이 들어가는 수일 경우에 대한 규칙 
*/
#include <iostream>
using namespace std;

int main(){
	while(1){
	int num;
		cin>>num;
	int i=0, cnt=1, state=11;//i : 출력 시 사용할 값, cnt : 반복횟수 계산, state : 11일 경우의 의미는 보통의 규칙이 적용.
	while(cnt<num){
		if((cnt-6)%19==0){
			if(num-cnt==66){
				
			}
		}
		else{
			cnt++;
			i++;
		}
	}
	int res;
	if(state==11)
		res=666+(i*1000);
	else
		res=(i+1)*1000+660+state;
	cout<<res<<endl;
	}
}

