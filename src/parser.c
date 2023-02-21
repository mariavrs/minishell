/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:28:59 by mvorslov          #+#    #+#             */
/*   Updated: 2023/02/21 18:10:14 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

t_cmd	*parse_pipe(char *line, char *eline)
{
	t_pipe	*cmd;
	char	*del;
	int		quo_flag;

	cmd = NULL;
	trim_whitespaces(&line, &eline);
	del = eline - 1;
	quo_flag = 0;
	while (del > line && ((*del != '|' && *del != '(' && *del != ')') || quo_flag))
	{
		quo_flag = quo_check(*del, quo_flag);
		del--;
	}
	if (del == line)
		return (parse_simple_cmd(line, eline));
	cmd = malloc(sizeof(t_pipe));
	if (!cmd)
		printf("malloc error\n"); //modify after
	cmd->type = PIPE_CMD;
	cmd->left = parse_pipe(line, del);
	if (cmd->left)
		cmd->right = parse_pipe(del + 1, eline);
	if (!cmd->right)
	{
		if (cmd->left)
			free(cmd->left);
		free(cmd);
	}
	return ((t_cmd *)cmd);
}

int	list_delim_locator(char *line, char *eline, char **del)
{
	int	block_check;
	int	quo_flag;

	block_check = 0;
	quo_flag = 0;
	*del = eline - 1;
	while (*del > line && !(!block_check && !quo_flag
		&& ((**del == '&' && *(*del - 1) == '&')
			|| (**del == '|' && *(*del - 1) == '|'))))
	{
		if (**del == ')' && !quo_flag)
			block_check++;
		else if (**del == '(' && !quo_flag)
			block_check--;
		else
			quo_flag = quo_check(**del, quo_flag);
		*del = *del - 1;
	}
	if (*del == line)
		return (1);
	*del = *del - 1;
	return (0);
}

t_cmd	*parse_list(char *line, char *eline)
{
	t_lol	*cmd;
	char	*del;

	cmd = NULL;
	trim_whitespaces(&line, &eline);
	trim_brackets(&line, &eline);
	if(list_delim_locator(line, eline, &del) == 1)
		return (parse_pipe(line, eline));
	cmd = malloc(sizeof(t_lol));
	if (!cmd)
		printf("malloc error\n"); //modify after
	cmd->type = LIST_CMD;
	cmd->mode = *del;
	cmd->left = parse_list(line, del);
	if (cmd->left)
		cmd->right = parse_list(del + 2, eline);
	if (!cmd->right)
	{
		if (cmd->left)
			free(cmd->left);
		free(cmd);
	}
	return ((t_cmd *)cmd);
}
