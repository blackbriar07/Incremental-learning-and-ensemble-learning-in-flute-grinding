#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#include <time.h>

#include "csvDataFileReading.h"
#include <algorithm>
#include "clustering.h"

void cluster::read_data(string input_file, string output_file, int numofcluster) {

	int K = numofcluster;
	cout << "Reading dimension reduction data file csv format" << endl;
	csvReading.getlinedatafile(input_file);

	int pointId = 1;
	vector<Point> all_points;

	for (unsigned int iterator = 0; iterator < csvReading.InputData.size(); iterator++) {
		Point point(pointId, csvReading.InputData.at(iterator), csvReading.OutputData.at(iterator));
		all_points.push_back(point);
		pointId++;
	}

	cout << "\nData fetched successfully!" << endl << endl;

	//Return if number of clusters > number of points

	//if (all_points.size() < K) {
	//	cout << "Error: Number of clusters greater than number of points." << endl;
	//	return 1;
	//}



	//Running K-Means Clustering
	int iters = 300;

	KMeans kmeans(K, iters);
	kmeans.dimensions = csvReading.InputData.at(0).size();
	kmeans.run(all_points);

	for (int i = 0; i < K; i++) {
		ofstream outfile;
		string cluster_location = output_file + "\\"+ "cluster" + to_string(i + 1) + ".csv";
		outfile.open(cluster_location);
		if (outfile.is_open()) {
			outfile << "CLUSTER" << "," << to_string(i+1) << endl;
			outfile << "INPUT" << ","<<"6"<< endl;
			outfile << "HIDDEN1" << "," << "5" << endl;
			outfile << "OUTPUT" << "," << "4" << endl;
			outfile << "LearningRate" << "," << "0.25" << endl;
			outfile << "Convergence" << "," << "0.01" << endl;
			outfile << "MaxTraining" << "," << "10000000" << endl;
			outfile << "DataDescriptionBegin" << endl;
			for (unsigned int i2 = 0; i2 < csvReading.data_parameters_input.size(); i2++) {
				outfile << csvReading.data_parameters_input.at(i2).at(0) << "," << csvReading.data_parameters_input.at(i2).at(1) << endl;
			}
			for (unsigned int i2 = 0; i2 < csvReading.data_parameters_output.size(); i2++) {
				outfile << csvReading.data_parameters_output.at(i2).at(0) << "," << csvReading.data_parameters_output.at(i2).at(1) << endl;
			}
			outfile << "DataDescriptionEnd" << endl;
			outfile << "TrainingSetBegin" <<",";
			for (unsigned int i2 = 0; i2 < csvReading.data_parameters_input.size(); i2++) {
				outfile << csvReading.data_parameters_input.at(i2).at(0) << "," ;
			}
			for (unsigned int i2 = 0; i2 < csvReading.data_parameters_output.size(); i2++) {
				outfile << csvReading.data_parameters_output.at(i2).at(0) << "," ;
			}
			outfile << endl;
			for (int j = 0; j < kmeans.clusters[i].getSize(); j++) {
				outfile << "TD" + to_string(j) << ",";
				for (int k = 0; k < kmeans.dimensions; k++) {
					outfile << kmeans.clusters[i].getPoint(j).getVal(k) << ",";
				}
				for (int k = 0; k < kmeans.output_dimensions; k++) {
					outfile << kmeans.clusters[i].getPoint(j).getOutputVal(k) << ",";
				}
				outfile << endl;
			}
			outfile << "TrainingSetEnd" << endl;
			outfile << "Centroid" << ",";
			for (int k = 0; k < kmeans.dimensions; k++) {
				//outfile << clusters[i].getPoint(j).getVal(k) << ",";
				//cout << clusters[i].getCentroidByPos(j) << " ";     //Output to console
				outfile << kmeans.clusters[i].getCentroidByPos(k) << ",";  //Output to file
			}
			cout << "Cluster " << i << "   writing to CSV completed" << endl;
		}

	}
}