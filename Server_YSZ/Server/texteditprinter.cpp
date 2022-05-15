#include "texteditprinter.h"


TextEditPrinter::TextEditPrinter(Subject *sub, QTextEdit *edit)
    :MessagePrint(sub),_edit(edit)
{

}

void TextEditPrinter::PrintMsg(QString msg)
{
    this->_edit->append("\n" + msg);
}

void TextEditPrinter::PrintError(QString error_msg)
{
    QColor original_color = this->_edit->textColor();
    this->_edit->setTextColor(QColor().red());
    this->_edit->append("\n" + error_msg);
    this->_edit->setTextColor(original_color);
}

void TextEditPrinter::Clear()
{
    this->_edit->setText("");
}
