/*
	greedy 알고리즘 연습용 문제(백준 1541번. 잃어버린 괄호)
	문제 분석 : 숫자와 '+', '-'가 주어지고 해당 값들을 가지고 만들 수 있는 최소값 구하기. 
	해 선택 전략 : '-'의 존재 여부를 기준으로 경우를 나눈다.
					1. '-' 없는 경우 : 그냥 전체 합이 곧 최소값.
					2. '-' 존재 : -가 나오기 전과 후의 식을 더한 값이 최소값. 
						-> -가 2개 이상일 경우에도 순차적으로 작용하면 된다. 
	접근 방법 : 계산식의 결과 중 최소값을 찾는 문제이므로, '-'의 갯수에 집중. 
*/
#include <iostream>
#include <string>
using namespace std;
int sign=0, len=0;
string minu;

void find(string calcul){
	int i=0;
	while(calcul[len++]!=0){
		if(calcul[len]=='-') minu[i++]=len;
		sign++;
	}
}

int main(){
	
	int num=0; // num : 식이 가질 수 있는 정수의 최대.
	string calcul; //calcul : 식을 입력받는 공간.
	
	cin>>calcul;
	find(calcul);
	int x=1, count=0, j=0, cnt=0;
	int res_1=0, res_2=0;
	for(len=0; len<calcul.length(); len++){
		x=1;
		if(calcul[len]>='0' && calcul[len]<='9')
			count++;
		else{
			int tmp=count-1;//자리수 
			while(tmp-->0)
				x*=10;
			for(;count>0;count--){
				num+=(calcul[len-count]-'0')*x;
				x/=10;
			}
			count=0;
			res_2+=num;
			if(calcul[len]=='-'){
				if(cnt==0){
					res_1=res_2;
					cnt++;
				}
				else{
					res_1-=res_2;
					cnt++;
				}
					
				res_2=0;
			}
			num=0;
		}
	}
	int tmp=count-1;//자리수 
	while(tmp-->0)
		x*=10;
	for(int i=count;i>0;i--){
		num+=(calcul[len-i]-'0')*x;
		x/=10;
	}
	res_2+=num;
	if(minu[0]==0 || calcul[len-count-1]=='+')//'-'가 없는 경우. 
		res_1=res_2;
	else if(len-count-1==minu[cnt-1])//마지막 연산자가 '-' 인 경우.
		res_1-=res_2;
	printf("%d", res_1);
}
