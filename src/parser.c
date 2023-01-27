/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:28:59 by mvorslov          #+#    #+#             */
/*   Updated: 2023/01/27 12:48:34 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

t_cmd	*parse_exec(char *line, char *eline)
{
	t_exec	*cmd;
	int		i;

	i = -1;
	cmd = NULL;
	if (trim_whitespaces(&line, &eline))
		return (NULL);
	cmd = malloc(sizeof(t_exec));
	if (!cmd)
		printf("malloc error\n"); //modify after
	cmd->type = EXEC_CMD;
	cmd->argv = NULL;
	cmd->argv = malloc(sizeof(char *) * (words_counter(line, eline) + 1));
	if (!cmd->argv)
		printf("malloc error\n"); //modify after
	while (line < eline)
	{
		cmd->argv[++i] = line;
		while (line < eline && !check_whitespace(*line))
			line++;
		while (line < eline && check_whitespace(*line))
		{
			*line = '\0';
			line++;
		}
	}
	*line = '\0';
	cmd->argv[++i] = NULL;
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

	cmd = NULL;
	if (trim_whitespaces(&line, &eline))
		return (NULL);
	if (*eline - 1 == '|' || *line == '|')
		return (printf("minishell: syntax error: '%c'\n", '|'), NULL); //panic syntax error, stop here, execute nothing at all
	del = eline - 1;
	while (del > line && *del != '|' && *del != '(' && *del != ')')
		del--;
	if (del == line)
		return (parse_redir(line, eline));
	else if (*del != '|')
		return (printf("minishell: syntax error: incorrect usage of parentheses\n"), NULL);
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

t_cmd	*parse_list(char *line, char *eline)
{
	t_lol	*cmd;
	char	*del;

	cmd = NULL;
	if (trim_whitespaces(&line, &eline) || trim_brackets(&line, &eline))
		return (printf("minishell: syntax error: incorrect usage of parentheses\n"), NULL);
	if(list_delim_locator(line, eline, &del) == 1)
		return (parse_pipe(line, eline));
	if (del == line || del + 1 == eline)
		return (printf("minishell: syntax error: '%c'\n", *del), NULL); //panic syntax error, stop here, execute nothing at all
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
