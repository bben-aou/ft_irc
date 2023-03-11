/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-aou <bben-aou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 13:05:08 by bben-aou          #+#    #+#             */
/*   Updated: 2023/03/11 15:03:23 by bben-aou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Server/server.hpp"

// & ------------- Command : + PONG + ---------------------- 

// @ Syntax: PONG <server1> [<server2>] | this command is a reply to the PING command and works in much the same way

void    Server::pong(User* user, std::string response) const{
    buildResponseToSend(NULL, user, "PONG :" + response);
}