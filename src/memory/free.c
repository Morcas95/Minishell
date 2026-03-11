/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcerezo- <dcerezo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:53:40 by dcerezo-          #+#    #+#             */
/*   Updated: 2026/03/11 17:54:55 by dcerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Helper: free NULL-terminated array of strings

void free_string_array(char **arr)
{
    int i;

    if (!arr)
        return;
    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

// Free tokens list 

void free_tokens(t_token *tokens)
{
    t_token *tmp;

    while (tokens)
    {
        tmp = tokens->next;
        if (tokens->value)
            free(tokens->value);
        free(tokens);
        tokens = tmp;
    }
}

//Free redirections list

void free_redir_list(t_redir *redir)
{
    t_redir *tmp;

    while (redir)
    {
        tmp = redir->next;
        if (redir->file)
            free(redir->file);
        free(redir);
        redir = tmp;
    }
}

// Free command list

void free_cmd_list(t_cmd *cmd)
{
    t_cmd *tmp;

    while (cmd)
    {
        tmp = cmd->next;
        if (cmd->args)
            free_string_array(cmd->args);
        if (cmd->redirects)
            free_redir_list(cmd->redirects);
        free(cmd);
        cmd = tmp;
    }
}