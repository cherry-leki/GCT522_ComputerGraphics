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
	MGlobal::getSelectionListByName("clDeformer1", selDeformer);

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
	
	//1
	MPlug blendMeshPlug = deformerNode.findPlug("blendMesh");
	MPlug blendWeightPlug = deformerNode.findPlug("blendWeight");
	//2

	MArrayDataHandle meshDataHandle = blendMeshPlug.asMDataHandle();
	MArrayDataHandle meshWeightHandle = blendWeightPlug.asMDataHandle();

	MArrayDataBuilder meshBuilder(blendMeshPlug, length);
	MArrayDataBuilder weightBuilder(blendWeightPlug, length);

	for (int attrNum = 0; attrNum < length; attrNum++) {
		MDataHandle meshHandle = meshBuilder.addElement(attrNum);
		MDataHandle weightHandle = weightBuilder.addElement(attrNum);
		MObject outmeshData;

		meshHandle.set(outmeshData);
		weightHandle.set(0.0f);
	}
	meshDataHandle.set(meshBuilder);
	meshWeightHandle.set(weightBuilder);
	meshDataHandle.setAllClean();
	meshWeightHandle.setAllClean();


	//3
	MDagPath dagPath;
	unsigned int count;

	MItSelectionList iter(selection, MFn::kMesh);
	for (iter.reset(), count=0; !iter.isDone(); iter.next(), count++) {
		MDagPath shapePath;
		iter.getDagPath(shapePath);

		MFnMesh fnMesh(shapePath);

		if (fnMesh.name() == "clDeformer1") continue;

		MPlug srcOutMesh = fnMesh.findPlug("outMesh");
		MGlobal::displayInfo("name: " + srcOutMesh.name());

		MPlug meshElement = blendMeshPlug.elementByLogicalIndex(count);
		MPlug weightElement = blendWeightPlug.elementByLogicalIndex(count);

		//4 Make the connections
		dgMod.connect(srcOutMesh, meshElement);
		weightElement.setFloat(0.0f);
	}

	//5

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