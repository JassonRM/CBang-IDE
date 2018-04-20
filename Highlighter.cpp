//
// Created by marco on 19/04/18.
//

#include "Highlighter.h"

Highlighter::Highlighter(QTextDocument *parent)
        : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\bchar\\b" << "\\bfloat\\b"
                    << "\\bdouble\\b" <<"\\bint\\b"
                    << "\\blong\\b" << "\\bstruct\\b";
    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    numericFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegularExpression("(\\d+\\.*\\d*)");;
    rule.format = numericFormat;
    highlightingRules.append(rule);

    quotationFormat.setFontWeight(QFont::Bold);
    quotationFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegularExpression("\'.*\'");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    functionFormat.setFontItalic(true);
    functionFormat.setForeground(Qt::blue);
    rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);
    singleLineCommentFormat.setForeground(Qt::red);
    rule.pattern = QRegularExpression("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);


    commentStartExpression = QRegularExpression("/\\*");
    commentEndExpression = QRegularExpression("\\*/");
}

void Highlighter::highlightBlock(const QString &text) {
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}