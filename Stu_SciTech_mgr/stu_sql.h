#ifndef STU_SQL_H
#define STU_SQL_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>


class stu_sql : public QObject
{
    Q_OBJECT
public:
    explicit stu_sql(QObject *parent = nullptr);

    static bool Connection();
    static void CloseConnection();

private:
    static QSqlDatabase db;
    static QSqlQuery * sql;

signals:

};

#endif // STU_SQL_H
