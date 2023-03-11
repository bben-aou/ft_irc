/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalidCommand.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-aou <bben-aou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 13:08:07 by bben-aou          #+#    #+#             */
/*   Updated: 2023/03/11 13:39:54 by bben-aou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Server/server.hpp"

// & ------------- Uknown Command --------------------------

void    Server::uknownCommandRpl(User * user, std::string command) const{
    buildResponseToSend(NULL, user, repliesMessage("421", user) + command + " ::Unknown command");
}