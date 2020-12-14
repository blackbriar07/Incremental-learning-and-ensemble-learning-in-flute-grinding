#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#include <time.h>

#include "csvDataFileReading.h"
#include <algorithm>
#include "csvDataFileReading.h"

using namespace std;


class cluster {
public:
	csvdatafilereading csvReading;
	void read_data(string input_file,string output_file, int numofcluster);
};

class Point {

private:
	int pointId, clusterId;
	int dimensions;
	int output_dimensions;
	vector<double> values;
	vector<double> output_values;

public:
	/*
	Point(int id, string line) {
		dimensions = 0;
		pointId = id;
		stringstream is(line);
		double val;
		while (is >> val) {
			values.push_back(val);
			dimensions++;
		}
		clusterId = 0; //Initially not assigned to any cluster
	}
	*/
	Point(int id, vector<double> values1, vector<double> values2) {

		dimensions = values1.size();
		pointId = id;
		values = values1;
		output_values = values2;
		output_dimensions = values2.size();
		clusterId = 0; //Initially not assigned to any cluster
	}


	int getDimensions() {
		return dimensions;
	}

	int getOutputDimensions() {
		return output_dimensions;
	}

	int getCluster() {
		return clusterId;
	}

	int getID() {
		return pointId;
	}

	void setCluster(int val) {
		clusterId = val;
	}

	double getVal(int pos) {
		return values[pos];
	}

	double getOutputVal(int pos) {
		return output_values[pos];
	}
};

class Cluster {

private:
	int clusterId;
	vector<double> centroid;
	vector<Point> points;

public:
	Cluster(int clusterId, Point centroid) {
		this->clusterId = clusterId;
		for (int i = 0; i < centroid.getDimensions(); i++) {
			this->centroid.push_back(centroid.getVal(i));
		}
		this->addPoint(centroid);
	}

	void addPoint(Point p) {
		p.setCluster(this->clusterId);
		points.push_back(p);
	}

	bool removePoint(int pointId) {
		int size = points.size();

		for (int i = 0; i < size; i++)
		{
			if (points[i].getID() == pointId)
			{
				points.erase(points.begin() + i);
				return true;
			}
		}
		return false;
	}

	int getId() {
		return clusterId;
	}

	Point getPoint(int pos) {
		return points[pos];
	}


	int getSize() {
		return points.size();
	}

	double getCentroidByPos(int pos) {
		return centroid[pos];
	}

	void setCentroidByPos(int pos, double val) {
		centroid[pos] = val;
		//this->centroid[pos] = val;

	}
};

class KMeans {
public:
	double silhoutte_value;
	int K, iters, dimensions, total_points,output_dimensions;
	vector<Cluster> clusters;
	//vector<vector<double>> distance_matrix;

	double point_distance(int *K1, int *P1, int *K2, int *P2) {
		double sum = 0;
		for (int k2 = 0; k2 < dimensions; k2++)
		{
			//cout << clusters[0].getCentroidByPos(i) << endl;
			sum += pow(clusters[*K1].getPoint(*P1).getVal(k2) - clusters[*K2].getPoint(*P2).getVal(k2), 2.0);
		}
		sum = sqrt(sum);

		return sum;
	}


	double distance(Point point1, Point point2) {

			double sumdis = 0.0;
			for (int j = 0; j < dimensions; j++)
			{
				sumdis += pow(point2.getVal(j) - point2.getVal(j), 2.0);
			}
			sumdis = sqrt(sumdis);
			return sumdis;
		
	}

	double calculate_ai(int *j1, int *i1) {

		if (clusters[*i1].getSize() == 1) {
			return 0;
		}
		double sum2 = 0.0;
		for (int j2 = 0; j2 < clusters[*i1].getSize(); j2++) {
			bool dec = true;
			if (j2 != *j1) {
				
				/*
				for (int k2 = 0; k2 < dimensions; k2++)
				{
					//cout << clusters[0].getCentroidByPos(i) << endl;
					sum += pow(clusters[*i1].getPoint(j2).getVal(k2) - clusters[*i1].getPoint(*j1).getVal(k2), 2.0);
				}
				//sum = sqrt(sum);
				*/
				double sum = point_distance(i1, &j2, i1,j1);
				sum2 += sum;
			}
		}
		return sum2 / clusters[*i1].getSize()-1;
	}


	double calculate_bi(int *j1, int *i1) {

		//vector<double> b_i;
		double min_avg = 0.0;
		int countf = 0;
		for (int i3 = 0; i3 < K; i3++) {
			double sum2 = 0.0;
			if (i3 != *i1) {
				for (int j3 = 0; j3 < clusters[i3].getSize(); j3++) {
					/*
					double sum = 0.0;
					for (int k3 = 0; k3 < dimensions; k3++) {
						sum += pow(clusters[i3].getPoint(j3).getVal(k3) - clusters[*i1].getPoint(*j1).getVal(k3), 2.0);
					}
					sum = sqrt(sum); // clusters[i3].getSize();
					*/
					double sum = point_distance(&i3, &j3, i1, j1);
					sum2 += sum;
					//b_i.push_back(sum);
				}
				if (countf == 0) {
					//cout << "hello inside" << endl;
					//cout << sum2 << endl;
					//cout << clusters[i3].getSize() << endl;;
					min_avg = sum2 / clusters[i3].getSize();
					countf += 1;
				}
				//cout << "sum " << sum2/ clusters[i3].getSize() << endl;
			}
			
			
			if (min_avg < sum2/clusters[i3].getSize()) {
				min_avg = min_avg;
			}
			else {
				min_avg = sum2 / clusters[i3].getSize();
			}
			//cout << "min_abg " << min_avg << endl;
			
		}
		/*
		double mini = b_i.at(0);
		for (unsigned int k4 = 1; k4 < b_i.size(); k4++) {
			if (mini > b_i.at(k4)) {
				mini = b_i.at(k4);
			}
		}
		*/
		return min_avg;
	}

	double sil_value() {
		vector<double> si;
		double maxi = 0.0;
		double sum3 = 0.0;
		int count = 0;

		for (int i = 0; i < K; i++) {

			for (int j = 0; j < clusters[i].getSize(); j++) {
				//cout << "j" << i << endl;
				double ai = calculate_ai(&j, &i);
				//cout << "ai" << ai << endl;
				double bi = calculate_bi(&j, &i);
				//cout << "bi" << bi << endl;
				if (ai > bi) {
					maxi = ai;
				}
				else {
					maxi = bi;
				}
				double s_i = (bi - ai) / maxi;
				cout << "s_i" << s_i << endl;
				sum3 += s_i;
				count += 1;
			}
		}
		return sum3 / count;

	}


	int getNearestClusterId(Point point) {
		//cout << "helloooooo1" << endl;
		double sum = 0.0, min_dist;
		int NearestClusterId;


		for (int i = 0; i < dimensions; i++)
		{
			//cout << clusters[0].getCentroidByPos(i) << endl;
			sum += pow(clusters[0].getCentroidByPos(i) - point.getVal(i), 2.0);
		}

		min_dist = sqrt(sum);
		NearestClusterId = clusters[0].getId();


		for (int i = 0; i < K; i++)
		{
			double dist;
			sum = 0.0;

			for (int j = 0; j < dimensions; j++)
			{
				sum += pow(clusters[i].getCentroidByPos(j) - point.getVal(j), 2.0);
			}

			dist = sqrt(sum);

			if (dist < min_dist)
			{
				min_dist = dist;
				NearestClusterId = clusters[i].getId();
			}
		}

		return NearestClusterId;
	}

public:

	KMeans(int K, int iterations) {
		this->K = K;
		this->iters = iterations;
	}

	void run(vector<Point>& all_points) {

		total_points = all_points.size();
		cout << "calculating distance matrix" << endl;
		//distance_matrix_computation(all_points);
		cout << "calculating distance matrix ended" << endl;
		
		dimensions = all_points[0].getDimensions();
		output_dimensions = all_points[0].getOutputDimensions();
		
		srand((unsigned int)time(NULL));

		//Initializing Clusters
		vector<int> used_pointIds;

		for (int i = 1; i <= K; i++)
		{
			while (true)
			{
				int index = rand() % total_points;
				cout << "Index :" << index << endl;

				if (find(used_pointIds.begin(), used_pointIds.end(), index) == used_pointIds.end())
				{

					used_pointIds.push_back(index);
					all_points[index].setCluster(i);
					Cluster cluster(i, all_points[index]);
					clusters.push_back(cluster);
					break;
				}
			}
		}

		cout << "Clusters initialized = " << clusters.size() << endl << endl;


		cout << "Running K-Means Clustering.." << endl;

		int iter = 1;
		while (true)
		{
			cout << "Iter - " << iter << "/" << iters << endl;
			bool done = true;

			// Add all points to their nearest cluster
			for (int i = 0; i < total_points; i++)
			{
				int currentClusterId = all_points[i].getCluster();
				int nearestClusterId = getNearestClusterId(all_points[i]);

				if (currentClusterId != nearestClusterId)
				{
					if (currentClusterId != 0) {
						for (int j = 0; j < K; j++) {
							if (clusters[j].getId() == currentClusterId) {
								clusters[j].removePoint(all_points[i].getID());
							}
						}
					}

					for (int j = 0; j < K; j++) {
						if (clusters[j].getId() == nearestClusterId) {
							clusters[j].addPoint(all_points[i]);
						}
					}
					all_points[i].setCluster(nearestClusterId);
					done = false;
				}
			}

			// Recalculating the center of each cluster
			for (int i = 0; i < K; i++)
			{
				int ClusterSize = clusters[i].getSize();

				for (int j = 0; j < dimensions; j++)
				{

					double sum = 0.0;
					if (ClusterSize > 0)
					{

						for (int p = 0; p < ClusterSize; p++) {
							sum += clusters[i].getPoint(p).getVal(j);
						}

						//cout << clusters[i].centroid.size() << endl;

						clusters[i].setCentroidByPos(j, sum / ClusterSize);

					}
				}
			}

			if (done || iter >= iters)
			{
				cout << "Clustering completed in iteration : " << iter << endl << endl;
				break;
			}
			iter++;
		}
		
		//silhoutte_value = sil_value();
		//cout << "The silhoutte value is :" << silhoutte_value << endl;
		/*
		vector<double> si;
		double maxi = 0.0;
		double sum = 0.0;
		double ai = 0.0;
		double bi = 0.0;

		for (int i = 0; i < K; i++) {
			for (int j = 0; j < clusters[i].getSize(); j++) {
				if (clusters[i].getSize() == 1) {
						ai =  0;
					}
				else {
					double sum2 = 0.0;
					vector<double> a_i;
					for (int j2 = 0; j2 < clusters[i].getSize(); j2++) {
						bool dec = true;
						for (int j5 = 0; j5 < dimensions; j5++) {
							if (clusters[i].getPoint[j2].getVal(j5) != clusters[i].getPoint[j].getVal(j5)) {
								dec = false;
								break;
							}
						}
						if (dec == false) {
							double sum = 0.0;
							for (int k2 = 0; k2 < dimensions; k2++)
							{
								//cout << clusters[0].getCentroidByPos(i) << endl;
								sum += pow(clusters[i].getPoint[j2].getVal(k2) - clusters[i].getPoint[j].getVal(k2), 2.0);
							}
							sum = sqrt(sum);
							sum2 += sum;
							a_i.push_back(sum);
						}
					}
					ai = sum2 / a_i.size();
				}

				vector<double> b_i;
				for (int i3 = 0; i3 < K; i3++) {
					if (i3 != i) {

						for (int j3 = 0; j3 < clusters[i3].getSize(); j3++) {
							double sum = 0.0;
							for (int k3 = 0; k3 < dimensions; k3++) {
								sum += pow(clusters[i3].getPoint[j3].getVal(k3) - clusters[i].getPoint[j].getVal(k3), 2.0);
							}
							sum = sqrt(sum) / clusters[i3].getSize();
							b_i.push_back(sum);
						}

					}
				}
				double mini = b_i.at(0);
				for (unsigned int k4 = 1; k4 < b_i.size(); k4++) {
					if (mini > b_i.at(k4)) {
						mini = b_i.at(k4);
					}
				}
				bi =  mini;

				if (ai > bi) {
					maxi = ai;
				}
				else {
					maxi = bi;
				}
				double s_i = (bi - ai) / maxi;
				sum += s_i;
				si.push_back(s_i);
			}
		}
		silhoutte_value =  sum / si.size();

		*/


	}

};