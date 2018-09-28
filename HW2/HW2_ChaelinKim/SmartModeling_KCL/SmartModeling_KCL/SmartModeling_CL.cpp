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
	MDGModifier dgMod;
	int height;
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

	MStatus stat;
	MArgDatabase argData(syntax(), args, &stat);
	if (!stat) return stat;

	isQuery = argData.isQuery();

	if (argData.isFlagSet(objectFlag) && !isQuery)
		argData.getFlagArgument(objectFlag, 0, objects);

	MGlobal::displayInfo(objects);

	if (argData.isFlagSet(planeFlag) && !isQuery)
		argData.getFlagArgument(planeFlag, 0, plane);

	if (argData.isFlagSet(heightFlag))
		argData.getFlagArgument(heightFlag, 0, height);

	MSelectionList selection;
	selection.clear();
	MGlobal::getSelectionListByName(plane, selection);


	// Register objects
	// Plane
	MDagPath dagMesh;
	MFnMesh fnMesh;
	fnMesh.setObject(dagMesh);

	// Objects
	MObject dagModel;
	MFnTransform fnTransform;
	fnTransform.setObject(dagModel);


	MString txt;
	MItSelectionList iter(selection, MFn::kMesh);
	for (; !iter.isDone(); iter.next()) {
		iter.getDagPath(dagMesh);

		// Iterate over the mesh vertices
		int vertCount, vertIndex;
		MItMeshVertex iterVtx(dagMesh);
		for (; !iterVtx.isDone(); iterVtx.next()) {
			MPoint pt = iterVtx.position(MSpace::kWorld);
			vertIndex = iterVtx.index();
			txt += MString(" ") + vertIndex + ": " +
				pt.x + ", " + pt.y + ", " + pt.z + "\n";

			int tempHeight = (rand() % height + 1);
			MGlobal::executeCommand(MString("cylinder -pivot ") + pt.x + " " + (pt.y + tempHeight * 2) + " " + pt.z
				+ " -radius 5 -axis 0 1 0 -heightRatio " + tempHeight);
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
	}	

	return redoIt();
}

MStatus SmartModeling::undoIt() {
	return dgMod.undoIt();
}

MStatus SmartModeling::redoIt() {
	return dgMod.doIt();
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