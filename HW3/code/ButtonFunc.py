import numpy as np
import maya.cmds as cmds
import sys
sys.path.insert(0, '.')
import MatrixModule as mm
reload(mm)

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
    cameraDist = cmds.textField(distance, q=True, tx=True)
    if not cameraDist:
        print "Please input the distance"
        return

    target = cmds.textScrollList(targetObj, q=True, ai=True)
    if not target:
        print "Please register the target object!"
        return
    target = ''.join(target)
    print target

    # Target Position
    targetPos = cmds.getAttr(target + '.translate')
    targetPos = list(targetPos[0])

    # Target Rotation
    targetRot = cmds.getAttr(target + '.rotate')
    targetRot = list(targetRot[0])
    cameraDirSwitch = { list_cameraPlace[0]: -90, list_cameraPlace[1]: 90,
                    list_cameraPlace[2]: 0, list_cameraPlace[3]: 180}
    cameraDir = cameraDirSwitch.get(cmds.optionMenu(cameraPlace, q=True, v=True), 0)
    cameraDir += targetRot[1]
    cameraDirRad = np.deg2rad(cameraDir)

    # Transform Matrix
    cameraPos = mm.createRotationMatrix(cameraDirRad, cameraDist, targetPos)

    # Create a camera
    newCamera = cmds.camera()
    cmds.setAttr(newCamera[0] + '.rotateY', cameraDir)
    cmds.setAttr(newCamera[0] + '.translate', cameraPos[0], cameraPos[1], cameraPos[2], type="double3")


# Make the camera follow the curve path with keyframes and interval length
def followPath(*args):
    target = ''.join(cmds.textScrollList(targetObj, q=True, ai=True))
    if not target:
        print "Please register the target object!"
        return

    targetCur = ''.join(cmds.textScrollList(targetCurve, q=True, ai=True))
    if not targetCur:
        print "Please register the target curve!"
        return

    keyframe = int(cmds.textField(keyframes, q=True, tx=True))
    if not keyframe:
        print "Please input the keyframe value!"
        return

    interval = int(cmds.textField(intervals, q=True, tx=True))
    if not keyframe:
        print "Please input the interval value!"
        return

    targetPos = cmds.getAttr(target + '.translate')
    targetPos = list(targetPos[0])
    cmds.setAttr(targetCur +'.translateY', targetPos[1])

    newCamera = cmds.camera()
    postAngle = 0;
    plus360Flag = False;

    for itr in range(0, keyframe):
        spans = cmds.getAttr(targetCur + '.spans')
        para = float(itr * (float(spans) / float(keyframe)))
        points = cmds.pointOnCurve(targetCur, pr=para, p=True)
        cmds.setAttr(newCamera[0] + '.translate', points[0], points[1], points[2])
        cmds.setKeyframe(newCamera[0], at='translate', t=itr*interval)

        posVector = [targetPos[0] - points[0],
                    targetPos[1] - points[1],
                    targetPos[2] - points[2]]
        posVector = posVector / np.linalg.norm(posVector)

        cameraVector = [0, 0, -1]

        # Calculate the angle
        angle = mm.vectorAngle(cameraVector, posVector)

        if not plus360Flag:
            if postAngle > 0 and angle < 0:
                plus360Flag = True
        if plus360Flag: angle += 360

        cmds.setAttr(newCamera[0] + '.rotateY', angle)
        cmds.setKeyframe(newCamera[0], at='.rotate', t=itr*interval)

        postAngle = angle
