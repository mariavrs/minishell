/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:28:59 by mvorslov          #+#    #+#             */
/*   Updated: 2023/02/11 00:17:52 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

void	set_to_null_and_move(char **line)
{
	**line = '\0';
	*line = *line + 1;
}

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

t_cmd	*parse_simple_cmd(char *line, char *eline)
{
	t_spl_cmd	*cmd;
	int		i_arg;
	int		i_redir;

	i_arg = -1;
	i_redir = -1;
	cmd = ft_malloc_spl_cmd(line, eline);
	if (!cmd)
		return (NULL);
	cmd->type = EXEC_CMD;
	*eline = '\0';
	while (line < eline)
	{
		if (*line != '<' && *line != '>')
			cmd->argv[++i_arg] = line;
		while (line < eline && !check_whitespace(*line) && *line != '<' && *line != '>')
			line++;
		while (line < eline && check_whitespace(*line) && *line != '<' && *line != '>')
			set_to_null_and_move(&line);
		if (*line == '<' || *line == '>')
		{
			i_redir++;
			if (*line != *(line + 1))
				cmd->redir[i_redir].mode = *line;
			else if (*line == '>')
				cmd->redir[i_redir].mode = '+';
			else if (*line == '<')
				cmd->redir[i_redir].mode = '-';
			set_to_null_and_move(&line);
			if (*line == '<' || *line == '>')
				set_to_null_and_move(&line);
			while (line < eline && check_whitespace(*line))
				set_to_null_and_move(&line);
			cmd->redir[i_redir].file = line;
			while (line < eline && !check_whitespace(*line) && *line != '<' && *line != '>')
				line++;
			while (line < eline && check_whitespace(*line) && *line != '<' && *line != '>')
				set_to_null_and_move(&line);
		}
	}
	return ((t_cmd *)cmd);
}

/* t_cmd	*parse_exec(char *line, char *eline)
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
	char	*del;

	cmd = NULL;
	if (trim_whitespaces(&line, &eline))
		return (NULL);
	if (*eline - 1 == '<' || *eline -1 == '>')
		return(printf("minishell: syntax error: '%c'\n", *eline), NULL);
	del = line;
	while (del < eline && *del != '<' && *del != '>')
		del++;
	if (del == eline)
		return(parse_exec(line, eline));
	else if (del != del + 1)
		cmd->mode = *del;
	else if (del == '>' && del + 1 == '>')
		cmd->mode = '+';
	else if (del == '<' && del + 1 == '<')
		cmd->mode = '-';
	while (*del == '>' || *del == '<')
		del++;
	while (check_whitespace(*del))
		del++;
	cmd->file = del;
	while (!check_whitespace(*del))
		del++;
	cmd->efile = del;
	cmd->cmd = parse_redir(line, eline);
	return((t_cmd *)cmd);
} */

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
