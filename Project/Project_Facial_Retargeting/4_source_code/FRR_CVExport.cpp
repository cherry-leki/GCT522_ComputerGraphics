//FRRCVExport -cln "kokoCtrlList.dat" -cfn "kokoROE.dat" -f 36

#include "FRR_CVExport.h"
#include <maya/MPlug.h>

const char *ctrlFileNameFlag = "-cln", *ctrlFileNameLongFlag = "-ctrlListFileName";
const char *CVExportFileNameFlag = "-cfn", *CVExportFileNameLongFlag = "-cvFileName";
const char *frameNumFlag = "-f", *frameNumLongFlag = "-frame";

MSyntax FRRCVEXPORTCmd::newSyntax()
{
	MSyntax syntax;
	syntax.addFlag(ctrlFileNameFlag, ctrlFileNameLongFlag, MSyntax::kString);
	syntax.addFlag(CVExportFileNameFlag, CVExportFileNameLongFlag, MSyntax::kString);
	syntax.addFlag(frameNumFlag, frameNumLongFlag, MSyntax::kDouble);
	return syntax;
}

MStatus FRRCVEXPORTCmd::doIt(const MArgList &args)
{
	MString ctrlFileName;
	MString CVExportFileName;
	int frameNum = 0;
	MArgDatabase argData(syntax(), args);
	if (argData.isFlagSet(ctrlFileNameFlag))
		argData.getFlagArgument(ctrlFileNameFlag, 0, ctrlFileName);
	if (argData.isFlagSet(CVExportFileNameFlag))
		argData.getFlagArgument(CVExportFileNameFlag, 0, CVExportFileName);
	if (argData.isFlagSet(frameNumFlag))
		argData.getFlagArgument(frameNumFlag, 0, frameNum);

	//open controller list file
	ifstream fin;
	fin.open(ctrlFileName.asChar());

	//---------------------------------------------------------------TODO---------------------------------------------------------------//
	//	Write your code here! (5~20 lines)																								//
	//	Make controller list from the file(kokoCtrlList.dat) by using MStringArray.														//
	//----------------------------------------------------------------------------------------------------------------------------------//

	MStringArray ctrlListArr;
	while (!fin.eof()) {
		char temp[100];
		fin >> temp;
		ctrlListArr.append(temp);
	}

	//close controller list file
	fin.close(); 
	

	//---------------------------------------------------------------TODO---------------------------------------------------------------//
	//	Write your code here! (20~40 lines)																								//
	//																																	//
	//	1. Iterate the controllers at each frame																						//
	//																																	//
	//	2. Get plugs to access the keyable attribute values of controllers using MPlug													//
	//	   (HINT (Attributes list): "translateX","translateY","translateZ","rotateX","rotateY","rotateZ")								//
	//																																	//
	//	3. Write down the value on the file																								//
	//	   (HINT: yourplug.asDouble())																									//
	//																																	//
	//	   The form of the file is as follows(each row means one frame and each column means one attribute value).						//
	//	   (value1) (value2) (value3) ... (valueN)																						//
	//	   (value1) (value2) (value3) ... (valueN)																						//
	//	   ...																															//
	//	   Given example, "kokoCROE.mb" should generate 36x201 matrix	
	//
	//----------------------------------------------------------------------------------------------------------------------------------//
	//	HINT Functions:  MGlobal::selectByName(your controller), MFnTransform.findPlug(attributes..)
	//----------------------------------------------------------------------------------------------------------------------------------//

	//open the export file
	ofstream fout;
	fout.open(CVExportFileName.asChar());
			
	// Iterate the controllers at each frame
	for (int i = 1; i <= frameNum; i++) {
		MGlobal::viewFrame(i);

		for (int j = 0; j < ctrlListArr.length(); j++) {
			MGlobal::selectByName(ctrlListArr[j], MGlobal::kReplaceList);
			MSelectionList selected;
			MGlobal::getSelectionListByName(ctrlListArr[j], selected);

			MObject ctrlNode;
			selected.getDependNode(0, ctrlNode);
			
			MFnTransform ctrlTransform(ctrlNode);

			MPlug trXPlug = ctrlTransform.findPlug("translateX");
			MPlug trYPlug = ctrlTransform.findPlug("translateY");
			MPlug trZPlug = ctrlTransform.findPlug("translateZ");
			MPlug rtXPlug = ctrlTransform.findPlug("rotateX");
			MPlug rtYPlug = ctrlTransform.findPlug("rotateY");
			MPlug rtZPlug = ctrlTransform.findPlug("rotateZ");

			if (trXPlug.isConnected())	fout << trXPlug.asDouble() << " ";
			if (trYPlug.isConnected())	fout << trYPlug.asDouble() << " ";
			if (trZPlug.isConnected())	fout << trZPlug.asDouble() << " ";
			if (rtXPlug.isConnected())	fout << rtXPlug.asDouble() << " ";
			if (rtYPlug.isConnected())	fout << rtYPlug.asDouble() << " ";
			if (rtZPlug.isConnected())	fout << rtZPlug.asDouble() << " ";
		}
		fout << endl;
	}
	

	//close the export file
	fout.close();
	
	return redoIt();
}

MStatus FRRCVEXPORTCmd::undoIt()
{
	return dgMod.undoIt();
}

MStatus FRRCVEXPORTCmd::redoIt()
{
	return dgMod.doIt();
}

