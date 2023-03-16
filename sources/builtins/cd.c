void	cd(t_command *command)
{
	if (command->argument[1])
		ft_putstr_fd("too many arguments", 2);
	else if (chdir(command->argument[0]) == -1)
		ft_putstr_fd("No such directory", 2);
	else
		
}