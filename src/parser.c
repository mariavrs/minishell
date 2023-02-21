/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:28:59 by mvorslov          #+#    #+#             */
/*   Updated: 2023/02/16 15:05:13 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

/*
void	ft_free_spl_cmd(t_spl_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->argv)
		free(cmd->argv);
	if (cmd->redir)
		free(cmd->redir);
	cmd = NULL;
}

t_spl_cmd	*ft_malloc_spl_cmd(char *line, char *eline)
{
	t_spl_cmd	*cmd;

	cmd = NULL;
	cmd = malloc(sizeof(t_spl_cmd));
	if (!cmd)
		return(printf("malloc error\n"), NULL); //modify after
	cmd->argv = NULL;
	cmd->redir = NULL;
	if (words_counter(line, eline, cmd))
		return (ft_free_spl_cmd(cmd), NULL);
	cmd->argv = malloc(sizeof(char *) * (cmd->argc + 1));
	cmd->redir = malloc(sizeof(t_redir) * (cmd->redir_counter));
	if (!cmd->argv || !cmd->redir)
		return(ft_free_spl_cmd(cmd), printf("malloc error\n"), NULL); //modify after
	cmd->argv[cmd->argc] = NULL;
	cmd->stdin_cpy = 0;
	cmd->stdout_cpy = 0;
	return (cmd);
}
*/

t_cmd	*parse_pipe(char *line, char *eline)
{
	t_pipe	*cmd;
	char	*del;
	int		quo_flag;

	cmd = NULL;
	if (trim_whitespaces(&line, &eline))
		return (NULL);
	if (*eline - 1 == '|' || *line == '|')
		return (printf("minishell: syntax error: '%c'\n", '|'), NULL); //panic syntax error, stop here, execute nothing at all
	del = eline - 1;
	quo_flag = 0;
	while (del > line && ((*del != '|' && *del != '(' && *del != ')') || quo_flag))
	{
		quo_flag = quo_check(*del, quo_flag);
		del--;
	}
	if (del == line)
		return (parse_simple_cmd(line, eline));
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
	if (trim_whitespaces(&line, &eline) || trim_brackets(&line, &eline))//this should be modified
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
