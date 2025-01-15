CXX = c++
CXXFLAGS = -Werror -Wall -Wextra -std=c++98 -I./include -I./include/utils
RM = rm -rf
MAINSRC = source
UTILSRC = source/utils
COMMANDSRC = source/command
SRC = main $(MAINSRC)/Server $(MAINSRC)/Client $(MAINSRC)/Channel $(MAINSRC)/CommandExecute \
	  $(UTILSRC)/utils $(UTILSRC)/Buffer $(UTILSRC)/error $(UTILSRC)/Message $(UTILSRC)/Print $(UTILSRC)/reply $(UTILSRC)/List \
	  $(COMMANDSRC)/authenticateCommand $(COMMANDSRC)/channelCommand $(COMMANDSRC)/connectCheckCommand $(COMMANDSRC)/messageCommand \
	  $(COMMANDSRC)/modeCommand $(COMMANDSRC)/operCommand $(COMMANDSRC)/quitCommand
SRCC = $(addsuffix .cpp, $(SRC))
OBJ = $(addsuffix .o, $(SRC))
NAME = ircserv

ifdef DEBUG
	CXXFLAGS += -g -DDEBUG
endif

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $<

clean:
	$(RM) $(OBJ)

fclean:
	make -s clean
	$(RM) $(NAME)

re:
	make -s fclean
	make -s all

.PHONY: all clean fclean re
