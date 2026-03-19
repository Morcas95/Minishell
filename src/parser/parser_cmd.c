/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalonso <maalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 11:11:52 by maalonso          #+#    #+#             */
/*   Updated: 2026/03/19 13:20:06 by maalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	free_cmd_on_error(t_cmd *cmd)
{
	if (cmd->args)
		free_string_array(cmd->args);
	if (cmd->redirects)
		free_redir_list(cmd->redirects);
	free(cmd);
	return (0);
}

static int	handle_redir(t_token *tokens, t_cmd *cmd)
{
	t_redir_type	type;
	t_redir			*redir;

	if (!tokens->next)
		return (free_cmd_on_error(cmd), -1);
	type = token_to_redir_type(tokens->type);
	redir = create_redir(type, ft_strdup(tokens->next->value));
	if (!redir)
		return (free_cmd_on_error(cmd), -1);
	add_redir_to_cmd(cmd, redir);
	return (0);
}

t_cmd	*parse_one_cmd(t_token *tokens)
{
	t_cmd	*cmd;

	cmd = create_cmd();
	if (!cmd)
		return (NULL);
	cmd->args = fill_args(tokens);
	if (!cmd->args)
		return (free(cmd), NULL);
	while (tokens && tokens->type != TOKEN_PIPE)
	{
		if (tokens->type != TOKEN_WORD)
		{
			if (handle_redir(tokens, cmd) < 0)
				return (NULL);
			tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	return (cmd);
}

void	add_redir_to_cmd(t_cmd *cmd, t_redir *new_redir)
{
	t_redir	*current;

	if (!cmd->redirects)
	{
		cmd->redirects = new_redir;
		return ;
	}
	current = cmd->redirects;
	while (current->next)
		current = current->next;
	current->next = new_redir;
}

t_cmd	*create_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirects = NULL;
	cmd->next = NULL;
	return (cmd);
}
