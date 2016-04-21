#include "layout.h"
#include "parser.h"
#include <QApplication>
#include <QMainWindow>
#include <QFileDialog>
#include <QClipboard>
#include <QString>
#include <string>
#include <iostream>
#include <fstream>
#include <QMessageBox>
using namespace std;

class mips : public Ui::Mips_Assembler, public QMainWindow {
public:
    mips() {
        mw = new QMainWindow;
        setupUi(mw);
        retranslateUi(mw);
        highlighter1 = new Highlighter(textEdit->document());
		highlighter2 = new Highlighter(textBrowser_2->document());
        textEdit->setStyleSheet("QTextEdit{font: bold large \"Consolas\";font-size:16px;color:rgb(30,30,30);height:50px;border:2px solid rgb(160,0,28);border-radius:15px;selection-color:pink}");
        textBrowser_2->setStyleSheet("QTextBrowser{font: bold large \"Consolas\";font-size:16px;color:rgb(30,30,30);height:50px;border:2px solid rgb(20,100,190);border-radius:15px;selection-color:blue}");
        textBrowser_2->setPlainText(QString::fromStdString(string("Result Browser")));
        textBrowser_3->setStyleSheet("QTextBrowser{font: bold large \"Consolas\";font-size:16px;color:rgb(30,30,30);height:50px;border:2px solid rgb(80,120,110);border-radius:15px;selection-color:darkBlue}");
        textBrowser_3->setPlainText(QString::fromStdString(string("Debug information")));
        connect(new_menu, &QAction::triggered, this, &mips::othersaveFile);
        connect(open_menu, &QAction::triggered, this, &mips::openFile);
        connect(save_menu, &QAction::triggered, this, &mips::saveFile);
        connect(othersave_menu, &QAction::triggered, this, &mips::othersaveFile);
        connect(bin_menu, &QAction::triggered, this, &mips::asm2bin);
        connect(coe_menu, &QAction::triggered, this, &mips::asm2coe);
        connect(disasm_menu, &QAction::triggered, this, &mips::bin2asm);
        connect(copy_menu, &QAction::triggered, this, &mips::copytext);
        connect(paste_menu, &QAction::triggered, this, &mips::paste2text);
        connect(back_menu, &QAction::triggered, this, &mips::backtext);
        connect(about_menu, &QAction::triggered, this, &mips::info);
    }

    void info(){
        QMessageBox msgBox;
        msgBox.setText("© 2016 Haojie PAN. \n Contact with me: 3140102237@zju.edu.cn \n https://github.com/ScarletPan");
        msgBox.exec();
    }

    void asm2bin() {
        assembler a;
        textBrowser_3->clear();
        if (fname.length() == 0)
            mips::othersaveFile();
        else {
            QString plaintext;
            ofstream out(fname);
            plaintext = textEdit->toPlainText();
            text = string(plaintext.toLatin1().data());
            out << text;
        }
		if (fname.length() == 0)
			return;
        a.execute_parser(fname);
        string biname;
        for (unsigned int i = 0; i < fname.length() && fname[i] != '.'; ++i) {
            biname.append(1, fname[i]);
        }
        if (error_str.length() == 0) {
            ofstream binout(biname + ".bin");
            a.outputBin(binout);
            binout.close();
            ifstream binfile(biname + ".bin");
            text.clear();
            while (!binfile.eof()) {
                string tmp;
                getline(binfile, tmp);
                text.append(tmp + "\n");
            }
            textBrowser_2->setPlainText(QString::fromStdString(text));
            if (text.length() > 0)
                textBrowser_3->setPlainText(QString::fromStdString(string("Build succeed!\nSaving to the bin file")));
            else {
                textBrowser_3->setPlainText(QString::fromStdString(string("Build Failed")));
            }
        }
        else {
            error_str.insert(0, "Build failed.\n");
            textBrowser_3->setPlainText(QString::fromStdString(error_str));
        }
        error_str.clear();

    }

    void asm2coe() {
        assembler a;
        textBrowser_3->clear();
        if (fname.length() == 0)
            mips::othersaveFile();
        else {
            QString plaintext;
            ofstream out(fname);
            plaintext = textEdit->toPlainText();
            text = string(plaintext.toLatin1().data());
            out << text;
        }
		if (fname.length() == 0)
			return;
        a.execute_parser(fname);
        string coename;
        for (unsigned int i = 0; i < fname.length() && fname[i] != '.'; ++i) {
            coename.append(1, fname[i]);
        }
        if (error_str.length() == 0) {
            ofstream binout(coename + ".coe");
            a.outputCoe(binout);
            binout.close();
            ifstream binfile(coename + ".coe");
            text.clear();
            while (!binfile.eof()) {
                string tmp;
                getline(binfile, tmp);
                text.append(tmp + "\n");
            }
            textBrowser_2->setPlainText(QString::fromStdString(text));
            if (text.length() > 0)
                textBrowser_3->setPlainText(QString::fromStdString(string("Build succeed!\nSaving to the bin file")));
            else {
                textBrowser_3->setPlainText(QString::fromStdString(string("Build Failed")));
            }
        }
        else {
            error_str.insert(0, "Build failed.\n");
            textBrowser_3->setPlainText(QString::fromStdString(error_str));
        }
        error_str.clear();

    }

    void bin2asm() {
        disassembler d;
        if (fname.length() == 0)
            mips::othersaveFile();
        else {
            QString plaintext;
            ofstream out(fname);
            plaintext = textEdit->toPlainText();
            text = string(plaintext.toLatin1().data());
            out << text;
        }
		if (fname.length() == 0)
			return;
        string asmname;
        for (unsigned int i = 0; i < fname.length() && fname[i] != '.'; ++i) {
            asmname.append(1, fname[i]);
        }
        ofstream asmout(asmname + ".asm");
        ifstream in(fname);
		int flag = 1;
		if (text.find("memory_initialization_radix") != string::npos)
			flag = 0;
		string tmp = d.execute(in, asmout, flag);
		if (tmp != "ok") {
			textBrowser_3->setPlainText(QString::fromStdString(tmp));
			return;
		}
        asmout.close();
        ifstream asmfile(asmname + ".asm");
        text.clear();
        while (!asmfile.eof()) {
            string tmp;
            getline(asmfile, tmp);
            text.append(tmp + "\n");
        }
        textBrowser_2->setPlainText(QString::fromStdString(text));
    }

    void backtext() {
        textEdit->undo();
    }

    void copytext() {
        textEdit->copy();
    }

    void paste2text() {
        textEdit->paste();
    }

    void show() {
        mw->show();
    }

    void openFile() {
        QString filename;
        filename = QFileDialog::getOpenFileName(this, tr("Open file"),
            "C:/", tr("Files(*.*)"));
        fname = string(filename.toLatin1().data());
		if (fname.length() == 0)
			return;
        ifstream in(fname);
        text.clear();
        while (!in.eof()) {
            string tmp;
            getline(in, tmp);
            text.append(tmp + "\n");
        }
        textEdit->setPlainText(QString::fromStdString(text));
    }

    void saveFile() {
        if (fname.length() == 0)
            mips::othersaveFile();
        else {
            QString plaintext;
            ofstream out(fname);
            plaintext = textEdit->toPlainText();
            text = string(plaintext.toLatin1().data());
            out << text;
        }

    }

    void othersaveFile() {
        QString filename;
        filename = QFileDialog::getSaveFileName(this, tr("Open file"),
            "C:/", tr("Files(*.bin, *asm, *coe)"));
        fname = string(filename.toLatin1().data());
        QString plaintext;
        ofstream out(fname);
        plaintext = textEdit->toPlainText();
        text = string(plaintext.toLatin1().data());
        out << text;
    }


private:
    QMainWindow *mw;
    string fname;
    string text;
    Highlighter *highlighter1;
	Highlighter *highlighter2;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mips m;
    m.show();
    return a.exec();
}
