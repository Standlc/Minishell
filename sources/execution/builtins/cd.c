#include "minishell.h"

extern int	g_status;

char	*getenv_ms(char *variable)
{
	char	**env;
	char	*str;
	int		i;
	int		len_variable;

	i = 0;
	env = (*environnement(NULL));
	if (!variable || !env)
		return (NULL);
	len_variable = ft_strlen(variable);
	while (env[i])
	{
		if (ft_strncmp(env[i], variable, len_variable + 1) == '=')
		{
			str = ft_strdup(&env[i][len_variable + 1]);
			if (!str)
				return (ft_putstr_fd("Cannot allocate memory\n", 2), NULL);
			return (str);
		}
		i++;
	}
	return (NULL);
}

void	complete_env_pwd(t_command *command, char *old_pwd, char *pwd)
{
	command->position = 2;
	command->arguments = malloc(sizeof(char *) * 4);
	if (!command->arguments)
		return (ft_putstr_fd("Cannot allocate memory\n", 2), free(pwd));
	command->arguments[0] = malloc(1);
	command->arguments[0][0] = '\0';
	command->arguments[1] = ft_strjoin("PWD=", pwd);
	if (!command->arguments[1])
		return (ft_putstr_fd("Cannot allocate memory\n", 2), free(command->arguments), free(pwd));
	if (old_pwd)
	{
		command->arguments[2] = ft_strjoin("OLDPWD=", old_pwd);
		if (!command->arguments[2])
			return (ft_putstr_fd("Cannot allocate memory\n", 2), free(command->arguments[1]), free(command->arguments), free(pwd));
	}
	else
		command->arguments[2] = NULL;
	command->arguments[3] = NULL;
	export_ms(command);
	free_dup(command->arguments);
}

void	env_pwd(char *old_pwd)
{
	t_command	export_pwd;
	char		*pwd;

	pwd = getcwd(NULL, 1024);
	if (!pwd)
	{
		if (errno == ERANGE)
			ft_putstr_fd("Path exceeds max buffer lenght\n", 2);
		else if (errno == ENOMEM)
			ft_putstr_fd("Cannot allocate memory\n", 2);
	}
	else
		complete_env_pwd(&export_pwd, old_pwd, pwd);
	free(pwd);
}

void	cd_ms(t_command *command)
{
	char	*str;
	char	*old_pwd;

	g_status = 0;
	if (command->position != 2)
		return ;
	if (command->arguments[1] && command->arguments[2])
		return (ft_putstr_fd("too many arguments\n", 2), g_status = 1, (void)0);
	old_pwd = getenv_ms("PWD");
	if (command->arguments[1])
	{
		if (chdir(command->arguments[1]) == -1)
			return (ft_putstr_fd("No such directory\n", 2), g_status = 1, free(old_pwd));
	}
	else
	{
		str = getenv_ms("HOME");
		if (!str)
			return (ft_putstr_fd("HOME not set\n", 2), g_status = 1, free(old_pwd));
		if (chdir(str) == -1)
			return (ft_putstr_fd("No such directory\n", 2), g_status = 1, free(old_pwd));
	}
	(env_pwd(old_pwd), free(old_pwd));
}