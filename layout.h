/********************************************************************************
** Form generated from reading UI file 'layout.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef LAYOUT_H
#define LAYOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <QSyntaxHighlighter>

QT_BEGIN_NAMESPACE

class Ui_Mips_Assembler
{
public:
    QAction *new_menu;
    QAction *open_menu;
    QAction *save_menu;
    QAction *othersave_menu;
    QAction *exit_menu;
    QAction *back_menu;
    QAction *copy_menu;
    QAction *paste_menu;
    QAction *bin_menu;
    QAction *coe_menu;
    QAction *disasm_menu;
    QAction *about_menu;
    QWidget *centralWidget;
    QTextBrowser *textBrowser_2;
    QTextBrowser *textBrowser_3;
    QTextEdit *textEdit;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Mips_Assembler)
    {
        if (Mips_Assembler->objectName().isEmpty())
            Mips_Assembler->setObjectName(QStringLiteral("Mips_Assembler"));
        Mips_Assembler->resize(1058, 746);
        new_menu = new QAction(Mips_Assembler);
        new_menu->setObjectName(QStringLiteral("new_menu"));
        open_menu = new QAction(Mips_Assembler);
        open_menu->setObjectName(QStringLiteral("open_menu"));
        save_menu = new QAction(Mips_Assembler);
        save_menu->setObjectName(QStringLiteral("save_menu"));
        othersave_menu = new QAction(Mips_Assembler);
        othersave_menu->setObjectName(QStringLiteral("othersave_menu"));
        exit_menu = new QAction(Mips_Assembler);
        exit_menu->setObjectName(QStringLiteral("exit_menu"));
        back_menu = new QAction(Mips_Assembler);
        back_menu->setObjectName(QStringLiteral("back_menu"));
        copy_menu = new QAction(Mips_Assembler);
        copy_menu->setObjectName(QStringLiteral("copy_menu"));
        paste_menu = new QAction(Mips_Assembler);
        paste_menu->setObjectName(QStringLiteral("paste_menu"));
        bin_menu = new QAction(Mips_Assembler);
        bin_menu->setObjectName(QStringLiteral("bin_menu"));
        coe_menu = new QAction(Mips_Assembler);
        coe_menu->setObjectName(QStringLiteral("coe_menu"));
        disasm_menu = new QAction(Mips_Assembler);
        disasm_menu->setObjectName(QStringLiteral("disasm_menu"));
        about_menu = new QAction(Mips_Assembler);
        about_menu->setObjectName(QStringLiteral("about_menu"));
        centralWidget = new QWidget(Mips_Assembler);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        textBrowser_2 = new QTextBrowser(centralWidget);
        textBrowser_2->setObjectName(QStringLiteral("textBrowser_2"));
        textBrowser_2->setGeometry(QRect(540, 0, 511, 531));
        textBrowser_3 = new QTextBrowser(centralWidget);
        textBrowser_3->setObjectName(QStringLiteral("textBrowser_3"));
        textBrowser_3->setGeometry(QRect(0, 530, 1061, 151));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(10, 0, 511, 531));
        Mips_Assembler->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Mips_Assembler);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1058, 26));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QStringLiteral("menu_3"));
        menu_4 = new QMenu(menuBar);
        menu_4->setObjectName(QStringLiteral("menu_4"));
        Mips_Assembler->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Mips_Assembler);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Mips_Assembler->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Mips_Assembler);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Mips_Assembler->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menuBar->addAction(menu_4->menuAction());
        menu->addAction(new_menu);
        menu->addAction(open_menu);
        menu->addAction(save_menu);
        menu->addAction(othersave_menu);
        menu->addAction(exit_menu);
        menu_2->addAction(back_menu);
        menu_2->addAction(copy_menu);
        menu_2->addAction(paste_menu);
        menu_3->addAction(bin_menu);
        menu_3->addAction(coe_menu);
        menu_3->addAction(disasm_menu);
        menu_4->addAction(about_menu);

        retranslateUi(Mips_Assembler);

        QMetaObject::connectSlotsByName(Mips_Assembler);
    } // setupUi

    void retranslateUi(QMainWindow *Mips_Assembler)
    {
        Mips_Assembler->setWindowTitle(QApplication::translate("Mips_Assembler", "Mips_Assembler", 0));
        new_menu->setText(QApplication::translate("Mips_Assembler", "\346\226\260\345\273\272", 0));
        new_menu->setShortcut(QApplication::translate("Mips_Assembler", "Ctrl+N", 0));
        open_menu->setText(QApplication::translate("Mips_Assembler", "\346\211\223\345\274\200", 0));
        open_menu->setShortcut(QApplication::translate("Mips_Assembler", "Ctrl+O", 0));
        save_menu->setText(QApplication::translate("Mips_Assembler", "\344\277\235\345\255\230", 0));
        save_menu->setShortcut(QApplication::translate("Mips_Assembler", "Ctrl+S", 0));
        othersave_menu->setText(QApplication::translate("Mips_Assembler", "\345\217\246\345\255\230\344\270\272", 0));
        othersave_menu->setShortcut(QApplication::translate("Mips_Assembler", "Ctrl+Shift+S", 0));
        exit_menu->setText(QApplication::translate("Mips_Assembler", "exit", 0));
        exit_menu->setShortcut(QApplication::translate("Mips_Assembler", "Ctrl+E", 0));
        back_menu->setText(QApplication::translate("Mips_Assembler", "\346\222\244\351\224\200", 0));
        back_menu->setShortcut(QApplication::translate("Mips_Assembler", "Ctrl+Z", 0));
        copy_menu->setText(QApplication::translate("Mips_Assembler", "\345\244\215\345\210\266", 0));
        copy_menu->setShortcut(QApplication::translate("Mips_Assembler", "Ctrl+C", 0));
        paste_menu->setText(QApplication::translate("Mips_Assembler", "\347\262\230\350\264\264", 0));
        paste_menu->setShortcut(QApplication::translate("Mips_Assembler", "Ctrl+V", 0));
        bin_menu->setText(QApplication::translate("Mips_Assembler", "\344\272\214\350\277\233\345\210\266\346\226\207\344\273\266(B)", 0));
        bin_menu->setShortcut(QApplication::translate("Mips_Assembler", "F9", 0));
        coe_menu->setText(QApplication::translate("Mips_Assembler", "coe\346\226\207\344\273\266(C)", 0));
        coe_menu->setShortcut(QApplication::translate("Mips_Assembler", "F10", 0));
        disasm_menu->setText(QApplication::translate("Mips_Assembler", "\345\217\215\346\261\207\347\274\226(A)", 0));
        disasm_menu->setShortcut(QApplication::translate("Mips_Assembler", "F11", 0));
        about_menu->setText(QApplication::translate("Mips_Assembler", "about"));
        menu->setTitle(QApplication::translate("Mips_Assembler", "\346\226\207\344\273\266", 0));
        menu_2->setTitle(QApplication::translate("Mips_Assembler", "\347\274\226\350\276\221", 0));
        menu_3->setTitle(QApplication::translate("Mips_Assembler", "\346\236\204\345\273\272", 0));
        menu_4->setTitle(QApplication::translate("Mips_Assembler", "\345\205\263\344\272\216", 0));
        textEdit->setVisible(true);
    } // retranslateUi

};


class Highlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    Highlighter(QTextDocument *parent = 0) : QSyntaxHighlighter(parent)
    {
        HighlightingRule rule;

        instFormat.setForeground(Qt::darkRed);
        instFormat.setFontWeight(QFont::Bold);
        QStringList instPatterns;
        instPatterns << "\\bsll\\b" << "\\bsrl\\b" << "\\bsra\\b"
            << "\\bjalr\\b" << "\\badd\\b" << "\\baddu\\b" << "\\bandu\\b"
            << "\\bsub\\b" << "\\bsubu\\b" << "\\bnor\\b"
            << "\\bor\\b" << "\\bxor\\b" << "\\boperator\\b"
            << "\\bslt\\b" << "\\bsltu\\b" << "\\bmfhi\\b"
            << "\\bmflo\\b" << "\\bmfc0\\b" << "\\bdiv\\b"
            << "\\bdivu\\b" << "\\bmult\\b" << "\\bmultu\\b"
            << "\\bmtc0\\b" << "\\bjr\\b" << "\\bmthi\\b"
            << "\\bmtlo\\b" << "\\bbltz\\b" << "\\bbgez\\b"
            << "\\bbeq\\b" << "\\bbne\\b" << "\\bblez\\b"
            << "\\bbgtz\\b" << "\\baddi\\b" << "\\baddiu\\b"
            << "\\bslti\\b" << "\\bandi\\b" << "\\bori\\b"
            << "\\bxori\\b" << "\\blui\\b" << "\\blb\\b"
            << "\\blh\\b" << "\\blw\\b" << "\\blbu\\b"
            << "\\blhu\\b" << "\\bsb\\b" << "\\bsh\\b"
            << "\\bsw\\b" << "\\bj\\b" << "\\bjal\\b"
            << "\\beret\\b" << "\\bsyscall\\b" << "\\bbreak\\b";
        foreach(const QString &pattern, instPatterns) {
            rule.pattern = QRegExp(pattern);
            rule.format = instFormat;
            highlightingRules.append(rule);
        }

        regFormat.setForeground(Qt::darkYellow);
        regFormat.setFontWeight(QFont::Bold);
        QStringList regPatterns;
        regPatterns << "\\bzero\\b" << "\\bat\\b" << "\\bv0\\b"
            << "\\bv1\\b" << "\\ba0\\b" << "\\ba1\\b"
            << "\\ba2\\b" << "\\ba3\\b" << "\\bt0\\b"
            << "\\bt1\\b" << "\\bt2\\b" << "\\bt3\\b"
            << "\\bt4\\b" << "\\bt5\\b" << "\\bt6\\b"
            << "\\bt7\\b" << "\\bt8\\b" << "\\bs0\\b"
            << "\\bs1\\b" << "\\bs2\\b" << "\\bs3\\b"
            << "\\bs4\\b" << "\\bs5\\b" << "\\bs6\\b"
            << "\\bs7\\b" << "\\bt8\\b" << "\\bt9\\b"
            << "\\bk0\\b" << "\\bk1\\b" << "\\bgp\\b"
            << "\\bsp\\b" << "\\bfp\\b" << "\\bra\\b";
        foreach(const QString &pattern, regPatterns) {
            rule.pattern = QRegExp(pattern);
            rule.format = regFormat;
            highlightingRules.append(rule);
        }

        baseFormat.setForeground(Qt::darkBlue);
        baseFormat.setFontItalic(true);
        baseFormat.setFontWeight(QFont::Bold);
        QStringList basePatterns;
        basePatterns << "\\bbaseAddre\\b" << "\\bdataAddre\\b" << "\\bbyte\\b"
            << "\\bhalf\\b" << "\\bword\\b";
        foreach(const QString &pattern, basePatterns) {
            rule.pattern = QRegExp(pattern);
            rule.format = baseFormat;
            highlightingRules.append(rule);
        }

		coeFormat.setForeground(Qt::red);
		rule.pattern = QRegExp("\\bmemory_initialization_radix\\b");
		rule.format = coeFormat;
		highlightingRules.append(rule);
		rule.pattern = QRegExp("\\bmemory_initialization_vector\\b");
		rule.format = coeFormat;
		highlightingRules.append(rule);

        singleLineCommentFormat.setForeground(Qt::gray);
        rule.pattern = QRegExp("//[^\n]*");
        rule.format = singleLineCommentFormat;
        highlightingRules.append(rule);

        multiLineCommentFormat.setForeground(Qt::gray);

        commentStartExpression = QRegExp("/\\*");
        commentEndExpression = QRegExp("\\*/");
    }
protected:
    void highlightBlock(const QString &text) {
        foreach(const HighlightingRule &rule, highlightingRules) {
            QRegExp expression(rule.pattern);
            int index = expression.indexIn(text);
            while (index >= 0) {
                int length = expression.matchedLength();
                setFormat(index, length, rule.format);
                index = expression.indexIn(text, index + length);
            }
        }
        setCurrentBlockState(0);
        int startIndex = 0;
        if (previousBlockState() != 1)
            startIndex = commentStartExpression.indexIn(text);
        while (startIndex >= 0) {
            int endIndex = commentEndExpression.indexIn(text, startIndex);
            int commentLength;
            if (endIndex == -1) {
                setCurrentBlockState(1);
                commentLength = text.length() - startIndex;
            }
            else {
                commentLength = endIndex - startIndex
                    + commentEndExpression.matchedLength();
            }
            setFormat(startIndex, commentLength, multiLineCommentFormat);
            startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
        }
    }

private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    QRegExp commentStartExpression;
    QRegExp commentEndExpression;

    QTextCharFormat instFormat;
    QTextCharFormat regFormat;
    QTextCharFormat baseFormat;
	QTextCharFormat coeFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
};

namespace Ui {
    class Mips_Assembler : public Ui_Mips_Assembler {};
} // namespace Ui

QT_END_NAMESPACE

#endif // LAYOUT_H
