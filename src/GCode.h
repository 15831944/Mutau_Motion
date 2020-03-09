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
	int TypeNumber;
	std::string Text = "";
	GCodeType Type;
	std::map<const char, const float> Tokens;

public:
	GCode(std::string text);
	std::string getText();
};

GCode::GCode(std::string text)
{
	transform(text.begin(), text.end(), text.begin(), ::toupper);
	Text = text;

	std::istringstream ss(Text);
	char Key;
	std::string Value;
	bool first = true;
	do
	{
		std::string word;
		Key = word[0];
		Value = word.erase(0, 1);

		Tokens.insert(std::pair<char, float>(Key, std::stof(Value)));

		if (first)
		{
			first = false;
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

	} while (ss);
}

std::string GCode::getText()
{
	return Text;
}