//FRRTraining -bfn "humanROE.dat" -cfn "kokoROE.dat" -sfn "humanSourceAnimation.dat" -ffn "kokoFinalResult.dat"

#include "FRR_Training.h"

const char *blendFileFlag = "-bfn", *blendFileLongFlag = "-blendFileName";
const char *cvFileFlag = "-cfn", *cvFileLongFlag = "-cvFileName";
const char *sourceFileFlag = "-sfn", *sourceFileLongFlag = "-sourceFileName";
const char *finalFileFlag = "-ffn", *finalFileLongFlag = "-finalFileName";

MSyntax FRRTRAININGCmd::newSyntax()
{
	MSyntax syntax;
	syntax.addFlag( blendFileFlag, blendFileLongFlag, MSyntax::kString);		
	syntax.addFlag( cvFileFlag, cvFileLongFlag, MSyntax::kString);
	syntax.addFlag( sourceFileFlag, sourceFileLongFlag, MSyntax::kString);
	syntax.addFlag( finalFileFlag, finalFileLongFlag, MSyntax::kString);
	return syntax;
}

MStatus FRRTRAININGCmd::doIt ( const MArgList &args )
{ 
	MString blendFile;
	MString CVFile;
	MString sourceFile;
	MString finalFile;

	MArgDatabase argData(syntax(), args);
	if(argData.isFlagSet(blendFileFlag))
		argData.getFlagArgument(blendFileFlag, 0, blendFile);
	if(argData.isFlagSet(cvFileFlag))
		argData.getFlagArgument(cvFileFlag, 0, CVFile);
	if(argData.isFlagSet(sourceFileFlag))
		argData.getFlagArgument(sourceFileFlag, 0, sourceFile);
	if(argData.isFlagSet(finalFileFlag))
		argData.getFlagArgument(finalFileFlag, 0, finalFile);

	unsigned int humanFaceDim;
	unsigned int cartoonFaceDim;
	unsigned int numDataPair;
	unsigned int numSamplePair;	//numSamplePair -> the frame number of a new input animation
	const char* exportFile = finalFile.asChar();


	//Initialize the object of RBF class
	//Set basis function as hardy multiquadric function
	rbf rbfn;
	rbfn.setBasisFunc( rbf::BF_HARDY );
	rbfn.setLamda(0.1);


	//Import training sample data matrix from input files
	std::vector<std::vector<double>> humanFaceVec = importData(blendFile);
	std::vector<std::vector<double>> cartoonFaceVec = importData(CVFile);


	//Initialize the dimension of the source&target data and the number of data pair
	humanFaceDim = humanFaceVec[0].size();
	cartoonFaceDim = cartoonFaceVec[0].size();
	if (humanFaceVec.size() != cartoonFaceVec.size()) {
		MStatus stat;
		stat.perror("Data Pair Size is different!");
		return stat;
	}
	numDataPair = humanFaceVec.size();


	//Reshape training sample data matrix (for using BOOST)
	//humanFaceVec -> input
	//cartoonFaceVec -> output
	vector<vector<double>> input;
	vector<vector<double>> output;
	input.resize(numDataPair);
	output.resize(numDataPair);

	for(unsigned int i=0 ; i<numDataPair ; i++)
	{
		vector<double> tempVec;
		tempVec.resize(humanFaceDim);
		for(unsigned int j=0 ; j<humanFaceDim ; j++)
		{
			tempVec(j) = humanFaceVec[i][j];
		}

		input(i) = tempVec;
		tempVec.clear();
		tempVec.resize(cartoonFaceDim);
		for(unsigned int k=0 ; k<cartoonFaceDim ; k++)
		{
			tempVec(k) = cartoonFaceVec[i][k];
		}		
		output(i) = tempVec;
		tempVec.clear();
	}	

	//free
	humanFaceVec.clear();
	cartoonFaceVec.clear();


	//Train RBF network from the source and target ROE data
	rbfn.Train(input, output);

	//Import source animation data matrix from file
	std::vector<std::vector<double>> WVec = importData(sourceFile);

	numSamplePair = WVec.size();
	vector<vector<double>> result(numSamplePair);

	//---------------------------------------------------------------TODO---------------------------------------------------------------//
	//	write your code here! (10~15 lines)
	//	Run RBF interpolation by using .interpolate(sourceInput, interpolateResult) function of rbf class
	//----------------------------------------------------------------------------------------------------------------------------------//

	

	//export the final result matrix to file
	exportData(result, finalFile);
	
	return redoIt();
}

MStatus FRRTRAININGCmd::undoIt()
{
	return dgMod.undoIt();
}

MStatus FRRTRAININGCmd::redoIt()
{
	return dgMod.doIt();
}



//other functions

void FRRTRAININGCmd::split(std::string& text, std::string& separators, std::list<std::string>& words)
{
	int n = text.length();
	int start, stop;

	start = text.find_first_not_of(separators);
	while ((start >= 0) && (start < n)) {
		stop = text.find_first_of(separators, start);
		if ((stop < 0) || (stop > n)) stop = n;
		words.push_back(text.substr(start, stop - start));
		start = text.find_first_not_of(separators, stop + 1);
	}
}

std::vector<std::vector<double>> FRRTRAININGCmd::importData(MString& fileName)
{
	std::vector<std::vector<double>> result;
	std::ifstream fin;
	fin.open(fileName.asChar());
	std::string inputLine;
	std::string empty = " ";
	while (!fin.eof())
	{
		std::list<std::string> inputLineList;
		std::vector<double> temp;
		getline(fin, inputLine);
		split(inputLine, empty, inputLineList);
		while (!inputLineList.empty())
		{
			std::istringstream stm;
			stm.str(inputLineList.front());
			double d;
			stm >> d;
			temp.push_back(d);
			inputLineList.pop_front();
		}
		if (temp.size() > 0) { result.push_back(temp); }
	}

	fin.close();
	fin.clear();
	return result;
}

void FRRTRAININGCmd::exportData(vector<vector<double>> result, MString& fileName)
{
	std::ofstream fout;
	fout.open(fileName.asChar());
	unsigned int numDimPair = result.size();
	for (unsigned int i = 0; i<numDimPair; i++)
	{
		vector<double> output = result(i);
		unsigned int numOutputElem = output.size();
		for (unsigned int j = 0; j<numOutputElem; j++)
		{
			fout << output(j) << " ";
		}
		fout << std::endl;
	}
	fout.close();
}