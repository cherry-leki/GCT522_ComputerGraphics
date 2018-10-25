#include "blendshapeCmd.h"
#include "blendshapeNode.h"
#include <maya/MSelectionList.h>
#include <maya/MGlobal.h>
#include <maya/MDagPath.h>
#include <maya/MFnTransform.h>
#include <maya/MItSelectionList.h>
#include <maya/MPlug.h>
#include <maya/MArrayDataBuilder.h>

MStatus blendshapeCmd::doIt(const MArgList &args)
{
	MStatus stat;

	// Get a list of currently selected objects
	MSelectionList selection;
	MGlobal::getActiveSelectionList(selection);
	unsigned int length = selection.length();

	// Get the deformer node
	MSelectionList selDeformer;
	MGlobal::getSelectionListByName("sjDeformer1", selDeformer);

	MObject deformerObj;
	selDeformer.getDependNode(0, deformerObj);
	MFnDependencyNode deformerNode(deformerObj);

	// ------------------------------------------------------------------------------------------------------------------- //
	//														 TO DO - (4)								  
	// ------------------------------------------------------------------------------------------------------------------- //
	// 1. Get plugs to access the attributes of the deformer node (use MPlug)	  
	// 2. Pre-allocate the size of array attributes (use MArrayDataBuilder)	 and initialize them 
	// 3. Iterate the selected source meshes									  
	// 4. Make a connection from the plug of each source outMesh to the plug of the corresponding attribute of the deformer
	// 5. Initialize the weight value as 0.0 using the plug
	// * HINT : you can use 'elementByLogicalIndex' function of MPlug
	// ------------------------------------------------------------------------------------------------------------------- //
















	return redoIt();
}

MStatus blendshapeCmd::undoIt()
{
	return dgMod.undoIt();
}

MStatus blendshapeCmd::redoIt()
{
	return dgMod.doIt();
}