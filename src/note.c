#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>


char	**cvt_storage_allotator(char *msg)
{
	int		msg_len;
	char	**cvt_storage;

	msg_len = 0;
	msg_len = strlen(msg);
	cvt_storage = malloc(msg_len * sizeof(char *));
	while (msg_len > 0)
	{
		cvt_storage[msg_len - 1] = malloc(9 * sizeof(char));
		msg_len--;
	}
	return (cvt_storage);
}

char	**bit_coverter(char *msg)
{
	int		str_index;
	int		bit_index;
	int		char_in_ascii;
	char	**cvt_storage;

	cvt_storage = cvt_storage_allotator(msg);
	str_index = 0;
	char_in_ascii = 0;
	while (msg[str_index] != '\0')
	{
		char_in_ascii = msg[str_index];
		bit_index = 7;
		while (bit_index >= 0)
		{
			if (char_in_ascii & (1 << bit_index))
				cvt_storage[str_index][7 - bit_index] = '1';
			else
				cvt_storage[str_index][7 - bit_index] = '0';
			bit_index--;
		}
		cvt_storage[str_index][8] = '\0';
		str_index++;
	}
	return (cvt_storage);
}

int	main(void)
{
	char	*str = "Hello.";
	char	**result = bit_coverter(str);

	for (int i = 0; result[i] != NULL; i++) {
        free(result[i]);
    }
    free(result);
    
	return (0);
}
