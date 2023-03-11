/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-aou <bben-aou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:01:33 by bben-aou          #+#    #+#             */
/*   Updated: 2023/03/11 15:06:25 by bben-aou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./User/user.hpp"
#include "./Server/server.hpp"


int main(int argc, char **argv){
    if (argc != 3){
        std::cerr << "Error: bad arguments" << std::endl;
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while (argv[1][i]){
        if (argv[1][i] >= '0' && argv[1][i] <= '9'){
            i++;
        }
        else{
            std::cerr << "Error : port should be number !" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    Server  server("server1", atoi(argv[1]), argv[2]);
    server.establishListening();
    server.handlingEvents();
}