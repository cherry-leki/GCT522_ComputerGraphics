import maya.cmds as cmds
import sys
import os

# Add target object
def addTargetObj(*args):
    selectedTargetObj = cmds.ls(selection=True)
    if not selectedTargetObj:
        print "Please select the target object!"
        return
    if len(selectedTargetObj) > 1:
        print "Please select only one target object"
        return
    cmds.textScrollList(targetObj, edit=True, ra=True)
    cmds.textScrollList(targetObj, edit=True, append=selectedTargetObj)
    
# Remove target object
def removeTargetObj(*args):
    cmds.textScrollList(targetObj, edit=True, ra=True)
        
# Add Curve object
def addCurve(*args):
    selectedCurve = cmds.ls(selection=True)
    if not selectedCurve:
        print "Please select the target object!"
        return
    if len(selectedCurve) > 1:
        print "Please select only one target object"
        return
    cmds.textScrollList(targetCurve, edit=True, ra=True)
    cmds.textScrollList(targetCurve, edit=True, append=selectedCurve)
        
# Remove Curve object
def removeCurve(*args):
    cmds.textScrollList(targetCurve, edit=True, ra=True)

# Place a camera in accordance with direction and distance
def placeCamera(*args):
    print "Place Camera"

# Make the camera follow the curve path with keyframes and interval length
def followPath(*args):
    print "follow path"


''' Window Setting '''
windowName = "Camera Path Generator"
windowSize = [500, 130]

window = cmds.window(title=windowName, widthHeight=windowSize, sizeable=False)

''' Main Layout '''
cmds.columnLayout("mainCol", rs=3)
cmds.text("", h=5)

''' Target Object Layout '''
cmds.rowLayout("targetObjLayout", p="mainCol", numberOfColumns = 5)
cmds.text(label="Target Object", p="targetObjLayout", w=80)
targetObj = cmds.textScrollList(p="targetObjLayout", w=300, h=20)
cmds.text("",w=5)
cmds.button(label="Add", p="targetObjLayout", w=40, command=addTargetObj)
cmds.button(label="Remove", p="targetObjLayout", w=55, command=removeTargetObj)

''' Curve Layout '''
cmds.rowLayout("curveLayout", p="mainCol", numberOfColumns = 5)
cmds.text(label="  Curve", p="curveLayout", w=80, al='left')
targetCurve = cmds.textScrollList(p="curveLayout", w=300, h=20)
cmds.text("",w=5)
cmds.button(label="Add", p="curveLayout", w=40, command=addCurve)
cmds.button(label="Remove", p="curveLayout", w=55, command=removeCurve)

''' Camera Placement Layout '''
list_cameraPlace = ['Right', 'Left', 'Front', 'Back']
cmds.rowLayout("cameraPlaceLayout", p="mainCol", numberOfColumns = 7)
cmds.text(label="Camera Placement", p="cameraPlaceLayout", w=103)
cameraPlace = cmds.optionMenu("cameraPlaceItem", p="cameraPlaceLayout", w=97)
for direction in list_cameraPlace:
    cmds.menuItem(direction)
cmds.text("", w=7)
cmds.text(label="Distance", p="cameraPlaceLayout", w=50)
distance = cmds.textField("distanceTextField", p="cameraPlaceLayout", w=117)
cmds.text(" ", w=5)
cmds.button(label="Place Camera", p="cameraPlaceLayout", w=97)

''' Keyframes Layout '''
cmds.rowLayout("keyframeLayout", p="mainCol", numberOfColumns = 5)
cmds.text(label=" Keyframes / Interval Length", p="keyframeLayout", w=146)
keyframes = cmds.textField(p="keyframeLayout", w=116)
intervals = cmds.textField(p="keyframeLayout", w=116)
cmds.text("",w=5)
cmds.button(label="Follow Path", p="keyframeLayout", w=97)


# Show Window
cmds.showWindow(window)