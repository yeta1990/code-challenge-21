
/* albgarci@student.42madrid.com */
/* https://github.com/yeta1990 */

#include <stdio.h>

int	main(void)
{
	FILE	*f;
	int		read;
	int		n;
	int		i;
	int		dice[2] = {0};
	int		result;

	f = fopen("submitInput.txt", "r");
	n = 0;
	read = 0;
	i = 0;
	result = 0;
	if (f)
	{
		read = fscanf(f, "%i\n", &n);
		while (i < n && read != -1)
		{
			read = fscanf(f, "%i:%i\n", &dice[0], &dice[1]);
			result = dice[0] + dice[1]; 
			printf("Case #%i: ", i + 1);
			if (result < 12)
				printf("%i\n", result + 1);
			else
				printf("-\n");
			i++;
		}
	}
	else
		printf("Error loading the file\n");
}
