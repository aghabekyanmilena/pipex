/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:59:03 by miaghabe          #+#    #+#             */
/*   Updated: 2025/03/26 14:07:12 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

int		open_infile(char *filename);
int		open_outfile(char *filename);
void	free_split(char **split);
char	*get_right_path(char **env);
char	*get_path(char *command, char **env);
void	check_empty_command(char *argument);

#endif