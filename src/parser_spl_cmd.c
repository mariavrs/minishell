#include "../include/mini_fun.h"

int	check_if_in_str(char c, char *str)
{
	while (*str)
		if (c == *str++)
			return (1);
	return (0);
}

int	redir_info(char *line, char *mode)
{
	int		count;

	count = 1;
	if (*line != *(line + 1))
		*mode = *line;
	else if (*line == '<')
		*mode = '-';
	else
		*mode = '+';
	if (*line == *(line + 1))
		count++;
	while (*(line + count) && check_if_in_str(*(line + count), STR_WHSPACE))
		count++;
	if (check_if_in_str(*(line + count), STR_REDIRSIGN))
		return (printf("minishell: syntax error: '%c'\n", *(line + count)), *mode = '\0', 0); //manage error
	return (count);
}

int	wrd_collect(char *line, int *env_flag)
{
	int	count;
	int	quo_flag;

	count = 0;
	*env_flag = 0;
	quo_flag = quo_check(*line, 0);
	if (quo_flag)
	{
		while (*(line + count) && quo_flag)
		{
			if (*(line + count) == '$' && quo_flag != 1)
				*env_flag = 1;
			count++;
			quo_flag = quo_check(*(line + count), quo_flag);
		}
	}
	else
	{
		while (*(line + count) && !check_if_in_str(*(line + count), STR_WHSPACE)
			&& !check_if_in_str(*(line + count), STR_QUOTE))
		{
			if (*(line + count) == '$')
				*env_flag = 1;
			count++;
		}
	}
	return (count);
}

char	*env_join_str(char *line, int symb_count)
{
	char	*str;

//	THIS FUN WILL BE DEVELOPED LATER (for now it's just a copy of the general one)
	str = malloc(sizeof(char) * (symb_count));
	str[symb_count] = '\0';
	while (--symb_count >= 0)
		str[symb_count] = *(line + symb_count);
	return (str);
}

int	fill_the_struct(t_spl_cmd *cmd, char *line, int argc, int redirc, int symb_count, char mode, int env_flag)
{
	char	*str;

	if (!env_flag)
	{
		str = malloc(sizeof(char) * (symb_count + 1));
		str[symb_count] = '\0';
		while (--symb_count >= 0)
			str[symb_count] = *(line + symb_count);
	}
	else
		str = env_join_str(line, symb_count);
	if (mode)
	{
		cmd->redir[redirc - 1].file = str;
		cmd->redir[redirc - 1].mode = mode;
	}
	else
		cmd->argv[argc - 1] = str;
	return (0);
}

int	ft_malloc_spl_cmd(t_spl_cmd *cmd, int argc, int redirc)
{
	cmd->argv = NULL;
	cmd->redir = NULL;
	cmd->argv = malloc(sizeof(char *) * (argc + 1));
	if (!cmd->argv)
		return (1);
	cmd->redir = malloc(sizeof(t_redir) * redirc);
	if (!cmd->redir)
		return (free(cmd->argv), 1);//print error
	cmd->argv[argc] = NULL;
	cmd->argc = argc;
	cmd->redir_counter = redirc;
	return (0);
}

int	build_the_struct(t_spl_cmd *cmd, char *line, int argc, int redirc)
{
	int		symb_count;
	char	mode;
	int		env_flag;

	symb_count = 0;
	mode = '\0';
	while (line && check_if_in_str(*line, STR_WHSPACE))
		line++;
	if (!(*line))
		return (ft_malloc_spl_cmd(cmd, argc, redirc));
	if (check_if_in_str(*line, STR_REDIRSIGN))
	{
		line += redir_info(line, &mode);
		if (!mode)
			return (1);//manage error
		redirc++;
	}
	else
		argc++;
	symb_count = wrd_collect(line, &env_flag);
	if (build_the_struct(cmd, line + symb_count, argc, redirc))
		return (1);//manage error
	return (fill_the_struct(cmd, line, argc, redirc, symb_count, mode, env_flag));
}

t_cmd	*parse_simple_cmd(char *line, char *eline)
{
	t_spl_cmd	*cmd;

	cmd = NULL;
	if (trim_whitespaces(&line, &eline))
		return (NULL);
	cmd = malloc(sizeof(t_spl_cmd));
	if (!cmd)
		return (NULL); //manage error etc
	cmd->type = EXEC_CMD;
	*eline = '\0';
/* 	if (words_counter)
		return (NULL); //print error */
	if (build_the_struct(cmd, line, 0, 0))
		return (free(cmd), NULL);
	cmd->stdin_cpy = 0;
	cmd->stdout_cpy = 0;
	return ((t_cmd *)cmd);
}
