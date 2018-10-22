#include "FRR_blendExport.h"
#include "FRR_CVExport.h"
#include "FRR_ctrlListExport.h"
#include "FRR_Training.h"
#include "FRR_CVImport.h"
#include <maya/MFnPlugin.h>

MStatus initializePlugin(MObject obj)
{
	MFnPlugin plugin(obj, "Jaewon Song", "1.0");

	MStatus stat;
	stat = plugin.registerCommand("FRRBlendExport", FRRBLENDEXPORTCmd::creator, FRRBLENDEXPORTCmd::newSyntax);
	if (!stat)
		stat.perror("registerCommand failed");

	stat = plugin.registerCommand("FRRCVExport", FRRCVEXPORTCmd::creator, FRRCVEXPORTCmd::newSyntax);
	if (!stat)
		stat.perror("registerCommand failed");

	stat = plugin.registerCommand("FRRCtrlListExport", FRRCTRLLISTEXPORTCmd::creator, FRRCTRLLISTEXPORTCmd::newSyntax);
	if (!stat)
		stat.perror("registerCommand failed");

	stat = plugin.registerCommand("FRRTraining", FRRTRAININGCmd::creator, FRRTRAININGCmd::newSyntax);
	if (!stat)
		stat.perror("registerCommand failed");

	stat = plugin.registerCommand("FRRCVImport", FRRCVIMPORTCmd::creator, FRRCVIMPORTCmd::newSyntax);
	if (!stat)
		stat.perror("registerCommand failed");


	return stat;
}

MStatus uninitializePlugin(MObject obj)
{
	MFnPlugin plugin(obj);

	MStatus	stat;
	stat = plugin.deregisterCommand("FRRBlendExport");
	if (!stat)
		stat.perror("deregisterCommand failed");
	stat = plugin.deregisterCommand("FRRCVExport");
	if (!stat)
		stat.perror("deregisterCommand failed");

	stat = plugin.deregisterCommand("FRRCtrlListExport");
	if (!stat)
		stat.perror("deregisterCommand failed");

	stat = plugin.deregisterCommand("FRRTraining");
	if (!stat)
		stat.perror("deregisterCommand failed");

	stat = plugin.deregisterCommand("FRRCVImport");
	if (!stat)
		stat.perror("deregisterCommand failed");

	return stat;
}
