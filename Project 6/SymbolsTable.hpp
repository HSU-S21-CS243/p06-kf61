#pragma once
#include <unordered_map>
#include <string>
using std::unordered_map;
using std::string;
using std::to_string;

class SymbolsTable
{
private:
	unordered_map<string, int> _lookup_table;
	int _address_counter = 16;
public:
	SymbolsTable()
	{
		//predefined symbols (p. 110 in book)
		_lookup_table["SP"] = 0;
		_lookup_table["LCL"] = 1;
		_lookup_table["ARG"] = 2;
		_lookup_table["THIS"] = 3;
		_lookup_table["THAT"] = 4;
		_lookup_table["SCREEN"] = 16384;
		_lookup_table["KBD"] = 24576;
		for (int i = 0; i < 16; i++)
		{
			string reg = "R" + to_string(i);
			_lookup_table[reg] = i;
		}
	}

	int& operator[](string key)
	{
		//key not found, add new entry
		if (_lookup_table.find(key) == _lookup_table.end())
		{
			_lookup_table[key] = _address_counter;
			_address_counter++;
		}
		return _lookup_table[key];
	}
};