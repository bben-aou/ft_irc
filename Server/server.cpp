/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-aou <bben-aou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 12:28:55 by bben-aou          #+#    #+#             */
/*   Updated: 2023/03/11 15:06:47 by bben-aou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./server.hpp"

Server::Server(){
    this->_password = "passwd";
    this->_port     = 0;
    this->_AddressSize = sizeof(this->_ServerAddress);
}

Server::Server(std::string serverName, int port, char *password){
    this->_serverName = serverName;
    this->_port       = port;
    this->_password   = password;
    this->_AddressSize = sizeof(this->_ServerAddress);
}

Server:: Server(Server const &server){
    this->_serverName = server._serverName;
    this->_port       = server._port;
    this->_password   = server._password;
}

Server&  Server::operator=(Server const &obj){
    this->_serverName = obj._serverName;
    this->_port       = obj._port;
    this->_password   = obj._password;
    return(*this);
}

// -getters- :

std::string     Server::getServerName() const{
    return (this->_serverName);
}

std::string     Server::getPassword() const{
    return (this->_password);
}

int             Server::getPort() const{
    return (this->_port);
}

std::vector<pollfd> Server::getFds(){
    return (this->_fds);
}

void    Server::establishListening(){
    pollfd      socketFd;
    int         bindStatus;
    int         listenStatus;    
    // Creation socket for the server and check it's status 
    socketFd.fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFd.fd < 0){
        std::cerr << "Error : Creation of Socket Failed !" << std::endl;
        exit(EXIT_FAILURE);
    }
    {
        int optvul = 1;
        setsockopt (socketFd.fd, SOL_SOCKET, SO_REUSEADDR, &optvul, sizeof(optvul) );
    }// Set the socket to non-blocking mode
    fcntl(socketFd.fd, F_SETFL, O_NONBLOCK);
    
    // Filling the struct members with data 
    this->_ServerAddress.sin_family      = AF_INET;
    this->_ServerAddress.sin_port        = htons(this->_port);
    this->_ServerAddress.sin_addr.s_addr = INADDR_ANY;
    
    //  Set the events member of poll_fd to monitor for input and output events
    socketFd.events  = POLLIN|POLLOUT;
    socketFd.revents = 0;

    // Bind the socket to the IP address and port of the server and check the status 
    bindStatus = bind(socketFd.fd, (struct sockaddr *)&_ServerAddress, _AddressSize);
    if (bindStatus < 0){
        std::cerr << "Error : Binding Failed !" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    // Listing for incoming connection requests and check the status
    listenStatus = listen(socketFd.fd, MAXUSERS);
    if (listenStatus < 0){
        std::cerr << "Error : Listing Failed !" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    // push the SocketFd struct to the victor
    this->_fds.push_back(socketFd);
}
    //! @ poll() is system call that allows a program to monitor multiple file descriptors

void    Server::handlingEvents(){
    int     pollStatus = 0;
    char    buffer[4096];
    // int     command;

    while (true){
        // reach for the file descriptors who's available to be read or write in 
        pollStatus = poll(this->_fds.data(), this->_fds.size(), 0);
        
        // check Poll() status : error case
        if (pollStatus < 0){
            std::cerr << "Error : Poll Failed !" << std::endl;
            break; 
        }
        // check Poll() status : unavailable file descriptors yet
        else if (pollStatus == 0)
            continue;
        // check Poll() status : available file descriptors 
        else if (this->_fds[0].revents & POLLIN){
            
            int newUserSocket;
            // accept the new connection and create newUserSocket
            newUserSocket = accept(this->_fds[0].fd, (struct sockaddr *)(&this->_ServerAddress),(socklen_t *)(&this->_AddressSize));
            if ( newUserSocket < 0){
                std::cerr << "Error : Accept Failed !" << std::endl;
                break;
            }
            std::cout << "Alert: New User has been accepted d(*_*)b" << std::endl;
            // set the newUserSocket to the non-blocking mode
            fcntl(newUserSocket, F_SETFL, O_NONBLOCK);
            pollfd  newUserFd;
            
            // fill the new pollfd struct of the newUser 
            newUserFd.fd      = newUserSocket;
            newUserFd.events  = POLLIN | POLLOUT;
            newUserFd.revents = 0;
            // push the new struct into the pollfd Vector
            this->_fds.push_back(newUserFd);
            // create a new user with fd
            User    newUser(newUserFd);
            // push it to the Users Vector
            this->_users.push_back(newUser);
        }
        std::vector<pollfd>::iterator  it = this->_fds.begin();
        int     readStatus = 1;
        int     index = 0;
        it++;        
        while(it != this->_fds.end()){
            if (it->revents & POLLIN){
                readStatus = 1;
                memset(buffer,'\0',4096);
                readStatus = read(it->fd, buffer, 4096);
                this->_users[index].joinPollExtractedData(buffer);
                // there is nothing to read from the client and the file descriptor is closed :
                if (readStatus == 0){
                    std::cout << "Fd is = " << it->fd << " |  Revents is = " <<  it->revents << std::endl;
                    quit(&_users[index],"");
                    close(it->fd);
                    it = this->_fds.erase(it);
                    this->_users.erase(_users.begin() + index);
                    it = this->_fds.begin() + 1;
                    index = 0;
                    continue;
                }

                else if (int command = itsCommand(_users[index].getPollExtractedData())){
                    if (parser(_users[index].getPollExtractedData().substr(0, command), index) == 1){
						std::cout << "Fd is = " << it->fd << " |  Revents is = " <<  it->revents << std::endl;
                        close(it->fd);
                        it = _fds.erase(it);
                        _users.erase(_users.begin() + index);
                        it = _fds.begin() + 1;
                        index = 0;
                        continue;
                    }  
                    _users[index].setPollExtractedData(_users[index].getPollExtractedData().substr(command + 1, _users[index].getPollExtractedData().size() - (command + 1)));
                }
            }
            index++;
            it++;
        }
        this->_fds[0].revents = 0;
    }     
}

int    Server::itsCommand(std::string  line){
    int i = 0;
    while (line[i]){
        if (line[i] == '\r' && line[i + 1] == '\n')
            return (i + 1);
        i++;
    }
    return (0);
}

// std::string     Server::getCommandInLine(std::string line, int *posPointer) const{
//     std::string     word;
//     while (line[*posPointer] == ' ')
//         *posPointer += 1;
//     if (line[*posPointer] == ':'){
//         *posPointer += 1;
//         while (line[*posPointer] != '\r' && line[*posPointer]){
//             word +=  line[*posPointer];
//             *posPointer += 1;
//         }
//     }
//     else{
//         while (line[*posPointer] != ' ' && line[*posPointer] != '\r' && line[*posPointer]){
//             word +=  line[*posPointer];
//             *posPointer += 1;
//         }
//     }
//     return (word);
// }

// std::vector<std::string>     Server::getVectorOfArgs(std::string line, int* posPointer){
//     std::string tmpStr;
//     std::vector<std::string> argsVector;

//     while (line[*posPointer] != '\r' && line[*posPointer])
//     {
//         tmpStr.clear();
//         while (line[*posPointer] == ' ' ||  line[*posPointer] == ',')
//             *posPointer += 1;
//         if (line[*posPointer] == ':')
//             return (argsVector);
//         while (line[*posPointer] != ' ' && line[*posPointer] != ','  && line[*posPointer] != '\r' && line[*posPointer]){
//             tmpStr = tmpStr + line[*posPointer];
//             *posPointer = *posPointer + 1;
//         }
//         argsVector.push_back(tmpStr);
//     }
//     return (argsVector);
// }



// int   Server::parser(std::string buffer, int index){
//     size_t  i = 0;
//     std::string     command;
//     std::string     line;
    
//     while (i < buffer.size()){
//         int posPointer = 0;
//         while (buffer[i] && buffer[i] != '\r'){
//             line += buffer[i];
//             i++;
//         }
//         if(line[0] == ':'){
//             std::cout << "Case 1 : source exist \n" << std::endl;
//             getCommandInLine(line,&(posPointer = 1)); // read and skip the prefix ....
//             command = getCommandInLine(line,&(posPointer));
//         }
//         else{
//                 command = getCommandInLine(line,&(posPointer));
//         }
//         std::cout << " Command is : " << command << std::endl;
//         if (!checkCommandValidation(command))
//         {
//             uknownCommandRpl(&_users[index], command);
//             std::cout << "Invalid Command !" << std::endl;
//         }
//         if (command == "PASS"){
//             std::cout << "The Command Is : PASS" << std::endl;
//             pass(&_users[index], getCommandInLine(line,&(posPointer)));
//         }
//         else if (command == "NICK"){
//             std::cout << "The Command Is : NICK" << std::endl;
//             nick(&_users[index], getCommandInLine(line, &(posPointer)));
//         }
//         else if (command == "USER"){
//             std::cout << "The Command Is : USER" << std::endl;
//             std::string     userName = getCommandInLine(line, &(posPointer));
//             std::string     hostName = getCommandInLine(line, &(posPointer));
//             std::string     serverName = getCommandInLine(line, &(posPointer));
//             std::string     realName = getCommandInLine(line, &(posPointer));
//             user(&_users[index], userName, hostName, serverName, realName);
//         }
//         else if (!_users[index].isAuthenticated()){
//             userIsNotLoggedIn(&_users[index]);
//             std::cout << "The User is not logged in !" << std::endl;
//         }
//         else if (command == "JOIN"){
//             std::cout << "The Command Is : JOIN" << std::endl;
//             std::vector<std::string> argVector;
//             std::vector<std::string>::const_iterator it;
//             argVector = getVectorOfArgs(line, &(posPointer));
//             join(&_users[index],argVector);
//         }
//         else if (command == "INVITE"){
//             std::string     invitedUser = getCommandInLine(line, &(posPointer));
//             std::string     channel = getCommandInLine(line, &(posPointer));
//             invite(&_users[index], invitedUser, channel);   
//         }
        
//         else if (command == "QUIT"){
//             std::cout << "The Command Is : QUIT" << std::endl;
//             std::string quitMessage = getCommandInLine(line, &(posPointer));
//             std::cout << quitMessage << std::endl;
//             quit(&_users[index], quitMessage);
//             return (1);
//         }
//         else if (command == "PART"){
//             std::cout << "The Command Is : PART" << std::endl;
//             std::vector<std::string> channels = getVectorOfArgs(line, &(posPointer));
//             std::string              partReasonMessage = getCommandInLine(line, &(posPointer));
//             part(&_users[index], channels, partReasonMessage);   
//         }
//         else if (command == "PONG"){
//             std::cout << "The Command Is : PING" << std::endl;
//             std::string message = getCommandInLine(line, &(posPointer));
//             pong(&_users[index], message);
//         }
//         else if (command == "LIST"){
//             std::cout << "The Command Is : LIST" << std::endl;
//             std::vector<std::string>    channelsArgs = getVectorOfArgs(line, &(posPointer));
//             list(&_users[index], channelsArgs);
//         }
//         else if (command == "KICK"){
//             std::cout << "The Command Is : KICK" << std::endl;
//             std::string  channel = getCommandInLine(line, &(posPointer));
//             std::string  target = getCommandInLine(line, &(posPointer));
//             std::string  reason = getCommandInLine(line, &(posPointer));
//             kick(&_users[index], channel, target, reason);
//         }
//         else if (command == "NAMES"){
//             std::cout << "The Command Is : NAMES" << std::endl;
//             std::vector<std::string> channels = getVectorOfArgs(line, &(posPointer));
//             names(&_users[index], channels);
            
//         }
//         else if (command == "PRIVMSG"){
//             std::cout << "The Command Is : PRIVMSG" << std::endl;
//             std::vector<std::string>  targets = getVectorOfArgs(line, &(posPointer));
//             std::string               message = getCommandInLine(line, &(posPointer));
//             privmsg(&_users[index], targets, message);
//         }
//         else if (command == "MODE"){
//             std::cout << "The Command Is : MODE" << std::endl;
//             std::string target = getCommandInLine(line, &(posPointer));
//             std::vector<std::string> args = getVectorOfArgs(line, &(posPointer));
//             mode(&_users[index], target, args);
//         }
//         else if (command == "NOTICE"){
//             std::cout << "The Command Is : NOTICE" << std::endl;
//             std::vector<std::string>    targets = getVectorOfArgs(line, &(posPointer));
//             std::string                 NoticeMessage = getCommandInLine(line, &(posPointer));
//             notice(&_users[index], targets, NoticeMessage);
//         }
//         else if (command == "TOPIC"){
//             std::cout << "The Command Is : TOPIC" << std::endl;
//             std::string channel = getCommandInLine(line, &(posPointer));
//             std::string chanTopic = getCommandInLine(line, &(posPointer));
//             topic(&_users[index], channel, chanTopic);
//         }
//         else if (command == "BOT"){
//             std::cout << "BOT Service :" << std::endl;
//             std::string     service = getCommandInLine(line, &(posPointer));
//             std::string     channelType = getCommandInLine(line, &(posPointer));
//             bot(&_users[index], service, channelType);
//         }
//         i += 2;
//         line.erase();
//     }
//     return (0);
// }

// bool    Server::checkCommandValidation(std::string command) {
//     if (command == "PASS")
//         return (true);
//     if (command == "NICK")
//         return (true);
//     if (command == "USER")
//         return (true);
//     if (command == "PONG")
//         return (true);
//     if (command == "JOIN")
//         return (true);
//     if (command == "INVITE")
//         return (true);
//     if (command == "PART")
//         return (true);
//     if (command == "NOTICE")
//         return (true);
//     if (command == "PRIVMSG")
//         return (true);
//     if (command == "QUIT")
//         return (true);
//     if (command == "KICK")
//         return (true);
//     if (command == "NAMES")
//         return (true);
//     if (command == "LIST")
//         return (true);
//     if (command == "TOPIC")
//         return (true);
//     if (command == "MODE")
//         return (true);
//     if (command == "BOT")
//         return (true);
//     return (false);
// }


Server::~Server(){}