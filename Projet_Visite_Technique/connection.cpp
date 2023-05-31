#include "connection.h"

connection::connection(){}

bool connection::createconnect()
{
bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("AutoTech");
db.setUserName("jawher");//inserer nom de l'utilisateur
db.setPassword("jawher");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;
return  test;
}
