#pragma warning(disable: 4996)
#ifndef _FRRTRAININGCmd
#define _FRRTRAININGCmd

#include "global.h"
#include "rbfKernel.h"
#include <iostream>

class FRRTRAININGCmd : public MPxCommand
{
public:
	virtual MStatus	doIt(const MArgList&);
	virtual MStatus undoIt();
	virtual MStatus redoIt();
	virtual bool isUndoable() const { return true; }

	static void *creator() { return new FRRTRAININGCmd; }
	static MSyntax newSyntax();

	static void split(std::string& text, std::string& separators, std::list<std::string>& words);
	static std::vector<std::vector<double>> importData(MString& fileName);
	static void exportData(vector<vector<double>> result, MString& fileName);

private:
	MDGModifier dgMod;
};

#endif