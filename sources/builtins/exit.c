#include <minishell.h>

int	exit_max(char *value, char *max)
{
	int	i;

	i = 0;
	if (value[i] == '+')
		i++;
	if (ft_strlen(&value[i]) < ft_strlen(max))
		return (0);
	if (ft_strlen(&value[i]) > ft_strlen(max))
		return (1);
	while (value[i])
	{
		if (!ft_isdigit(value[i]))
			return (1);
		if (value[i] < max[i])
			return (0);
		if (value[i] > max[i])
			return (1);
		i++;
	}
	return (0);
}

int	exit_min(char *value, char *min)
{
	int	i;

	i = 0;
	if (ft_strlen(value) < ft_strlen(min))
		return (0);
	if (ft_strlen(value) > ft_strlen(min))
		return (1);
	i++;
	while (value[i])
	{
		if (!ft_isdigit(value[i]))
			return (1);
		if (value[i] < min[i])
			return (0);
		if (value[i] > min[i])
			return (1);
		i++;
	}
	return (0);
}

int	strcmp_for_exit(char *value, char *min, char *max)
{
	int	i;
	int	return_value;

	i = 0;
	while ((value[i] >= 9 && value[i] <= 13) || value[i] == ' ')
		i++;
	if (value[i] == '-')
		return_value = exit_min(value, min);
	else
		return_value = exit_max(value, max);
	if (return_value == 1)
		return (1);
	return (return_value);
}

long	ft_atoi_exit(char *str)
{
	long	result;
	int		i;
	int		sign;

	sign = 1;
	result = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	result *= sign;
	return (result);
}

void	exit_ms(t_command *command)
{
	long	value;
	int		i;

	i = 0;
	ft_putstr_fd("exit", 1);
	while (command->arguments[i])
		i++;
	if (i > 0)
	{
		value = strcmp_for_exit(command->argument[i], "-9223372036854775808", "9223372036854775807");
		if (value == 0)
			(value = ft_atoi_exit(command->argument[i]));
		else
			(ft_putstr_fd("numeric argument required", 2), errno = 2, exit(g_status));
	}
	if (i > 1)
		return (ft_putstr_fd("too many arguments", 2), errno = 127);
	errno = value % 256;
	exit(g_status);
}
