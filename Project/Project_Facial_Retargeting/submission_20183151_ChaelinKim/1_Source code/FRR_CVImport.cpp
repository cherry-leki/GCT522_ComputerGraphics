//FRRCVImport -cln "kokoCtrlList.dat" -ffn "kokoFinalResult.dat"

#include "FRR_CVImport.h"
#include <maya/MPlug.h>
#include <maya/MFnAnimCurve.h>
#include <maya/MTime.h>
#include <sstream>

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

	// Make the controller list and get each controller from the target controller list file
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

	// Make variables for final result
	MStringArray finalResultArr;
	std::string temp;
	int frameCount = 1;

	// Read each line of control vector list file and split the values
	while (std::getline(fin, temp)) {
		MGlobal::viewFrame(frameCount);
		int tempNum = 0;

		// Split the values in final result file
		std::istringstream iss(temp);
		while (iss) {
			std::string tmp;
			iss >> tmp;
			finalResultArr.append(tmp.c_str());
		}

		// Iterate controllers at each frame
		for (int j = 0; j < ctrlListArr.length(); j++) {
			// Select a blendshape node by name
			MGlobal::selectByName(ctrlListArr[j], MGlobal::kReplaceList);
			MSelectionList selected;
			MGlobal::getSelectionListByName(ctrlListArr[j], selected);

			// Make the object for getting transform attributes
			MObject ctrlNode;
			selected.getDependNode(0, ctrlNode);

			MFnTransform ctrlTransform(ctrlNode);

			// Get plugs to access the keyable attribute values of controllers
			// - Attributes list: "translateX","translateY","translateZ","rotateX","rotateY","rotateZ"
			MPlug trXPlug = ctrlTransform.findPlug("translateX");
			MPlug trYPlug = ctrlTransform.findPlug("translateY");
			MPlug trZPlug = ctrlTransform.findPlug("translateZ");
			MPlug rtXPlug = ctrlTransform.findPlug("rotateX");
			MPlug rtYPlug = ctrlTransform.findPlug("rotateY");
			MPlug rtZPlug = ctrlTransform.findPlug("rotateZ");

			// View the next frame
			MTime frameTime((float)frameCount);

			// Set the keyable attribute values of controllers
			// - Since all joints do not have all attributes (because of DoF), check that the plug is connected
			if (trXPlug.isConnected()) {
				trXPlug.setDouble(finalResultArr[tempNum++].asDouble());
				MGlobal::executeCommand(MString("setKeyframe " + ctrlListArr[j] +".translateX"));
			}
			if (trYPlug.isConnected()) {
				trYPlug.setDouble(finalResultArr[tempNum++].asDouble());
				MGlobal::executeCommand(MString("setKeyframe " + ctrlListArr[j] + ".translateY"));
			}
			if (trZPlug.isConnected()) {
				trZPlug.setDouble(finalResultArr[tempNum++].asDouble());
				MGlobal::executeCommand(MString("setKeyframe " + ctrlListArr[j] + ".translateZ"));
			}
			if (rtXPlug.isConnected()) {
				rtXPlug.setDouble(finalResultArr[tempNum++].asDouble());
				MGlobal::executeCommand(MString("setKeyframe " + ctrlListArr[j] + ".rotateX"));
			}
			if (rtYPlug.isConnected()) {
				rtYPlug.setDouble(finalResultArr[tempNum++].asDouble());
				MGlobal::executeCommand(MString("setKeyframe " + ctrlListArr[j] + ".rotateY"));
;			}
			if (rtZPlug.isConnected()) {
				rtZPlug.setDouble(finalResultArr[tempNum++].asDouble());
				MGlobal::executeCommand(MString("setKeyframe " + ctrlListArr[j] + ".rotateZ"));
			}
		}
		// Free finalResultArr
		finalResultArr.clear();
		frameCount++;	// set the next frame number
	}
	
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