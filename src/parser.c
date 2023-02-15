/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:28:59 by mvorslov          #+#    #+#             */
/*   Updated: 2023/02/15 16:45:40 by mvorslov         ###   ########.fr       */
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

int	parse_pipe(t_cmd **res, char *line, char *eline)
{
	t_pipe	cmd;
	char	*del;
	int		quo_flag;

	*res = NULL;
	printf("im here\n");
	trim_whitespaces(&line, &eline);
	if (*eline - 1 == '|' || *line == '|')
		return (ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2), 1); //panic syntax error, stop here, execute nothing at all
	del = eline - 1;
	quo_flag = 0;
	while (del > line && ((*del != '|' && *del != '(' && *del != ')') || quo_flag))
	{
		quo_flag = quo_check(*del, quo_flag);
		del--;
	}
	if (del == line)
		return (parse_simple_cmd(res, line, eline));
	else if (*del != '|')//check if it can actually happen
		return (ft_putstr_fd("minishell: syntax error: incorrect usage of parentheses\n", 2), 1);
	cmd.type = PIPE_CMD;
	printf("hey\n");
	if (parse_pipe(&cmd.left, line, del) || parse_pipe(&cmd.right, del + 1, eline)) 
		return (1);
	printf("%d\n", cmd.left->type);
	printf("%d\n", cmd.right->type);
	*res = (t_cmd *)(&cmd);
	return (0);
}

int	parse_list(t_cmd **res, char *line, char *eline)
{
	t_lol	cmd;
	char	*del;

	*res = NULL;
	trim_whitespaces(&line, &eline);
	if (trim_brackets(&line, &eline))
		return (ft_putstr_fd("minishell: syntax error near unexpected token `)'\n", 2), 1);
	if (list_delim_locator(line, eline, &del) == 1)
		return (parse_pipe(res, line, eline));
	if (del == line || del + 1 == eline)
		return (ft_putstr_fd("minishell: syntax error near unexpected token `", 2),
			ft_putchar_fd(*del, 2), ft_putstr_fd("\"\n", 2), 1); //panic syntax error, stop here, execute nothing at all
	cmd.type = LIST_CMD;
	cmd.mode = *del;
	if (parse_list(&cmd.left, line, del) || parse_list(&cmd.right, del + 2, eline)) 
		return (1);
	*res = (t_cmd *)(&cmd);
	return (0);
}
