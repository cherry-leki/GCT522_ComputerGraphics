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
#include <math.h>

class SmartModeling : public MPxCommand {
public:
	virtual MStatus doIt(const MArgList&);
	virtual MStatus undoIt();
	virtual MStatus redoIt();
	virtual bool isUndoable() const;

	static void *creator() { return new SmartModeling; }
	static MSyntax newSyntax();

private:
	bool isQuery;
	MDagPathArray planePath;
	MObjectArray objects;
};

const char *heightFlag = "-h", *heightLongFlag = "-height";

MSyntax SmartModeling::newSyntax() {
	MSyntax syntax;

	syntax.addFlag(heightFlag, heightLongFlag, MSyntax::kDouble);
	
	return syntax;
}

MStatus SmartModeling::doIt(const MArgList &args) {
	MGlobal::displayInfo("working?");

	// Register objects
	MDagPath dagMesh;
	MFnMesh fnMesh;
	fnMesh.setObject(dagMesh);

	MObject dagModel;
	MFnTransform fnTransform;
	fnTransform.setObject(dagModel);


	// Iterate over the mesh vertices
	MItMeshVertex iterVtx(dagMesh);
	for (; !iterVtx.isDone(); iterVtx.next()) {
		// iterVtx.Something();
	}


	// Duplicate an object
	// During the iteration
	MObject instance = fnTransform.duplicate();

	// Register the duplicated instance and set its transformation
	MFnTransform fnInstance(instance);
	// fnInstance.setSomething();


	// Initial Shading Group
	// Refer to a Ground-Shadow plug-in in your textbook
	MSelectionList sList;
	sList.clear();

	MGlobal::getSelectionListByName("initialShadingGroup", sList);
	//sList.getDependNode(0, shadingGroupObj);

	MFnSet shadingGroupFn;
	//shadingGroupFn.setObject(shadingGroupObj);

	// Connect a duplicated instance with initial shading group during the iteration
	shadingGroupFn.addMember(instance);

	return redoIt();
}

MStatus SmartModeling::undoIt() {
	return MS::kSuccess;
}

MStatus SmartModeling::redoIt() {
	return MS::kSuccess;
}

bool SmartModeling::isUndoable() const {
	return isQuery ? false : true;
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