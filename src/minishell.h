/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas-ma <lucas-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:38:30 by lucas-ma          #+#    #+#             */
/*   Updated: 2022/12/16 01:03:20 by lucas-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//------------------------------INCLUDES------------------------------//
# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <errno.h>

//------------------------------DEFINES------------------------------//
# define OPERATORS		"<>|"
# define WHITE_SPACE	" \t\r\n\v\f"

//------------------------------GLOBAL_VARS------------------------------//
extern int	g_exit_status;

//------------------------------STRUCTS------------------------------//
typedef enum e_type
{
	E_WORD,
	E_CMD,
	E_PIPE,
	E_IN,
	E_OUT,
	E_APPEND,
	E_HDOC,
	E_BUILT
}	t_type;

typedef struct s_tree
{
	void			*token;
	int				type;
	int				p[2];
	struct s_tree	*left;
	struct s_tree	*right;
	struct s_tree	*parent;
}					t_tree;

typedef struct s_exec
{
	int		n_c;
	int		c;
	int		fd;
	int		pid;
}					t_exec;

//------------------------------ENV------------------------------//
void	get_env(t_list **env, char **envp);
void	print_env(t_list *env, int fd);
char	**env_matrix(t_list *env);

//------------------------------FREE_FUNCS------------------------------//
void	free_matrix(char **matrix);
void	free_str(char *str);
void	free_tree(t_tree *tree);

//------------------------------BUILTINS------------------------------//
void	builtins(t_tree *branch, t_list **env, int fd);

//------------------------------EXEGGUTOR------------------------------//
void	exeggutor(t_tree **root, t_list **env, int c);
void	start_tree(t_tree *tree, t_list *env, t_exec *exec);
void	do_comand(t_tree *tree, t_list *env, t_exec *exec);
void	child_labor(t_tree *tree, t_list *env, t_exec *exec);

//------------------------------REDIR------------------------------//
void	redir(t_tree *branch, t_exec *exec);

//------------------------------PATH_UTILS------------------------------//
char	*cmd_path(char *cmd, t_list *env);
char	*absolute_path(char *cmd);

//------------------------------RELATIVE_PATH------------------------------//
char	*relative_path(char *cmd, t_list *env);
char	*get_path(char *env, char *cmd);
char	*get_cmd_path(char **path, char *cmd);
int		is_path(char *str, char *path);

//------------------------------PARSER_MAIN-----------------------------//
t_tree	*parser_main(char *s, t_list *env);

//------------------------------PARSE_UTILS2---------------------------//
int		is_node_red(t_tree *node);
int		is_node_cmd(t_tree *node);
int		is_node_pipe(t_tree *node);

#endif
