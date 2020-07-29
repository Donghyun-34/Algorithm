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
using namespace std;
int len=0, minu=0, num_min=0;

int init(int *num, char *calcul, char *temp){
	gets(calcul);
	
	int j=0, y=0; //j : temp의 순서, y : num의 순서. 
	int x=1, count=0;//x는 자리수.
	int res_1=0, res_2=0; // res_1 : - 앞에 나온 수들의 합, res_2 : - 이후에 나온 수들 합. 
	while(calcul[len]!=0){
		x=1;
		if(calcul[len]>='0' && calcul[len]<='9')
			count++;
		else{
			temp[j++]=calcul[len];
			int tmp=count-1;//자리수 
			while(tmp-->0)
				x*=10;
			for(;count>0;count--){
				num[y]+=(calcul[len-count]-'0')*x;
				x/=10;
			}
			y++;
			count=0;	
			if(calcul[len]=='-'){
					minu++;
			}
		}
		len++;
	}
	int tmp=count-1;//자리수 
	while(tmp-->0)
		x*=10;
	for(;count>0;count--){
		num[y]+=(calcul[len-count]-'0')*x;
		x/=10;
	}//마지막 입력이 숫자이므로 해당 값 입력위한 부분.
	
	return y+1;
}

int main(){
	
	int num[25]={0}, cnt=0; // num : 식이 가질 수 있는 정수의 최대.
	char calcul[51], temp[24]={0}; //calcul : 식을 입력받는 공간.
	
	cnt=init(num, calcul, temp);
}
