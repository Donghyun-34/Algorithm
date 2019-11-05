/*
	프로그램 설명 : 나만의 shell 만들기
	만든 사람 :김동현(akakak413@naver.com)
	구현 내용
		1. redirection
		2. back_ground
		3. pipeline
		4. cd
*/
#include <sys/types.h>//시스템 자료형을 사용하기 위한 헤더.
#include <unistd.h>//표준 심볼릭 상수 및 자료형에 대한 헤더.
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>//파일제어에 대한 함수들이 있는 헤더.
#include <sys/stat.h>
#include <stdlib.h>
#define Max_buf 256
char delim[] = "\n\t\r ";//'\n', '\t', '\r', ' '를 구분자로서 선언.

int tokenize(char *argv, char** tokens, int max_tokens) {
	int token_count;
	char *token = strtok(argv, delim);
	for (token_count = 0; token && token_count < max_tokens; token_count++) {
		tokens[token_count] = token;
		token = strtok(NULL, delim);
		/*찾은 토큰의 바로 뒤를 NULL로 바꿔버리는 strtok의 특성 때문에 NULL을 인자로 전달하면 앞
		에서 구분한 토큰의 바로 뒤에서부터 이어서 검색한다.*/
	}
	tokens[token_count] = NULL;
	return token_count;
}

void background(int index, char** argv) {
	pid_t pid;
	int exit_status, i;
	char **forward_str;//& 키워드 앞 부분의 문자열들을 저장하기 위한 배열.
	//index : & 키워드의 위치.
	forward_str = (char **)malloc(32 * sizeof(char *));
	for (i = 0; i < 32; i++)
		forward_str[i] = (char *)malloc(64 * sizeof(char));

	for (i = 0; i < index; i++) {
		strcpy(forward_str[i], argv[i]);
	}
	forward_str[index] = NULL;

	if ((pid = fork()) == -1) {
		printf("fork() 에러\n");
	}
	else if (pid == 0) {
		if (fork() != 0) {
			printf("\t[pid]\t:\t%ld\n", (long)getpid());
			if (execvp(forward_str[0], forward_str) == -1)
				printf("%s에 대한 정의을 찾을 수 없습니다.\n", forward_str[0]);
			exit(1);
		}
		else
		{
			exit(1);
		}
	}
	else {
		wait(&exit_status);
	}
}

int cd(int argc, char** argv) {
	char *path;

	if (argc > 1)
	{
		path = argv[1];
	}
	//인자가 하나일 경우 : cd -> HOME을 경로로 지정.
	else if ((path = (char*)getenv("HOME")) == NULL)
	{
		// HOME에 대한 환경 변수가 없을 경우 경로를 현재 디렉토리로 설정
		path = ".";
	}

	if (chdir(path) == -1)
	{
		fprintf(stderr, "%s: Wrong directory.\n", path);
	}
	return 0;
}

int help() {
	printf("----------사용할 수 있는 명령어 목록들----------\n\n");
	printf("\t1. 내부 명령어\n\n\t\t1) cd : 디렉토리 이동\t2) 그 외의 모든 내장 명령어 사용 가능\n\n");
	printf("\t2. 외부 명령어\n\t-> 외부명령어는 중복 호출 또는 다중 호출이 불가능합니다.\n\t\t1) redirection : 출력 재지향(> or >>) 및 입력 재지향(<)\t2) pipe : 다중 명령어(|)\t3) background : background processing(&)\n\n");
	return 0;
}

void redirection(int flag, int index, char **argv) {//index : >의 위치에 대한 인덱스 
	char **forward_str;
	char **backward_str;
	int i, j = 0;
	int fd;
	int exit_status;
	pid_t pid;

	forward_str = (char **)malloc(32 * sizeof(char *));
	for (i = 0; i < 32; i++)
		forward_str[i] = (char *)malloc(64 * sizeof(char));

	backward_str = (char **)malloc(32 * sizeof(char *));
	for (i = 0; i < 32; i++)
		backward_str[i] = (char *)malloc(64 * sizeof(char));

	for (i = 0; i < index; i++)//forward_str에 키워드 앞까지의 내용 복사. 
		strcpy(forward_str[i], argv[i]);

	forward_str[index] = NULL;// > 위치에 널 입력. 
	for (i = index + 1; argv[i] != NULL; i++) {// 키워드 뒷부분 내용 저장.
		strcpy(backward_str[j++], argv[i]);
	}
	backward_str[j] = NULL;

	switch (flag) {
	case 1://>인 경우(덮어쓰기)
		if ((pid = fork()) == -1)
		{
			printf("fork() 에러");
			exit(1);
		}
		else if (pid == 0) {
			close(fd);
			fd = open(backward_str[0], O_RDWR | O_CREAT | O_TRUNC, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
			if (execvp(forward_str[0], forward_str) == -1)
				printf("명령을 찾을 수 없습니다. %s\n", forward_str[0]);
			exit(1);
		}
		else {
			wait(&exit_status);
		}
		break;
	case 2://>>인 경우(이어서 입력)
		if ((pid = fork()) == -1)
		{
			printf("fork() 에러");
			exit(1);
		}
		else if (pid == 0) {
			close(fd);
			fd = open(backward_str[0], O_RDWR | O_CREAT | O_APPEND, 0644);//>>은 붙여넣기의 개념이므로 excl이 아닌 append 옵션으로 파일 생성.
			dup2(fd, STDOUT_FILENO);
			close(fd);
			if (execvp(forward_str[0], forward_str) == -1)
				printf("명령을 찾을 수 없습니다. %s\n", forward_str[0]);
			exit(1);
		}
		else {
			wait(&exit_status);
		}
		break;
	case 3://< 또는 <<인 상황(입력 재지정)
		if ((pid = fork()) == -1)
		{
			printf("fork() 에러");
			exit(1);
		}
		else if (pid == 0) {
			fd = open(backward_str[0], O_RDONLY);
			dup2(fd, STDIN_FILENO);
			close(fd);
			if (execvp(forward_str[0], forward_str) == -1)
				printf("명령을 찾을 수 없습니다. %s\n", forward_str[0]);
			exit(1);
		}
		else {
			wait(&exit_status);
		}
		break;
	default:
		break;
	}
}

void pipeline(int index, char **argv) {
	char **forward_str;
	char **backward_str;
	int i, j = 0;
	int exit_status;
	pid_t pid;
	int fd[2];//pipe의 결과를 저장하기 위한 배열. [0]은 출력, [1]은 입력

	forward_str = (char **)malloc(32 * sizeof(char *));
	for (i = 0; i < 32; i++)
		forward_str[i] = (char *)malloc(64 * sizeof(char));

	backward_str = (char **)malloc(32 * sizeof(char *));
	for (i = 0; i < 32; i++)
		backward_str[i] = (char *)malloc(64 * sizeof(char));

	for (i = 0; i < index; i++) {
		strcpy(forward_str[i], argv[i]);
	}

	forward_str[index] = NULL;
	for (i = index + 1; argv[i] != NULL; i++) {
		strcpy(backward_str[j++], argv[i]);
	}
	backward_str[j] = NULL;

	pipe(fd);
	if ((pid = fork()) == -1) {
		printf("fork() 에러\n");
	}
	else if (pid == 0) {
		if (fork() == 0) {
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			if (execvp(backward_str[0], backward_str) == -1)
				printf("명령을 찾을 수 없습니다. %s\n", backward_str[0]);
			exit(1);
		}
		else {
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			if (execvp(forward_str[0], forward_str) == -1)
				printf("명령을 찾을 수 없습니다. %s\n", forward_str[0]);
			exit(1);
		}
	}
	else {
		wait(exit_status);
	}
}

void standard_command(char **tokens) {
	pid_t pid;
	int exit_status;
	if ((pid = fork()) == -1) {
		printf("fork() 에러\n");
	}
	else if (pid == 0) {
		if (execvp(tokens[0], tokens) == -1)
			printf("명령을 찾을 수 없습니다. %s\n", tokens[0]);
		exit(1);
	}
	else {
		wait(&exit_status);
	}
}

//중복 처리 아이디어 : int **flag 선언 후 flag[i]의 0과 1에 명령어에 대한 정보들을 넣어주고 run 함수에서 반복문으로 실행.
void check_command(int argc, char **argv, int* flag) {
	int i = 0;
	
	for (i = 0; i < argc; i++) {
		if (strcmp(argv[i], ">") == 0) {
			flag[0] = 1;
			flag[1] = i;
			break;
		}
		else if (strcmp(argv[i], ">>") == 0) {
			flag[0] = 2;
			flag[1] = i;
			break;
		}
		else if (strcmp(argv[i], "<") == 0 || strcmp(argv[i], "<<") == 0) {
			flag[0] = 3;
			flag[1] = i;
			break;
		}
		else if (strcmp(argv[i], "|") == 0) {
			flag[0] = 4;
			flag[1] = i;
			break;
		}
		else if (strcmp(argv[i], "&") == 0) {
			flag[0] = 5;
			flag[1] = i;
			break;
		}
		else if (strcmp(argv[i], "cd") == 0) {
			flag[0] = 6;
			break;
		}
		else if (strcmp(argv[i], "help") == 0 || strcmp(argv[i], "h") == 0) {
			flag[0] = 7;
			flag[1] = i;
			break;
		}
		else {
			flag[0] = 0;
			flag[1] = i;
		}
	}
}

int run(char *argv) {
	char *tokens[Max_buf];
	int token_count;
	token_count = tokenize(argv, tokens, sizeof(tokens) / sizeof(char*));
	int flag[2] = { 0, };//각각의 명령어들을 구별하기 위한 정보를 담기위한 배열.
	check_command(token_count, tokens, flag);

	switch (flag[0]) {
	case 0:
		standard_command(tokens);
		break;
	case 1://>
		redirection(flag[0], flag[1], tokens);
		break;
	case 2://>>
		redirection(flag[0], flag[1], tokens);
		break;
	case 3://< or <<
		redirection(flag[0], flag[1], tokens);
		break;
	case 4:
		pipeline(flag[1], tokens);
		break;
	case 5:
		background(flag[1], tokens);
		break;
	case 6:
		cd(token_count, tokens);
		break;
	case 7:
		help();
		break;
	default:
		break;
	}
	return 0;
}

/*이 함수를 사용하면 현재 위치만 출력하도록 해준다.
char* mypwd() {
	char* buf, *path;
	int index = 0;
	path = (char*)malloc(1024);
	getcwd(path, 1024);
	char* input_tem[5];
	char* show;
	buf = strtok(path, "/");
	while (buf) {
		input_tem[index] = buf;
		buf = strtok(NULL, "/");
		while (buf) {
			input_tem[index] = buf;
			buf = strtok(NULL, "/");
		}
		show = input_tem[index];
		return show;
	}
}*/ 

int main() {
	char argv[Max_buf];
	while (1) {
		//get_current_dir_name()은 현재 위치한 디렉토리의 경로를 표시해준다.
		printf("[%s@%s]$ ", getlogin(), get_current_dir_name());
		fgets(argv, sizeof(argv) - 1, stdin);
		if (strstr(argv, "exit") != 0) // 문자열 비교를 통해서 exit 명령어 구현.
			break;
		run(argv);
	}
	printf("Myshell을 종료합니다.\n\n안녕히가세요.\n");
	return 0;
}