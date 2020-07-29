/*
	브루트 포스 알고리즘 연습용 문제(백준 2231번. 분해합) 
	문제 분석 : 자연수 N이 주어지면, 해당 자연수의 생성자 중 최소 생성자 출력.(없으면 0출력) 
	해 선택 전략 : 단순히 1부터 최대값까지 분해합을 구하고 주어진 N과 동일한 값이 나오면 출력, 없으면 0 출력. 
*/
#include <iostream>
using namespace std;

int cal(int num){
	int sum=num;//분해합이 자기자신 + 각 자리 숫자들의 합 이므로 sum을 입력값으로 초기화. 
	while(num>0){
		sum+=num%10;
		num=num/10;
	}
	return sum;
}

int main(){
	int num=0;
	cin>>num;
	for(int i=1; i<=1000000; i++){
		if(cal(i)==num){
			cout<<i;
			return 0;
		}
	}
	cout<<"0";
	return 0;
}
