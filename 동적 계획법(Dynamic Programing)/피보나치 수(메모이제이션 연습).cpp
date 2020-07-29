/*
	만든 사람 : 김동현(akakak413@naver.com) 
	만든 목적 : 동적 계획법 연습(메모이제이션)
	코드 내용 : 피보나치 수를 재귀함수로 구하기.
	접근 방법 
		1. 일반적인 목적 수까지 순차적으로 구하는 방법
		2. 메모이제이션을 적용시켜서 실행횟수를 최소화 시킨 방법
*/
#include <stdio.h>
#include <sys/time.h> 
long long int data[100000000]; 
//메모이제이션 적용 전 (A)
long long int fibo_nonmemo(int n)
{
	if(n<=2)
		return 1; 
	else
		return fibo_nonmemo(n-1)+fibo_nonmemo(n-2);
}

//메모이제이션 적용 후 (B) 
long long int fibo_memo(int n)
{
	if(n<=2)
		return 1;
	else if(data[n]!=0)//이미 한번 계산했던 값일 경우 
		return data[n];//저장한 값을 반환한다.(캐싱) 
	else{
		data[n]=fibo_memo(n-1)+fibo_memo(n-2);
		return data[n];
	}
}

int main(){
	struct timeval stime, etime;
	double diffTime;

	
	gettimeofday(&stime, NULL);
	printf("메모이제이션 적용 전\n\n\t40번째 피보나치 수 : %d\n\n", fibo_nonmemo(40));
	gettimeofday(&etime, NULL);
	
	diffTime = etime.tv_usec - stime.tv_usec;
    printf("%lf us\n\n\n\n", diffTime);
    
    gettimeofday(&stime, NULL);
	printf("메모이제이션 적용 후\n\n\t445544번째 피보나치 수 : %d\n\n", fibo_memo(445544));
	gettimeofday(&etime, NULL);
	
	diffTime = etime.tv_usec - stime.tv_usec;
    printf("%lf us\n", diffTime);
}
