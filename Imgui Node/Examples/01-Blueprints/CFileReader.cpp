#include "CFileReader.h"
#include <string>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <fstream>

CFileReader::CFileReader()
{
}


CFileReader::~CFileReader()
{
}

std::vector<std::string> CFileReader::ReadDirectory(const char * aDirectory)
{
	std::vector<std::string> files;

	std::string path = aDirectory;
	for (auto & file : std::experimental::filesystem::directory_iterator(path))
	{
		std::stringstream oss;
		oss << file;
		files.push_back(oss.str());
	}
	return files;
}

READ_ERROR_CODE CFileReader::ReadNode(const std::string & aPath, SNodeData& out)
{
	std::ifstream ifs(aPath.c_str());

	int counter = 0;
	std::string line;
	while (std::getline(ifs, line))
	{
		if (counter == 0)
		{
			out.name = line;
		}
		else
		{
			SPinData pin_data;

			int cutoff;
			if (line.find("out") != -1)
			{
				cutoff = line.find("out") + 3;
				pin_data.connection_type = EConnection::Out;

			}
			else if (line.find("in") != -1)
			{
				cutoff = line.find("in") + 2;
				pin_data.connection_type = EConnection::In;
			}
			else
			{
				return READ_ERROR_CODE::Invalid_Node_Connection;
			}
			if (line[cutoff] != ' ')
			{
				return READ_ERROR_CODE::Invalid_Node_Connection;
			}
			line = line.substr(cutoff + 1);
			std::string name = line.substr(0, line.find_first_of(' '));
			std::string type = line.substr(line.find_first_of(' ')+1);
			pin_data.name = name;
			pin_data.type = type;

			switch (pin_data.connection_type)
			{
			case EConnection::In:
				out.ins.push_back(pin_data);
				break;
			case EConnection::Out:
				out.outs.push_back(pin_data);
				break;
			default:
				break;
			}
		}
		++counter;
	}

	return READ_ERROR_CODE::Success;
}
