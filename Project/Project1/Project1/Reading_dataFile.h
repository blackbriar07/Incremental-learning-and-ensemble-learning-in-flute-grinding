#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <dirent.h>
#include "user_data.h"
#include "trainingset.h"
#include "Write_to_csv.h"

using namespace std;

class reading_datafile : public user_CSVReader
{
public:	
	int cluster_number;
	void user_defined_file_data();
	vector<string> loc_file;
	vector<trainingSet> m_trainingset;
	vector<string> folders_in_directory;
	void find_all_folder_paths(string fileName1);
	void find_OU1_files(string name_of_folder_path);
	void split_words(vector<string> vect);
	vector<string> input_name;
	vector<string> decision;
	vector<string> output_name;
	vector<double> find_vector_input(vector<vector<string>> vec);
	vector<double> find_vector_output(vector<vector<string>> vec); 
	string check_tab_string(string word);
	vector<string> split_strings_space(string string_sent);
	virtual void write_in_csv();
	write_into_csv wv;


	


	

};

