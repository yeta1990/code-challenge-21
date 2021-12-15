
/* albgarci@student.42madrid.com */
/* https://github.com/yeta1990 */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

void	free_double(char ***map, int rows);
char	*ft_strjoin(char const *s1, char const *s2);
void	solve_map(int pok, char **map, char ***names);
char	*create_map(int rows, FILE *f);
void	print_case(int cas, char **map);

int	main(void)
{
	FILE	*f;
	int		cases;
	int		pok;
	int		rows;
	int		cols;
	int		i;
	int		p;
	char	**names;
	char	s[256] = {0};
	char	*map;

	i = 0;
	map = 0;
	cases = 0;
	rows = 0;
	cols = 0;
	names = 0;
	f = fopen("testInput.txt", "r");
	if (f)
	{
		fscanf(f, "%i\n", &cases);
		while (i < cases)
		{
			p = 0;
			fscanf(f, "%i %i %i\n", &pok, &rows, &cols);
			names = malloc(sizeof(char *) * pok);
			while (p < pok)
			{
				fscanf(f, "%s\n", s);
				names[p] = strdup(s);
				bzero(s, 256);
				p++;
			}
			map = create_map(rows, f);
		//	printf("map: %s\n", map);
			solve_map(pok, &map, &names);
			print_case(i, &map);
			free_double(&names, pok);
			bzero(map, strlen(map));
			map = 0;
			free(map);
			i++;
		}
	}
	else
		printf("Error loading the file\n");
}

char *create_map(int rows, FILE *f)
{
	int	c;
	int	j;
	int	p;
	char	*line;
	char	aux[101] = {0};
	size_t	len;
	char	*map;
	char	*aux_map;

	line = 0;
	c = 0;
	j = 0;
	p = 0;
	map = 0;
	aux_map = 0;
	while (c < rows)
	{
		j = 0;
		p = 0;
		line = malloc(sizeof(char) * 300);
		getline(&line, &len, f);
		while (line && line[p])
		{
			while (line && line[p] == ' ')
				p++;
			if (line && line[p] != '\n')
			{
				aux[j] = line[p];
				j++;
			}
			p++;
		}
		free(line);
		if (!map)
			map = strdup(aux);
		else
		{
			aux_map = strdup(map);
			free(map);
			map = 0;
			map = ft_strjoin(aux_map, aux);
			free(aux_map);
			aux_map = 0;
		}
		bzero(aux, 101);
		c++;
	}
	return (map);
}


char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;

	if (!s1 || !s2)
		return (NULL);
	s3 = malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1));
	if (!s3)
		return (NULL);
	memmove(s3, (char *)s1, strlen(s1));
	memmove(s3 + strlen(s1), (char *)s2, strlen(s2));
	s3[strlen(s1) + strlen(s2)] = '\0';
	return (s3);
}

void	solve_map(int pok, char **map, char ***names)
{
	int	i;
	int	len;
	int	name_len;
	int	p;
	int	j;
	int	z;
	int	found;

	len = 0;
	name_len = 0;
	i = 0;
	p = 0;
	j = 0;
	z = 0;
	found = 0;
	while(p < pok)
	{
		len = strlen(*map);
		name_len = strlen((*names)[p]);
		i = 0;
	//	printf("Looking for name %s ", (*names)[p]);
		while (i < len)
		{
			j = 0;
			z = 0;
			while (j < name_len && i + j < len)
			{
			//	printf("%c", (*names)[p][j + z]);
				if ((*map)[i + j + z] == (*names)[p][j])
					j++;
				else if ((*map)[i + j + z] == 1)
					z++;
				else
				{
				//	j++;
					break ;
				}
			}
			if (j == name_len)
			{
			//	printf("Found: %s\n", (*names)[p]);
			//	printf("Map: %s\n", (*map));
				j = 0;
				z = 0;
				while (j < name_len)
				{
					if ((*map)[i + j + z] != 1)
					{
						(*map)[i + j + z] = 1;
 						j++;
					}
					else if ((*map)[i + j + z] == 1)
						z++;
				}
				found++;
				if (found == pok)
					return ;
			}
			j = 0;
			z = 0;
			while (j < name_len && i + j < len)
			{
				if ((*map)[i + j + z] == (*names)[p][name_len - j - 1])
					j++;
				else if ((*map)[i + j + z] == 1)
					z++;
				else
				{
//					j++;
					break ;
				}
			}
			if (j == name_len)
			{
			//	printf("Found: %s\n", (*names)[p]);

				j = 0;
				z = 0;
				while (j < name_len)
				{
					if ((*map)[i + j + z] != 1)
					{
						(*map)[i + j + z] = 1;
 						j++;
					}
					else if ((*map)[i + j + z] == 1)
						z++;
				}
			//	printf("Map: %s\n", (*map));
				found++;
				if (found == pok)
					return ;
			}
			i++;
		}
		p++;
		if (found < pok && p == pok)
			p = 0;
	}
}

void	print_case(int cas, char **map)
{
	int	i;
	int	len;

	i = 0;
	len = strlen(*map);
	printf("Case #%i: ", cas + 1);
	while (i < len)
	{
		if ((*map)[i] != 1)
			printf("%c", (*map)[i]);
		i++;
	}
	printf("\n");
}

void	free_double(char ***map, int rows)
{
	int	c;

	c = 0;
	while (c < rows)
	{
		free((*map)[c]);
		c++;
	}
	free(*map);
	map = 0;
}
