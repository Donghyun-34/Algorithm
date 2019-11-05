/*
	���α׷� ���� : ������ shell �����
	���� ��� :�赿��(akakak413@naver.com)
	���� ����
		1. redirection
		2. back_ground
		3. pipeline
		4. cd
*/
#include <sys/types.h>//�ý��� �ڷ����� ����ϱ� ���� ���.
#include <unistd.h>//ǥ�� �ɺ��� ��� �� �ڷ����� ���� ���.
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>//������� ���� �Լ����� �ִ� ���.
#include <sys/stat.h>
#include <stdlib.h>
#define Max_buf 256
char delim[] = "\n\t\r ";//'\n', '\t', '\r', ' '�� �����ڷμ� ����.

int tokenize(char *argv, char** tokens, int max_tokens) {
	int token_count;
	char *token = strtok(argv, delim);
	for (token_count = 0; token && token_count < max_tokens; token_count++) {
		tokens[token_count] = token;
		token = strtok(NULL, delim);
		/*ã�� ��ū�� �ٷ� �ڸ� NULL�� �ٲ������ strtok�� Ư�� ������ NULL�� ���ڷ� �����ϸ� ��
		���� ������ ��ū�� �ٷ� �ڿ������� �̾ �˻��Ѵ�.*/
	}
	tokens[token_count] = NULL;
	return token_count;
}

void background(int index, char** argv) {
	pid_t pid;
	int exit_status, i;
	char **forward_str;//& Ű���� �� �κ��� ���ڿ����� �����ϱ� ���� �迭.
	//index : & Ű������ ��ġ.
	forward_str = (char **)malloc(32 * sizeof(char *));
	for (i = 0; i < 32; i++)
		forward_str[i] = (char *)malloc(64 * sizeof(char));

	for (i = 0; i < index; i++) {
		strcpy(forward_str[i], argv[i]);
	}
	forward_str[index] = NULL;

	if ((pid = fork()) == -1) {
		printf("fork() ����\n");
	}
	else if (pid == 0) {
		if (fork() != 0) {
			printf("\t[pid]\t:\t%ld\n", (long)getpid());
			if (execvp(forward_str[0], forward_str) == -1)
				printf("%s�� ���� ������ ã�� �� �����ϴ�.\n", forward_str[0]);
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
	//���ڰ� �ϳ��� ��� : cd -> HOME�� ��η� ����.
	else if ((path = (char*)getenv("HOME")) == NULL)
	{
		// HOME�� ���� ȯ�� ������ ���� ��� ��θ� ���� ���丮�� ����
		path = ".";
	}

	if (chdir(path) == -1)
	{
		fprintf(stderr, "%s: Wrong directory.\n", path);
	}
	return 0;
}

int help() {
	printf("----------����� �� �ִ� ��ɾ� ��ϵ�----------\n\n");
	printf("\t1. ���� ��ɾ�\n\n\t\t1) cd : ���丮 �̵�\t2) �� ���� ��� ���� ��ɾ� ��� ����\n\n");
	printf("\t2. �ܺ� ��ɾ�\n\t-> �ܺθ�ɾ�� �ߺ� ȣ�� �Ǵ� ���� ȣ���� �Ұ����մϴ�.\n\t\t1) redirection : ��� ������(> or >>) �� �Է� ������(<)\t2) pipe : ���� ��ɾ�(|)\t3) background : background processing(&)\n\n");
	return 0;
}

void redirection(int flag, int index, char **argv) {//index : >�� ��ġ�� ���� �ε��� 
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

	for (i = 0; i < index; i++)//forward_str�� Ű���� �ձ����� ���� ����. 
		strcpy(forward_str[i], argv[i]);

	forward_str[index] = NULL;// > ��ġ�� �� �Է�. 
	for (i = index + 1; argv[i] != NULL; i++) {// Ű���� �޺κ� ���� ����.
		strcpy(backward_str[j++], argv[i]);
	}
	backward_str[j] = NULL;

	switch (flag) {
	case 1://>�� ���(�����)
		if ((pid = fork()) == -1)
		{
			printf("fork() ����");
			exit(1);
		}
		else if (pid == 0) {
			close(fd);
			fd = open(backward_str[0], O_RDWR | O_CREAT | O_TRUNC, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
			if (execvp(forward_str[0], forward_str) == -1)
				printf("����� ã�� �� �����ϴ�. %s\n", forward_str[0]);
			exit(1);
		}
		else {
			wait(&exit_status);
		}
		break;
	case 2://>>�� ���(�̾ �Է�)
		if ((pid = fork()) == -1)
		{
			printf("fork() ����");
			exit(1);
		}
		else if (pid == 0) {
			close(fd);
			fd = open(backward_str[0], O_RDWR | O_CREAT | O_APPEND, 0644);//>>�� �ٿ��ֱ��� �����̹Ƿ� excl�� �ƴ� append �ɼ����� ���� ����.
			dup2(fd, STDOUT_FILENO);
			close(fd);
			if (execvp(forward_str[0], forward_str) == -1)
				printf("����� ã�� �� �����ϴ�. %s\n", forward_str[0]);
			exit(1);
		}
		else {
			wait(&exit_status);
		}
		break;
	case 3://< �Ǵ� <<�� ��Ȳ(�Է� ������)
		if ((pid = fork()) == -1)
		{
			printf("fork() ����");
			exit(1);
		}
		else if (pid == 0) {
			fd = open(backward_str[0], O_RDONLY);
			dup2(fd, STDIN_FILENO);
			close(fd);
			if (execvp(forward_str[0], forward_str) == -1)
				printf("����� ã�� �� �����ϴ�. %s\n", forward_str[0]);
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
	int fd[2];//pipe�� ����� �����ϱ� ���� �迭. [0]�� ���, [1]�� �Է�

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
		printf("fork() ����\n");
	}
	else if (pid == 0) {
		if (fork() == 0) {
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			if (execvp(backward_str[0], backward_str) == -1)
				printf("����� ã�� �� �����ϴ�. %s\n", backward_str[0]);
			exit(1);
		}
		else {
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			if (execvp(forward_str[0], forward_str) == -1)
				printf("����� ã�� �� �����ϴ�. %s\n", forward_str[0]);
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
		printf("fork() ����\n");
	}
	else if (pid == 0) {
		if (execvp(tokens[0], tokens) == -1)
			printf("����� ã�� �� �����ϴ�. %s\n", tokens[0]);
		exit(1);
	}
	else {
		wait(&exit_status);
	}
}

//�ߺ� ó�� ���̵�� : int **flag ���� �� flag[i]�� 0�� 1�� ��ɾ ���� �������� �־��ְ� run �Լ����� �ݺ������� ����.
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
	int flag[2] = { 0, };//������ ��ɾ���� �����ϱ� ���� ������ ������� �迭.
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

/*�� �Լ��� ����ϸ� ���� ��ġ�� ����ϵ��� ���ش�.
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
		//get_current_dir_name()�� ���� ��ġ�� ���丮�� ��θ� ǥ�����ش�.
		printf("[%s@%s]$ ", getlogin(), get_current_dir_name());
		fgets(argv, sizeof(argv) - 1, stdin);
		if (strstr(argv, "exit") != 0) // ���ڿ� �񱳸� ���ؼ� exit ��ɾ� ����.
			break;
		run(argv);
	}
	printf("Myshell�� �����մϴ�.\n\n�ȳ���������.\n");
	return 0;
}