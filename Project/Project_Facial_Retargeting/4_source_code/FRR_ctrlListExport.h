#ifndef _FRRCTRLLISTEXPORTCmd
#define _FRRCTRLLISTEXPORTCmd

#include "global.h"
#include <iostream>

class FRRCTRLLISTEXPORTCmd : public MPxCommand
{
public:
	virtual MStatus	doIt(const MArgList&);
	virtual MStatus undoIt();
	virtual MStatus redoIt();
	virtual bool isUndoable() const { return true; }

	static void *creator() { return new FRRCTRLLISTEXPORTCmd; }
	static MSyntax newSyntax();

private:
	MDGModifier dgMod;
};

#endif