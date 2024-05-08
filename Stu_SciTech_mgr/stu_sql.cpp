#include "stu_sql.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>

QSqlDatabase stu_sql::db = QSqlDatabase::addDatabase("QODBC");
//qsqkquery * databse::sql = null;

stu_sql::stu_sql(QObject *parent)
    : QObject{parent}
{
}


bool stu_sql::Connection()
{
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("data_base");
    db.setUserName("root");
    db.setPassword("root");
    if(!db.open())
    {
        qDebug() << "Error!";
        qDebug() << db.lastError().text();
        return false;
    }
    else {
        qDebug() << "connection success!";
        return true;
    }
}

void stu_sql::CloseConnection()
{
    db.close();
}
