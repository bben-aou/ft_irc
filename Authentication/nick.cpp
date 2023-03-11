/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-aou <bben-aou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:45:26 by bben-aou          #+#    #+#             */
/*   Updated: 2023/03/11 14:54:30 by bben-aou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Server/server.hpp"

void    Server::updateNickNameInChannels(std::string currentNickName, std::string newNickName){
    std::vector<Channel>::iterator  channel_it;
    for (channel_it = _channels.begin(); channel_it != _channels.end(); ++channel_it)
        channel_it->changeUserNickName(currentNickName, newNickName);
}

// & ------------- Command : + NICK + ---------------------- 

// @ Syntax: NICK <nickname> | Allows a client to change their IRC nickname.

void    Server::nick(User* user, std::string nickName){
    std::vector<User>::const_iterator   it;
    
    if (nickName.empty())
        buildResponseToSend(NULL, user, repliesMessage("431", user) + ":No nickname given");
    else if (checkIfNickNameAlreadyUsed(nickName))
        buildResponseToSend(NULL, user, repliesMessage("433", user) + nickName + " :Nickname is already in use");
    else if (!checkIfNickNameValid(nickName))
        buildResponseToSend(NULL, user, repliesMessage("432", user) + nickName + " :Erroneous nickname");
    else{
        for (it = _users.begin(); it != _users.end(); ++it){
            if (user->isAuthenticated())
                buildResponseToSend(user, &*it, "Changed his nickname to " + nickName); // inform All the users that you changed your nickname
            }
        if (user->isAuthenticated())
            updateNickNameInChannels(user->getNickName(), nickName); // update the old nickname in the channels
        user->setNickName(nickName);
        if (!(user->isAuthenticated()) && user->Authenticate(_password))
            welcome(user);
    }
}