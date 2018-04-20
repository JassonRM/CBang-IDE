//
// Created by marco on 19/04/18.
//

#ifndef CFACTORIAL_IDE_TEXTEDITOR_H
#define CFACTORIAL_IDE_TEXTEDITOR_H

#include <QtWidgets/QPlainTextEdit>
#include <QtGui/QTextBlock>
#include <QtGui/QPainter>

class TextEditor : public QPlainTextEdit
{
Q_OBJECT

public:
    TextEditor(QWidget *parent = 0);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect &, int);

private:
    QWidget *lineNumberArea;
};


#endif //CFACTORIAL_IDE_TEXTEDITOR_H


#ifndef CFACTORIAL_IDE_LINENUMBERAREA_H
#define CFACTORIAL_IDE_LINENUMBERAREA_H

#include <QtWidgets/QWidget>


class LineNumberArea : public QWidget
{
public:
    LineNumberArea(TextEditor* editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const override {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    TextEditor* codeEditor;
};


#endif //CFACTORIAL_IDE_LINENUMBERAREA_H