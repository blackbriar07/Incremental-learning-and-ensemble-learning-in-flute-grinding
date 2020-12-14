// Project1.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>
#include "user_data.h"
#include "Reading_dataFile.h"
#include "trainingset.h"
#include "non_dimensionalize.h"
#include "dimensional_reduction.h"
#include "clustering.h"
#include "Implement_OU1_file.h"
#include<time.h>

using namespace std;

int main()
{
	time_t begin, end;
	time(&begin);

	cout << "The program is starting" <<endl;
	string filename = "D:\\VC6_c++_practice\\Project\\Project1\\user_defined_data.csv";
	
	user_CSVReader user_reader; 
	user_reader.fileName = filename;
	
	user_reader.getData();

	cout << "Reading USER file finished" << endl;
	//cout << reader.location_file.at(0);

	reading_datafile read_data_object;
	
	read_data_object.cluster_number = user_reader.cluster_info;
	read_data_object.input_name = user_reader.input_data_name;
	read_data_object.output_name = user_reader.output_data_name;
	read_data_object.loc_file = user_reader.location_file;
	read_data_object.decision = user_reader.decision;

	vector<trainingSet> m_trainingset;

	if (read_data_object.decision.at(0) == "yes") {
		read_data_object.find_all_folder_paths(read_data_object.loc_file.at(0));
	}

	/*
	vector<trainingSet>::iterator it;
	for (it = read_data_object.m_trainingset.begin(); it != read_data_object.m_trainingset.end(); ++it) {
		cout << "hello i m here";
		it->printinput();
		cout << endl;
	}
	*/
	
	non_dimensionalization non_dimensionalize;
	non_dimensionalize.user_input_name = user_reader.input_data_name;
	non_dimensionalize.user_output_name = user_reader.output_data_name;
	non_dimensionalize.non_dim = user_reader.non_dim_name;
	//vector<trainingSet> m_trainingset;
	string location_raw_data_csv = user_reader.location_file.at(1) + "\\" + user_reader.location_file.at(2);
	string non_dim_outputcsv = user_reader.location_file.at(1) + "\\" + user_reader.location_file.at(3);
	if(read_data_object.decision.at(1) == "yes") {
		//non_dimensionalization non_dimensionalize(read_data_object.m_trainingset);
		
		non_dimensionalize.read_rawdata_file(location_raw_data_csv, non_dim_outputcsv);
		
	}
	

	dimension_reduce dr;
	//string location_nondim_data_csv = user_reader.location_file.at(1) + "\\" + user_reader.location_file.at(3);
	string dimreduce_outputcsv = user_reader.location_file.at(1) + "\\" + user_reader.location_file.at(4);
	if (read_data_object.decision.at(2) == "yes") {
		//non_dimensionalization non_dimensionalize(read_data_object.m_trainingset);

		dr.dimension_reduce_operation(non_dim_outputcsv, dimreduce_outputcsv);

	}

	cluster clu;
	string cluster_outputcsv = user_reader.location_file.at(1) ;
	if (read_data_object.decision.at(3) == "yes") {
		//non_dimensionalization non_dimensionalize(read_data_object.m_trainingset);

		clu.read_data(dimreduce_outputcsv, cluster_outputcsv, user_reader.cluster_info);

	}

	if (read_data_object.decision.at(5) == "yes") {
		implement_to_OU1_file implement_file;
		implement_file.cluster_folder_location = user_reader.location_file.at(5);
		implement_file.test_OU1_file_location = user_reader.location_file.at(7);
		implement_file.input_data_name = user_reader.input_data_name;
		implement_file.output_data_name = user_reader.output_data_name;
		implement_file.non_dim_name = user_reader.non_dim_name;
		implement_file.extract_cluster_info();
		//cluster_info clusterop(user_reader.location_file.at(5));

	}



	time(&end);
	time_t elapsed = end - begin;

	cout <<"\n"<< "Time taken to finish:  " << elapsed <<" seconds"<< endl;


}


