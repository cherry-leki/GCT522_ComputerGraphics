from functools import partial as ft
import maya.cmds as cmds
import maya.mel as mel
import os
from os.path import basename

''' Funtion Part '''
def exportSrcAni(*args):
    blendNodeName = cmds.textField(srcBlendNode, q=True, text=True)
    fileName = cmds.textField(srcFileName, q=True, text=True)
    frame = cmds.intField(srcFrames, q=True, value=True)
    mel.eval("FRRBlendExport -bn " + blendNodeName +
                            " -bfn " + fileName +
                            " -f " + 360)

''' GUI Part '''
''' Window Setting '''
windowName = "Facial Retargeting To Frame"
window = cmds.window(title=windowName)

''' Main Layout '''
cmds.columnLayout("mainLayout", w=300)

''' Export Source Animation Data File '''
cmds.frameLayout("exportSource", l="Export Source Animation Data File",
                p="mainLayout", nch=2, cll=True, w=270)
cmds.rowColumnLayout("exportSourceList", p="exportSource", nc=2, cw=[(1,100), (2,150)])
cmds.text(l="FileName:")
srcFileName = cmds.textField("srcFileNameTxtField", tx="humanSourceAnimation.dat")
cmds.text(l="BlendNode:")
srcBlendNode = cmds.textField("srcBlendNodeTxtField", tx="targetBlend")
cmds.text(l="Frames:")
srcFrames = cmds.intField("srcFramesIntField", v=360)
cmds.button(l="Export Source Animation Data", w=250, c=exportSrcAni)

cmds.separator(style='none', height=5, p="mainLayout")

''' Export Range of Expression File '''
cmds.frameLayout("exportSrcROE", l="Export Range of Expression File",
                p="mainLayout", nch=2, cll=True, w=270)
cmds.rowColumnLayout("exportROEList", p="exportSrcROE", nc=2, cw=[(1,100), (2,150)])
cmds.text(l="FileName:")
srcROEFileName = cmds.textField("srcROEFileNameTxtField", tx="humanROE.dat")
cmds.text(l="BlendNode:")
srcROEBlendNode = cmds.textField("srcROEBlendNodeTxtField", tx="targetBlend")
cmds.text(l="Frames:")
srcROEFrames = cmds.intField("srcROEFramesIntField", v=36)
cmds.button(l="Export Source ROE", w=250)

cmds.separator(style='none', height=5, p="mainLayout")

''' Export Target CV List File '''
cmds.frameLayout("exportTarget", l="Export Target CV List File",
                p="mainLayout", nch=2, cll=True, w=270)
cmds.rowColumnLayout("exportTargetList", p="exportTarget", nc=2, cw=[(1,100), (2,150)])
cmds.text(l="FileName:")
trgFileName = cmds.textField("trgFileNameTxtField", tx="kokoCtrlList.dat")
cmds.button(l="Export Target CV List", w=250)

cmds.separator(style='none', height=5, p="mainLayout")

''' Export Target Range Of Expression File '''
cmds.frameLayout("exportTrgROE", l="Export Range of Expression File",
                p="mainLayout", nch=2, cll=True, w=270)
cmds.rowColumnLayout("exportTrgROEList", p="exportTrgROE", nc=2, cw=[(1,100), (2,150)])
cmds.text(l="Ctrl List:")
cmds.button(l="Import File")
cmds.separator(style='none')
trgROEBlendNode = cmds.textField("trgROEBlendNodeTxtField", tx="kokoCtrlList.dat")
cmds.text(l="FileName:")
trgROEFileName = cmds.textField("trgROEFramesTxtField", tx="kokoROE.dat")
cmds.text(l="# of Sets:")
trgROEFileName = cmds.intField("trgROESetsIntField", v=36)
cmds.button(l="Export Target ROE", w=250)

cmds.separator(style='none', height=5, p="mainLayout")

''' Export Final Retargeting Result File '''
cmds.frameLayout("finalResult", l="Export Final Retargeting Result File",
                p="mainLayout", nch=2, cll=True, w=270)
cmds.rowColumnLayout("finalResultList", p="finalResult", nc=2, cw=[(1,100), (2,150)])
cmds.text(l="Source ROE File:")
cmds.button(l="Source ROE Import")
cmds.separator(style='none')
srcROEFile = cmds.textField("srcROEFileTxtField")
cmds.text(l="Target ROE File:")
cmds.button(l="Target ROE Import")
cmds.separator(style='none')
trgROEFile = cmds.textField("trgROEFileTxtField")
cmds.text(l="Source Data File:")
cmds.button(l="Source Animation Import")
cmds.separator(style='none')
srcAniFile = cmds.textField("srcAniTxtField")
cmds.text(l="Final Data File:")
finalDataFile = cmds.textField("finalDataFileTxtField", tx="kokoFinalResult.dat")
cmds.button(l="Export Final Result", w=250)

cmds.separator(style='none', height=5, p="mainLayout")

''' Import Final Result File '''
cmds.frameLayout("importFinalFile", l="Import Final Result File",
                p="mainLayout", nch=2, cll=True, w=270)
cmds.rowColumnLayout("importFinalFileList", p="importFinalFile", nc=2, cw=[(1,100), (2,150)])
cmds.text(l="Ctrl List:")
cmds.button(l="Import file")
cmds.separator(style='none')
ctrlListFile = cmds.textField("ctrlListFileTxtField")
cmds.text(l="Final Result File:")
cmds.button(l="Import file")
cmds.separator(style='none')
finalResultFile = cmds.textField("finalResultFileTxtField")
cmds.button(l="Import Final Result", w=250)

cmds.separator(style='none', height=5, p="mainLayout")

# Show window
cmds.showWindow(window)
