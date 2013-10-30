# -*- coding: utf-8 -*-

"""

"""

from __future__ import print_function

import sys
import os
from PyQt4 import QtGui, QtCore, uic

def current_directory():
    return os.path.dirname(os.path.realpath(__file__))

class PhotoCat(QtGui.QMainWindow):

    def __init__(self):
        QtGui.QMainWindow.__init__(self)
        self.setWindowTitle("PhotoCat")
        self.ui = uic.loadUi(os.path.join(current_directory(), 'mainwindow.ui'))
        self.ui.show()

        self.ui.Close.triggered.connect(QtGui.qApp.quit)

        self.connect(self.ui.chooseSorceFolder,
                     QtCore.SIGNAL("clicked()"), self.choose_source_folder)

        self.connect(self.ui.chooseDestDir,
                     QtCore.SIGNAL("clicked()"), self.choose_destination_folder)

        self.connect(self.ui.destFolder,
                     QtCore.SIGNAL("textChanged(QString)"),
                     self.folders_changed)
        self.connect(self.ui.sourceFolder,
                     QtCore.SIGNAL("textChanged(QString)"),
                     self.folders_changed)

    def choose_source_folder(self):
        source_folder = QtGui.QFileDialog\
            .getExistingDirectory(self, "Choose source directory", '/home',
                                     options=QtGui.QFileDialog.ShowDirsOnly)

        if source_folder and os.access(source_folder, os.R_OK):
            self.ui.sourceFolder.setText(source_folder)

    def choose_destination_folder(self):
        destination_folder = QtGui.QFileDialog\
            .getExistingDirectory(self, "Choose destination directory", '/home',
                                     options=QtGui.QFileDialog.ShowDirsOnly)

        if destination_folder and os.access(destination_folder, os.W_OK):
            self.ui.destFolder.setText(destination_folder)

    def folders_changed(self, text):
        enabled = True
        if not self.ui.sourceFolder.text() or not self.ui.destFolder.text():
            enabled =False
        self.ui.start.setEnabled(enabled)

def main():
    app = QtGui.QApplication(sys.argv)
    photocat = PhotoCat()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()
