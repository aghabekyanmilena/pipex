/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:58:00 by miaghabe          #+#    #+#             */
/*   Updated: 2025/03/26 14:20:01 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/pipex.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!*split)
		return ;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	check_empty_command(char *argument)
{
	if (!argument || !*argument)
	{
		ft_putendl_fd("pipex: command cannot be empty", 2);
		exit(1);
	}
}

char	*get_right_path(char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
		{
			j = 0;
			while (env[i][j] && env[i][j] != '=')
				j++;
			return (env[i] + j + 1);
		}
		i++;
	}
	return (NULL);
}

char	*get_path(char *command, char **env)
{
	char	*temp_path;
	char	*final_path;
	char	**s_paths;
	char	**paths_start;

	s_paths = ft_split(get_right_path(env), ':');
	if (!s_paths)
		return (NULL);
	paths_start = s_paths;
	while (*s_paths)
	{
		temp_path = ft_strjoin(*s_paths, "/");
		final_path = ft_strjoin(temp_path, command);
		free(temp_path);
		if (access(final_path, F_OK | X_OK) == 0)
		{
			free_split(paths_start);
			return (final_path);
		}
		free(final_path);
		s_paths++;
	}
	free_split(paths_start);
	return (NULL);
}
