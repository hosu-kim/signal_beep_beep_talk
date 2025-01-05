/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:41:03 by hoskim            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/01/03 17:04:00 by hoskim           ###   ########.fr       */
=======
/*   Updated: 2024/12/31 00:30:38 by hoskim           ###   ########.fr       */
>>>>>>> 44d29d31f16193e3944eee3eb0c57bc9dc3fa03f
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
// 비트로 변환된 문자열을 저장할 배열 할당.
char	**bit_storage_allotator(char *msg)
{
	int		msg_len;
	int		msg_index;
	char	**bits_storage;

	msg_len = ft_strlen(msg);
	// 스트링의 길이만큼 배열 할당
	bits_storage = malloc((msg_len + 1) * sizeof(char *));
	if (!bits_storage)
		return (NULL);
	msg_index = 0;
	// 비트로 변환된 문자열을 저장할 배열 할당.
	// 콘솔에 입력 가능한 아스키 코드의 마지막 값은 126(binary: 1111110이므로 9개(+'\0')
	while (msg_index < msg_len)
	{
		bits_storage[msg_index] = malloc(9 * sizeof(char));
		if (!bits_storage[msg_index]) // 할당 오류 시 메모리  해제 처리
		{ 
			while (msg_index > 0)
				free(bits_storage[--msg_index]);
			free (bits_storage);
			return (NULL);
		}
		msg_index++;
	}
	// 마지막에 NULL로 배열 마무리
	bits_storage[msg_len] = NULL;
	return (bits_storage);
}

// 문자열을 비트로 변환한다.
void	**str_to_bits(char *msg, char **bits_storage)
{
	int		str_index;
	int		bit_index;
	int		char_in_ascii;

	str_index = 0;
	// 문자열을 하나씩 순회한다.
	while (msg[str_index])
	{
		char_in_ascii = msg[str_index]; // 문자를 이 변수에 저장
		bit_index = 7;
		while (bit_index >= 0) // 비트의 마지막 자리에 도달할 동안.
		{
			if (char_in_ascii & (1 << bit_index)) // <<: bit_index자리에 1을 비트 이동하여 저장한다. &: 공통된 1이 있는 자리만 남긴다.
				bits_storage[str_index][7 - bit_index] = '1'; // 0만 아니면 참임.
			else
				bits_storage[str_index][7 - bit_index] = '0';
			bit_index--;
		}
		bits_storage[str_index][8] = '\0'; // 끝단 처리 (문자열 구분을 위해서)
		str_index++; 
	}
}

void	send_message(int pid, char **bit_storage)
{
	int	str_index;
	int	bit_index;

	str_index = 0;
	while (bit_storage[str_index]) // 문자열을 하나씩 순회하는 동안.
	{
		bit_index = 0;
		while (bit_storage[str_index][bit_index]) // 변환된 각 문자의 비트를 하나씩 순회하는 동안
		{
			if (bit_storage[str_index][bit_index] == '1') // 순회하는 자리에 1을 찾으면 SIGUSR1을 보낸다.
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2); // 0을 찾으면 SIGUSR2를 보낸다.
			bit_index++;
			usleep(100);
		}
		str_index++;
	}
}

int	main(int argc, char *argv[])
{
	int		pid;
	int		index_in_str;
	char	**bit_storage;
	
	if (argc != 3)
	{
		printf("Please input only two parameters!\n 1. Server's PID(ex.0014) \
				2. A message(ex.\"Hello\"\n");
		return (1);
	}
	pid = ft_atoi(argv[1]); // 문자열로 입력된 PID를 숫자로 변환한다.
	bit_storage = bit_storage_allotator(argv[2]); // 입력된 메세지를 기반으로 스토리지에 메모리 할당.
	if (!bit_storage) // 메모리 할당 실패 시 오류 처리
		return (1);
	str_to_bits(argv[2], bit_storage); // 메세지를 비트로 변환하고 스토리지에 저장.
	send_message(pid, bit_storage); // 시그널로 메세지 전송.
	index_in_str = 0;
	while (bit_storage[index_in_str]) // 메모리 해제 처리
		free(bit_storage[index_in_str++]); // 이중포인터 먼저 해제
	free(bit_storage); // 포인터 해제
	return (0);
}

/* This project is about seding a messsaage from client to server using signal.
So I made four functions to implement it.
Let's look at the main function first.
The main function takes two parameters from the command line.
The first parameter is the server's PID, and the second one is the message to send.
it converts the PID provided as a string to an interger using the ft_atoi function.

*/
