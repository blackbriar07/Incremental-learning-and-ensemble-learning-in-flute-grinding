#pragma once
#include <iostream>
#include<vector>
#include<string>
#include "csvDataFileReading.h"
#include "Write_to_csv.h"

using namespace std;

class dimension_reduce {
public:
	void dimension_reduce_operation(string inp_filename, string out_filename);
	csvdatafilereading csvReading;
	void get_tensordata();
	vector<vector<double>> tensordata;
	vector<vector<string>> data_parameters;
	void get_data_parameters();
	void variance_threshold();
	void reducing_data(vector<int>* position);
	void write_in_csv(string output_filename);
	write_into_csv wv;


};