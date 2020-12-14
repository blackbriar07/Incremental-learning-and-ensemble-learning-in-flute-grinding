#pragma once
#include<iostream>
#include<vector>
#include<string>
#include <dirent.h>
#include <fstream>
#include <sstream>

using namespace std;



class data_info {
public:
	vector<double> original_input;
	vector<string> data_name;
	vector<string> non_dim_name;
	vector<double> dimensionless_data;
	vector<double> reduced_data;
	vector<int> nondim_position;
	data_info(vector<string> input_name, vector<string> output_name, vector<string> nondim_name) {
		
		for (size_t ii = 0; ii != input_name.size(); ii++) {
			data_name.push_back(input_name.at(ii));
		}
		for (size_t ii = 0; ii != output_name.size(); ii++) {
			data_name.push_back(output_name.at(ii));
		}
		non_dim_name = nondim_name;
	}
};

class mathematics {
public:
	double squared_distance(vector<double> v1, vector<double> v2);
	vector<double> matrix_multiplication(vector<vector<vector<double>>> weights, vector<double> layer_output);
	vector<double> multiply_layer(vector<vector<double>> layerweight, vector<double> layerou);
	vector<double> sigmoid_function(vector<double> result);
};


class cluster_info {
public:
	int ID;
	string cluster_location;
	string cluster_trained_location;
	int Input_value;
	int Output_value;
	int num_hidden_layers;
	vector<int> layer_number;
	vector<int> dim_hidden_layers;
	vector<string> clusterinputname;
	vector<double> centroid;
	vector<double> scale;
	vector<double> minimum;
	vector<vector<vector<double>>> weights;
	double radius;

public:
	void read_file_lines(string *cluster_file,vector<string> *data_names);
	void split_line(vector<string> *line);
	void extract_info(vector<string> *split_words);
	bool find_string(string main_word, string part_word);
	void extract_weights(vector<string> *line);
	//void extract_info(vector<vector<string>> *split_words);
	string check_tab_string(string word);
	cluster_info(int ID,string cluster_file,string trained_cluster_file);
};


class implement_to_OU1_file {
public:
	string cluster_folder_location;
	string test_OU1_file_location;
	vector<cluster_info> all_clusters;
	vector<string> input_data_name;
	vector<string> output_data_name;
	vector<string> non_dim_name;
	vector<vector<string>> cluster_files;
	void get_OU1_file();
	void process_OU1_file_info(string filePathName);
	void process_inputData(data_info di);
	void split_words(vector<string> vect);
	void extract_cluster_info();
	int cluster_predictions(data_info data);
	vector<vector<string>> finding_cluster_locations(string folder_location);
	vector<double> find_vector_input(vector<vector<string>> *vec);
	string check_tab_string(string word);
	vector<string> split_strings_space(string string_sent);
	mathematics math;
	vector<double> find_vector_output(data_info data, int mini_index);
	
};





