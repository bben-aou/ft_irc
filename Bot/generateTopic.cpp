/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generateTopic.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-aou <bben-aou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 13:48:29 by bben-aou          #+#    #+#             */
/*   Updated: 2023/03/11 13:48:39 by bben-aou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Server/server.hpp"

void    Server::generateTopic(User * user, std::string channelType){
    if (channelType.empty()){
        buildBotResponse("bot@error ", user, "Error syntax : please enter a specific channel type !");
        return;
    }
    std::cout << "|"<<channelType<<"|" <<std::endl;
    srand(time(0));
    std::string generatedTopic;
    
    if (channelType == "sport"){
        std::string  sport[5] = {
            "Sport fanatics",
            "Game talk",
            "Athlete's world",
            "Sport news",
            "Score update"
        };
        int randomIndex = rand() % 5;
        generatedTopic = sport[randomIndex];
        buildBotResponse("bot@generateTopic ", user, "Topic Is : \033[32m" +generatedTopic + RESET);
    }
    else if (channelType == "music"){
        std::string  music[3] = {
            "Soundcheck",
            "Music vibes",
            "Melodic musings"
        };
        int randomIndex = rand() % 3;
        generatedTopic = music[randomIndex];
        buildBotResponse("bot@generateTopic ", user, "Topic Is : \033[32m" + generatedTopic + RESET);
        return;
    }
    else if (channelType == "programming"){
        std::string  programming[3] = {
            "Hackerspace",
            "Dev squad",
            "Tech talk"
        };
        int randomIndex = rand() % 3;
        generatedTopic = programming[randomIndex];
        buildBotResponse("bot@generateTopic ", user,"Topic Is : \033[32m" + generatedTopic + RESET);
        return;
    }
    else{
        buildBotResponse("bot@error ", user,  "Error : unvailable service !");
        return;
    }
}