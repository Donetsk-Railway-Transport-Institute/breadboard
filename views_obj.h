//
// Created by User on 16.02.2018.
//

#ifndef BREADBOARD_VIEWS_OBJ_H
#define BREADBOARD_VIEWS_OBJ_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>
#include <QtWidgets/QStyledItemDelegate>
#include <QtGui/QMouseEvent>
#include <QtGlobal>
#include <QtWidgets/QScrollBar>
#include <QPainter>

#include "startup_config.h"
#include "environment.h"
#include "rw_view_obj.h"

QT_BEGIN_NAMESPACE

//модель таблицы,
//содержит объекты отображения "клетки" в виде указателей в массиве cached
class views_obj : public QAbstractTableModel
{
Q_OBJECT

public:
    explicit views_obj(QObject *parent,int rows,int columns) :
            QAbstractTableModel(parent), count_row(rows), count_column(columns){
        //по умолчанию все указатели на объекты нулевые
        for(int i=0;i<count_row*count_column;i++) cached.push_back(nullptr);
    }

    int rowCount(const QModelIndex &parent) const override {
        Q_UNUSED(parent);
        return count_row;
    }

    int columnCount(const QModelIndex &parent) const override {
        Q_UNUSED(parent);
        return count_column;
    }

    //виртуальная функция, возвращает данные "клетки",
    //координаты которой задаются параметром index из массива cached
    QVariant data(const QModelIndex &index, int role) const override {
        if (!index.isValid()) return QVariant();
        if (index.row() >= count_row || index.row() < 0) return QVariant();
        if (index.column() >= count_column || index.column() < 0) return QVariant();
        if (role == Qt::DisplayRole)
            return QVariant::fromValue(cached[index.row()*count_column+index.column()]);
        return QVariant();
    }

    //установка нового значения данных "клетки"
    //координаты которой задаются параметром index
    bool setData(const QModelIndex &index, const QVariant &value, int role) override {
        if (index.isValid() && role == Qt::EditRole) {
            cached[index.row()*count_column+index.column()] = value.value<one_cell_base*>();
            //перерисовка новых данных
            dataChanged(index,index);
            return true;
        }
        return false;
    }

private:
    //объекты отображения "клетки" в виде указателей на one_cell_base
    QVector<one_cell_base*> cached;

    //общее количество колонок и рядов (количество "клеток")
    int count_row;
    int count_column;
};

class ImageDelegate: public QStyledItemDelegate
{
public:
    views_obj* views;
    explicit ImageDelegate(QWidget *parent, int c_row, int c_column) :
            QStyledItemDelegate(parent), views(new views_obj(parent,c_row,c_column)){}

    void paint(QPainter * painter,const QStyleOptionViewItem & option, const QModelIndex & index ) const final {
        QStyleOptionGraphicsItem opt = QStyleOptionGraphicsItem();
        auto obj = views->data(index,Qt::DisplayRole).value<one_cell_base*>();
        //если объект существует, а не создан конструктором класса views_obj по умолчанию
        if (obj) obj->paint_object(painter,option.rect);
    }
};

#endif //BREADBOARD_VIEWS_OBJ_H
