/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:45:05 by miaghabe          #+#    #+#             */
/*   Updated: 2025/03/21 17:16:32 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/pipex.h"

void	execute_command(char *argument, char **env)
{
	char	*full_path;
	char	**split_argument;

	split_argument = ft_split(argument, ' ');
	full_path = get_path(split_argument[0], env);
	if (execve(full_path, split_argument, env) == -1)
	{
		ft_putendl_fd("Command not found", 2);
		free_split(split_argument);
		free(full_path);
		exit (1);
	}
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
	pid_t	proc_id;

	if (argc != 5)
	{
		write(2, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 38);
		return (1);
	}
	if (pipe(pipe_fd) == -1)
	{
		perror("Pipe fail");
		return (1);
	}
	proc_id = fork();
	if (proc_id == -1)
	{
		perror("Fork fail");
		return (1);
	}
	if (proc_id == 0)
		execute_child(argv, env, pipe_fd);
	waitpid(proc_id, NULL, 0);
	execute_parent(argv, env, pipe_fd);
	return (0);
}
