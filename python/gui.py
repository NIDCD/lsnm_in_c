# !/usr/bin/python
# ============================================================================
#
#                            PUBLIC DOMAIN NOTICE
#
#       National Institute on Deafness and Other Communication Disorders
#
# This software/database is a "United States Government Work" under the 
# terms of the United States Copyright Act. It was written as part of 
# the author's official duties as a United States Government employee and 
# thus cannot be copyrighted. This software/database is freely available 
# to the public for use. The NIDCD and the U.S. Government have not placed 
# any restriction on its use or reproduction. 
#
# Although all reasonable efforts have been taken to ensure the accuracy 
# and reliability of the software and data, the NIDCD and the U.S. Government 
# do not and cannot warrant the performance or results that may be obtained 
# by using this software or data. The NIDCD and the U.S. Government disclaim 
# all warranties, express or implied, including warranties of performance, 
# merchantability or fitness for any particular purpose.
#
# Please cite the author in any work or product based on this material.
# 
# ==========================================================================



# ***************************************************************************
#
#   Large-Scale Neural Modeling software (LSNM)
#
#   Section on Brain Imaging and Modeling
#   Voice, Speech and Language Branch
#   National Institute on Deafness and Other Communication Disorders
#   National Institutes of Health
#
#   This file (gui.py) was created on February 17, 2015.
#
#
#   Author: Antonio Ulloa. Last updated by Antonio Ulloa on February 17 2015  
# **************************************************************************/

# gui.py
#
# GUI for LSNM simulation
#

import sys
from PyQt4 import QtGui, QtCore


# create a class for our GUI and define its methods
class SimGUI(QtGui.QMainWindow):

    def __init__(self):

        super(SimGUI, self).__init__()

        self.initUI()

    def initUI(self):

        textEdit = QtGui.QTextEdit()
        self.setCentralWidget(textEdit)

        exitAction = QtGui.QAction(QtGui.QIcon.fromTheme('exit'), 'Exit', self)
        exitAction.setShortcut('Ctrl+Q')
        exitAction.setStatusTip('Exit application')
        exitAction.triggered.connect(self.close)

        self.statusBar()

        menubar = self.menuBar()
        fileMenu = menubar.addMenu('&File')
        fileMenu.addAction(exitAction)

        toolbar = self.addToolBar('Exit')
        toolbar.addAction(exitAction)
        
        # create a push button object labeled 'Run'
        # runButton = QtGui.QPushButton('Run', self)
        # define the action to be taken if Run button is clicked on
        # runButton.clicked.connect(QtCore.QCoreApplication.instance().quit)
        # apply a standard size to the button
        # runButton.resize(runButton.sizeHint())
        # position the button within the window
        # runButton.move(50, 20)
        
        # create a push button object labeled 'Quit'
        # quitButton = QtGui.QPushButton('Quit', self)
        # define the action to be taken if Quit button is clicked on
        # quitButton.clicked.connect(QtCore.QCoreApplication.instance().quit)
        # apply a standard size to it
        # quitButton.resize(quitButton.sizeHint())
        # position the button within the window
        # quitButton.move(50, 50)

        # set window's (x_position, y_position, width, height) 
        self.setGeometry(0, 0, 1000, 500)
        
        # set window's title
        self.setWindowTitle('Large-Scale Neural Modeling (LSNM)')

        # ... and display it on the screen!
        self.show()

    def closeEvent(self, event):

        # display a message box to confirm user really intended to quit current session
        reply = QtGui.QMessageBox.question(self, 'Message',
                                           'Are you sure you want to quit LSNM?',
                                           QtGui.QMessageBox.Yes | QtGui.QMessageBox.No,
                                           QtGui.QMessageBox.No)
        if reply == QtGui.QMessageBox.Yes:
            event.accept()
        else:
            event.ignore()

def main():
    
    # create application object called 'app'
    app = QtGui.QApplication(sys.argv)

    # create a widget window called "w"
    w = SimGUI()

    # main loop of application with a clean exit
    sys.exit(app.exec_())

# the following is the standard boilerplate that calls the main() function
if __name__ == '__main__':
    main()
