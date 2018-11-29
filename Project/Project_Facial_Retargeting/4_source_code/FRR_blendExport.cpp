//FRRBlendExport -bn "targetBlend" -bfn "humanSourceAnimation.dat" -f 360 
//FRRBlendExport -bn "targetBlend" -bfn "humanROE.dat" -f 36

#include "FRR_blendExport.h"

const char *blendNodeNameFlag = "-bn", *blendNodeNameLongFlag = "-blendNodeName";
const char *blendExportFileNameFlag = "-bfn", *blendExportFileNameLongFlag = "-blendFileName";
const char *frameFlag = "-f", *frameLongFlag = "-frame";


MSyntax FRRBLENDEXPORTCmd::newSyntax()
{
	MSyntax syntax;
	syntax.addFlag(blendNodeNameFlag, blendNodeNameLongFlag, MSyntax::kString);
	syntax.addFlag(blendExportFileNameFlag, blendExportFileNameLongFlag, MSyntax::kString);
	syntax.addFlag(frameFlag, frameLongFlag, MSyntax::kDouble);

	return syntax;
}

MStatus FRRBLENDEXPORTCmd::doIt(const MArgList &args)
{
	MString blendNodeName;
	MString blendExportFileName;
	int frameNum = 0;

	MArgDatabase argData(syntax(), args);
	if (argData.isFlagSet(blendNodeNameFlag))
		argData.getFlagArgument(blendNodeNameFlag, 0, blendNodeName);
	if (argData.isFlagSet(blendExportFileNameFlag))
		argData.getFlagArgument(blendExportFileNameFlag, 0, blendExportFileName);
	if (argData.isFlagSet(frameFlag))
		argData.getFlagArgument(frameFlag, 0, frameNum);

	//open the export file
	ofstream fout;
	fout.open(blendExportFileName.asChar());

	//---------------------------------------------------------------TODO---------------------------------------------------------------//
	//	Write your code here! (20~30 lines)																								//
	//	1. select blendshape node by name																								//
	//	2. get blendshape weights at each frames by using "MFnBlendShapeDeformer" 														//
	//	3. write down on the file																										//
	//																																	//
	//	form of the file is like this. (each row means one frame. each column means one blendshape weight)								//
	//																																	//
	//	 (weight1) (weight2) (weight3) ... (weightN)																					//
	//	 (weight1) (weight2) (weight3) ... (weightN)																					//
	//	 ...																															//
	//																																	//	 
	//	Given example, "humanSourceAnimation.mb" should generate 360x35 matrix, "humanROE.mb" should generate 36x35 matrix				//
	//----------------------------------------------------------------------------------------------------------------------------------//

	// Select blendshape node by name
	MGlobal::selectByName(blendNodeName, MGlobal::kReplaceList);
	MSelectionList selected;
	MGlobal::getSelectionListByName(blendNodeName, selected);

	MObject blendNode;
	selected.getDependNode(0, blendNode);
	
	// Get blendshape weights at each frames
	for (int i = 1; i <= frameNum; i++) {
		MTime frameTime((float)i);
		MGlobal::viewFrame(frameTime);
		
		MFnBlendShapeDeformer bnDeformer(blendNode);
		int bnNumWeights = bnDeformer.numWeights();

		// Write down on the file
		for (int j = 0; j < bnNumWeights; j++) {
			fout << bnDeformer.weight(j) <<" ";
		}
		fout << endl;
	}

	//close the export file
	fout.close();

	return redoIt();
}

MStatus FRRBLENDEXPORTCmd::undoIt()
{
	return dgMod.undoIt();
}

MStatus FRRBLENDEXPORTCmd::redoIt()
{
	return dgMod.doIt();
}

