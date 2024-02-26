#include "philo.h"

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*(s + i))
		i++;
	return (i);
}

static int	ft_check_max(const char *str)
{
	long int	nbr;
	int			sign;

	nbr = 0;
	while (ft_isdigit(*str))
		nbr = (nbr * 10) + (*str++ - '0');
	if (nbr > 2147483647)
	{
		return (0);
	}
	return (1);
}

int	ft_isstrdigit(const char *s)
{
	int	i;

	i = 0;
	if (ft_strlen(s) > 12)
		return (0);
	while (s[i])
		if (!ft_isdigit(s[i++]))
			return (0);
	return (ft_check_max(s));
}

int	ft_atoi(const char *str)
{
	int	nbr;

	nbr = 0;
	while (ft_isdigit(*str))
		nbr = (nbr * 10) + (*str++ - '0');
	return (nbr);
}
