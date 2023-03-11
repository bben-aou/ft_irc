# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bben-aou <bben-aou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/08 15:11:24 by blind-eagle       #+#    #+#              #
#    Updated: 2023/03/11 14:47:29 by bben-aou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = ircserv

CFLAGS = -Wall -Wextra -Werror -std=c++98

SRC = ./User/user.cpp \
	  ./Channel/channel.cpp \
	  ./Authentication/pass.cpp \
	  ./Authentication/nick.cpp \
	  ./Authentication/user.cpp \
	  ./Authentication/notLoggedIn.cpp \
	  ./Commands/join.cpp \
	  ./Commands/part.cpp \
	  ./Commands/list.cpp \
	  ./Commands/names.cpp \
	  ./Commands/mode.cpp \
	  ./Commands/kick.cpp \
	  ./Commands/invite.cpp \
	  ./Commands/topic.cpp \
	  ./Commands/notice.cpp \
	  ./Commands/privmsg.cpp \
	  ./Commands/pong.cpp \
	  ./Commands/quit.cpp \
	  ./Commands/invalidCommand.cpp \
	  ./Parser/parser.cpp \
	  ./Parser/commandChecker.cpp \
	  ./Parser/parserUtils.cpp \
	  ./Bot/help.cpp \
	  ./Bot/logtime.cpp \
	  ./Bot/generateTopic.cpp \
	  ./Bot/sendBotResponse.cpp \
	  ./Bot/bot.cpp \
	  ./Server/server.cpp \
	  ./Server/utilsServer.cpp \
	  main.cpp \

HDRS = ./User/user.hpp \
	   ./Channel/channel.hpp \
	   ./Server/server.hpp 

OBJ = $(SRC:.cpp=.opp)

all : $(NAME)

$(NAME): $(OBJ) $(HDRS)
	@c++ $(CFLAGS) $(OBJ) -o $@
	@echo "\033[0;36m ⚙️  MakeFile ⚙️ : ✅ COMPILED SUCCESSFULY\033[0m"

%.opp:%.cpp  
	@c++ $(CFLAGS) -o $@ -c $<
clean :
	@rm -f $(OBJ)
	@echo "\033[0;36m ⚙️  MakeFile ⚙️ : 🗑️ Objects removed!\033[0m"
fclean : clean
	@rm -f $(NAME)
	@echo "\033[0;36m ⚙️  MakeFile ⚙️ : 🗑️ CLEANED SUCCESSFULY\033[0m"

re: fclean all

.PHONY : all clean fclean re