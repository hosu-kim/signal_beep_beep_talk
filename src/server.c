#include "../include/minitalk.h"
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static int	g_bit_count = 0;  // 비트 카운트
static char	g_char = 0;       // 받은 문자

// 비트를 받아서 문자로 변환하는 함수
void	handle_signal(int sig)
{
	if (sig == SIGUSR1)
	{
		g_char |= (1 << (7 - g_bit_count));  // 1을 해당 비트에 설정
	}
	else if (sig == SIGUSR2)
	{
		g_char &= ~(1 << (7 - g_bit_count));  // 0을 해당 비트에 설정
	}

	g_bit_count++;

	// 8비트를 다 받으면 문자 출력하고 초기화
	if (g_bit_count == 8)
	{
		write(1, &g_char, 1);  // 문자 출력
		g_char = 0;            // 문자 초기화
		g_bit_count = 0;       // 비트 카운트 초기화
	}
}

// 서버 실행 함수
int	main(void)
{
	struct sigaction sa;

	// SIGUSR1과 SIGUSR2에 대한 신호 처리 함수 설정
	sa.sa_handler = handle_signal;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);

	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		perror("sigaction");
		return (1);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		perror("sigaction");
		return (1);
	}

	// 서버 PID 출력
	printf("Server PID: %d\n", getpid());

	// 무한 대기 (신호를 계속 받을 수 있도록)
	while (1)
	{
		pause();  // 신호가 올 때까지 대기
	}

	return (0);
}
