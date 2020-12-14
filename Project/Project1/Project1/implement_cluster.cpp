#include<iostream>
#include<vector>
#include<string>
#include "Implement_OU1_file.h"

cluster_info::cluster_info(int id, string cluster_file, string trained_cluster_file) {
	//cout << "hey i am in the constructor" << endl;
	ID = id;
	cluster_location = cluster_file;
	cluster_trained_location = trained_cluster_file;
	vector<string> datanames{ "INPUT","OUTPUT","HIDDEN","Input","Centroid","Radius" };
	read_file_lines(&cluster_file, &datanames);
	datanames.clear();
	//datanames.push_back("Neuron");
	datanames.push_back("Scale");
	datanames.push_back("Minimum");
	read_file_lines(&trained_cluster_file, &datanames);
}

void cluster_info::read_file_lines(string *pathname,vector<string> *datanames) {
	
	//cout << "hey  i am in the readfile" << endl;
	ifstream file(*pathname);
	string str;
	vector<string> line;
	vector<string> weights_line;
	while (getline(file, str)) {
		
		for (int sizearr = 0; sizearr != datanames->size(); sizearr++) {
			
			if (find_string(str, datanames->at(sizearr))) {
				line.push_back(str);
			}
		}
		if (find_string(str, "Neuron")) {
			weights_line.push_back(str);
		}
		
	}
	file.close();

	split_line(&line);
	
	if (*pathname == cluster_trained_location) {
		extract_weights(&weights_line);
	}

}

void cluster_info::split_line(vector<string> *line) {
	
	vector<vector<string>> split_words;
	
	string delm = ",";

	for (unsigned i = 0; i < line->size(); i++) {

		vector<string> elems;
		stringstream ss(line->at(i));
		string item;
		while (getline(ss, item, ',')) {

			
			elems.push_back(item);
		}
		extract_info(&elems);
		
	}
}



void cluster_info::extract_info(vector<string> *split_words) {
	

		if (split_words->size() != 0) {
			
			if (check_tab_string(split_words->at(0)) == "INPUT") {
				Input_value = stoi(check_tab_string(split_words->at(1)));	
			}
			if (check_tab_string(split_words->at(0)) == "OUTPUT") {
				Output_value = stoi(check_tab_string(split_words->at(1)));
			}
			if (find_string(check_tab_string(split_words->at(0)),"HIDDEN")) {
				
				dim_hidden_layers.push_back( stoi(check_tab_string(split_words->at(1))));
				
			}
			if (find_string(check_tab_string(split_words->at(0)), "Input")) {
				
				clusterinputname.push_back(check_tab_string(split_words->at(2)));

			}
			if (check_tab_string(split_words->at(0)) == "Centroid") {
				for (size_t cen = 1; cen != split_words->size(); cen++) {
					centroid.push_back(stod(split_words->at(cen)));
				}
			}
			if (check_tab_string(split_words->at(0)) == "Radius") {
				radius = stod(split_words->at(1));
			}

			if (check_tab_string(split_words->at(0)) == "Scale") {
				for (size_t cen = 1; cen != split_words->size(); cen++) {
					scale.push_back(stod(split_words->at(cen)));
				}
			}
			if (check_tab_string(split_words->at(0)) == "Minimum") {
				for (size_t cen = 1; cen != split_words->size(); cen++) {
					minimum.push_back(stod(split_words->at(cen)));
				}
			}

				
		}
	
}

void cluster_info::extract_weights(vector<string> *line) {
	
	cout << "extracting weights" << endl;
	layer_number.push_back(Input_value);
	for (size_t hiddl = 0; hiddl != dim_hidden_layers.size(); hiddl++) {
		layer_number.push_back(dim_hidden_layers.at(hiddl));
	}
	layer_number.push_back(Output_value);

	vector<vector<string>> weights_unprocessed;
	
	string delm = ",";

	for (unsigned i = 0; i < line->size(); i++) {

		vector<string> elems;
		stringstream ss(line->at(i));
		string item;
		while (getline(ss, item, ',')) {

			elems.push_back(item);
		}
		elems.erase(elems.begin());
		
		weights_unprocessed.push_back(elems);
		
	}
	
	int start = 0;
	
	for (size_t i1 = 0; i1 != layer_number.size() - 1; i1++) {
		int j1 = start;
		int j2 = start + layer_number.at(i1);
		vector<vector<double>> w1;
		for (int j = j1; j < j2; j++) {
			vector<double> weight;
			for (int k = 0; k < layer_number.at(i1 + 1); k++) {
				weight.push_back(stod(check_tab_string(weights_unprocessed.at(j).at(k))));
			}
			w1.push_back(weight);
		}
		weights.push_back(w1);
		start = start + layer_number.at(i1);
	}
	cout << "done with extracting weights" << endl;


}

string cluster_info::check_tab_string(string word) {

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

bool  cluster_info::find_string(string main_word, string part_word) {
	
	size_t found = main_word.find(part_word);
	if (found != string::npos) {
		
		return true;
	}

	return false;
}