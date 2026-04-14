#include "libft.h"

int is_valid_float(const char *str)
{
	int has_digits;

	has_digits = 0;
	if (*str == '+' || *str == '-')
		str++;
	while (ft_isdigit(*str))
	{
		has_digits = 1;
		str++;
	}
	if (*str == '.')
	{
		str++;
		while (ft_isdigit(*str))
		{
			has_digits = 1;
			str++;
		}
	}
	return (has_digits && *str == '\0');
}

int	is_valid_int(const char *str)
{
	if (str == NULL || *str == '\0')
		return (0);
	while (ft_isdigit(*str))
		str++;
	if (*str == '\n')
		str++;
	return (*str == '\0');
}

void	free_content(void *content)
{
	free(content);
}

