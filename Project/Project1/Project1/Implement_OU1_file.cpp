#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include "Implement_OU1_file.h"


using namespace std;

void implement_to_OU1_file::extract_cluster_info() {
	
cout << "Reading the number of clusters" << endl;
finding_cluster_locations(cluster_folder_location);
cout << "Finished reading the number of clusters" << endl;
//vector<cluster_info> all_clusters;
 
cout << "Making cluster objects" << endl;
cout << "Number of cluster files :" << cluster_files.size() << endl;
for (size_t i = 0; i != cluster_files.size(); i++) {
	
	cluster_info clusters(stoi(cluster_files.at(i).at(0)), cluster_files.at(i).at(1), cluster_files.at(i).at(2));
	all_clusters.push_back(clusters);	
}
cout << "finished Making cluster objects" << endl;
/*
for (size_t j = 0; j != all_clusters.size(); j++) {
	cout << "Input :" << all_clusters[j].Input_value << endl;
	cout << "Output :" << all_clusters[j].Output_value << endl;
	cout << "Hidden :" << "  ";
	for (size_t hiddl = 0; hiddl != all_clusters[j].dim_hidden_layers.size(); hiddl++) {
		cout << all_clusters[j].dim_hidden_layers.at(hiddl) << "  ";

	}
	cout << endl;
	cout << "Centroid :" << "  ";
	for (size_t hiddl = 0; hiddl != all_clusters[j].centroid.size(); hiddl++) {
		cout << all_clusters[j].centroid.at(hiddl) << "  ";

	}
	cout << endl;
	cout << "Radius :" << all_clusters[j].radius << endl;
	cout << "Scale :" << "  ";
	for (size_t hiddl = 0; hiddl != all_clusters[j].scale.size(); hiddl++) {
		cout << all_clusters[j].scale.at(hiddl) << " ";

	}
	cout << endl;
	cout << "Minimum :" << "  ";
	for (size_t hiddl = 0; hiddl != all_clusters[j].minimum.size(); hiddl++) {
		cout << all_clusters[j].minimum.at(hiddl) << " ";

	}
}*/

	
get_OU1_file();
}


void implement_to_OU1_file::get_OU1_file() {

	cout << "Reading and implementing Ou1 files" << endl;
	
	DIR *di;
	char *ptr1, *ptr2;
	int retn;
	struct dirent *dir;
	string result;

	string path_name = test_OU1_file_location;

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
					process_OU1_file_info(result);

				}
			}
		}
		closedir(di);
	}

}


void implement_to_OU1_file::process_OU1_file_info(string filePathName) {
	ifstream file(filePathName);
	string str;
	vector<string> line;
	while (getline(file, str)) {
		line.push_back(str);
	}
	file.close();
	split_words(line);
}


void implement_to_OU1_file::split_words(vector<string> vect) {

	vector<vector<string>> split_word;
	string delm = " = ";

	for (unsigned i = 0; i < vect.size(); i++) {

		vector<string> elems;
		stringstream ss(vect.at(i));
		string item;
		while (getline(ss, item, '=')) {
			
			elems.push_back(item);
		}
		split_word.push_back(elems);

	}
		
	data_info data(input_data_name,output_data_name,non_dim_name);

	data.original_input =  find_vector_input(&split_word);
	
	process_inputData(data);

	
	//g_output = find_vector_output(split_word);
		
}

void implement_to_OU1_file::process_inputData(data_info data) {

	
	//vector<int> nondim_position;
	for (unsigned int j1 = 0; j1 < non_dim_name.size(); j1++) {
		auto it = find(data.data_name.begin(), data.data_name.end(), non_dim_name.at(j1));
		if (it != data.data_name.end()) {
			int index = distance(data.data_name.begin(), it);
			data.nondim_position.push_back(index);
		}
		else {
			data.nondim_position.push_back(-1);
		}
	}
	//cout << " non dim position" << endl;
	//for (size_t dd = 0; dd != nondim_position.size(); dd++) {
		//cout << nondim_position.at(dd) << " ";
	//}
	//cout << endl;
	for (size_t jj = 0; jj < data.original_input.size(); jj++) {
		if (data.nondim_position.at(jj) != -1) {
			
			data.dimensionless_data.push_back(data.original_input.at(jj) / data.original_input.at(data.nondim_position.at(jj)));
		}
		if (data.nondim_position.at(jj) == -1) {
			data.dimensionless_data.push_back(data.original_input.at(jj));
		}
	}
	//for (size_t dd = 0; dd != data.dimensionless_data.size(); dd++) {
	//	cout << data.dimensionless_data.at(dd) << " ";
	//}
	//cout << endl;
	//cout << "predicting cluster" << endl;

	cluster_predictions(data);
	//find_vector_output(data, cluster_index);

}


vector<double> implement_to_OU1_file::find_vector_input(vector<vector<string>> *vec) {
	string DIC;
	double value = 0.0;
	vector<double> original_input1;

	for (unsigned int i = 0; i <= vec->size() - 1; i++) {


		if ((vec->at(i)).size() != 0) {


			if (check_tab_string(vec->at(i).at(0)) == "Direction of Cut Is Right") {
				DIC = check_tab_string((vec->at(i)).at(1));
				if (DIC == "true") {
					value = 1.0;
				}
				else { value = 0.0; }
				original_input1.push_back(value);
			}

			if (check_tab_string(vec->at(i).at(0)) == "End Mill Open") {
				DIC = check_tab_string((vec->at(i)).at(1));
				if (DIC == "true") {
					value = 1.0;
				}
				else { value = 0.0; }
				original_input1.push_back(value);
			}

			if (check_tab_string(vec->at(i).at(0)) == "Diameter") {
				value = stod(check_tab_string((vec->at(i)).at(1)));
				original_input1.push_back(value);
			}
			if (check_tab_string(vec->at(i).at(0)) == "Pass") {
				value = stod(check_tab_string((vec->at(i)).at(1)));
				original_input1.push_back(value);
			}
			if (check_tab_string(vec->at(i).at(0)) == "Helix Angle") {
				value = stod(check_tab_string((vec->at(i)).at(1)));
				original_input1.push_back(value);
			}
			if (check_tab_string(vec->at(i).at(0)) == "Base Distance For Rake Angle Measurement") {
				value = stod(check_tab_string((vec->at(i)).at(1)));
				original_input1.push_back(value);
			}
			if (check_tab_string(vec->at(i).at(0)) == "Number of Teeth") {
				value = stod(check_tab_string((vec->at(i)).at(1)));
				original_input1.push_back(value);
			}
			if (check_tab_string(vec->at(i).at(0)) == "Wheel Diameter") {
				value = stod(check_tab_string((vec->at(i)).at(1)));
				original_input1.push_back(value);
			}
			if (check_tab_string(vec->at(i).at(0)) == "Profile Angle") {
				value = stod(check_tab_string((vec->at(i)).at(1)));
				original_input1.push_back(value);
			}
			if (check_tab_string(vec->at(i).at(0)) == "Radius 1") {
				value = stod(check_tab_string((vec->at(i)).at(1)));
				original_input1.push_back(value);
			}
			if (check_tab_string(vec->at(i).at(0)) == "Radius 2") {
				value = stod(check_tab_string((vec->at(i)).at(1)));
				original_input1.push_back(value);
			}
			if (check_tab_string(vec->at(i).at(0)) == "Rake Angle") {
				vector<string> space_words = split_strings_space((vec->at(i)).at(1));
				value = stod(check_tab_string(space_words.at(1)));
				original_input1.push_back(value);
			}
			if (check_tab_string(vec->at(i).at(0)) == "Circular Land") {
				vector<string> space_words = split_strings_space((vec->at(i)).at(1));
				value = stod(check_tab_string(space_words.at(1)));
				original_input1.push_back(value);
			}
			if (check_tab_string(vec->at(i).at(0)) == "Small Core Diameter") {
				vector<string> space_words = split_strings_space((vec->at(i)).at(1));
				value = stod(check_tab_string(space_words.at(1)));
				original_input1.push_back(value);
			}


		}
	}


	return original_input1;
}

string implement_to_OU1_file::check_tab_string(string word) {
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

vector<string> implement_to_OU1_file::split_strings_space(string string_sent) {

	vector<string> elems1;
	stringstream ss(string_sent);
	string item1;
	while (getline(ss, item1, ' ')) {

		elems1.push_back(item1);
	}

	return elems1;
}

vector<vector<string>> implement_to_OU1_file::finding_cluster_locations(string folder_location) {
	
	
	
	DIR *di;
	char *ptr1, *ptr2;
	int retn;
	struct dirent *dir;
	string result;

	string path_name = folder_location;
	string name = "cluster";
	string delm = "csv";
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
					string str(ptr1);
					size_t index = str.find(name);
					if (index != string::npos) {
						result = path_name + "\\" + ptr1 + "." + delm;
						ifstream file(result);
						string str;
						vector<string> line;
						while (getline(file, str)) {
							//cout << str << endl;
							line.push_back(str);
							break;
						}
						file.close();
						vector<string> elems;
						for (size_t i = 0; i != line.size(); i++) {
							stringstream ss(line.at(i));
							string item;
							while (getline(ss, item, ',')) {
		
								elems.push_back(item);
								
							}
							vector<string> files;
							if (elems.at(0) == "CLUSTER") {
								files.push_back(elems.at(1));
								files.push_back(result);
								string trained_file = path_name + "\\" + ptr1 +"_S"+ "." + delm;
								files.push_back(trained_file);

								cluster_files.push_back(files);
							}
							
						}
					}
					

				}
			}
		}
		closedir(di);
	}

	return cluster_files;
}


int implement_to_OU1_file::cluster_predictions(data_info data) {
	//cout << "hellllo" << endl;
	double mini;
	int min_index; 
	for (size_t cl = 0; cl != all_clusters.size(); cl++) {
		
		vector<double> td;
		for (int jk = 0; jk != all_clusters[cl].clusterinputname.size(); jk++) {
			for (int kj = 0; kj != data.data_name.size(); kj++) {
				
				if (all_clusters[cl].clusterinputname[jk] == data.data_name[kj]) {
					
					td.push_back(data.dimensionless_data[kj]);
					//cout << data.dimensionless_data[kj] << "\t";
					break;
				}
			}
		}
		double distance_point_cc = math.squared_distance(td, all_clusters[cl].centroid);
		if (cl == 0) {
			mini = distance_point_cc;
			min_index = cl;
		}
		if (mini > distance_point_cc && distance_point_cc <= all_clusters[cl].radius) {
			min_index = cl;
			mini = distance_point_cc;
		}
	}
	find_vector_output(data, min_index);
	return 0;
}

vector<double> implement_to_OU1_file::find_vector_output(data_info data, int mini_index) {
	vector<double> ou;
	cout << " index : " << mini_index << endl;
	for (int jk = 0; jk != all_clusters[mini_index].clusterinputname.size(); jk++) {
		for (int kj = 0; kj != data.data_name.size(); kj++) {

			if (all_clusters[mini_index].clusterinputname[jk] == data.data_name[kj]) {

				data.reduced_data.push_back(data.dimensionless_data[kj]);
				//cout << data.dimensionless_data[kj] << "\t";
				break;
			}
		}
	}

	for (size_t ti = 0; ti != data.reduced_data.size(); ti++) {
		data.reduced_data[ti] = (data.reduced_data[ti] - all_clusters[mini_index].minimum[ti]) / all_clusters[mini_index].scale[ti];
	}

	
	ou = math.matrix_multiplication(all_clusters[mini_index].weights, data.reduced_data);

	for (size_t tti = 0; tti != ou.size(); tti++) {
		int point = all_clusters[mini_index].scale.size() - ou.size() + tti;
		int point1 = data.nondim_position.at(data.nondim_position.size() - ou.size() + tti);
		if (point1 != -1) {
			
			double multiply_factor = data.original_input.at(point1);
			ou[tti] = (ou[tti] * all_clusters[mini_index].scale[point] + all_clusters[mini_index].minimum[point]) * multiply_factor;
		}
		if (point1 == -1) {
			
			ou[tti] = (ou[tti] * all_clusters[mini_index].scale[point] + all_clusters[mini_index].minimum[point]); 
		}
	}

	
	for (size_t tt = 0; tt != ou.size(); tt++) {
		cout << ou[tt] << "\t";
	}
	cout << "\nnext output" << endl;
	
	return ou;
}

