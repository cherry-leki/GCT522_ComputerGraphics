//FRRCVImport -cln "kokoCtrlList.dat" -ffn "kokoFinalResult.dat"

#include "FRR_CVImport.h"
#include <maya/MPlug.h>
#include <maya/MFnAnimCurve.h>
#include <maya/MTime.h>

const char *importCharCtrlListFlag = "-cln", *importCharCtrlListLongFlag = "-ctrlListFileName";
const char *importFileNameFlag = "-ffn", *importFileNameLongFlag = "-finalFileName";



MSyntax FRRCVIMPORTCmd::newSyntax()
{
	MSyntax syntax;
	syntax.addFlag(importCharCtrlListFlag, importCharCtrlListLongFlag, MSyntax::kString);
	syntax.addFlag(importFileNameFlag, importFileNameLongFlag, MSyntax::kString);
	return syntax;
}

MStatus FRRCVIMPORTCmd::doIt(const MArgList &args)
{
	MString CVImportFileName;
	MString ctrlListFileName;
	int frameNum = 0;
	MArgDatabase argData(syntax(), args);
	if (argData.isFlagSet(importCharCtrlListFlag))
		argData.getFlagArgument(importCharCtrlListFlag, 0, ctrlListFileName);
	if (argData.isFlagSet(importFileNameFlag))
		argData.getFlagArgument(importFileNameFlag, 0, CVImportFileName);

	//open controller list file
	ifstream fin;
	fin.open(ctrlListFileName.asChar());

	//---------------------------------------------------------------TODO---------------------------------------------------------------//
	//	Write your code here! (5~20 lines)																								//
	//	Make controller list from the file(kokoCtrlList.dat) by using MStringArray(SAME code as FRR_CVExport.cpp).						//	
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
	//	Write your code here! (20~45 lines)																								//
	//																																	//
	//	1. Read each line of file and split the values																					//
	//																																	//
	//	2. Iterate the controllers at each frame																						//
	//																																	//
	//	2. Get plugs to access the keyable attribute values of controllers using MPlug(SAME code as the FRR_CVExport.cpp)				//
	//	   (HINT (Attributes list): "translateX","translateY","translateZ","rotateX","rotateY","rotateZ")								//
	//																																	//
	//	3. Set the keyable attribute values of controllers																				//																								//
	//	   (HINT: yourplug.setDouble())																									//
	//																																	//
	//	4. Lastly, set keyframes!																										//
	//----------------------------------------------------------------------------------------------------------------------------------//

	//open the final result file
	fin.open(CVImportFileName.asChar());

	// Read each line of file and split the values
	MStringArray finalResultArr;
	while (!fin.eof()) {
		char temp[10];
		fin >> temp;
	}

	// Iterate the controllers at each frame
	for (int i = 1; i <= ctrlListArr.length(); i++) {

	}
	//

	//close the final result file
	fin.close();


	return redoIt();
}

MStatus FRRCVIMPORTCmd::undoIt()
{
	return dgMod.undoIt();
}

MStatus FRRCVIMPORTCmd::redoIt()
{
	return dgMod.doIt();
}