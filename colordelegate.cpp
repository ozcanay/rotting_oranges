#include "colordelegate.h"
#include <QDebug>
#include <QPainter>

void ColorDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();
    QBrush color;

    if(index.model()->data(index, Qt::DisplayRole) == "2") {
        color  = QBrush(Qt::red);
    } else if(index.model()->data(index, Qt::DisplayRole) == "1") {
        color  = QBrush(Qt::green);
    } else if(index.model()->data(index, Qt::DisplayRole) == "0") {
        color  = QBrush(Qt::yellow);
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }

    painter->fillRect(option.rect, color);
    painter->restore();
}
