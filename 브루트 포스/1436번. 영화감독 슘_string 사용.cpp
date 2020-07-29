/*
	브루트 포스 알고리즘 연습용 문제(백준 1436번. 영화감독 슘.) 
	문제 분석 : 단순히 n을 입력 받으면 규칙상 n번째 수를 출력. 
	해 선택 전략 : 단순 누적 계산 + 6이 들어가는 수일 경우에 대한 규칙 
*/
#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>

using namespace std;

int main(void)
{
	int cnt = 0, N, i=666;
	cin >> N;

	while (cnt < N)
	{
		auto s = to_string(i);
		if (s.find("666") != string::npos)
		{
			cnt++;
			if (cnt == N)
			{
				cout << s << endl;
				break;
			}
		}
		i++;
	}
	return 0;
}
