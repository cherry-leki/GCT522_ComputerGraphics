import numpy as np
import maya.cmds as cmds
import sys
sys.path.insert(0, '.')
import MatrixModule as mm
reload(mm)

''' Add target object '''
def addTargetObj(targetObj, *args):
    # Get the selected target object
    selectedTargetObj = cmds.ls(selection=True)
    selectedTargetObjShape = cmds.listRelatives(selectedTargetObj, shapes=True)

    # Check if user choose a target correctly
    if not selectedTargetObj or cmds.nodeType(selectedTargetObjShape) != "mesh":
        print "Please select the target object!"
        return
    if len(selectedTargetObj) > 1:
        print "Please select only one target object"
        return

    cmds.textScrollList(targetObj, edit=True, ra=True)
    cmds.textScrollList(targetObj, edit=True, append=selectedTargetObj)


''' Remove target object '''
def removeTargetObj(targetObj, *args):
    cmds.textScrollList(targetObj, edit=True, ra=True)


''' Add target curve object '''
def addCurve(targetCurve, *args):
    # Get the selected target curve
    selectedCurve = cmds.ls(selection=True)
    selectedCurveShape = cmds.listRelatives(selectedCurve, shapes=True)

    # Check if user choose a target correctly
    if not selectedCurve or cmds.nodeType(selectedCurveShape) != "nurbsCurve":
        print "Please select the curve!"
        return
    if len(selectedCurve) > 1:
        print "Please select only one curve"
        return

    cmds.textScrollList(targetCurve, edit=True, ra=True)
    cmds.textScrollList(targetCurve, edit=True, append=selectedCurve)


''' Remove target curve object '''
def removeCurve(targetCurve, *args):
    cmds.textScrollList(targetCurve, edit=True, ra=True)


''' Place a camera in accordance with direction and distance '''
def placeCamera(distance, targetObj, cameraPlace, list_cameraPlace, *args):
    # Get the distance value and check if user input a distance
    cameraDist = cmds.textField(distance, q=True, tx=True)
    if not cameraDist:
        print "Please input the distance"
        return

    # Get the target object and check if the target is registered
    target = cmds.textScrollList(targetObj, q=True, ai=True)
    if not target:
        print "Please register the target object!"
        return
    target = ''.join(target)

    # Target Position
    targetPos = cmds.getAttr(target + '.translate')
    targetPos = list(targetPos[0])

    # Target Rotation
    targetRot = cmds.getAttr(target + '.rotate')
    targetRot = list(targetRot[0])

    # Calculate the camera's direction
    # Camera's default view direction: (0, 0, -1)
    cameraDirSwitch = { list_cameraPlace[0]: -90, list_cameraPlace[1]: 90,
                    list_cameraPlace[2]: 0, list_cameraPlace[3]: 180}
    cameraDir = cameraDirSwitch.get(cmds.optionMenu(cameraPlace, q=True, v=True), 0)

    # Get value from the transform matrix
    targetPosMat = mm.createTranslateMatrix(targetPos)
    targetRotMat = mm.createRotationMatrix(np.deg2rad(targetRot[1]), "y")
    cameraDistMat = mm.createTranslateMatrix([0, 0, float(cameraDist)])
    cameraDirMat = mm.createRotationMatrix(np.deg2rad(cameraDir), "y")

    # Calculate camera Position
    cameraPos = mm.calPosVector([targetPosMat, targetRotMat, cameraDirMat, cameraDistMat],
                             [0, 0, 0, 1])

    # Create a camera with upper settings
    newCamera = cmds.camera()
    cmds.setAttr(newCamera[0] + '.rotateY', cameraDir + targetRot[1])
    cmds.setAttr(newCamera[0] + '.translate', cameraPos[0], cameraPos[1], cameraPos[2], type="double3")


''' Make the camera follow the curve path with keyframes and interval length '''
def followPath(targetObj, targetCurve, keyframes, intervals,*args):
    # Get the target object and check if the target is registered
    target = ''.join(cmds.textScrollList(targetObj, q=True, ai=True))
    if not target:
        print "Please register the target object!"
        return

    # Get the target curve and check if the curve is registered
    targetCur = ''.join(cmds.textScrollList(targetCurve, q=True, ai=True))
    if not targetCur:
        print "Please register the target curve!"
        return

    # Get the keyframe value and check if user input a keyframe
    keyframe = int(cmds.textField(keyframes, q=True, tx=True))
    if not keyframe:
        print "Please input the keyframe value!"
        return

    # Get the interval value and check if user input a interval
    interval = int(cmds.textField(intervals, q=True, tx=True))
    if not keyframe:
        print "Please input the interval value!"
        return

    # Get the position of target object
    targetPos = cmds.getAttr(target + '.translate')
    targetPos = list(targetPos[0])

    # Set the curve's y position equal to target object's y position
    cmds.setAttr(targetCur +'.translateY', targetPos[1])

    # Create a camera and set the variables for correction of degree range
    newCamera = cmds.camera()
    postAngle = 0
    correctAngleFlag = False
    correctAngleValue = 0

    # Calculate camera to look at the target at each keyframe
    for itr in range(0, keyframe):
        # Calculate camera's position at each keyframe
        spans = cmds.getAttr(targetCur + '.spans')
        para = float(itr * (float(spans) / float(keyframe)))
        points = cmds.pointOnCurve(targetCur, pr=para, p=True)
        cmds.setAttr(newCamera[0] + '.translate', points[0], points[1], points[2])
        cmds.setKeyframe(newCamera[0], at='translate', t=itr*interval)

        # Set the vector of target object's point and camera's point
        posVector = [targetPos[0] - points[0],
                    targetPos[1] - points[1],
                    targetPos[2] - points[2]]
        posVector = posVector / np.linalg.norm(posVector)

        # Camera's default view direction vector
        cameraVector = [0, 0, -1]

        # Calculate the angle of how much the camera rotates
        angle = mm.vectorAngle(cameraVector, posVector)

        # Correct of degree range
        if not correctAngleFlag:
            if postAngle > 0 and angle < 0:     correctAngleValue = 360
            elif postAngle < 0 and angle > 180: correctAngleValue = -360
            if correctAngleValue != 0:          correctAngleFlag = True
        if correctAngleFlag: angle += correctAngleValue

        cmds.setAttr(newCamera[0] + '.rotateY', angle)
        cmds.setKeyframe(newCamera[0], at='.rotate', t=itr*interval)

        postAngle = angle
