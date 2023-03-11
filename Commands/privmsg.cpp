/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-aou <bben-aou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 13:03:24 by bben-aou          #+#    #+#             */
/*   Updated: 2023/03/11 15:03:52 by bben-aou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Server/server.hpp"

// & ------------- Command : + PRIVMSG + ---------------------- 

// @ Syntax: PRIVMSG <msgtarget> :<message> | Sends <message> to <msgtarget>, which is usually a user or channel

void    Server::privmsg(User *user, std::vector<std::string> & targets, std::string message) const{
    std::vector<std::string>::const_iterator  targetIt;
    std::vector<User>::const_iterator         userIt;
    std::vector<Channel>::const_iterator      chanIt;
    
    if (targets.empty()){
        buildResponseToSend(NULL, user, repliesMessage("411", user) + ":No recipient given (<PRIVMSG>)");
        return;
    }
    if (message.empty()){
        buildResponseToSend(NULL, user, repliesMessage("412", user) + ":No text to send");
        return;
    }
    for (targetIt = targets.begin(); targetIt != targets.end(); ++targetIt){
        if ((*targetIt)[0] == '#'){
            for (chanIt = _channels.begin(); chanIt != _channels.end(); ++chanIt){
                if (chanIt->getChannelName() == *targetIt)
                    break;
            }
            if (chanIt == _channels.end())
                buildResponseToSend(NULL, user, repliesMessage("401", user) + *targetIt + " :No such nick/channel");
            else if (!(chanIt->checkIfUserAllowedToMessageChannel(user->getNickName())))
                buildResponseToSend(NULL, user, repliesMessage("404", user) + *targetIt + " :Cannot send to channel");
            else
                buildResponseToSendToChanMembers(user, *chanIt, generatePrefix(user) + "PRIVMSG " + *targetIt + " :"+ message);
        }
        else{
            for (userIt = _users.begin(); userIt != _users.end(); ++userIt){
                if (userIt->getNickName() == *targetIt)
                    break;
            }
            if (userIt == _users.end()){
                buildResponseToSend(NULL, user, repliesMessage("401", user) + *targetIt + " :No such nick/channel");
                return;
            }
            buildResponseToSend(user, &*userIt, "PRIVMSG " + *targetIt + " :" +message);
        }
    }
}