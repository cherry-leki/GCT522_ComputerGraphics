import numpy as np
import maya.cmds as cmds
from functools import partial as ft
import sys
sys.path.insert(0, '.')
import ButtonFunc as bf
reload(bf)

list_cameraPlace = ['Right', 'Left', 'Front', 'Back']

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
cmds.button(label="Add", p="targetObjLayout", w=40, command=ft(addTargetObj, targetObj))
cmds.button(label="Remove", p="targetObjLayout", w=55, command=ft(removeTargetObj, targetObj))

''' Curve Layout '''
cmds.rowLayout("curveLayout", p="mainCol", numberOfColumns = 5)
cmds.text(label="  Curve", p="curveLayout", w=80, al='left')
targetCurve = cmds.textScrollList(p="curveLayout", w=300, h=20)
cmds.text("",w=5)
cmds.button(label="Add", p="curveLayout", w=40, command=ft(addCurve, targetCurve))
cmds.button(label="Remove", p="curveLayout", w=55, command=ft(removeCurve, targetCurve))

''' Camera Placement Layout '''
cmds.rowLayout("cameraPlaceLayout", p="mainCol", numberOfColumns = 7)
cmds.text(label="Camera Placement", p="cameraPlaceLayout", w=103)
cameraPlace = cmds.optionMenu("cameraPlaceItem", p="cameraPlaceLayout", w=97)
for direction in list_cameraPlace:
    cmds.menuItem(direction)
cmds.text("", w=7)
cmds.text(label="Distance", p="cameraPlaceLayout", w=50)
distance = cmds.textField("distanceTextField", p="cameraPlaceLayout", w=117)
cmds.text(" ", w=5)
cmds.button(label="Place Camera", p="cameraPlaceLayout", w=97,
            command=ft(placeCamera, distance,targetObj,cameraPlace,list_cameraPlace))

''' Keyframes Layout '''
cmds.rowLayout("keyframeLayout", p="mainCol", numberOfColumns = 5)
cmds.text(label=" Keyframes / Interval Length", p="keyframeLayout", w=146)
keyframes = cmds.textField(p="keyframeLayout", w=116)
intervals = cmds.textField(p="keyframeLayout", w=116)
cmds.text("",w=5)
cmds.button(label="Follow Path", p="keyframeLayout", w=97,
            command=ft(followPath, targetObj,targetCurve,keyframes,intervals))


# Show Window
cmds.showWindow(window)
