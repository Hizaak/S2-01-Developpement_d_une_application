#include "database.h"
#include <QDebug>

Database::Database()
{

}

bool Database::openDataBase() {
    qDebug() << "";
    mydb = QSqlDatabase::addDatabase(CONNECT_TYPE);
    qDebug() << "";
    if (mydb.databaseName() != DATABASE_NAME) {
        mydb.setDatabaseName(DATABASE_NAME);
    }
    qDebug() << "";

    return mydb.open();
}

void Database::closeDataBase() {
    mydb.close();
}
