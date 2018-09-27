import maya.cmds as cmds
import maya.mel as mel

# Add items to Object list
def addToObjList(*args):
    selectedObjects = cmds.ls(selection=True)
    if not selectedObjects:
        print "Please select objects!"
        return
    selectedObjects.sort()
    for obj in selectedObjects:
        cmds.textScrollList(objList, edit=True, append=obj)
        
# Delete items in Object list
def delInObjList(*args):
    cmds.textScrollList(objList, edit=True, removeAll=True)

# Add plane to Plane list        
def addToPlaneList(*args):
    selectedPlane = cmds.ls(selection=True)
    if not selectedPlane:
        print "Please select plane!"
        return
    cmds.textScrollList(pList, edit=True, append=selectedPlane)
    
# Delete item in Plane list
def delInPlaneList(*args):
    cmds.textScrollList(pList, edit=True, removeAll=True)

# Generate objects on the plane
def generateModels(*args):
    modelHeight = cmds.textField(height, query=True, text=True)
    if not modelHeight:
        print "Please write model height!"
        return
    regObjects = cmds.textScrollList(objList, query=True, allItems=True)
    regPlane = cmds.textScrollList(pList, query=True, allItems=True)
    mel.eval("SmartModeling -o " + regObjects + " -p " + regPlane + ";")

''' Window Setting '''
windowName = "Smart Modeling"
windowSize = [350, 350]

window = cmds.window(title=windowName, widthHeight=windowSize, sizeable=False)

''' Main Layout '''
cmds.columnLayout("mainRow", co=["both", 24], rs=10, columnAlign="center", w=300)

''' Object & Plane List Layout '''
cmds.rowLayout("listColumn", p="mainRow", numberOfColumns=2)

''' Object List Layout '''
cmds.columnLayout("objectList", p="listColumn", rs=10, co=["right", 15])
cmds.text(label="")
cmds.text(label="Object List", p="objectList", w=140)
objList = cmds.textScrollList(p="objectList", allowMultiSelection=True, w=140, h=130)
cmds.button(label="Add", p="objectList", w=140, bgc=[0.698,0.501,0.490], command=addToObjList)
cmds.button(label="Delete", p="objectList", w=140, bgc=[0.705,0.4,0.4], command=delInObjList)
cmds.text(label="Height: ", align='center', w=140, h=20)

''' Plane List Layout '''
cmds.columnLayout("planeList", p="listColumn", rs=10)
cmds.text(label="")
cmds.text(label="Plane List", p="planeList", w=140)
pList = cmds.textScrollList(p="planeList", w=140, h=130)
cmds.button(label="Add", p="planeList", w=140, bgc=[0.701,0.901,0.694], command=addToPlaneList)
cmds.button(label="Delete", p="planeList", w=140, bgc=[0.4,0.701,0.396], command=delInPlaneList)
height = cmds.textField("heightTextField", p="planeList", w=140)


''' Generate button '''
cmds.button(label="Generate", p="mainRow", w=300, h=30, bgc=[0.203,0.203,0.498], command=generateModels)

# Show Window
cmds.showWindow(window)