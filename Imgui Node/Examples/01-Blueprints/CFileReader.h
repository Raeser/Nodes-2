#pragma once
#include <vector>

enum class READ_ERROR_CODE
{
	Success,
	Invalid_Node_Connection
};

enum class EConnection
{
	In,
	Out,
	Count
};
struct SPinData
{
	EConnection connection_type;
	std::string name;
	std::string type;
};

struct SNodeData
{
	std::string name;
	std::vector<SPinData> outs;
	std::vector<SPinData> ins;

};

class CFileReader
{
public:
	CFileReader();
	~CFileReader();

	std::vector<std::string> ReadDirectory(const char* aDirectory);
	READ_ERROR_CODE ReadNode(const std::string& aPath, SNodeData& out);
};

