/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euiclee <euiclee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:32:05 by euiclee           #+#    #+#             */
/*   Updated: 2023/02/27 08:52:39 by euiclee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"

typedef struct s_quo
{
	char	*ret;
	char	*temp;
	char	*loca;
	int		i;
}t_quo;

/*parse*/
int			get_pipe(char *line);
int			until_pipe(char *line);
int			parsing(char *line, t_tokens **tokens, char **env);

/*parse_split*/
int			until_sep(char **token);
int			is_spaquot(char **token, int qut, int db_qut, int *len);
int			is_redirection(char **token, int qut, int db_qut, int *len);
char		**split_token(char *token);

/*parse_expand*/
int			cnt_tok(char **tok);
int			check_space(char *str);
void		plus_token(t_tokens tokens, int *ori, int *cp, t_tokens *temp);
void		free_token(t_tokens *tokens);
t_tokens	env_expand(t_tokens *tokens);

/*parse_tokens*/
int			is_tokens(char **tok, int qut, int db_qut);
int			cnt_tokens(char *token);

/*pase_env*/
int			get_len(char *str, int position);
int			get_end_with_len(char **loca, char **finish, char **env);
char		*make_ret(char **loca, char *origin, char **env, char **finish);
char		*replace_env(char **loca, char *origin, char **env);
void		check_env(t_tokens *tokens, char **env);

/*parse_redir*/
void		is_redir(t_tokens **tok, int idx, int token_num);

/*parse_quote*/
int			env_qut_check(char *str);
void		check_quote(t_tokens *tokens);
int			check_quote_num(char *str);
char		*rm_quote(char *str, int len);

/*parse_exit*/
char		*re_quo(char **loca, char *origin);
#endif