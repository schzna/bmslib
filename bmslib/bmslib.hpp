#pragma once
#include<string>
#include<cstdint>
#include<fstream>
#include<array>
#include<vector>
#include<algorithm>
namespace bmslib {

	std::vector<std::string> split_naive(const std::string &s, char delim) {
		std::vector<std::string> elems;
		std::string item;
		for (char ch : s) {
			if (ch == delim) {
				if (!item.empty())
					elems.push_back(item);
				item.clear();
			}
			else {
				item += ch;
			}
		}
		if (!item.empty())
			elems.push_back(item);
		return elems;
	}

	std::string trim(const std::string& string, const char* trimCharacterList = " \t\v\r")
	{
		std::string result;

		// 左側からトリムする文字以外が見つかる位置を検索します。
		std::string::size_type left = string.find_first_not_of(trimCharacterList);

		if (left != std::string::npos)
		{
			// 左側からトリムする文字以外が見つかった場合は、同じように右側からも検索します。
			std::string::size_type right = string.find_last_not_of(trimCharacterList);

			// 戻り値を決定します。ここでは右側から検索しても、トリムする文字以外が必ず存在するので判定不要です。
			result = string.substr(left, right - left + 1);
		}

		return result;
	}

	enum Player {
		None,
		Single,
		Couple,
		Double,
		Battle
	};

	enum Rank {
		Veryhard,
		Hard,
		Normal,
		Easy
	};

	struct Header
	{
		Player player;
		std::string genre, title, artist, stagefile;
		double bpm;
		unsigned int level, volume, total;
		Rank rank;
		std::array<std::string, 575> wav, bmp;
	};

	enum Channel {
		None1,
		Backwav,
		Shortening,
		Changebpm,
		Bga,
		None2,
		Pooranim,
		Bgalayer,
		exBPM,
		Stop,
		None3,
		Key1,
		Key2,
		Key3,
		Key4,
		Key5,
		Key6,
		Key7,
		Key8,
		Key9,
		None4,
		Key1_2P,
		Key2_2P,
		Key3_2P,
		Key4_2P,
		Key5_2P,
		Key6_2P,
		Key7_2P,
		Key8_2P,
		Key9_2P,
	};

	struct Bar {
		Channel channel;
		int backchorus; // Set WAV number
		int length = 1000; // Default Value = 1000
		std::vector<double> bpms;
		int bga, pooranim, layerbga;
		std::array<std::vector<bool>, 9> objects;
	};

	struct Object {
		int data;
		long time;
		Channel channel;

		bool operator<(const Object obj) {
			return time < obj.time;
		}
	};


	struct Bms {
		Header header;
		std::vector<Object> bar;
	};

	Bms load_data(std::string bmsfile) {
		std::ifstream file(bmsfile);
		std::string line;
		if (file.fail())
		{
			return Bms();
		}
		Bms bms;
		while (getline(file, line))
		{
			trim(line);
			if (line[0] == '#') {
				if (isdigit(line[1])) {
					auto str = split_naive(line,':');
					
					auto command = str[0];
					auto data = str[1];

					if (bms.bar.size() < std::stoi(command.substr(1, 3)) + 1){
						bms.bar.reserve(std::stoi(command.substr(1, 3)) + 1);
					}
					auto channel = static_cast<Channel>(std::stoi(command.substr(4, 2)));
					int num_bar = std::stoi(command.substr(0, 3));
					int num_note = data.size() / 2;
					for (int i = 0; i < num_note - 1; i++) {
						Object obj;
						obj.time = 9600 * num_bar + i*(9600 / num_note);
						obj.data = std::stoi(data.substr(i, 2));
						obj.channel = channel;
						bms.bar.push_back(obj);
					}
				}
			}
		}
		std::sort(bms.bar.begin(), bms.bar.end());
	}

	Bms loadheader(std::string bmsfile) {
		std::ifstream file(bmsfile);
		std::string line;
		if (file.fail())
		{
			return Bms();
		}
		Bms bms;

		while (getline(file, line))
		{

			if (line[0] == '#') {

				if (!isdigit(line[1])) {

					auto strs = split_naive(line, ' ');
					std::string command = strs[0].substr(1);
					std::string arg1;
					if (strs.size() == 1) {
						arg1 = "";
					}
					else {
						arg1 = strs[1];
					}

					if (!std::strcmp(command.c_str(), "PLAYER")) {

						bms.header.player = static_cast<Player>(std::stoi(arg1.c_str()));
					}
					if (!std::strcmp(command.c_str(), "GENRE")) {
						bms.header.genre = arg1;
					}
					if (!std::strcmp(command.c_str(), "TITLE")) {
						std::string rs;
						for (int i = 1; i < strs.size() - 1; i++) {
							rs += strs[i];
							rs += " ";
						}
						bms.header.title = rs;
					}
					if (!std::strcmp(command.c_str(), "ARTIST")) {
						bms.header.artist = arg1;
					}
					if (!std::strcmp(command.c_str(), "BPM")) {
						bms.header.bpm = std::stof(arg1);
					}
					if (!std::strcmp(command.c_str(), "PLAYLEVEL")) {
						bms.header.level = std::stoi(arg1);
					}
					if (!std::strcmp(command.c_str(), "RANK")) {
						bms.header.rank = static_cast<Rank>(std::stoi(arg1));
					}
					if (!std::strcmp(command.c_str(), "VOLWAV")) {
						bms.header.volume = std::stoi(arg1);
					}
					if (!std::strcmp(command.c_str(), "TOTAL")) {
						bms.header.total = std::stoi(arg1);
					}
					if (!std::strcmp(command.substr(0, 3).c_str(), "WAV")) {
						bms.header.wav[std::stoi(command.substr(3, 2), nullptr, 36)] = arg1;
					}
					if (!std::strcmp(command.substr(0, 3).c_str(), "BMP")) {
						bms.header.bmp[std::stoi(command.substr(3, 2), nullptr, 36)] = arg1;
					}
					if (!std::strcmp(command.c_str(), "StageFile") || !std::strcmp(command.c_str(), "STAGEFILE")) {
						bms.header.stagefile = arg1;
					}
				}
			}
		}
		return bms;
	}

	void save(std::string filename, const Bms& bms) {

	}
}