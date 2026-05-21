#include <vector>
#include <iostream>
#include <conio.h>
//#include <windows.h>
#include <filesystem>

#define YELLOW "\x1b[33m"
#define BLACK "\x1b[30m"

#define WHITE_BG "\x1b[47m"
#define YELLOW_BG "\x1b[43m"

#define CURSOR "|>  "

#define CLEAR "\x1B[2J\x1B[H"

void resetCur(int64_t&);
void loadDirectories(std::vector<std::filesystem::path>&, const std::filesystem::path&);
void clearBuffer(std::string&);
void renderAllSh(std::string&);
//void clear();


int rows{12};


std::string buffer{};

void start() {
	setlocale(LC_ALL, "");

	int64_t cur{};
	std::vector<std::filesystem::path> list;

	std::filesystem::path path = std::filesystem::current_path().string() + '\\';

	bool scrollAllScene{ false };
	int scan{};
	resetCur(cur);
	loadDirectories(list, path);

	int temp{};
	while (1) {
		clearBuffer(buffer);
		//system("cls");
		//clear();

		// ===============================
		if (scan == 13) {		// ENTER 10
			if (cur == -1) {

				std::string ttt = std::string(path.string().c_str(), path.string().substr(0, path.string().size() - 1).find_last_of('\\'));
				std::filesystem::path temp = std::filesystem::path(ttt + '\\');
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

					// TODO: ОТМЕНЯТЬ ПЕРЕРЕНДЕР А ТО ОН РЕНДЕРИТ ВСЕ НАХУЯЯ
					system(("start " + temp.string()).c_str());
					//scan = 0;
					//continue;
				}
			}
		};
		if (scan == 27) return; // ESC
		if (scan == 72) {		// UP 119
			if (cur > -1) cur--;
		}
		if (scan == 80) {		// DOWN 115
			if (cur < static_cast<int64_t>(list.size()) - 1) cur++;   // !!!!!!!!!!!!!!!!!!!
		}

		// ===============================
		buffer += "Current directory:\n" + path.string() + "\n\n";

		if (path == path.root_path()) {
			if (cur == -1) cur++;
			//temp--;
			//cur = 0;
		} else {
			if (cur == -1) buffer += CURSOR "<--\n";

			else buffer += "<--\n";

		}
		// ============= All to buffer =============
		for (size_t i{}; i < list.size(); i++) {
			if (cur == i) {
				if (std::filesystem::is_directory(list.at(i)))
					buffer += YELLOW_BG BLACK CURSOR;
				else
					buffer += (WHITE_BG  BLACK  CURSOR);
				//continue;
			} else {
				if (std::filesystem::is_directory(list.at(i)))
					buffer += (YELLOW);
			}



			buffer += (list.at(i).filename().string() + "\x1b[0m\n");

		}
		// ===============================
		renderAllSh(buffer);

		scan = _getch();

	}
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

void renderAllSh(std::string& buf) {
	printf("%s%s%s", CLEAR, buffer.c_str(), "\x1B[?25l");
};


//void clear() {
//	std::cout << "\x1B[2J\x1B[H";
//}
