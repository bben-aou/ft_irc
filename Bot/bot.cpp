/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-aou <bben-aou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 13:44:43 by bben-aou          #+#    #+#             */
/*   Updated: 2023/03/11 13:46:40 by bben-aou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Server/server.hpp"

void    Server::bot(User * user, std::string option, std::string channelType){
    std::string service;
    if (option.empty()){
        buildBotResponse("bot@error ", user, "Error syntax : please enter a specific service !");
        return;
    }
    std::cout << option << " channelType : " << channelType << std::endl;
    service = option;
    std::map<std::string, ltime>::iterator it;

    
    ltime Mytime;
    std::time_t current_time = std::time(NULL);
    std::tm* time_info = std::localtime(&current_time);
    Mytime.hours =  time_info->tm_hour;
    Mytime.minutes =  time_info->tm_min;

    int loghours ;
    int logminutes;
        
    std::string    services[3] = {
                "logtime",
                "help",
                "generateTopic"
    };
    int i = 0;
    while (i < 3 && option != services[i])
        i++;
    switch(i){
        case 0 :{
            for (it = my_map.begin(); it != my_map.end(); ++it) {
                if (it->first == user->getNickName()){
                    loghours = Mytime.hours - it->second.hours;
                    logminutes = Mytime.minutes - it->second.minutes;
                    if (logminutes < 0){
                        loghours -= 1;
                        logminutes += 60;
                    }
                    std::string     message =  " -> User : \033[33m" + user->getNickName() + "\033[0m has been loggedin for : " + RED + std::to_string(loghours) + "h" + std::to_string(logminutes) + "min" + RESET;
                    buildBotResponse("bot@logtime", user, message);
                    return;
                }
            }
            if (it == my_map.end()){
            buildBotResponse("bot@error ", user, "Error : user not found !");
                return;
            }
            break;
        }
        case 1 :{
            help(user);
            break;
        }
        case 2 :{
            generateTopic(user, channelType);
            break;
        }
        default :
            buildBotResponse("bot@error ", user, "Error : unvailable service !");
    }
}