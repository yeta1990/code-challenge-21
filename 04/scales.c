/* albgarci@student.42madrid.com */
/* https://github.com/yeta1990 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(void)
{
	FILE	*f;
	int		cases;
	int		i;
	char	notes[25] = "A.BC.D.EF.G.A.BC.D.EF.G.";
	char	order[15] = "ABCDEFGABCDEFG";
	char	sequence[8] = {0};
	char	key[3] = {0};
	int		j;
	char	*scale_aux;
	char	*order_aux;

	cases = 0;
	i = 0;
	f = fopen("submitInput.txt", "r");
	fscanf(f, "%i\n", &cases);
	while (i < cases)
	{
		fscanf(f, "%2[^\n]\n", key);
		fscanf(f, "%7[^\n]\n", sequence);
		scale_aux = strchr(notes, key[0]);
		order_aux = strchr(order, key[0]);
		j = 0;
		if (key [1] == 'b')
		{
			printf("Case #%i: %cb", i + 1, order_aux[j]);
			scale_aux--;
		}
		else if (key[1] == '#')
		{
			printf("Case #%i: %c#", i + 1, order_aux[j]);
			scale_aux++;
		}
		else
			printf("Case #%i: %c", i + 1, order_aux[j]);
j++;
		while (j < 7)
		{
			if (sequence[j - 1] == 'T')
				scale_aux++;
			scale_aux++;
			if (*scale_aux == '.')
			{
				if (scale_aux[1] == order_aux[j])
					printf("%cb", order_aux[j]);
				else
					printf("%c#", order_aux[j]);
			}
			else
			{
				if (*scale_aux == order_aux[j])
					printf("%c", order_aux[j]);
				else
					printf("%c#", order_aux[j]);
			}
			j++;
		}
		printf("%s\n", key);
		bzero(key, 3);
		i++;
	}
	fclose(f);
}
