/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:28:59 by mvorslov          #+#    #+#             */
/*   Updated: 2023/01/25 19:15:46 by mvorslov         ###   ########.fr       */
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
	if (*eline == '|' || *line == '|')
		return (printf("minishell: syntax error: '%c'\n", '|'), NULL); //panic syntax error, stop here, execute nothing at all
	del = eline;
	while (del > line && *del != '|' && *del != '(' && *del != ')')
		del--;
	if (del == line)
		return (parse_redir(line, eline));
	else if (*del != '|')
		return (printf("minishell: syntax error: unexpected symbol '%c'\n", *del), NULL);
	cmd = malloc(sizeof(t_pipe));
	cmd = NULL;
	if (!cmd)
		printf("malloc error\n"); //modify after
	cmd->type = PIPE_CMD;
	cmd->left = parse_pipe(line, del - 1);
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

t_cmd	*parse_list(char *line, char *eline)
{
	t_lol	*cmd;
	char	*del;

	trim_whitespaces(&line, &eline);
	if (trim_brackets(&line, &eline))
		return (printf("minishell: syntax error: '%c'\n", *eline), NULL);
	if(list_delim_locator(line, eline, &del) == 1)
		return (parse_pipe(line, eline));
	if (del == line || del + 1 == eline)
		return (printf("minishell: syntax error: '%c'\n", *del), NULL); //panic syntax error, stop here, execute nothing at all
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
