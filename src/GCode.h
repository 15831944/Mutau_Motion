#pragma once
#include <string>
#include <map>
#include <bits/stdc++.h>

enum GCodeType
{
	G,
	M,
	S,
	T
};

class GCode
{
	std::string Text = "";
	int TypeNumber;
	std::map<const char, const float> Tokens;

public:
	GCode(std::string text);
	std::string getText();
	int getTypeNumber();
	std::map<const char, const float> getTokens();
	GCodeType CommandType;
};

GCode::GCode(std::string text = "G1")
{
	transform(text.begin(), text.end(), text.begin(), ::toupper);
	Text = text;

	std::stringstream ss;
	ss.str(Text);
	char Key;
	std::string Value;
	bool first = true;
	std::string word;

	ss >> word;

	do
	{
		Key = word[0];
		Value = word.erase(0, 1);

		Tokens.insert(std::pair<char, float>(Key, std::stof(Value)));

		if (first)
		{
			first = false;
			TypeNumber = std::stoi(Value);
			switch (Key)
			{
			case 'G':
				CommandType = GCodeType::G;
				break;
			case 'M':
				CommandType = GCodeType::G;
				break;
			case 'S':
				CommandType = GCodeType::G;
				break;
			case 'T':
				CommandType = GCodeType::G;
				break;
			}
		}

	} while (ss >> word);
}

std::string GCode::getText()
{
	return Text;
}

int GCode::getTypeNumber()
{
	return TypeNumber;
}

std::map<const char, const float> GCode::getTokens()
{
	return Tokens;
}