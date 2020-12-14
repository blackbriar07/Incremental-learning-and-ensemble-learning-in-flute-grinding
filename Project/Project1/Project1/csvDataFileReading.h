#pragma once
#include<iostream>
#include<vector>
#include<string>
using namespace std;

class csvdatafilereading {
public:
	void getlinedatafile(string filename);
	void split_words(string str);
	void find_vector(vector<string> vec);
	string check_tab_string(string word);
	bool string_containing_word(string word, string findword);
	vector<vector<string>> split_word;
	vector<vector<string>> data_parameters_input;
	vector<vector<string>> data_parameters_output;
	vector<vector<double>> InputData;
	vector<vector<double>> OutputData;
	vector<int> input_position;
	vector<int> output_position;
	void getInputTensor(vector<string> vec);
	void getOutputTensor(vector<string> vec);
	void getposition(vector<string> vec);
	vector<vector<double>> data;
	void getTensorData(vector<string> vec);
};