/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-aou <bben-aou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 13:10:42 by bben-aou          #+#    #+#             */
/*   Updated: 2023/03/11 13:40:49 by bben-aou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Server/server.hpp"

int   Server::parser(std::string buffer, int index){
    size_t  i = 0;
    std::string     command;
    std::string     line;
    
    while (i < buffer.size()){
        int posPointer = 0;
        while (buffer[i] && buffer[i] != '\r'){
            line += buffer[i];
            i++;
        }
        if(line[0] == ':'){
            std::cout << "Case 1 : source exist \n" << std::endl;
            getCommandInLine(line,&(posPointer = 1)); // read and skip the prefix ....
            command = getCommandInLine(line,&(posPointer));
        }
        else{
                command = getCommandInLine(line,&(posPointer));
        }
        std::cout << " Command is : " << command << std::endl;
        if (!checkCommandValidation(command))
        {
            uknownCommandRpl(&_users[index], command);
            std::cout << "Invalid Command !" << std::endl;
        }
        if (command == "PASS"){
            std::cout << "The Command Is : PASS" << std::endl;
            pass(&_users[index], getCommandInLine(line,&(posPointer)));
        }
        else if (command == "NICK"){
            std::cout << "The Command Is : NICK" << std::endl;
            nick(&_users[index], getCommandInLine(line, &(posPointer)));
        }
        else if (command == "USER"){
            std::cout << "The Command Is : USER" << std::endl;
            std::string     userName = getCommandInLine(line, &(posPointer));
            std::string     hostName = getCommandInLine(line, &(posPointer));
            std::string     serverName = getCommandInLine(line, &(posPointer));
            std::string     realName = getCommandInLine(line, &(posPointer));
            user(&_users[index], userName, hostName, serverName, realName);
        }
        else if (!_users[index].isAuthenticated()){
            userIsNotLoggedIn(&_users[index]);
            std::cout << "The User is not logged in !" << std::endl;
        }
        else if (command == "JOIN"){
            std::cout << "The Command Is : JOIN" << std::endl;
            std::vector<std::string> argVector;
            std::vector<std::string>::const_iterator it;
            argVector = getVectorOfArgs(line, &(posPointer));
            join(&_users[index],argVector);
        }
        else if (command == "INVITE"){
            std::string     invitedUser = getCommandInLine(line, &(posPointer));
            std::string     channel = getCommandInLine(line, &(posPointer));
            invite(&_users[index], invitedUser, channel);   
        }
        
        else if (command == "QUIT"){
            std::cout << "The Command Is : QUIT" << std::endl;
            std::string quitMessage = getCommandInLine(line, &(posPointer));
            std::cout << quitMessage << std::endl;
            quit(&_users[index], quitMessage);
            return (1);
        }
        else if (command == "PART"){
            std::cout << "The Command Is : PART" << std::endl;
            std::vector<std::string> channels = getVectorOfArgs(line, &(posPointer));
            std::string              partReasonMessage = getCommandInLine(line, &(posPointer));
            part(&_users[index], channels, partReasonMessage);   
        }
        else if (command == "PONG"){
            std::cout << "The Command Is : PING" << std::endl;
            std::string message = getCommandInLine(line, &(posPointer));
            pong(&_users[index], message);
        }
        else if (command == "LIST"){
            std::cout << "The Command Is : LIST" << std::endl;
            std::vector<std::string>    channelsArgs = getVectorOfArgs(line, &(posPointer));
            list(&_users[index], channelsArgs);
        }
        else if (command == "KICK"){
            std::cout << "The Command Is : KICK" << std::endl;
            std::string  channel = getCommandInLine(line, &(posPointer));
            std::string  target = getCommandInLine(line, &(posPointer));
            std::string  reason = getCommandInLine(line, &(posPointer));
            kick(&_users[index], channel, target, reason);
        }
        else if (command == "NAMES"){
            std::cout << "The Command Is : NAMES" << std::endl;
            std::vector<std::string> channels = getVectorOfArgs(line, &(posPointer));
            names(&_users[index], channels);
            
        }
        else if (command == "PRIVMSG"){
            std::cout << "The Command Is : PRIVMSG" << std::endl;
            std::vector<std::string>  targets = getVectorOfArgs(line, &(posPointer));
            std::string               message = getCommandInLine(line, &(posPointer));
            privmsg(&_users[index], targets, message);
        }
        else if (command == "MODE"){
            std::cout << "The Command Is : MODE" << std::endl;
            std::string target = getCommandInLine(line, &(posPointer));
            std::vector<std::string> args = getVectorOfArgs(line, &(posPointer));
            mode(&_users[index], target, args);
        }
        else if (command == "NOTICE"){
            std::cout << "The Command Is : NOTICE" << std::endl;
            std::vector<std::string>    targets = getVectorOfArgs(line, &(posPointer));
            std::string                 NoticeMessage = getCommandInLine(line, &(posPointer));
            notice(&_users[index], targets, NoticeMessage);
        }
        else if (command == "TOPIC"){
            std::cout << "The Command Is : TOPIC" << std::endl;
            std::string channel = getCommandInLine(line, &(posPointer));
            std::string chanTopic = getCommandInLine(line, &(posPointer));
            topic(&_users[index], channel, chanTopic);
        }
        else if (command == "BOT"){
            std::cout << "BOT Service :" << std::endl;
            std::string     service = getCommandInLine(line, &(posPointer));
            std::string     channelType = getCommandInLine(line, &(posPointer));
            bot(&_users[index], service, channelType);
        }
        i += 2;
        line.erase();
    }
    return (0);
}