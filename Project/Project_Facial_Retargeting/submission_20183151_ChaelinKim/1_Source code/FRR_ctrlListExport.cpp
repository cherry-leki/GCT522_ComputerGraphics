//FRRCtrlListExport -cln "kokoCtrlList.dat"

#include "FRR_ctrlListExport.h"

const char *ctrlListFileNameFlag = "-cln", *ctrlListFileNameLongFlag = "-ctrlListFileName";

MSyntax FRRCTRLLISTEXPORTCmd::newSyntax()
{
	MSyntax syntax;
	syntax.addFlag(ctrlListFileNameFlag, ctrlListFileNameLongFlag, MSyntax::kString);
	return syntax;
}

MStatus FRRCTRLLISTEXPORTCmd::doIt(const MArgList &args)
{
	MString ctrlListFileName;
	int frameNum = 0;
	MArgDatabase argData(syntax(), args);
	if (argData.isFlagSet(ctrlListFileNameFlag))
		argData.getFlagArgument(ctrlListFileNameFlag, 0, ctrlListFileName);

	MSelectionList selection;
	MGlobal::getActiveSelectionList(selection);

	MItSelectionList iter(selection);

	ofstream fout;
	fout.open(ctrlListFileName.asChar());
	for (; !iter.isDone(); iter.next())
	{
		MObject selectObj;
		iter.getDependNode(selectObj);
		MDagPath dagPath;
		iter.getDagPath(dagPath);
		fout << dagPath.partialPathName() << endl;
	}
	fout.close();

	return redoIt();
}

MStatus FRRCTRLLISTEXPORTCmd::undoIt()
{
	return dgMod.undoIt();
}

MStatus FRRCTRLLISTEXPORTCmd::redoIt()
{
	return dgMod.doIt();
}
