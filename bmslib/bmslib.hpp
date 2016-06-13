#pragma once
#include<string>
#include<fstream>
#include<array>
#include<vector>
namespace bmslib {

	enum class Player {
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
		while (getline(file, line))
		{
			
		}
	}

	void save(std::string filename, const Bms& bms) {

	}
}