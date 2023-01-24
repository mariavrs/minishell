/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:28:59 by mvorslov          #+#    #+#             */
/*   Updated: 2023/01/24 18:06:46 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

t_cmd	*parse_exec()
{
	t_exec	*cmd;
}

t_cmd	*parse_redir(char *line, char *eline)
{
	t_redir	*cmd;
}

t_cmd	*parse_pipe(char *line, char *eline)
{
	t_pipe	*cmd;
	char	*del;
	char	*edel;

	trim_whitespaces(&line, &eline);
	del = eline;
	while (del > line && *del != '|')
		del--;
	if (del == line)
		return (parse_redir(line, eline));
	edel = del + 1;
	cmd = malloc(sizeof(t_pipe));
	cmd->type = PIPE_CDM;
	cmd->left = parse_pipe(line, del);
	cmd->right = parse_pipe(edel, eline);
	return ((t_cmd *)cmd);
}

t_cmd	*parse_list(char *line, char *eline)
{
	t_list	*cmd;
	char	*del;
	char	*edel;

	trim_whitespaces(&line, &eline);
	if(list_delim_locator(line, eline, &del, &edel) == 1) //there is only one pipeline
		return (parse_pipe(line, eline));
	cmd = malloc(sizeof(t_list));
	cmd->type = LIST_CDM;
	if (*del == '&')
		cmd->mode = 0;
	else
		cmd->mode = 1;
	cmd->left = parse_list(line, del);
	cmd->right = parse_list(edel, eline);
	return ((t_cmd *)cmd);
}