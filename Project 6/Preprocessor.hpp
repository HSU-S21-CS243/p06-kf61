#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <regex> 
#include <sstream>

using namespace std;

class Preprocessor
{
private:
	const string LABEL = "\\(([a-zA-Z.$:_]+[\\da-zA-Z.$:_]*)\\)";
	const string A_CONST = "(@)([\\d]+)";
	const string A_SYMBL = "(@)([a-zA-Z.$:_]+[\\da-zA-Z.$:_]*)";
	const string C_COMP = "([DMA]*)=([!-DMA][-+\\|&]*[DMA\\d]*)";
	const string C_JMP = "([DMA\\d]);([J][\\w]+)";
	vector<string> regular_expressions;
        vector<string> _failed_lines;
	string _file_to_process;

public:

	Preprocessor(string file_name)
		: _file_to_process(file_name)
	{
		regular_expressions = vector<string>{ LABEL, A_CONST, A_SYMBL, C_COMP, C_JMP,  };
	}

    string removeAllWhiteSpace(const string& text)
    {
        istringstream input{ text };
        ostringstream output{};
        while (input.good() == true)
        {
            string temp;
            input >> temp;
            output << temp;
        }
        return output.str();
    }

    string removeComments(const string& text)
    {
        string result{ text };
        int index = result.find("//");
        return result.substr(0, index);
    }

    /*
    Returns a 2D vector [ROW][DATA].
    The outside vector represents the line in the file.  Each line is itself a vector of data.
    DATA[X][0] tells you which regular expression was used to parse the line.  This can be used
               to tell you what type of command the line is (e.g. A instruction, C instruction, jump, etc.)
    DATA[X][1] always represents the raw line in the event that you need it
    DATA[X][2] through DATA[X][N] represent the pieces of each line that will be helpful in 
       converting the line to HACK machine language
    */
	vector<vector<string>> processFile()
	{
        vector<vector<string>> result{};
        ifstream to_process{_file_to_process};
        if (to_process.is_open() == true)
        {
            while (to_process.good() == true)
            {
                string line;
                getline(to_process, line);
                line = removeAllWhiteSpace(line);
                line = removeComments(line);
                bool has_match = false;
                for (int i = 0; i < regular_expressions.size(); i++)
                {
                    string& expression = regular_expressions[i];
                    smatch match;
                    regex pattern{ expression };
                    auto match_found = regex_match(line, match, pattern);
                    if (match_found == true)
                    {
                        has_match = true;
                        vector<string> pieces{};
                        pieces.push_back(to_string(i));
                        for (auto piece : match)
                        {
                            pieces.push_back(piece);
                        }
                        result.push_back(pieces);
                        break;
                    }
                }
                if (has_match == false)
                {
                    _failed_lines.push_back(line);
                }
            }
        }
        
        return result;
	}
};

