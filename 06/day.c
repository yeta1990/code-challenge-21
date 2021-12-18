/* https://es.wikipedia.org/wiki/Congruencia_de_Zeller */

#include <stdio.h>

int	get_week_day(int year, int month, int day);
int	error_checker(int date[3], int i);

int	main(void)
{
	char	*es[9][15] = {
			{"dissabte", "diumenge", "dilluns", "dimarts", "dimecres", "dijous", "divendres"}, 
			{"sábado", "domingo", "lunes", "martes", "miércoles" "jueves", "viernes"},
			{"szombat", "vasárnap", "hétfő", "kedd", "szerda", "csütörtök", "péntek"},
			{"sâmbătă", "duminică", "luni", "marți", "miercuri", "joi", "vineri"},
			{"sobota", "neděle", "pondělí", "úterý", "středa", "čtvrtek", "pátek"},
			{"lauantai", "sunnuntai", "maanantai", "tiistai", "keskiviikko", "torstai", "perjantai"},
			{"sabato", "domenica", "lunedì", "martedì",	"mercoledì", "giovedì",	"venerdì"},
			{"subbóta", "voskresénʹje", "ponedélʹnik", "vtórnik", "sredá", "četvérg", "pjátnica"}
	};

//	char *eq[20] = {"CA", "ES", "HU", "RO", "CZ", "FI", "IT", "RU", "DE", "FR", "NL", 
//			"SE", "DK", "IS", "VI", "SI", "EN", "GR", "PL", "SK"};
	int		day;
	FILE	*f;
	int		date[3] = {0};
	int		cases;
	int		i;
	char	lang[3] = {0};

	i = 0;
	cases = 0;
	f = fopen("input.txt", "r");
	fscanf(f, "%i\n", &cases);
	while (i < cases)
	{
		fscanf(f, "%i-%i-%i:%2c\n", &date[0], &date[1], &date[2], lang);
		if (error_checker(date, i) == 0)
		{
			if (date[0] >= 1970)
				day = get_week_day(date[0], date[1], date[2]);
			else
				day = get_week_day(date[2], date[1], date[0]);
			printf("Case #%i: %s\n", i + 1, es[0][day]);
		}
		i++;
	}
}
int	error_checker(int date[3], int i)
{
	int	j;

	j = 0;
	if (date[1] <= 0 || date[1] >= 13)
		j += printf("Case #%i: INVALID_DATE\n", i + 1);
	else if (date[2] >= 1970 && date[0] > 31)
		j += printf("Case #%i: INVALID_DATE\n", i + 1);
	else if (date[2] >= 1970 && date[0] < 1)
		j += printf("Case #%i: INVALID_DATE\n", i + 1);
	else if (date[0] < 1970 && date[2] < 1970)
		j += printf("Case #%i: INVALID_DATE\n", i + 1);
	else if (date[2] >= 1970 && date[2] % 4 == 0 && date[1] == 2 && date[0] > 29)
		j += printf("Case #%i: INVALID_DATE\n", i + 1);
	else if (date[2] >= 1970 && date[2] % 4 != 0 && date[1] == 2 && date[0] > 28)
		j += printf("Case #%i: INVALID_DATE\n", i + 1);
	else if (date[0] >= 1970 && date[0] % 4 == 0 && date[1] == 2 && date[2] > 29)
		j += printf("Case #%i: INVALID_DATE\n", i + 1);
	else if (date[0] >= 1970 && date[0] % 4 != 0 && date[1] == 2 && date[2] > 28)
		j += printf("Case #%i: INVALID_DATE\n", i + 1);
	return (j);
}

int	get_week_day(int year, int month, int day)
{
	float	week_day;
	int		m;
	int		y;

	m = month;
	y = year;
	if (m == 1 || m == 2)
	{
		m += 12;
		y -= 1;
	}
	week_day = (day + ((13 * (m + 1)) / 5) + y + (y / 4) - (y / 100) + (y / 400)) % 7;

	return ((int) week_day);
}
