#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <dirent.h>
#include <fstream>
#include <sstream>
#include "Reading_dataFile.h"
#include "trainingset.h"


using namespace std;


void reading_datafile::find_all_folder_paths(string filename) {
		
	cout << "Reading raw data......" << endl;
	DIR *dir;
	struct dirent *pdir;
	string path = filename;
	
	

	string file_subdirectories;
	
	if ((dir = opendir(path.c_str())) != NULL) {

		while ((pdir = readdir(dir)) != NULL) {

			if (strcmp(pdir->d_name, ".") == 0 || strcmp(pdir->d_name, "..") == 0) continue;
			if (pdir->d_type == DT_DIR) {
				file_subdirectories = path + "\\" + pdir->d_name;
				find_OU1_files(file_subdirectories);
				
			}

	
		}
	}
	closedir(dir);
	
	write_in_csv();
	/*
	vector<trainingSet>::iterator it;
	for (it = m_trainingset.begin(); it != m_trainingset.end(); ++it) {

		it->raw_Input();
		cout << endl;
	}
	*/
	
	
}

void reading_datafile::find_OU1_files(string name_of_folder_path) {
	DIR *di;
	char *ptr1, *ptr2;
	int retn;
	struct dirent *dir;
	string result;
	
	string path_name = name_of_folder_path;

	string delm = "ou1";
	di = opendir(path_name.c_str()); //specify the directory name
	if (di)
	{
		while ((dir = readdir(di)) != NULL)
		{
			ptr1 = strtok(dir->d_name, ".");
			ptr2 = strtok(NULL, ".");
			if (ptr2 != NULL)
			{
				retn = strcmp(ptr2, delm.c_str());
				if (retn == 0)
				{
					result = path_name + "\\" + ptr1 + "." + delm;
					
					ifstream file(result);
					string str;
					vector<string> line;

					while (getline(file, str)) {
						line.push_back(str);
					}
					file.close();
					split_words(line);
					
				}
			}
		}
		closedir(di);
	}
}


void reading_datafile::split_words(vector<string> vect) {

	vector<double> g_input;
	vector<double> g_output;
	vector<vector<string>> split_word;
	string delm = " = ";

	for (unsigned i = 0; i < vect.size(); i++) {

		//vector<string> elems = split_strings_space(vect.at(i));

		vector<string> elems;
		stringstream ss(vect.at(i));
		string item;
		while (getline(ss, item, '=')) {
			
			elems.push_back(item);
		}


		split_word.push_back(elems);

	}

	g_input = find_vector_input(split_word);
	g_output = find_vector_output(split_word);

	
	trainingSet *m_traininginstance = new trainingSet;
	m_traininginstance->raw_data_name(input_data_name);
	m_traininginstance->raw_data_name(output_data_name);
	m_traininginstance->raw_Input(g_input);
	m_traininginstance->raw_Output(g_output);
	m_traininginstance->raw_data();
	m_trainingset.push_back(*m_traininginstance);
	
}


vector<double> reading_datafile::find_vector_input(vector<vector<string>> vec) {
	string DIC;
	vector<double> input;
	double value = 0.0;

	for (unsigned int i = 0; i <= vec.size() - 1; i++) {

		
		if ((vec.at(i)).size() != 0) {


			if (check_tab_string(vec.at(i).at(0)) == "Direction of Cut Is Right") {
				DIC = check_tab_string((vec.at(i)).at(1));
				if (DIC == "true") {
					value = 1.0;
				}
				else { value = 0.0; }
				input.push_back(value);
			}

			if (check_tab_string(vec.at(i).at(0)) == "End Mill Open") {
				DIC = check_tab_string((vec.at(i)).at(1));
				if (DIC == "true") {
					value = 1.0;
				}
				else { value = 0.0; }
				input.push_back(value);
			}

			if (check_tab_string(vec.at(i).at(0)) == "Diameter") {
				value = stod(check_tab_string((vec.at(i)).at(1)));
				input.push_back(value);
			}
			if (check_tab_string(vec.at(i).at(0)) == "Pass") {
				value = stod(check_tab_string((vec.at(i)).at(1)));
				input.push_back(value);
			}
			if (check_tab_string(vec.at(i).at(0)) == "Helix Angle") {
				value = stod(check_tab_string((vec.at(i)).at(1)));
				input.push_back(value);
			}
			if (check_tab_string(vec.at(i).at(0)) == "Base Distance For Rake Angle Measurement") {
				value = stod(check_tab_string((vec.at(i)).at(1)));
				input.push_back(value);
			}
			if (check_tab_string(vec.at(i).at(0)) == "Number of Teeth") {
				value = stod(check_tab_string((vec.at(i)).at(1)));
				input.push_back(value);
			}
			if (check_tab_string(vec.at(i).at(0)) == "Wheel Diameter") {
				value = stod(check_tab_string((vec.at(i)).at(1)));
				input.push_back(value);
			}
			if (check_tab_string(vec.at(i).at(0)) == "Profile Angle") {
				value = stod(check_tab_string((vec.at(i)).at(1)));
				input.push_back(value);
			}
			if (check_tab_string(vec.at(i).at(0)) == "Radius 1") {
				value = stod(check_tab_string((vec.at(i)).at(1)));
				input.push_back(value);
			}
			if (check_tab_string(vec.at(i).at(0)) == "Radius 2") {
				value = stod(check_tab_string((vec.at(i)).at(1)));
				input.push_back(value);
			}
			if (check_tab_string(vec.at(i).at(0)) == "Rake Angle") {
				vector<string> space_words = split_strings_space((vec.at(i)).at(1));
				value = stod(check_tab_string(space_words.at(1)));
				input.push_back(value);
			}
			if (check_tab_string(vec.at(i).at(0)) == "Circular Land") {
				vector<string> space_words = split_strings_space((vec.at(i)).at(1));
				value = stod(check_tab_string(space_words.at(1)));
				input.push_back(value);
			}
			if (check_tab_string(vec.at(i).at(0)) == "Small Core Diameter") {
				vector<string> space_words = split_strings_space((vec.at(i)).at(1));
				value = stod(check_tab_string(space_words.at(1)));
				input.push_back(value);
			}


		}
	}
	

	return input;
}


vector<double> reading_datafile::find_vector_output(vector<vector<string>> vec) {
	string DIC;
	vector<double> output;
	double value = 0.0;

	for (unsigned int i = 0; i <= vec.size() - 1; i++) {

		
		if ((vec.at(i)).size() != 0) {

			if (check_tab_string(vec.at(i).at(0)) == "Wheel Setting Angle") {
				value = stod(check_tab_string((vec.at(i)).at(1)));
				output.push_back(value);
			}
			if (check_tab_string(vec.at(i).at(0)) == "Minimum Wheel Width") {
				value = stod(check_tab_string((vec.at(i)).at(1)));
				output.push_back(value);
			}
			if (check_tab_string(vec.at(i).at(0)) == "Wheel Displacement") {
				value = stod(check_tab_string((vec.at(i)).at(1)));
				output.push_back(value);
			}
			if (check_tab_string(vec.at(i).at(0)) == "Distance Between Axes") {
				value = stod(check_tab_string((vec.at(i)).at(1)));
				output.push_back(value);
			}

		}
	}
	
	return output;
}


string reading_datafile::check_tab_string(string word) {
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

vector<string> reading_datafile::split_strings_space(string string_sent) {

	vector<string> elems1;
	stringstream ss(string_sent);
	string item1;
	while (getline(ss, item1, ' ')) {

		elems1.push_back(item1);
	}

	return elems1;
}


void reading_datafile::write_in_csv() {

	cout << "writing raw data to a csv file" << endl;
	vector<vector<string>> to_write;

	vector<string> row_write;
	row_write.push_back("Data_description");
	to_write.push_back(row_write);

	/*
	vector<trainingSet>::iterator it;
	for (it = m_trainingset.begin(); it != m_trainingset.end(); ++it) {

		it->raw_Input();
		cout << endl;
	}
	*/
	
	for (unsigned int ill = 0; ill < input_name.size(); ill++) {
		
		string s1 = "Input";
		string s2 = to_string(ill);
		vector<string> row_write1;
		row_write1.push_back(s1 + s2);
		
		row_write1.push_back(input_name.at(ill));
		
		to_write.push_back(row_write1);
		
	}
	
	for (unsigned int j = 0; j < output_name.size(); j++) {
		
		string s1 = "Output";
		string s2 = to_string(j);
		vector<string> row_write1;
		row_write1.push_back(s1 + s2);
		row_write1.push_back(output_name.at(j));
		to_write.push_back(row_write1);
	}
	/*
	vector<trainingSet>::iterator it;
	for (it = m_trainingset.begin(); it != m_trainingset.end(); ++it) {

		it->raw_Input();
		cout << endl;
	}
	*/
	
	int size_input_output = input_name.size() + output_name.size();
	vector<string> row_write1;
	row_write1.push_back("Data begin");
	for (int i = 0; i < size_input_output; i++) {
		int in_nm_size = input_name.size();
		if (i < in_nm_size){
			string s1 = "Input";
			string s2 = to_string(i);
			row_write1.push_back(s1 + s2);
		}
		if (i >= in_nm_size) {
			string s1 = "Output";
			string s2 = to_string(output_name.size()-(size_input_output-i));
			row_write1.push_back(s1 + s2);
		}
	}
	to_write.push_back(row_write1);

	string s3 = "TD";
	vector<trainingSet>::iterator it;
	int counti = 0;
	for (it = m_trainingset.begin(); it != m_trainingset.end(); ++it) {
		vector<string> row_write1;
		row_write1.push_back(s3 + to_string(counti));
		for (unsigned int iterator1 = 0; iterator1 < it->raw_input.size(); iterator1++) {
			row_write1.push_back(to_string(it->raw_input.at(iterator1)));
		}
		for (unsigned int iterator2 = 0; iterator2 < it->raw_output.size(); iterator2++) {
			row_write1.push_back(to_string(it->raw_output.at(iterator2)));
		}
		to_write.push_back(row_write1);
		counti++;
	}

	vector<string> row_write2;
	row_write2.push_back("Data End");
	to_write.push_back(row_write2);
	


	
	string location = loc_file.at(1) + "\\" + loc_file.at(2);
	wv.write_csv(location, to_write);

}
