#pragma once
#include <string>
#include <map>
#include <bits/stdc++.h>

class GCode
{
	enum GCodeType
	{
		G,
		S,
		T,
		M
	};
	std::string Text = "";
	GCodeType Type;
	int TypeNumber;
	std::map<const char, const float> Tokens;

public:
	GCode();
	GCode(std::string text);
	std::string getText();
	GCodeType getGCodeType();
	int getTypeNumber();
	std::map<const char, const float> getTokens();
};

GCode::GCode()
{
	
}

GCode::GCode(std::string text)
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
				Type = G;
				break;
			case 'M':
				Type = M;
				break;
			case 'S':
				Type = S;
				break;
			case 'T':
				Type = T;
				break;
			}
		}

	} while (ss >> word);
}

std::string GCode::getText()
{
	return Text;
}

GCode::GCodeType GCode::getGCodeType()
{
	return Type;
}

int GCode::getTypeNumber()
{
	return TypeNumber;
}

std::map<const char, const float> GCode::getTokens()
{
	return Tokens;
}