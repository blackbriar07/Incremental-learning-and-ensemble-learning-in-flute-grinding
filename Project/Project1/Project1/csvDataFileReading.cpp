#pragma once
#include<iostream>
#include<vector>
#include<string>
#include <sstream>
#include <fstream>

#include "csvDataFileReading.h"

using namespace std;

void csvdatafilereading::getlinedatafile(string filename) {

	//cout << "getlinedatafile" << endl;
	ifstream file(filename);
	string str;

	vector<string> line;

	while (getline(file, str)) {
		split_words(str);
	}

}


void csvdatafilereading::split_words(string str) {

	//cout << "split_words" << endl;
	vector<string> elems;
	stringstream ss(str);
	string item;
	while (getline(ss, item, ',')) {
		elems.push_back(check_tab_string(item));
	}
	if (elems.size() != 0)
		find_vector(elems);
	
}

void csvdatafilereading::getposition(vector<string> vec) {
	
	
	for (unsigned int ik = 1; ik < vec.size(); ik++) {
		for (unsigned int jk = 0; jk < data_parameters_input.size(); jk++) {
			if (data_parameters_input.at(jk).at(0) == vec.at(ik)) {
				input_position.push_back(ik);
			}
		}
		
		for (unsigned int kk = 0; kk < data_parameters_output.size(); kk++) {
			if (data_parameters_output.at(kk).at(0) == vec.at(ik)) {
				output_position.push_back(ik);
			}
		}
		
	}

	

}


void csvdatafilereading::find_vector(vector<string> vec) {

	vector<string> data1;
	
	if (string_containing_word(vec.at(0), "Input") == 1){
		//cout << vec.at(1) << endl;
		data1.push_back(vec.at(0));
		data1.push_back(vec.at(1));
		data_parameters_input.push_back(data1);
	}
	if (string_containing_word(vec.at(0), "Output") == 1){
		data1.push_back(vec.at(0));
		data1.push_back(vec.at(1));
		
		data_parameters_output.push_back(data1);
	}
	if (vec.at(0) == "Data begin")  {
		getposition(vec);
	}
	if(string_containing_word(vec.at(0), "TD") == 1) {
		getTensorData(vec);
	}
		
}

void csvdatafilereading::getInputTensor(vector<string> vec) {
	vector<double> data;

	for (unsigned int jkk = 0; jkk < input_position.size(); jkk++) {
		data.push_back(stod(vec.at(input_position.at(jkk))));
	}
	InputData.push_back(data);

}

void csvdatafilereading::getOutputTensor(vector<string> vec) {
	vector<double> data;

	for (unsigned int jkk = 0; jkk < output_position.size(); jkk++) {
		data.push_back(stod(vec.at(output_position.at(jkk))));
	}
	OutputData.push_back(data);

}


void csvdatafilereading::getTensorData(vector<string> vec) {

	getInputTensor(vec);
	getOutputTensor(vec);

}



string csvdatafilereading::check_tab_string(string word) {
	//cout << word << endl;
	if (word.length() != 0) {
		if (word[word.length() - 1] == ' ') {
			word = word.substr(0, word.length() - 1);
		}

		if (word[0] == ' ') {
			word = word.substr(1, word.length() - 1);

		}
	}

	return word;
}

bool csvdatafilereading::string_containing_word(string word, string findword) {
	
	bool status = false;

	if (word.find(findword) != string::npos) {
		status = true;
	}
	//cout << "hello" << endl;
	return status;
}

	
/*
void csvdatafilereading::getlinedatafile(string filename) {

	ifstream file(filename);
	string str;

	vector<string> line;

	while (getline(file, str)) {
		line.push_back(str);
	}
	file.close();
	split_words(line);
	find_vector(split_word);

}


void csvdatafilereading::split_words(vector<string> vect) {

	for (unsigned i = 0; i < vect.size(); i++) {

		vector<string> elems;
		stringstream ss(vect.at(i));
		string item;
		while (getline(ss, item, ',')) {
			elems.push_back(item);

		}
		split_word.push_back(elems);

	}
}

bool csvdatafilereading::string_containing_word(string word, string findword) {
	bool status = false;
	
	if (word.find(findword) != string::npos) {
		status =  true;
	}
	
	return status;
}


string csvdatafilereading::check_tab_string(string word) {
	//cout << word << endl;
	if (word.length() != 0) {
		if (word[word.length() - 1] == ' ') {
			word = word.substr(0, word.length() - 1);
		}

		if (word[0] == ' ') {
			word = word.substr(1, word.length() - 1);

		}
	}

	return word;
}


void csvdatafilereading::find_vector(vector<vector<string>> vec) {

	cout << "inside find vector" << endl;
	int data_begin, data_end, data_des_begin;
	vector<int> no_of_InputOutput;
	for (unsigned int i = 0; i <= vec.size() - 1; i++) {

		if (vec.at(i).size() != 0) {

			if (check_tab_string(vec.at(i).at(0)) == "Data_description") {
				//data_des_begin = i;
				for (unsigned int jk = i; jk <= vec.size() - 1; jk++) {

					if ((string_containing_word(check_tab_string(vec.at(jk).at(0)), "Input")) == 1)
						//cout << vec.at(jk).at(0) << endl;
						data_parameters_input.push_back(check_tab_string(vec.at(jk).at(0)));
					if ((string_containing_word(check_tab_string(vec.at(jk).at(0)), "Output")) == 1)
						//cout << vec.at(jk).at(0) << endl;
						data_parameters_output.push_back(check_tab_string(vec.at(jk).at(0)));
					if (check_tab_string(vec.at(jk).at(0)) == "Data begin") {
						for (unsigned int jk1 = jk; jk1 <= vec.size() - 1; jk1++) {
							if ((string_containing_word(check_tab_string(vec.at(jk1).at(0)), "TD")) == 1) 
								cout << vec.at(jk1).at(0) << endl;
							
							}
							//break;
						}
				}
			}
		}
	}
}
*/
