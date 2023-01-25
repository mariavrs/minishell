/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:28:59 by mvorslov          #+#    #+#             */
/*   Updated: 2023/01/24 23:11:00 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

t_cmd	*parse_exec(char *line, char *eline)
{
	t_exec	*cmd;
	int		i;

	i = -1;
	cmd = malloc(sizeof(t_exec));
	if (!cmd)
		printf("malloc error\n"); //modify after
	cmd->type = EXEC_CMD;
	cmd->argv = NULL;
	cmd->argv = malloc(sizeof(char *) * (words_counter(line, eline) + 1));
	if (!cmd->argv)
		printf("malloc error\n"); //modify after
	while (line <= eline && check_whitespace(*line))
		line++;
	while (line <= eline)
	{
		cmd->argv[++i] = line;
		while (line <= eline && !check_whitespace(*line))
			line++;
		while (line <= eline && check_whitespace(*line))
		{
			*line = '\0';
			line++;
		}
	}
	return ((t_cmd *)cmd);
}

t_cmd	*parse_redir(char *line, char *eline)
{
	t_redir	*cmd;

	(void)cmd;
	return(parse_exec(line, eline));
}

t_cmd	*parse_pipe(char *line, char *eline)
{
	t_pipe	*cmd;
	char	*del;

	trim_whitespaces(&line, &eline);
/* 	if (*eline == '|' || *line == '|')
		panic syntax error, stop here, execute nothing at all */
	del = eline;
	while (del > line && *del != '|')
		del--;
	if (del == line)
		return (parse_redir(line, eline));
	cmd = malloc(sizeof(t_pipe));
	if (!cmd)
		printf("malloc error\n"); //modify after
	cmd->type = PIPE_CMD;
	cmd->left = parse_pipe(line, del);
	cmd->right = parse_pipe(del + 1, eline);
	return ((t_cmd *)cmd);
}

t_cmd	*parse_list(char *line, char *eline)
{
	t_lol	*cmd;
	char	*del;

	trim_whitespaces(&line, &eline);
	if(list_delim_locator(line, eline, &del) == 1) //there is only one pipeline
		return (parse_pipe(line, eline));
	cmd = NULL;
	cmd = malloc(sizeof(t_lol));
	if (!cmd)
		printf("malloc error\n"); //modify after
	cmd->type = LIST_CMD;
	if (*del == '&')
		cmd->mode = 0;
	else
		cmd->mode = 1;
	cmd->left = parse_list(line, del - 1);
	cmd->right = parse_list(del + 2, eline);
	return ((t_cmd *)cmd);
}