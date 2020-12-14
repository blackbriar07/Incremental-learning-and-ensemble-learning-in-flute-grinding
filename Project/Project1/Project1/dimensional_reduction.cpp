#include <iostream>
#include<vector>
#include<string>
#include "dimensional_reduction.h"

using namespace std;

void dimension_reduce::dimension_reduce_operation(string inp_filename, string out_filename) {
	

	cout << "Reading non-dimensionalized data file csv format" << endl;
	csvReading.getlinedatafile(inp_filename);

	get_data_parameters();
	get_tensordata();
	variance_threshold();
	write_in_csv(out_filename);

}

void dimension_reduce::get_tensordata() {

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

void dimension_reduce::get_data_parameters() {

	for (unsigned int i = 0; i < csvReading.data_parameters_input.size(); i++) {
		data_parameters.push_back(csvReading.data_parameters_input.at(i));
	}
	for (unsigned int i = 0; i < csvReading.data_parameters_output.size(); i++) {
		data_parameters.push_back(csvReading.data_parameters_output.at(i));
	}
}

void dimension_reduce::variance_threshold() {

	int size_of_tensor = tensordata.size();
	int size_of_inputdata = tensordata.at(0).size() - csvReading.OutputData.at(0).size();
	//cout << tensordata.at(0).size() << endl;
	//cout << csvReading.data_parameters_output.at(0).size() << endl;
	vector<int> keep_position;
	for (int i = 0; i < size_of_inputdata; i++) {
		int cout = 0;
		double value = tensordata.at(0).at(i);
		for (int j = 0; j < size_of_tensor; j++) {
			if (tensordata.at(j).at(i) != value) {
				keep_position.push_back(i);
				break;
			}
		}
	}
	

	reducing_data(&keep_position);
	
}

void dimension_reduce::reducing_data(vector<int>* position) {

	int input_output_size = csvReading.data_parameters_input.size() + csvReading.data_parameters_output.size();
	
	vector<vector<string>> data_parameters1 ;
	for (unsigned int i = 0; i < position->size(); i++) {
		data_parameters1.push_back(data_parameters.at(position->at(i)));
	}
	for (int j = csvReading.data_parameters_input.size(); j < input_output_size;j++) {
		data_parameters1.push_back(data_parameters.at(j));
	}
	
	data_parameters = data_parameters1;
	

	
	vector<vector<double>> tensordata1;
	for (unsigned int i = 0;i< tensordata.size(); i++) {
		vector<double> data1;
		//cout << i<<"heeeeeeeello";
		for (unsigned int j = 0; j < position->size(); j++) {
			//cout << j << "\t";
			data1.push_back(tensordata.at(i).at(position->at(j)));
		}
		for (int k = csvReading.data_parameters_input.size(); k < input_output_size; k++) {
			//cout << j << "\t";
			data1.push_back(tensordata.at(i).at(k));
		}

		tensordata1.push_back(data1);
	}
	
	tensordata = tensordata1;

}

void dimension_reduce::write_in_csv(string output_filename) {

	cout << "writing dimension reduce data to a csv file" << endl;
	vector<vector<string>> to_write;

	vector<string> row_write;
	row_write.push_back("Data_description");
	to_write.push_back(row_write);


	for (unsigned int ill = 0; ill < data_parameters.size(); ill++) {

		to_write.push_back(data_parameters.at(ill));

	}

	
	int size_input_output = data_parameters.size();
	vector<string> row_write1;
	row_write1.push_back("Data begin");
	for (unsigned int i = 0; i < data_parameters.size(); i++) {
		row_write1.push_back(data_parameters.at(i).at(0));
	}
	to_write.push_back(row_write1);

	string s3 = "TD";
	int counti = 0;
	for (unsigned int i = 0; i < tensordata.size(); i++) {
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