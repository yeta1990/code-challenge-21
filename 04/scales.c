#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(void)
{
	FILE	*f;
	int		cases;
	int		i;
	char	notes[25] = "A.BC.D.EF.G.A.BC.D.EF.G.";
	char	sequence[8] = {0};
	char	key[3] = {0};
	int		j;
	char	*scale_aux;
	char	scale[10] = {0};

	cases = 0;
	i = 0;
	f = fopen("testInput.txt", "r");
	fscanf(f, "%i\n", &cases);
	while (i < cases)
	{
		fscanf(f, "%2[^\n]\n", key);
		fscanf(f, "%7[^\n]\n", sequence);
		scale_aux = strchr(notes, key[0]);
		scale[0] = *scale_aux;
		if (key [1] == 'b')
		{
			printf("Case #%i: %cb", i + 1, *scale_aux);
			scale_aux--;
		}
		else if (key[1] == '#')
		{
			printf("Case #%i: %c#", i + 1, *scale_aux);
			scale_aux++;
		}
		else
			printf("Case #%i: %c", i + 1, *scale_aux);
		j = 1;
		while (j < 7)
		{
			if (sequence[j - 1] == 'T')
				scale_aux++;
			scale_aux++;
			if (*scale_aux == '.')
			{
				scale_aux--;
				if (strchr(scale, *scale_aux) == 0)
				{
					printf("%c#", *scale_aux);
					scale[j] = *scale_aux;
					scale_aux++;
				}
				else
				{
					scale_aux++;
					scale_aux++;
					printf("%cb", *scale_aux);
					scale[j] = *scale_aux;
					scale_aux--;
				}
			}
			else
			{
				if (strchr(scale, *scale_aux) == 0)
					printf("%c", *scale_aux);
				else
				{
					scale_aux++;
					printf("%cb", *scale_aux);
				}
		//		scale[j] = *scale_aux;
			}
			scale[j] = *scale_aux;
			j++;
		}
		printf("%s\n", key);
		bzero(scale, 10);
		bzero(key, 3);
		i++;
	}
	fclose(f);
}
