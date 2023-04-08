/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_list_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:28:59 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/08 22:12:49 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

extern int	g_exit_status;

t_cmd	*parse_pipe(char *line, char *eline, t_msh *msh)
{
	t_cmd	*cmd;
	char	*del;
	int		quo_flag;

	trim_whitespaces(&line, &eline);
	del = line;
	quo_flag = 0;
	cmd = NULL;
	while (del < eline && (*del != '|' || quo_flag))
	{
		quo_flag = quo_check(*del, quo_flag);
		del++;
	}
	cmd = parse_simple_cmd(line, del, msh);
	if (cmd && del < eline)
	{
		cmd->next = parse_pipe(del + 1, eline, msh);
		if (!cmd->next)
			ft_free_pipeline(&cmd);
	}
	return (cmd);
}

static void	list_delim_locator(char *line, char *eline, char **del)
{
	int	block_check;
	int	quo_flag;

	block_check = 0;
	quo_flag = 0;
	*del = line;
	while (*del < eline && !(!block_check && !quo_flag
			&& ((**del == '&' && *(*del + 1) == '&')
				|| (**del == '|' && *(*del + 1) == '|'))))
	{
		if (**del == '(' && !quo_flag)
			block_check++;
		else if (**del == ')' && !quo_flag)
			block_check--;
		else
			quo_flag = quo_check(**del, quo_flag);
		*del += 1;
	}
}

static void	cmd_block_merge(t_block **head, t_block *tail)
{
	t_block	*tmp;

	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = tail;
}

static t_block	*create_new_block(t_msh *msh, char *line,
	char *eline, char mode)
{
	t_block	*cmd_block;

	cmd_block = malloc(sizeof(t_block));
	if (!cmd_block)
		return (msh->malloc_err_parse = 1, malloc_error(), NULL);
	cmd_block->pipeline = NULL;
	cmd_block->mode = mode;
	cmd_block->next = NULL;
	cmd_block->pipeline = parse_pipe(line, eline, msh);
	if (!cmd_block->pipeline)
		return (ft_free_cmd_list_block(&cmd_block), NULL);
	return (cmd_block);
}

t_block	*parse_list(char *line, char *eline, t_msh *msh, char mode)
{
	t_block	*cmd_block;
	t_block	*cmd_block_tail;
	char	*del;

	trim_whitespaces(&line, &eline);
	trim_brackets(&line, &eline);
	list_delim_locator(line, eline, &del);
	if (del == eline)
		cmd_block = create_new_block(msh, line, eline, mode);
	else
	{
		cmd_block = parse_list(line, del, msh, mode);
		if (!cmd_block)
			return (NULL);
		cmd_block_tail = parse_list(del + 2, eline, msh, *del);
		if (!cmd_block_tail)
			return (ft_free_cmd_list_block(&cmd_block), NULL);
		cmd_block_merge(&cmd_block, cmd_block_tail);
	}
	return (cmd_block);
}
