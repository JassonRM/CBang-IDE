//
// Created by marco on 19/04/18.
//

#ifndef CFACTORIAL_IDE_HIGHLIGHTER_H
#define CFACTORIAL_IDE_HIGHLIGHTER_H


#include <QtGui/QSyntaxHighlighter>
#include <QtCore/QRegularExpression>

class Highlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    Highlighter(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text) override;

private:
    struct HighlightingRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    QRegularExpression commentStartExpression;
    QRegularExpression commentEndExpression;

    QTextCharFormat keywordFormat;
    QTextCharFormat numericFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;

};
#endif //CFACTORIAL_IDE_HIGHLIGHTER_H
