#include "rbfKernel.h"


// This function construct distance matrix (distMat) from sample data(input),
// and find minimum distances of each samples and save it to minimum distance vector(_minDist)
int	rbf::buildDistMatrix(matrix<double> &distMat, const vector<vector<double>> &input)
{	

	//---------------------------------------------------------------TODO---------------------------------------------------------------------------//
	//	Write your code here! (less than 10 lines)
	//	Compute distance from one point(source expression vector) to other points of sample data by using dist() funciton, and save it to distMat
	//----------------------------------------------------------------------------------------------------------------------------------------------//

	_numInput = input.size();
	for (int i = 0; i < _numInput; i++) {
		vector<double> s = input[i];
		for (int j = 0; j < _numInput; j++) {
			vector<double> t = input[j];
			distMat(i, j) = dist(s, t);
		}
	}

	// Calculate minimum distance for hardy-multiquadric function
	double dmin;
	for (int i = 0; i<_numInput; i++)
	{
		dmin = FLT_MAX;
		for (int j = 0; j<_numInput; j++)
		{
			if (distMat(i, j) < dmin && i != j) dmin = distMat(i, j);
		}
		_minDist(i) = dmin;
	}

	return 0;
}

// basis function
double rbf::basisFunc(int i, double x2)
{
	if (_basisFunc == BF_HARDY) // Hardy 
	{
		return sqrt(x2 + _minDist(i));
	}
	else return 0.0f;
}

// This function calculates distance from vector a to b
inline double rbf::dist(const vector<double> &a, const vector<double> &b)
{
	double d1, d2 = .0f;
	size_t dim = a.size();
	for (size_t i = 0; i < dim; i++)
	{
		d1 = a(i) - b(i);
		d2 += d1 * d1;
	}
	return d2; // returns the square of distance
}


// This function builds basis matrix and solve it.
//   - calculate distance matrix
//   - calculate basis matrix by using basis function
//   - calculate inverse matrix by solving basis matrix
int	rbf::buildBasisMat(const vector<vector<double>> &input)
{
	_numInput = input.size(); // numInput is the number of input data
	if (_numInput <= 0) return -1;
	_dimInput = input(0).size(); // dimInput is the dimension of input data

	matrix<double> distMat(_numInput, _numInput);					
	_minDist.resize(_numInput);										 

	buildDistMatrix(distMat, input);								


	_basisMat.resize(_numInput, _numInput);							 
	_inverseBasisMat.resize(_numInput, _numInput);					 


	for (int i = 0; i<_numInput; i++)
	{
		for (int j = 0; j<_numInput; j++)							 
		{															
			_basisMat(i, j) = basisFunc(j, distMat(i, j));			
			if (i == j) _basisMat(i, j) += _lamda;					
		}
	}

	if (!InvertMatrix(_basisMat, _inverseBasisMat)) return -1;	


	return 0;
}


// This function trains the Radial Basis Function Network. (Get _weightMat (M_RBF in paper) from input and output)
int rbf::Train(const vector<vector<double>> &input, const vector<vector<double>> &output)
{
	if (output.size() == 0) return -1;

	//build basis matrix
	_dimOutput = output(0).size();
	_input = input;


	//---------------------------------------------------------------TODO---------------------------------------------------------------//
	//	Write your code here! (less than 10 lines)
	//	1. build the basis matrix from input data by using buildBasisMat() function.
	//	2. calculate the matrix product of _inverseBasisMatrix and output data, and save it to _weightMat.
	//		you can use prod() function of BOOST.
	//		for this, you should change data type of output data form vector<vector<double>> to matrix<double>.
	//----------------------------------------------------------------------------------------------------------------------------------//













	return 0;
}




// Interpolate function for new input sequence

int rbf::Interpolate(const vector<double> &sample, vector<double> &result) // Input and output are vector
{
	int j;

	matrix<double> sampleMat(1, _numInput);
	matrix<double> resultMat(1, _dimOutput);

	for (j = 0; j<_numInput; j++)
	{
		sampleMat(0, j) = basisFunc(j, dist(sample, _input(j)));
	}
	resultMat = prod(sampleMat, _weightMat);

	result.resize(_dimOutput);
	for (j = 0; j< _dimOutput; j++)
	{
		result(j) = resultMat(0, j);
	}

	return 0;
}

int rbf::Interpolate(const vector<vector<double>> &sample, vector<vector<double>> &result) // Input and output are vector of vector
{
	int i, j;
	int numSample = sample.size();
	vector<double> temp(_dimOutput);

	matrix<double> sampleMat(numSample, _numInput);
	matrix<double> resultMat(numSample, _dimOutput);

	for (i = 0; i<numSample; i++)
	{
		for (j = 0; j<_numInput; j++)
		{
			sampleMat(i, j) = basisFunc(j, dist(sample(i), _input(j)));
		}
	}

	resultMat = prod(sampleMat, _weightMat);

	result.resize(numSample);

	for (i = 0; i<numSample; i++)
	{
		for (j = 0; j<_dimOutput; j++)
		{
			temp(j) = resultMat(i, j);
		}
		result(i) = temp;
	}
	return 0;
}

int rbf::Interpolate(const matrix<double> &sample, matrix<double> &result)	// Input and output are matrix
{
	int numSample = sample.size1();
	result.resize(numSample, _dimOutput);

	result = prod(sample, _weightMat);
	return 0;
}