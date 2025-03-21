/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:34:04 by miaghabe          #+#    #+#             */
/*   Updated: 2025/03/21 17:09:49 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/pipex.h"

int	open_infile(char *filename)
{
	if (access(filename, F_OK) != 0)
	{
		ft_putstr_fd("pipex: No such file or directory ", 2);
		ft_putendl_fd(filename, 2);
		return (-1);
	}
	if (access(filename, R_OK) != 0)
	{
		ft_putstr_fd("pipex: permission denied ", 2);
		ft_putendl_fd(filename, 2);
		return (-1);
	}
	return (open(filename, O_RDONLY));
}

int	open_outfile(char *filename)
{
	if (access(filename, F_OK) != 0)
		return (open(filename, O_CREAT | O_WRONLY));
	if (access(filename, W_OK) != 0)
	{
		ft_putstr_fd("pipex: permission denied ", 2);
		ft_putendl_fd(filename, 2);
		return (-1);
	}
	return (open(filename, O_WRONLY | O_TRUNC));
}
