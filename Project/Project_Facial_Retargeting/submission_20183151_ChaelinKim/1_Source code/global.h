#pragma once
#include <maya/MPxCommand.h>
#include <maya/MGlobal.h>
#include <maya/MSelectionList.h>
#include <maya/MItSelectionList.h>
#include <maya/MDagPath.h>
#include <maya/MString.h>
#include <maya/MArgList.h>
#include <maya/MSyntax.h>
#include <maya/MArgDatabase.h>
#include <maya/MDGModifier.h>
#include <maya/MFnNurbsCurve.h>
#include <maya/MFnTransform.h>

#include <maya/MFnBlendShapeDeformer.h>
#include <maya/MObjectArray.h>

#include <stdlib.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <list>
#include <time.h>

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;