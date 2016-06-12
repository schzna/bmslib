#pragma once
#include<string>
#include<array>
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


}