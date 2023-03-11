/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-aou <bben-aou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 12:50:52 by bben-aou          #+#    #+#             */
/*   Updated: 2023/03/11 15:00:16 by bben-aou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Server/server.hpp"

// ^ ------------------- Utils : MODE -------------------

void    Server::showChannelModes(User * user, Channel * channel){
    std::string mode = " +";

    if (!(channel->getAllowOutMessageStatus()))
        mode = mode + "n";
    if (channel->getPrivateChannelStatus())
        mode = mode + "p";
    if (channel->getSecretChannelStatus())
        mode = mode + "s";
    if (channel->getOperatorsTopicControlStatus())
        mode = mode + "t";
    if (channel->getInviteOnlyChannelStatus())
        mode = mode + "i";
    if (channel->getMaxMembers() != 0)
        mode = mode + "l" + std::to_string(channel->getMaxMembers());
    if (mode == " +")
        mode.clear();
    buildResponseToSend(NULL, user, repliesMessage("324", user) + channel->getChannelName() + mode); 
}

//* User Modes : TODO Later (user modes not required)
void    Server::userModes(User* user, User* target, std::vector<std::string> modes){
    (void)target;
    if (modes.empty())
        buildResponseToSend(NULL, user, repliesMessage("221", user));
    else
        buildResponseToSend(NULL, user, repliesMessage("501", user) + "MODE :Uknown MODE flag");
}

//* Channel Modes
void    Server::channelModes(User * user, Channel *channel, std::vector<std::string> modes){
    std::vector<std::string>::const_iterator    argsIt;
    std::string      modeLine;
    User * target;
    size_t      i;
    std::string modeStatus;
    int     limitNumber;
    bool        addMode;
    
    if (modes.empty()){
        showChannelModes(user, channel);
        return;
    }
    argsIt = modes.begin();
    modeLine = *argsIt;
    argsIt += 1;
    
    if (modeLine[0] == '+')
        addMode = true;
    else if (modeLine[0] == '-')
        addMode = false;
    else{
        buildResponseToSend(NULL, user, repliesMessage("472", user) + modeLine[0] + " :is unknown mode char to me for " + channel->getChannelName());
        return ;
    }
    for (i = 1; i < modeLine.size(); ++i){
        if (modeLine[i] == 'o'){
            if (argsIt->empty()){
                buildResponseToSend(NULL, user, repliesMessage("461", user) + "MODE :Not enough parameters");
                return;
            }
            target = getUser(*(argsIt++));
            if (!target){
                buildResponseToSend(NULL, user, repliesMessage("441", user) + *(argsIt - 1) + " " + channel->getChannelName() + " :They aren't on that channel");
                return ;
            }
            if (channel->checkSuperUserPermission(user->getNickName())){
                if (addMode){
                    modeStatus = "+";
                    channel->addUserToChannelOperators(target->getNickName());
                }
                else if (!addMode){
                    modeStatus = "-";
                    channel->deleteUserFromChannelOperators(target->getNickName());
                }
                buildResponseToSendToChanMembers(user, *channel, generatePrefix(user) + "MODE " + modeStatus + "o " + target->getNickName());
                buildResponseToSend(user, user, "MODE " + channel->getChannelName() + " " + modeStatus + "o " + target->getNickName());
            }
            else{
                buildResponseToSend(NULL, user, repliesMessage("482", user) + channel->getChannelName() + " :You're not channel operator");
                return;
            }
        }
        else if (!channel->checkSuperUserPermission(user->getNickName())){
            buildResponseToSend(NULL, user, repliesMessage("482", user) + channel->getChannelName() + " :You're not channel operator");
                return;
        }
        else if (modeLine[i] == 'n')
            channel->setAllowOutMessage(user->getNickName(), !addMode);
        else if (modeLine[i] == 'p'){
            if (channel->getSecretChannelStatus())
                channel->setSecretChannel(user->getNickName(), false);
            channel->setPrivateChannel(user->getNickName(), addMode);
        }
        else if (modeLine[i] == 's'){
            if (channel->getPrivateChannelStatus())
                channel->setPrivateChannel(user->getNickName(), false);
            channel->setSecretChannel(user->getNickName(), addMode);
        }
        else if (modeLine[i] == 'i')
            channel->setInviteOnlyChannel(user->getNickName(), addMode);
        else if (modeLine[i] == 't')
            channel->setOperatorsTopicControl(user->getNickName(), addMode);
        else if (modeLine[i] == 'l'){
            if (addMode){
                if (argsIt->empty()){
                    buildResponseToSend(NULL, user, repliesMessage("461", user) + "MODE :Not enough parameters");
                    return;
                }
                std::stringstream tmp;
                tmp << *(argsIt++);
                if (!tmp.fail()){
                    tmp >> limitNumber;
                    if (limitNumber > 0)
                        channel->setMaxMembers(user->getNickName(), limitNumber);
                }
            }
            else
                channel->setMaxMembers(user->getNickName(), 0);
        }
        else
        {
            buildResponseToSend(NULL, user, repliesMessage("472", user) + modeLine[0] + " :is unknown mode char to me for " + channel->getChannelName());
            return ;
        }
    }
    showChannelModes(user, channel);
}

// & ------------- Command : + MODE + ---------------------- 

// @ Syntax: MODE <channel> <flags> [<args>] | The MODE command is used set channel modes 

void    Server::mode(User *user, std::string target, std::vector<std::string> modes){
    std::vector<User>::iterator     userIt;
    std::vector<Channel>::iterator  chanIt;

    if (target.empty()){
        buildResponseToSend(NULL, user, repliesMessage("461", user) + "MODE :Not enough parameters");
        return;
    }
    for (userIt = _users.begin(); userIt != _users.end(); ++userIt){
        if (userIt->getNickName() == target)
            break;
    }
    if (userIt != _users.end()){
        userModes(user, &*userIt, modes);
        return;
    }
    for (chanIt = _channels.begin(); chanIt != _channels.end(); ++chanIt){
        if (chanIt->getChannelName() == target)
            break;
    }
    if (chanIt != _channels.end()){
        channelModes(user, &*chanIt, modes);
        return ;
    }
    else{
        buildResponseToSend(NULL, user, repliesMessage("401", user) + target + " :No such nick/channel");
        return;
    }
}