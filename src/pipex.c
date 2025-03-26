/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:45:05 by miaghabe          #+#    #+#             */
/*   Updated: 2025/03/26 16:28:29 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/pipex.h"

void	execute_and_check(char *full_path, char **split_argument, char **env)
{
	if (access(full_path, X_OK) == -1)
	{
		ft_putendl_fd("Command not found", 2);
		free_split(split_argument);
		exit(1);
	}
	if (execve(full_path, split_argument, env) == -1)
	{
		perror("execve failed");
		free_split(split_argument);
		free(full_path);
		exit(1);
	}
}

void	execute_command(char *argument, char **env)
{
	char	*full_path;
	char	**split_argument;

	check_empty_command(argument);
	split_argument = ft_split(argument, ' ');
	if (!split_argument || !split_argument[0])
	{
		free_split(split_argument);
		exit(1);
	}
	if (ft_strchr(split_argument[0], '/'))
		full_path = split_argument[0];
	else
	{
		full_path = get_path(split_argument[0], env);
		if (!full_path)
		{
			ft_putstr_fd("pipex: command not found: ", 2);
			ft_putendl_fd(split_argument[0], 2);
			free_split(split_argument);
			exit(1);
		}
	}
	execute_and_check(full_path, split_argument, env);
}

void	execute_child(char **argv, char **env, int *pipe_fd)
{
	int	infile;

	infile = open_infile(argv[1]);
	if (infile == -1)
		exit (1);
	dup2(infile, 0);
	dup2(pipe_fd[1], 1);
	close(infile);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execute_command(argv[2], env);
}

void	execute_parent(char **argv, char **env, int *pipe_fd)
{
	int	outfile;

	outfile = open_outfile(argv[4]);
	if (outfile == -1)
		exit (1);
	dup2(outfile, 1);
	dup2(pipe_fd[0], 0);
	close(outfile);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execute_command(argv[3], env);
}

int	main(int argc, char **argv, char **env)
{
	int		pipe_fd[2];
	pid_t	child1;
	pid_t	child2;

	if (argc != 5)
		return (write(2, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 38), 1);
	if (pipe(pipe_fd) == -1)
		return (perror("Pipe fail"), 1);
	child1 = fork();
	if (child1 == -1)
		return (perror("Fork fail"), 1);
	if (child1 == 0)
		execute_child(argv, env, pipe_fd);
	child2 = fork();
	if (child2 == -1)
		return (perror("Fork fail"), 1);
	if (child2 == 0)
		execute_parent(argv, env, pipe_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(child1, NULL, 0);
	waitpid(child2, NULL, 0);
	return (0);
}
