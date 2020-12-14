#include<iostream>
#include<vector>
#include<string>
#include<cmath>
#include "Implement_OU1_file.h"

double mathematics::squared_distance(vector<double> v1, vector<double> v2) {

	double sum = 0.0;
	if (v1.size() != v2.size()) {
		cout << "dimensions of the vectors are not same" << endl;
		return -1;
	}
	if (v1.size() == v2.size()) {
		
		for (size_t vv = 0; vv != v1.size(); vv++) {
			sum += pow((v1.at(vv) - v2.at(vv)),2) ;
		}
		sum = sqrt(sum);
		
	}
	return sum;
}


vector<double> mathematics::matrix_multiplication(vector<vector<vector<double>>> weights, vector<double> layer_output) {
	vector<double> layou = layer_output;

	//for (size_t len_result = 0; len_result != layou.size(); len_result++) {
		//	cout << layou[len_result] << "\t";
		//}
		//cout << endl;

	for (size_t size1 = 0; size1 != weights.size(); size1++) {

		

		layou = multiply_layer(weights[size1], layou);
		layou = sigmoid_function(layou);
	}
	
	return layou;
}


vector<double> mathematics::multiply_layer(vector<vector<double>> layerweight, vector<double> layerou) {
	vector<double> output;

	int size2 = layerweight.size(); // Row size
	//cout << "size2 : " << size2 << endl;
	int size3 = layerweight[0].size(); // Column size
	//cout << "size3 : " << size3 << endl;
	int size4 = layerou.size(); 
	//cout << "size4 : " << size4 << endl;
	
	
	if (size2 != size4)
		cout << "dimensions not satisfied" << endl;
	if (size2 == size4) {

		for (int i = 0; i < 1; i++) {
			for (int j = 0; j < size3; j++) {
				double sum = 0;
				for (int k = 0; k < size4; k++) {
					sum += layerou[k] * layerweight[k][j];
					//output.push_back(layerou)
				}
				output.push_back(sum);
			}
		}



	}
	return output;

}

vector<double> mathematics::sigmoid_function(vector<double> result) {

	for (size_t len_result = 0; len_result != result.size(); len_result++) {
		if (result[len_result] < 0) {
			result[len_result] = 1 - (1 / (1 + exp(result[len_result])));
		}
		else {
			result[len_result] =  (1 / (1 + exp(-result[len_result])));
		}
	}

	


	return result;

}