#ifndef _PRINT_HPP_
# define _PRINT_HPP_

# include "utils.hpp"

# include <iostream>

class Print {
private:
	Print();
public:
	~Print();
	static void PrintLineNoColor(std::string message);
	static void PrintLineWithColor(std::string message, Color color);
	static void PrintMultiLineNoColor(std::string* message, int size);
	static void PrintMultiLineWithColor(std::string* message, int size, Color color);

	template<typename S, typename T>
	static void PrintComplexLineWithColor(S message, T value, Color color) {
		std::cout << "\x1b[" << color << "m" << message << value << "\x1b[" << RESET << "m" << std::endl;
	}

	template<typename S, typename T>
	static void PrintComplexLineNoColor(S message, T value) {
		std::cout << message << value << std::endl;
	}
};

#endif
