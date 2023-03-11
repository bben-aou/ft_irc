/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-aou <bben-aou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:43:33 by bben-aou          #+#    #+#             */
/*   Updated: 2023/03/11 14:53:16 by bben-aou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Server/server.hpp"

// @ Syntax: PASS <password> | Sets a connection password. This command must be sent before the NICK/USER registration combination.

void    Server::pass(User* user, std::string password){
    if (user->isAuthenticated())
       buildResponseToSend(NULL, user, repliesMessage("462", user) + ":You may not reregister");
    else if (password.empty())
        buildResponseToSend(NULL, user, repliesMessage("461", user) + "PASS :Not enough parameters");
    else if (password != this->_password)
        buildResponseToSend(NULL, user, repliesMessage("464", user) + ":Password incorrect");
    else{
        user->setPassword(password);
        if (user->Authenticate(this->_password)){
            welcome(user);
        }
    }
}