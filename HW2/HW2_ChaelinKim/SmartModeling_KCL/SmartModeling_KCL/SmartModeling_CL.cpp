#include <maya/MPxCommand.h>
#include <maya/MGlobal.h>
#include <maya/MFnPlugin.h>
#include <maya/MSelectionList.h>
#include <maya/MItSelectionList.h>
#include <maya/MPoint.h>
#include <maya/MArgList.h>
#include <maya/MSyntax.h>

#include <maya/MArgDatabase.h>
#include <maya/MDagPath.h>
#include <maya/MDagPathArray.h>
#include <maya/MObjectArray.h>
#include <maya/MFnMesh.h>
#include <maya/MFnTransform.h>
#include <maya/MItMeshVertex.h>
#include <maya/MFnSet.h>
#include <maya/MDGModifier.h>
#include <maya/MString.h>
#include <maya/MStringArray.h>
#include <string.h>
#include <math.h>

class SmartModeling : public MPxCommand {
public:
	virtual MStatus doIt(const MArgList&);
	virtual MStatus undoIt();
	virtual MStatus redoIt();
	virtual bool isUndoable() const { return true;  };

	static void *creator() { return new SmartModeling; }
	static MSyntax newSyntax();

private:
	MObjectArray instanceArray;
	MDGModifier dgMod;
	int height;
	MSelectionList selectPlane;
	MSelectionList selectObjects;
	MStringArray objectArr;
};

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
	//MGlobal::displayInfo("working?");

	MString plane;
	MString objects;
	//MStringArray objectArr;

	MStatus stat;
	MArgDatabase argData(syntax(), args, &stat);
	if (!stat) return stat;
	
	if (argData.isFlagSet(objectFlag))
		argData.getFlagArgument(objectFlag, 0, objects);

	if (argData.isFlagSet(planeFlag))
		argData.getFlagArgument(planeFlag, 0, plane);

	if (argData.isFlagSet(heightFlag))
		argData.getFlagArgument(heightFlag, 0, height);

	MGlobal::displayInfo(objects);
	objects.split('|', objectArr);	

	//MSelectionList selectPlane;
	selectPlane.clear();
	MGlobal::getSelectionListByName(plane, selectPlane);

	//MSelectionList selectObjects;
	selectObjects.clear();
	for (int i = 0; i < objectArr.length(); i++) {
		selectObjects.add(objectArr[i]);
	}

	//// Register Plane
	//MDagPath dagMesh;
	//MFnMesh fnMesh;
	//fnMesh.setObject(dagMesh);

	//selectPlane.getDagPath(0, dagMesh);

	//// Iterate over the mesh vertices
	//int vertIndex;
	//MItMeshVertex iterVtx(dagMesh);

	//// Initial Shading Group
	//// Refer to a Ground-Shadow plug-in in your textbook
	//MSelectionList sList;
	//MObject shadingGroupObj;

	//sList.clear();
	//MGlobal::getSelectionListByName("initialShadingGroup", sList);
	//sList.getDependNode(0, shadingGroupObj);

	//MFnSet shadingGroupFn;
	//shadingGroupFn.setObject(shadingGroupObj);

	//// Clear MObjectArray
	//instanceArray.clear();

	//for (; !iterVtx.isDone(); iterVtx.next()) {
	//	MPoint pt = iterVtx.position(MSpace::kWorld);
	//	vertIndex = iterVtx.index();

	//	int randomModelNum = (rand() % (objectArr.length()));

	//	// Register objects
	//	MObject dagModel;
	//	MFnTransform fnTransform;
	//	selectObjects.getDependNode(randomModelNum, dagModel);
	//	fnTransform.setObject(dagModel);
	//	MObject instance = fnTransform.duplicate();

	//	// Register the duplicated instance and set its transformation
	//	MFnTransform fnInstance(instance);
	//	fnInstance.setTranslation(pt, MSpace::kTransform);

	//	instanceArray.append(instance);

	//	double scale[3];
	//	fnInstance.getScale(scale);
	//	scale[1] = rand() % height + 1;
	//	fnInstance.setScale(scale);


	//	// Connect a duplicated instance with initial shading group during the iteration
	//	shadingGroupFn.addMember(instance);
	//}

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
	MGlobal::displayInfo("redo");
	/*MString selectedObjects;

	for (int i = 0; i < instanceArray.length(); i++) {
		MFnDagNode tempNode;
		tempNode.setObject(instanceArray[i]);
		selectedObjects += tempNode.name() + " ";
	}

	MGlobal::executeCommand(MString("select -r ") + selectedObjects + " ;");*/

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