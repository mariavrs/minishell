/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:27:19 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/11 17:37:32 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

void	ft_free_str(char **str)
{
	if (!(*str))
		return ;
	ft_bzero(*str, ft_strlen(*str));
	free(*str);
	*str = NULL;
}

void	ft_free_dbl_str(char ***str)
{
	int	i;

	i = 0;
	if (!(*str))
		return ;
	while ((*str)[i])
	{
		ft_bzero((*str)[i], ft_strlen((*str)[i]));
		free((*str)[i]);
		(*str)[i] = NULL;
		i++;
	}
	free(*str);
	*str = NULL;
}

void	ft_free_redir_elem(t_redir **rdr)
{
	t_redir	*next;

	if (!(*rdr))
		return ;
	next = (*rdr)->next;
	ft_free_str(&(*rdr)->filename);
	free(*rdr);
	*rdr = next;
}

void	ft_free_cmd_elem(t_cmd **cmd)
{
	t_cmd	*next;

	if (!(*cmd))
		return ;
	next = (*cmd)->next;
	ft_free_str(&(*cmd)->spl_cmd);
	ft_free_str(&(*cmd)->argv_line);
	ft_free_dbl_str(&(*cmd)->argv);
	ft_free_redir(&(*cmd)->rdr);
	free(*cmd);
	*cmd = next;
}

void	ft_free_cmd_list_elem(t_block **cmd_block)
{
	t_block	*next;

	if (!(*cmd_block))
		return ;
	next = (*cmd_block)->next;
	ft_free_cmd(&(*cmd_block)->pipeline);
	free(*cmd_block);
	*cmd_block = next;
}
