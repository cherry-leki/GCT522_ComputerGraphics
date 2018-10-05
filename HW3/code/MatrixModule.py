import numpy as np
import maya.OpenMaya as om

def createRotationMatrix(cameraDirRad, cameraDist, targetPos):
    # Transform Matrix
    rotMat = [[np.cos(cameraDirRad), 0, np.sin(cameraDirRad), 0],
                [0, 1, 0, 0],
                [-np.sin(cameraDirRad), 0, np.cos(cameraDirRad), 0],
                [0, 0, 0, 1]]
    posMat = [[1, 0, 0, 0],
                [0, 1, 0, 0],
                [0, 0, 1, float(cameraDist)],
                [0, 0, 0, 1]]
    malPosMat = [[1, 0, 0, targetPos[0]],
                    [0, 1, 0, targetPos[1]],
                    [0, 0, 1, targetPos[2]],
                    [0, 0, 0, 1]]
    cameraPos = np.dot(malPosMat, rotMat)
    cameraPos = np.dot(cameraPos, posMat)
    cameraPos = np.dot(cameraPos, np.transpose([0, 0, 0, 1]))

    return cameraPos


def vectorAngle(cameraVector, posVector):
    # Calculate the angle
    angle = np.arccos(np.dot(cameraVector, posVector))
    orthoAxis = np.cross(cameraVector, posVector)

    q = om.MQuaternion(angle, om.MVector(orthoAxis[0], orthoAxis[1], orthoAxis[2]))
    euler = q.asEulerRotation()
    angle = np.rad2deg(euler.y)

    return angle
