#include "Textfill.h"

void textOpeningMenu() {
	std::cout << std::setfill('\n') << std::setw(100) << "\n";
	std::cout << std::setfill('=') << std::setw(80) << "=" << std::endl << std::endl;
	std::cout << "\t _______                   _    _       _     _\n";
	std::cout << "\t|__   __|                 | |  | |     | |   | |               \n";
	std::cout << "\t   | | _____  ____ _ ___  | |__| | ___ | | __| | ___ _ __ ___  \n";
	std::cout << "\t   | |/ _ \\ \\/ / _` / __| |  __  |/ _ \\| |/ _` |/ _ \\ '_ ` _ \\ \n";
	std::cout << "\t   | |  __/>  < (_| \\__ \\ | |  | | (_) | | (_| |  __/ | | | | |\n";
	std::cout << "\t   |_|\\___/_/\\_\\__,_|___/ |_|  |_|\\___/|_|\\__,_|\\___|_| |_| |_|\n\n\n";
	std::cout << std::setfill('=') << std::setw(80) << "=" << std::endl;
}

void textloadingGame() {
	std::cout << ".------..------..------..------..------.\n";
	std::cout << "|T.--. ||E.--. ||X.--. ||A.--. || S.--.|\n";
	std::cout << "| :/\\: || (\\/) || :/\\: || (\\/) || :/\\: |\n";
	std::cout << "| (__) || :\\/: || (__) || :\\/: || :\\/: |\n";
	std::cout << "| '--'T|| '--'E|| '--'X|| '--'A|| '--'S|\n";
	std::cout << "`------'`------'`------'`------'`------'\n";
	std::cout << std::setfill('\n') << std::setw(100) << "\n";
	std::cout << std::setfill('*') << std::setw(60) << "\n" << std::endl;
}