/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logtime.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-aou <bben-aou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 13:47:32 by bben-aou          #+#    #+#             */
/*   Updated: 2023/03/11 13:48:02 by bben-aou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Server/server.hpp"

void    Server::saveLoginTime(User *user){
    ltime Mytime;
    std::time_t current_time = std::time(NULL);
    std::tm* time_info = std::localtime(&current_time);
    Mytime.hours =  time_info->tm_hour;
    Mytime.minutes =  time_info->tm_min;
    my_map.insert(std::make_pair(user->getNickName(), Mytime));
}