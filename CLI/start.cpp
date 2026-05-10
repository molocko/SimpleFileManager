//#include "include/fmt/base.h"
#include <vector>
#include <iostream>
#include <conio.h>
//#include <windows.h>
#include <filesystem>
//#pragma comment(lib, "CLI/include/fmt.lib")

#define YELLOW "\x1b[33m"
#define BLACK "\x1b[30m"

#define WHITE_BG "\x1b[47m"
#define YELLOW_BG "\x1b[43m"

#define CURSOR "|>  "

#define CLEAR "\x1B[2J\x1B[H"

void resetCur(int64_t&);
void loadDirectories(std::vector<std::filesystem::path>&, const std::filesystem::path&);
void clearBuffer(std::string&);
//void clear();

//using fmt::print;
//using std::cout;
//using std::endl;

//int rows{12};

std::string buffer{};

void start() {
	setlocale(LC_ALL, "");

	int64_t cur{};
	std::vector<std::filesystem::path> list;

	//std::filesystem::path path = std::filesystem::current_path();
	std::filesystem::path path = std::filesystem::current_path().string() + '\\';

	int scan{};
	resetCur(cur);
	loadDirectories(list, path);
	while (1) {
		clearBuffer(buffer);
		//system("cls");
		//clear();
		if (scan == 13) {		// ENTER
			if (cur == -1) {
				
				std::string ttt = std::string(path.string().c_str(), path.string().substr(0,path.string().size()-1).find_last_of('\\'));
				std::filesystem::path temp = std::filesystem::path(ttt+'\\');
				//print(" || {} || ", );


				path = temp;
				resetCur(cur);
				loadDirectories(list, temp);
			} else {

				std::filesystem::path temp = std::filesystem::path(path.string() + list.at(cur).filename().string() + '\\');

				if (std::filesystem::directory_entry(temp).is_directory()) {
					path = temp;
					resetCur(cur);
					loadDirectories(list, temp);
				} else {
					system(("start " + temp.string()).c_str());
				}
			}
		}; 
		if (scan == 27) return; // ESC
		if (scan == 72) {		// UP
			if(cur > -1) cur--;
		}
		if (scan == 80) {		// DOWN
			if(cur < static_cast<int64_t>(list.size())-1) cur++;   // !!!!!!!!!!!!!!!!!!!
		}



		//print("Current directory:\n{}\n\n", path.string());
		//printf("Current directory:\n%s\n\n", path.string().c_str());
		buffer += "Current directory:\n" + path.string() + "\n\n";
		if (path == path.root_path()) {
			if (cur == -1) cur++;
			//cur = 0;
		} else {
			//if (cur == -1) printf(CURSOR "<--\n");
			if (cur == -1) buffer+=CURSOR "<--\n";

			//else printf("<--\n");
			else buffer+="<--\n";
			
		}
		for (size_t i{}; i < list.size(); i++) {
			if (cur == i) {
				//if(std::filesystem::directory_entry(list.at(i)).is_directory())
				if(std::filesystem::is_directory(list.at(i)))
					//printf(YELLOW_BG BLACK CURSOR);
					buffer += YELLOW_BG BLACK CURSOR;
				else
					//printf(WHITE_BG  BLACK  CURSOR);
					buffer+=(WHITE_BG  BLACK  CURSOR);
				//continue;
			} else {
				if (std::filesystem::is_directory(list.at(i)))
					//printf(YELLOW);
					buffer+=(YELLOW);
			}

			

			try {					/// IDKKK как фикс это
				//printf("%s\x1b[0m\n", list.at(i).filename().string().c_str());
				buffer += (list.at(i).filename().string()+"\x1b[0m\n");

			} catch (...) {
				//std::cout << list.at(i).filename().string() << std::endl;
				std::cout << "111111111111111111111111111111111111111" << std::endl;
			}
		}
		printf("%s%s%s", CLEAR, buffer.c_str(), "\x1B[?25l");

		scan = _getch();


	}

	
	//using namespace std;
	//std::this_thread::sleep_for(1s);
};

void loadDirectories(std::vector<std::filesystem::path>& vec, const std::filesystem::path& path) {
	vec.clear();
	for (auto& entry : std::filesystem::directory_iterator(path)) {
		vec.push_back(entry.path());
	}
}

void resetCur(int64_t& cur) {
	cur = -1;
}
void clearBuffer(std::string& buf) {
	buf.clear();
}


//void clear() {
//	std::cout << "\x1B[2J\x1B[H";
//}
