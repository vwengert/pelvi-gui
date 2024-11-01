#include "dbinit.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

DbInit::DbInit(QObject* parent) : QObject(parent) {}

DbInit::~DbInit() {}

void DbInit::initializeDatabase(QSqlDatabase& db) {
    createTables(db);
    insertInitialData(db);
}

void DbInit::createTables(QSqlDatabase& db) {
    QSqlQuery query(db);
    query.exec("BEGIN;");
    query.exec("CREATE TABLE database (version TEXT not null);");
    query.exec("CREATE TABLE user (userid INTEGER primary key, name TEXT, lastname TEXT);");
    query.exec("CREATE TABLE rfid (rfid INTEGER primary key, userid INTEGER not null, FOREIGN KEY (userid) REFERENCES user (userid));");
    query.exec("CREATE TABLE axis (axisid INTEGER primary key, axisname TEXT, minvalue INTEGER, maxvalue INTEGER, refvalue INTEGER);");
    query.exec("CREATE TABLE device (deviceid INTEGER primary key, devicename TEXT);");
    query.exec("CREATE TABLE deviceaxis (deviceaxisid INTEGER primary key, deviceid INTEGER not null, axisid INTEGER not null, FOREIGN KEY (deviceid) REFERENCES device (deviceid), FOREIGN KEY (axisid) REFERENCES axis (axisid));");
    query.exec("CREATE TABLE positions (positionsid INTEGER primary key, userid INTEGER not null, positionnumber INTEGER, duration INTEGER, FOREIGN KEY (userid) REFERENCES user (userid));");
    query.exec("CREATE TABLE position (positionid INTEGER primary key, positionsid INTEGER not null, deviceaxisid INTEGER not null, position INTEGER not null, FOREIGN KEY (positionsid) REFERENCES positions (positionsid), FOREIGN KEY (deviceaxisid) REFERENCES deviceaxis (deviceaxisid));");
    query.exec("CREATE TABLE devicepower (devicepowerid INTEGER primary key, positionsid INTEGER not null, deviceid INTEGER not null, power INTEGER, FOREIGN KEY (positionsid) REFERENCES positions (positionsid), FOREIGN KEY (deviceid) REFERENCES device (deviceid));");
    query.exec("CREATE TABLE blockedarea (blockedareaid INTEGER primary key, userid INTEGER, FOREIGN KEY (userid) REFERENCES user (userid));");
    query.exec("CREATE TABLE blockedvalue (blockedvalueid INTEGER primary key, blockedareaid INTEGER not null, axisid INTEGER not null, minvalue INTEGER not null, maxvalue INTEGER not null, FOREIGN KEY (blockedareaid) REFERENCES blockedarea (blockedareaid), FOREIGN KEY (axisid) REFERENCES axis (axisid));");
    query.exec("INSERT INTO database VALUES(1);");
    query.exec("COMMIT;");
}

void DbInit::insertInitialData(QSqlDatabase& db) {
    QSqlQuery query(db);

    // Create default user
    query.exec("INSERT INTO user (name, lastname) VALUES('default', 'user');");
    int defaultuser = query.lastInsertId().toInt();

    // Create device for Back
    query.exec("INSERT INTO axis (axisname, minvalue, maxvalue, refvalue) VALUES('X', 0, 300, 0);");
    int axisx = query.lastInsertId().toInt();
    query.exec("INSERT INTO axis (axisname, minvalue, maxvalue, refvalue) VALUES('Y', 0, 470, 0);");
    int axisy = query.lastInsertId().toInt();
    query.exec("INSERT INTO device (devicename) VALUES('Back');");
    int deviceback = query.lastInsertId().toInt();
    query.prepare("INSERT INTO deviceaxis (deviceid, axisid) VALUES(?, ?);");
    query.addBindValue(deviceback);
    query.addBindValue(axisx);
    query.exec();
    int back_device_x = query.lastInsertId().toInt();
    query.addBindValue(deviceback);
    query.addBindValue(axisy);
    query.exec();
    int back_device_y = query.lastInsertId().toInt();

    // Create device for Seat
    query.exec("INSERT INTO axis (axisname, minvalue, maxvalue, refvalue) VALUES('Z', 0, 290, 0);");
    int axisz = query.lastInsertId().toInt();
    query.exec("INSERT INTO axis (axisname, minvalue, maxvalue, refvalue) VALUES('E0', 0, 180, 0);");
    int axise0 = query.lastInsertId().toInt();
    query.exec("INSERT INTO device (devicename) VALUES('Seat');");
    int deviceseat = query.lastInsertId().toInt();
    query.prepare("INSERT INTO deviceaxis (deviceid, axisid) VALUES(?, ?);");
    query.addBindValue(deviceseat);
    query.addBindValue(axisz);
    query.exec();
    int seat_device_z = query.lastInsertId().toInt();
    query.addBindValue(deviceseat);
    query.addBindValue(axise0);
    query.exec();
    int seat_device_e0 = query.lastInsertId().toInt();

    // Create device for Leg
    query.exec("INSERT INTO axis (axisname, minvalue, maxvalue, refvalue) VALUES('E1', 0, 180, 0);");
    int axise1 = query.lastInsertId().toInt();
    query.exec("INSERT INTO device (devicename) VALUES('Leg');");
    int deviceleg = query.lastInsertId().toInt();
    query.prepare("INSERT INTO deviceaxis (deviceid, axisid) VALUES(?, ?);");
    query.addBindValue(deviceleg);
    query.addBindValue(axise1);
    query.exec();
    int leg_device_e1 = query.lastInsertId().toInt();

    // Create device for Legrest
    query.exec("INSERT INTO axis (axisname, minvalue, maxvalue, refvalue) VALUES('D', 0, 1000, 0);");
    int axisd = query.lastInsertId().toInt();
    query.exec("INSERT INTO device (devicename) VALUES('Legrest');");
    int devicelegrest = query.lastInsertId().toInt();
    query.prepare("INSERT INTO deviceaxis (deviceid, axisid) VALUES(?, ?);");
    query.addBindValue(devicelegrest);
    query.addBindValue(axisd);
    query.exec();
    int legrest_device_d = query.lastInsertId().toInt();

    // Block area for heart in back device
    query.prepare("INSERT INTO blockedarea (userid) VALUES(?);");
    query.addBindValue(defaultuser);
    query.exec();
    int blockedarea = query.lastInsertId().toInt();
    query.prepare("INSERT INTO blockedvalue (blockedareaid, axisid, minvalue, maxvalue) VALUES(?, ?, ?, ?);");
    query.addBindValue(blockedarea);
    query.addBindValue(axisx);
    query.addBindValue(350);
    query.addBindValue(1000);
    query.exec();
    query.addBindValue(blockedarea);
    query.addBindValue(axisy);
    query.addBindValue(200);
    query.addBindValue(500);
    query.exec();

    // Set all axis to be on refvalue for default user
    query.prepare("INSERT INTO positions (userid, positionnumber, duration) VALUES(?, ?, ?);");
    query.addBindValue(defaultuser);
    query.addBindValue(10);
    query.addBindValue(0);
    query.exec();
    int positionsid = query.lastInsertId().toInt();
    query.prepare("INSERT INTO position (positionsid, deviceaxisid, position) VALUES(?, ?, ?);");
    query.addBindValue(positionsid);
    query.addBindValue(back_device_x);
    query.addBindValue(0);
    query.exec();
    query.addBindValue(positionsid);
    query.addBindValue(back_device_y);
    query.addBindValue(0);
    query.exec();
    query.addBindValue(positionsid);
    query.addBindValue(seat_device_z);
    query.addBindValue(0);
    query.exec();
    query.addBindValue(positionsid);
    query.addBindValue(seat_device_e0);
    query.addBindValue(0);
    query.exec();
    query.addBindValue(positionsid);
    query.addBindValue(leg_device_e1);
    query.addBindValue(0);
    query.exec();
    query.addBindValue(positionsid);
    query.addBindValue(legrest_device_d);
    query.addBindValue(0);
    query.exec();

    db.commit();
}