/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notice.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-aou <bben-aou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 13:01:58 by bben-aou          #+#    #+#             */
/*   Updated: 2023/03/11 15:01:39 by bben-aou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Server/server.hpp"

// & ------------- Command : + NOTICE + ---------------------- 

// @ Syntax: NOTICE <msgtarget> <message> | This command works similarly to PRIVMSG, except automatic replies must never be sent in reply to NOTICE messages

void    Server::notice(User * user, std::vector<std::string> & targets, std::string noticeMessage) const{
    std::vector<std::string>::const_iterator   targetIt;
    std::vector<User>::const_iterator          userIt;
    std::vector<Channel>::const_iterator       chanIt;

    if (targets.empty() || noticeMessage.empty())
        return;
    for (targetIt = targets.begin(); targetIt != targets.end(); ++targetIt){
        if ((*targetIt)[0] == '#'){
            for (chanIt = _channels.begin(); chanIt != _channels.end(); ++chanIt){
                if (chanIt->getChannelName() == *targetIt)
                    break;
            }
            buildResponseToSendToChanMembers(user, *chanIt, generatePrefix(user) + "NOTICE " + *targetIt + " :" + noticeMessage);
        }
        else{
            for (userIt = _users.begin(); userIt != _users.end(); ++userIt){
                if (userIt->getNickName() == *targetIt){
                    buildResponseToSend(user, &*userIt, "NOTICE " + *targetIt + " :" + noticeMessage);
                    break;
                }
            }
        }
    }
}