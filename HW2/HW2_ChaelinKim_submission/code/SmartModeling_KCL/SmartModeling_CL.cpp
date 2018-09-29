#include "SmartModeling_CL.h"
#include <maya/MGlobal.h>
#include <maya/MFnPlugin.h>
#include <maya/MPoint.h>
#include <maya/MArgList.h>
#include <maya/MArgDatabase.h>
#include <maya/MDagPath.h>
#include <maya/MFnMesh.h>
#include <maya/MFnTransform.h>
#include <maya/MItMeshVertex.h>
#include <maya/MFnSet.h>
#include <maya/MString.h>
#include <math.h>

const char *heightFlag = "-h", *heightLongFlag = "-height";
const char *objectFlag = "-o", *objectLongFlag = "-objects";
const char *planeFlag = "-p", *planeLongFlag = "-plane";

MSyntax SmartModeling::newSyntax() {
	MSyntax syntax;

	syntax.addFlag(heightFlag, heightLongFlag, MSyntax::kLong);
	syntax.addFlag(objectFlag, objectLongFlag, MSyntax::kString);
	syntax.addFlag(planeFlag, planeLongFlag, MSyntax::kString);
	
	return syntax;
}

MStatus SmartModeling::doIt(const MArgList &args) {
	MString plane;
	MString objects;

	MStatus stat;
	MArgDatabase argData(syntax(), args, &stat);
	if (!stat) return stat;
	
	// Set values from flag arguments
	if (argData.isFlagSet(objectFlag))
		argData.getFlagArgument(objectFlag, 0, objects);
	
	if (argData.isFlagSet(planeFlag))
		argData.getFlagArgument(planeFlag, 0, plane);

	if (argData.isFlagSet(heightFlag))
		argData.getFlagArgument(heightFlag, 0, height);

	// set plane to selection
	selectPlane.clear();
	MGlobal::getSelectionListByName(plane, selectPlane);

	// set objects to selection
	objects.split('|', objectArr);	// Parse the string data 
	selectObjects.clear();
	for (int i = 0; i < objectArr.length(); i++) {
		selectObjects.add(objectArr[i]);
	}

	return redoIt();
}

MStatus SmartModeling::undoIt() {
	// Make instanceArray to String
	MString selectedObjects;

	for (int i = 0; i < instanceArray.length(); i++) {
		MFnDagNode tempNode;
		tempNode.setObject(instanceArray[i]);
		selectedObjects += tempNode.name() + " ";
	}

	// Undo command
	MGlobal::executeCommand(MString("select -r ") + selectedObjects + " ;");
	MGlobal::executeCommand("doDelete;");

	return MS::kSuccess;
}

MStatus SmartModeling::redoIt() {
	// Register Plane
	MDagPath dagMesh;
	MFnMesh fnMesh;
	fnMesh.setObject(dagMesh);

	selectPlane.getDagPath(0, dagMesh);

	// Initial Shading Group
	MSelectionList sList;
	MObject shadingGroupObj;

	sList.clear();
	MGlobal::getSelectionListByName("initialShadingGroup", sList);
	sList.getDependNode(0, shadingGroupObj);

	MFnSet shadingGroupFn;
	shadingGroupFn.setObject(shadingGroupObj);

	// Iterate over the mesh vertices
	int vertIndex;
	MItMeshVertex iterVtx(dagMesh);

	// Clear MObjectArray
	instanceArray.clear();

	// Arrange objects on the plane 
	for (; !iterVtx.isDone(); iterVtx.next()) {
		MPoint pt = iterVtx.position(MSpace::kWorld);
		vertIndex = iterVtx.index();

		int randomModelNum = (rand() % (objectArr.length()));

		// Register objects
		MObject dagModel;
		MFnTransform fnTransform;
		selectObjects.getDependNode(randomModelNum, dagModel);
		fnTransform.setObject(dagModel);
		MObject instance = fnTransform.duplicate();

		// Register the duplicated instance and set its transformation
		MFnTransform fnInstance(instance);
		// set objects to the each vertex on the plane
		fnInstance.setTranslation(pt, MSpace::kTransform);

		// append objects to instanceArray for undo/redo
		instanceArray.append(instance);

		// change objects height
		double scale[3];
		fnInstance.getScale(scale);
		scale[1] = scale[1] * (rand() % height + 1);
		fnInstance.setScale(scale);

		// Connect a duplicated instance with initial shading group during the iteration
		shadingGroupFn.addMember(instance);
	}

	return MS::kSuccess;
}

MStatus initializePlugin(MObject obj) {
	MFnPlugin plugin(obj, "Chaelin Kim", "1.0");

	MStatus stat;
	stat = plugin.registerCommand("SmartModeling", SmartModeling::creator, SmartModeling::newSyntax);
	if (!stat)
		stat.perror("registerCommand failed");

	return stat;
}

MStatus uninitializePlugin(MObject obj) {
	MFnPlugin plugin(obj);

	MStatus stat;
	stat = plugin.deregisterCommand("SmartModeling");
	if (!stat)
		stat.perror("deregisterCommand failed");

	return stat;
}