/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blind-eagle <blind-eagle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 03:46:06 by blind-eagle       #+#    #+#             */
/*   Updated: 2023/02/16 12:14:46 by blind-eagle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef     CHANNEL_HPP
#define     CHANNEL_HPP

#include "./User.hpp"

#include <string>
#include <iostream>
#include <limits>
#include <vector>

class Channel{
    private :
    std::string                  _channelName;
    std::string                  _channelTopic;
    unsigned int                 _maxMembers;
    std::vector<std::string>     _channelMembers;
    std::vector<std::string>     _channelOperators;
    bool                         _privateChannel;
    bool                         _secretChannel;
    bool                         _allowOutMessages;
    bool                         _operatorsTopicControl;

    public  :
    Channel();
    Channel(std::string channelName);
    ~Channel();
    
    Channel(const Channel &obj);
    Channel&  operator = (const Channel &obj);
    
    //^ -Setters- :

    bool    setChannelName(std::string user, std::string channelName);
    bool    setChannelTopic(std::string user, std::string channelTopic);
    bool    setMaxMembers(std::string user, unsigned int max);
    bool    setOperatorsTopicControl(std::string user, bool status);
    bool    setPrivateChannel(std::string user, bool status);
    bool    setSecretChannel(std::string user, bool status);
    bool    setAllowOutMessage(std::string user, bool status);
    

    // ^-Getters- :
    std::string                getChannelName()  const;
    std::string                getChannelTopic() const;
    std::vector<std::string>   getChannelMembers() ;
    std::vector<std::string>   getChannelOperators();
    unsigned int               getMaxMembers() const;
    bool                       getPrivateChannelStatus()  const;
    bool                       getSecretChannelStatus()   const;
    bool                       getAllowOutMessageStatus() const;
    bool                       getOperatorsTopicControlStatus() const;

    //^ -Checkers- :

    bool     checkSuperUserPermission(std::string user);
    bool     checkSetTopicPermission(std::string user);
    bool     checkMemberExistence(std::string memberName);

    //^ -Manage Channel- :
    
    void    addUserToChannelOperators(std::string nickName);
    void    deleteUserFromChannelOperators(std::string nickName);
};

#endif