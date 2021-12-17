#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <strings.h>

typedef struct s_letter
{
	char	letter;
	float	value;
	struct s_letter *next;
}	t_letter;

typedef struct s_anto
{
	char		*w1;
	char		*w2;
	int			winner;
	char		*raw_dict;
	t_letter	**dictionary;

}	t_anto;

void	free_case(t_anto *c);
void	create_dictionary(t_anto *c);
float	parse_value(char *s);
void	add_entry(t_letter **dictionary, char letter, float value);
void	calculate_winner(int i, t_anto *c);

int	main(void)
{
	FILE	*f;
	t_anto	*c;
	int		cases;
	int		i;

	f = fopen("submitInput.txt", "r");
	i = 0;
	cases = 0;
	c = 0;
	fscanf(f, "%i\n", &cases);
	while (i < cases)
	{
		c = malloc(sizeof(t_anto));
		c->w1 = malloc(sizeof(char) * 100);
		c->w2 = malloc(sizeof(char) * 100);
		c->raw_dict = malloc(sizeof(char) * 300);
		c->dictionary = malloc(sizeof(t_anto *));
		c->winner = 0;
		*c->dictionary = 0;
		fscanf(f, "%[^-]-%[^|]|%[^\n]\n", (c->w1), (c->w2), (c->raw_dict));
		create_dictionary(c);
		calculate_winner(i, c);
		free_case(c);
		i++;
	}
	fclose(f);
}

float	sum_points(char *word, t_letter **dictionary)
{
	float		p;
	t_letter	*aux;
	char		*str_aux;

	p = 0;
	aux = *dictionary;
	str_aux = word;
	while (str_aux && *str_aux)
	{
		aux = *dictionary;
		while (aux)
		{
			if (*str_aux == aux->letter)
				p += aux->value; 
			aux = aux->next;
		}
		str_aux++;
	}
	return (p);
}

void	calculate_winner(int i, t_anto *c)
{
	float		p1;
	float		p2;

	p1 = sum_points(c->w1, c->dictionary);
	p2 = sum_points(c->w2, c->dictionary);
	printf("Case #%i: ", i + 1);
	if (p1 > p2)
		printf("%s\n", c->w1);
	else if (p2 > p1)
		printf("%s\n", c->w2);
	else
		printf("-\n");
}

void	free_case(t_anto *c)
{
	t_letter *aux;
	t_letter *aux_next;

	aux = (*c->dictionary);
	bzero(c->w1, 100);
	free(c->w1);
	bzero(c->w2, 100);
	free(c->w2);
	bzero(c->raw_dict, 300);
	free(c->raw_dict);
	while (aux)
	{
		aux_next = aux->next;
		free(aux);
		aux = aux_next;
	}
	free(c->dictionary);
	free(c);
}

void	create_dictionary(t_anto *c)
{
	char	*aux;
	char	letter;
	float	value;

	aux = c->raw_dict;
	letter = 0;
	value = 0;
	while (aux && *aux)
	{
		if (isalpha(*aux) != 0)
			letter = *aux;
		else if (isdigit(*aux))
		{
			value = parse_value(aux);
			add_entry(c->dictionary, letter, value);
			while (aux && *aux && *aux != ',')
				aux++;
		}
		aux++;
	}
}

void	add_entry(t_letter **dictionary, char letter, float value)
{
	t_letter *new;

	new = malloc(sizeof(t_letter));
	new->letter = letter;
	new->value = value;
	new->next = *dictionary;
	*dictionary = new;
}

float	parse_value(char *s)
{
	int		is_fraction;
	char	*aux;
	float	div;

	div = 0;
	aux = 0;
	is_fraction = 0;
	aux = s;
	while (aux && *aux)
	{
		if (*aux == ',')
			break ;
		if (*aux == '/')
			is_fraction = 1;
		aux++;
	}
	if (is_fraction)
	{
		aux = s;
		while (*aux != '/')
			aux++;
		aux++;
		div = (float) atoi(s) / (float) atoi(aux);
		return (div);
	}
	return ((float) atoi(s));
}
