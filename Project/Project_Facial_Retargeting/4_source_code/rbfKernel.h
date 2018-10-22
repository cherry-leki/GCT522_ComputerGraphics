#pragma once
#pragma warning(disable: 4996)
#include <boost/numeric/ublas/matrix.hpp>	
#include <boost/numeric/ublas/vector.hpp>	
#include <boost/numeric/ublas/io.hpp>		
#include "inverseMatrix.h"					
using namespace boost::numeric::ublas;

class rbf
{
public:
	enum BFType				// Type of basis function
	{		
		BF_HARDY,			// Hardy multiquadric function		
	};

public:
	BFType	_basisFunc;	
	double	_lamda;
	int		_numInput;	
	int		_dimInput;	
	int		_dimOutput;	

	vector<vector<double>> _input;  

	matrix<double>	_basisMat;			
	matrix<double>	_inverseBasisMat;	
	matrix<double>	_weightMat;			

	vector<double>	_minDist;			

	
	int		buildDistMatrix(matrix<double> &distMat, const vector<vector<double>> &input);	
	double	basisFunc(int i, double x2);														
	inline	double dist(const vector<double> &a, const vector<double> &b);	
	int		buildBasisMat(const vector<vector<double>> &input);

public:

	rbf():																					// constructor
	  _basisFunc(BF_HARDY), _lamda(.0f), _numInput(0), _dimInput(0), _dimOutput(0),			// initialize
		  _basisMat(0, 0), _weightMat(0, 0), _minDist(0), _inverseBasisMat(0, 0)			// (0, 0) represents (row, column)
	  {
	  }

	  ~rbf()																				// destructor
	  {
		  reset();																			
	  }

	  void reset()																			
	  {
		  _basisFunc = BF_HARDY;
		  _lamda = .0f;
		  _numInput = 0;
		  _dimInput = 0;
		  _dimOutput = 0;
		  _basisMat.resize(0, 0);
		  _weightMat.resize(0, 0);
		  _minDist.resize(0);
		  _inverseBasisMat.resize(0, 0);
	  }

	  
	  void setBasisFunc(BFType bft)	{ _basisFunc = bft; }		
	  BFType getBasisFunc()			{ return _basisFunc; }		
	  void setLamda(double value)		{ _lamda = value; }			
	  double getLamda()				{ return _lamda; }		
	  
	  int Train(const vector<vector<double>> &input, const vector<vector<double>> &output);
	 
	  int Interpolate(const vector<double> &sample, vector<double> &result);
	  int Interpolate(const vector<vector<double>> &sample, vector<vector<double>> &result);
	  int Interpolate(const matrix<double> &sample, matrix<double> &result);
};