#pragma once
#include<iostream>
#include<vector>
#include<string>
#include <sstream>
#include <fstream>

#include "non_dimensionalize.h"

using namespace std;

void non_dimensionalization::read_rawdata_file(string inp_filename,  string out_filename) {

	cout << "Reading project raw data file csv format" << endl;
	csvReading.getlinedatafile(inp_filename);

	for (unsigned int i = 0; i < user_input_name.size(); i++) {
		data_name.push_back(user_input_name.at(i));
	}
	for (unsigned int i = 0; i < user_output_name.size(); i++) {
		data_name.push_back(user_output_name.at(i));
	}
	
	get_tensordata();
	get_nondim_position();
	write_in_csv(out_filename);

	

	
	//wv.write_csv(out_filename, tensordata);
}


void non_dimensionalization::get_nondim_position() {

	//vector<int> data_position;
	//for (unsigned int i1 = 0; i1 < data_name.size(); i1++) {
	//	data_position.push_back(i1);
	//}
	vector<int> nondim_position;
	for (unsigned int j1 = 0; j1 < non_dim.size(); j1++) {
		auto it = find(data_name.begin(), data_name.end(), non_dim.at(j1));
		if (it != data_name.end()) {
			int index = distance(data_name.begin(),it);
			nondim_position.push_back(index);
		}
		else {
			nondim_position.push_back(-1);
		}

	}
	//for (unsigned int k = 0; k < nondim_position.size(); k++) {
		
	//	cout << nondim_position.at(k)<< endl;
	//}

	non_dimensionalizing_data(&nondim_position);
	
}

void non_dimensionalization::get_tensordata() {
	

	for (unsigned int i1 = 0; i1 < csvReading.InputData.size(); i1++) {
		vector<double> data1;
		for (unsigned int i2 = 0; i2 < csvReading.InputData.at(i1).size(); i2++) {
			data1.push_back(csvReading.InputData.at(i1).at(i2));
		}
		for (unsigned int i3 = 0; i3 < csvReading.OutputData.at(i1).size(); i3++) {
			//cout << csvReading.InputData.at(i1).at(i3) << "\t";
			data1.push_back(csvReading.OutputData.at(i1).at(i3));
		}
		//cout << endl;
		tensordata.push_back(data1);
	}

	

}


void non_dimensionalization::non_dimensionalizing_data(vector<int>* vec) {

	vector<vector<double>> tensordata1 = tensordata;
	
	cout << "Non-dimensionalizing the data" << endl;

		
	for (unsigned int k = 0; k < tensordata1.size(); k++) {
		vector<double> data1;
		for (unsigned int l = 0; l < tensordata1.at(k).size(); l++) {
			
			if (vec->at(l) != -1) {
				tensordata.at(k).at(l) =  tensordata1.at(k).at(l) / tensordata1.at(k).at(vec->at(l));
			}	
		}
	}
}


void non_dimensionalization::write_in_csv(string output_filename) {


	cout << "writing non-dimensionalized data to a csv file" << endl;
	vector<vector<string>> to_write;

	vector<string> row_write;
	row_write.push_back("Data_description");
	to_write.push_back(row_write);


	for (unsigned int ill = 0; ill < user_input_name.size(); ill++) {

		string s1 = "Input";
		string s2 = to_string(ill);
		vector<string> row_write1;
		row_write1.push_back(s1 + s2);

		row_write1.push_back(user_input_name.at(ill));

		to_write.push_back(row_write1);

	}

	for (unsigned int j = 0; j < user_output_name.size(); j++) {

		string s1 = "Output";
		string s2 = to_string(j);
		vector<string> row_write1;
		row_write1.push_back(s1 + s2);
		row_write1.push_back(user_output_name.at(j));
		to_write.push_back(row_write1);
	}
	

	int size_input_output = user_input_name.size() + user_output_name.size();
	vector<string> row_write1;
	row_write1.push_back("Data begin");
	for (int i = 0; i < size_input_output; i++) {
		int user_in_size = user_input_name.size();
		if (i < user_in_size) {
			string s1 = "Input";
			string s2 = to_string(i);
			row_write1.push_back(s1 + s2);
		}
		if (i >= user_in_size) {
			string s1 = "Output";
			string s2 = to_string(user_output_name.size() - (size_input_output - i));
			row_write1.push_back(s1 + s2);
		}
	}
	to_write.push_back(row_write1);

	string s3 = "TD";
	int counti = 0;
	for (unsigned int i = 0; i < tensordata.size();i++) {
		vector<string> row_write1;
		row_write1.push_back(s3 + to_string(counti));
		for (unsigned int iterator1 = 0; iterator1 < tensordata.at(i).size(); iterator1++) {
			row_write1.push_back(to_string(tensordata.at(i).at(iterator1)));
		}
		to_write.push_back(row_write1);
		counti++;
	}

	vector<string> row_write2;
	row_write2.push_back("Data End");
	to_write.push_back(row_write2);
	
	wv.write_csv(output_filename, to_write);

}