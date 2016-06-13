#pragma once
#include<string>
#include<cstdint>
#include<fstream>
#include<array>
#include<vector>
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
		None,
		Backwav,
		Shortening,
		Changebpm,
		Bga,
		None,
		Pooranim,
		Bgalayer,
		Changebpm,
		Stop,
		None,
		Key1,
		Key2,
		Key3,
		Key4,
		Key5,
		Key6,
		Key7,
		Key8,
		Key9,
		None,
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
		int backchorus; // Set WAV number
		int length = 1000; // Default Value = 1000
		std::vector<double> bpms;
		int bga, pooranim, layerbga;
		std::array<std::vector<bool>, 9> objects;
	};

	struct Bms {
		Header header;
		std::vector<Bar> bar;
		bool ok = false;
	};

	Bms load(std::string bmsfile) {
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
				if (isdigit(line[1])) {

				}
				else {
					auto strs = split_naive(line, ' ');
					std::string command = strs[0].substr(1);
					std::string arg1 = strs[1];
					if (!std::strcmp(command.c_str(), "PLAYER")) {
						bms.header.player = static_cast<Player>(std::stoi(arg1.c_str()));
					}
					if (!std::strcmp(command.c_str(), "GENRE")) {
						bms.header.genre = arg1;
					}
					if (!std::strcmp(command.c_str(), "TITLE")) {
						bms.header.title = arg1;
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
					if (!std::strcmp(command.substr(0,3).c_str(), "WAV")) {
						bms.header.wav[std::stoi(command.substr(3, 2), nullptr, 36)] = arg1;
					}
					if (!std::strcmp(command.substr(0, 3).c_str(), "BMP")) {
						bms.header.bmp[std::stoi(command.substr(3, 2), nullptr, 36)] = arg1;
					}
					if (!std::strcmp(command.c_str(), "StageFile")) {
						bms.header.stagefile = arg1;
					}
				}
			}
		}
	}

	void save(std::string filename, const Bms& bms) {

	}
}