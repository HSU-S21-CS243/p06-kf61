#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <bitset>

#include "Preprocessor.hpp"
#include "SymbolsTable.hpp"

using namespace std;

//Shows how you can use the symbols table to keep track of
//symbols inside an ASM file;
void symbols_table_example()
{
	SymbolsTable symbols{};

	//R1 already exists so we should get memory location 1...
	cout << "Location of R1: " << symbols["R1"] << endl;

	//To add a new symbol, just access it and the symbols table will
	//associate that symbol with the next avaialble slot in memory
	symbols["MyVariable"];

	//should be 16 since it's the first variable that we defined
	cout << "Location of MyVariable: " << symbols["MyVariable"] << endl;


	cout << endl;
}

//Shows how you can use the preprocessor to load a file 
//and get it ready for parsing.
void preprocessor_example()
{
	cout << "preprocessing example..." << endl;

	Preprocessor prep{ "Max.asm" };
	vector<vector<string>> lines = prep.processFile();

	//TODO: Run in DEBUG mode and examine the results of lines
	cout << "preprocessing complete" << endl;
}

//convert to binary
string convertToBin(int decToConvert){
    
    string convertedBinary;
    convertedBinary = "0" + bitset<15>(decToConvert).to_string();  
    return convertedBinary;
    }
       


int main(int argc, char* argv[])
{

	//makes debugging easier by allowing you to directly load in files w/o using command line
	Preprocessor prep{"Rect.asm"};
	ofstream output{"Rect.hack"};

	//TODO: begin work here.
	vector<vector<string>> lines = prep.processFile();
	SymbolsTable symbols{};
	int program_counter = 0;
        int instruction_type;
   
        //first pass for labels 
	for (auto line : lines)
	{       
                //Demo code typed in 3/10/2021 lecture.  May or may not be useful for
		//actual program.          
                //A instruction with a variable (symbol)
		instruction_type = stoi(line[0]);                                  
                   if (instruction_type == 0)
                    {
			symbols[line[2]] = program_counter;
                    } 
                   else{
                       program_counter++;
                   }              						
	}
        
        //2nd pass main pass   
        for (auto line : lines)
        {
            //initialize variables
            string compbits = line[2];
            string compout = "0000000000";
            string jumpbitsout = "000";
            string jumpbits;
            string destbits = line[2];
            string destout = "000";
            //get instruction type 
            instruction_type = stoi(line[0]);            
            if (instruction_type == 3){
                destbits = line[2];
            }
            if (instruction_type == 2)
		{			
                    output << convertToBin(symbols[line[3]]) << endl;
		}
            if (instruction_type == 1)
            {
                int inValue = stoi(line[3]);
                output << convertToBin(inValue) << endl;
            }
            if (instruction_type == 3 || instruction_type == 4){  
                if (instruction_type == 3){
                    compbits = line[3];
                }
                else if (instruction_type == 4){
                    compbits = line[2];
                    jumpbits = line[3];
                }
                //check c bits 
                if(compbits == "0")
                {
                    compout = "1110101010";
                }
                else if(compbits == "1")
                {
                    compout  = "1110111111";
                }
                else if(compbits == "-1")
                {
                    compout  = "1110111111";
                }
                else if(compbits == "D")
                {
                    compout  = "1110001100";
                }
                else if(compbits == "A")
                {
                    compout  = "1110110000";
                }
                else if(compbits ==  "!D")
                {
                    compout  = "1110001101";
                }
                else if(compbits == "!A")
                {
                    compout  =  "1110110001";
                } 
                else if(compbits == "D+1")
                {
                    compout  =  "1110011111";
                }
                else if(compbits == "A+1")
                {
                    compout  = "1110110111";
                }
                else if(compbits == "D-1")
                {
                    compout  =  "1110001110";
                }
                else if(compbits == "A-1")
                {
                    compout  =  "1110110010";
                }
                else if(compbits == "D+A")
                {
                    compout  =  "1110000010";
                }  
                else if(compbits == "D-A")
                {
                    compout  =  "1110010011";
                }
                else if(compbits == "A-D")
                {
                    compout  =  "1110000111";
                }
                else if(compbits == "D&A")
                {
                    compout  =  "1110000000";
                }
                else if(compbits == "D|A")
                {
                    compout  = "1110010101";
                }
                else if(compbits == "M")
                {
                    compout  = "1111110000";
                }
                else if(compbits == "!M")
                {
                    compout  = "1111110001";
                }
                else if(compbits == "-M")
                {
                    compout  = "1111110011";
                }
                else if(compbits == "M+1")
                {
                    compout  = "1111110111";
                }
                else if(compbits == "M-1")
                {
                    compout  = "1111110010";
                }
                else if(compbits == "D+M")
                {
                    compout  = "1111000010";
                }
                else if(compbits == "D-M")
                {
                    compout  = "1111010011";
                }
                else if(compbits == "D-M")
                {
                    compout  = "1111010011";
                }
                else if(compbits == "M-D")
                {
                    compout  = "1111000111";
                }
                else if(compbits == "D&M")
                {
                    compout  = "1111000000";
                }
                else if(compbits == "D|M")
                {
                    compout  = "1111010101"; 
                }
                else
                {
                    compout  = "0000000000";
                }             
                //check jump bits
                if (instruction_type == 4)
                {    
                    if(jumpbits == "JGT")
                    {
                        jumpbitsout = "001";
                    }
                    else if(jumpbits == "JEQ")
                    {
                        jumpbitsout = "010";
                    }
                    else if(jumpbits == "JGE")
                    {
                        jumpbitsout = "011";
                    }
                    else if(jumpbits == "JLT")
                    {
                        jumpbitsout = "100";
                    }
                    else if(jumpbits == "JNE")
                    {
                        jumpbitsout = "101";
                    }
                    else if(jumpbits == "JLE")
                    {
                        jumpbitsout = "110";
                    }
                    else if(jumpbits == "JMP")
                    {
                        jumpbitsout = "111";
                    }
                    else if(jumpbits == "JMP")
                    {
                        jumpbitsout = "111";
                    }
                    else
                    {
                        jumpbitsout = "000";
                    }
                }
                //check dest bits
                if (instruction_type == 3 || instruction_type == 4)
                {    
                    if(destbits == "M")
                    {
                        destout = "001";
                    }
                    else if(destbits == "D")
                    {
                        destout = "010";
                    }           
                    else if (destbits == "MD")
                    {
                        destout = "011";
                    }
                    else if (destbits == "A"){
                        destout = "100";
                    }
                    else if (destbits == "AM"){
                        destout = "101";
                    }
                    else if (destbits == "AD"){
                        destout = "110";
                    }
                    else if (destbits == "ADM"){
                        destout = "111";
                    }
                    else{
                        destout = "000";
                    }
                }
                if(instruction_type != 0){
                output << compout << destout << jumpbitsout << endl;
                }
            }
        }
        output.close();
        return EXIT_SUCCESS;
}