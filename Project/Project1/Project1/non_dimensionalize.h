#pragma once
#include<iostream>
#include<vector>
#include<string>
#include "csvDataFileReading.h"
#include "trainingset.h"
#include "Write_to_csv.h"

using namespace std;

class non_dimensionalization {
public:
	vector<trainingSet> M_trainingset1;
	//non_dimensionalization(vector<trainingSet> m_trainingset1):
	//	M_trainingset1(m_trainingset1){}
	csvdatafilereading csvReading;
	void read_rawdata_file(string inp_filename, string out_filename);
	void non_dimensionalizing_data(vector<int>* vec);
	vector<string> user_input_name;
	vector<string> user_output_name;
	vector<double> raw_data_file_input;
	vector<double> raw_data_file_output;
	vector<string> data_name;
	vector<vector<double>> tensordata;
	vector<string> non_dim;
	void get_tensordata();
	void get_nondim_position();
	vector<vector<string>> dataPosition_nonDimPosition;
	write_into_csv wv;
	void write_in_csv(string output_filename);





};