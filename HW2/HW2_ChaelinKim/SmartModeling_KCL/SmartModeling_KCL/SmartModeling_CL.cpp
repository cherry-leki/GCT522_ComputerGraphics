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
	
	if (argData.isFlagSet(objectFlag))
		argData.getFlagArgument(objectFlag, 0, objects);
	objects.split('|', objectArr);

	if (argData.isFlagSet(planeFlag))
		argData.getFlagArgument(planeFlag, 0, plane);

	if (argData.isFlagSet(heightFlag))
		argData.getFlagArgument(heightFlag, 0, height);

	
	// set plane
	selectPlane.clear();
	MGlobal::getSelectionListByName(plane, selectPlane);

	selectObjects.clear();
	for (int i = 0; i < objectArr.length(); i++) {
		selectObjects.add(objectArr[i]);
	}

	/* Go to redo function
	// Register Plane
	MDagPath dagMesh;
	MFnMesh fnMesh;
	fnMesh.setObject(dagMesh);

	selectPlane.getDagPath(0, dagMesh);

	// Iterate over the mesh vertices
	int vertIndex;
	MItMeshVertex iterVtx(dagMesh);

	// Initial Shading Group
	// Refer to a Ground-Shadow plug-in in your textbook
	MSelectionList sList;
	MObject shadingGroupObj;

	sList.clear();
	MGlobal::getSelectionListByName("initialShadingGroup", sList);
	sList.getDependNode(0, shadingGroupObj);

	MFnSet shadingGroupFn;
	shadingGroupFn.setObject(shadingGroupObj);

	// Clear MObjectArray
	instanceArray.clear();

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
		fnInstance.setTranslation(pt, MSpace::kTransform);

		instanceArray.append(instance);

		double scale[3];
		fnInstance.getScale(scale);
		scale[1] = rand() % height + 1;
		fnInstance.setScale(scale);


		// Connect a duplicated instance with initial shading group during the iteration
		shadingGroupFn.addMember(instance);
	}
	*/

	return redoIt();
}

MStatus SmartModeling::undoIt() {
	MGlobal::displayInfo("undo");
	MString selectedObjects;

	for (int i = 0; i < instanceArray.length(); i++) {
		MFnDagNode tempNode;
		tempNode.setObject(instanceArray[i]);
		selectedObjects += tempNode.name() + " ";
	}

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

	// Iterate over the mesh vertices
	int vertIndex;
	MItMeshVertex iterVtx(dagMesh);

	// Initial Shading Group
	// Refer to a Ground-Shadow plug-in in your textbook
	MSelectionList sList;
	MObject shadingGroupObj;

	sList.clear();
	MGlobal::getSelectionListByName("initialShadingGroup", sList);
	sList.getDependNode(0, shadingGroupObj);

	MFnSet shadingGroupFn;
	shadingGroupFn.setObject(shadingGroupObj);

	// Clear MObjectArray
	instanceArray.clear();

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
		fnInstance.setTranslation(pt, MSpace::kTransform);

		instanceArray.append(instance);

		double scale[3];
		fnInstance.getScale(scale);
		scale[1] = rand() % height + 1;
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