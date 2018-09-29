* Source code (.sln/ .cpp / .h / .vcproj / .py)
- .cpp / .h / .vcproj: SmartModeling_KCL\SmartModeling_KCL
- .sln / .py	: SmartModeling_KCL

* Compiled binary file (.mll)
- SmartModeling_KCL\x64\Release

* Target Machine & Software
: Maya 2017, Visual Studio 2017, x64

* How to use command
1. Register objects to python GUI
 1-1. Select objects and click the add button below the object list
 1-2. Select plane and click the add button below the plane list
 1-3. Input the height value

2. Click the generate button
 2-1. then mel.eval code is executed
       : mel.eval("SmartModeling -h " + modelHeight + " -p " + plainList + " -o " + objectList + ";")
	> SmartModeling	: Plug-in name
	> -h modelHeight	: long flag that deliver height value
	> -p planeList	: string flag that deliver selected plane in Plane List
			  You have to change planeList list to string
	> -o objectList	: string flag that deliver selected objects in Object List
			  You have to change objectList list to string like 'object1|object2|object3' for parsing
	ex)	regObjects = cmds.textScrollList(objList, query=True, allItems=True)
    		regPlane = cmds.textScrollList(pList, query=True, allItems=True)
		mel.eval("SmartModeling -h " + modelHeight + " -p " + ''.join(regPlane) + " -o " + '|'.join(regObjects) + ";")
 2-2. Objects with various heights are arranged on the plane.