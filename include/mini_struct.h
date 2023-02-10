/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 00:38:32 by ede-smet          #+#    #+#             */
/*   Updated: 2023/02/10 23:10:31 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_STRUCT_H
# define MINI_STRUCT_H

# define EXEC_CMD 1
//# define REDIR_CMD 2
# define PIPE_CMD 3
# define LIST_CMD 4

//# define MAXARGC 10

typedef struct s_cmd
{
	int		type;
}	t_cmd;

typedef struct s_redir
{
	char	*file;
	char	mode;
	int		fd;
}	t_redir;

typedef struct s_simple_cmd
{
	int		type;
	int		argc;
	char	**argv;
	int		redir_counter;
	int		stdin_cpy;
	int		stdout_cpy;
	t_redir	*redir;
}	t_spl_cmd;

/* typedef struct s_exec_cmd
{
	int		type;
// 	char	*argv[MAXARGC];
//	char	*eargv[MAXARGC];
	char	**argv;
	char	**eargv;
}	t_exec;

typedef struct s_redir_cmd
{
	int		type;
	t_cmd	*cmd;
	char	*file;
	char	*efile;
	int		mode;
	int		fd;
}	t_redir; */

typedef struct s_pipe_cmd
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipe;

typedef struct s_logical_list_cmd
{
	int		type;
	char	mode;
	t_cmd	*left;
	t_cmd	*right;
}	t_lol;

#endif
