/* ***** BEGIN LICENSE BLOCK *****
 * Corentin Desfarges - Copyright (C) 2013 - 2015
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "dao.h"

DAO::DAO()
{
    data = "Callback function called";
}

vector<string> callback_v;

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    for(int i=0; i<argc; i++){
        callback_v.push_back(argv[i] ? argv[i] : "NULL");
    }
    return 0;
}


DAO::~DAO()
{  
}


void DAO::loadSchema()
{
    string create_script =
        "CREATE TABLE IF NOT EXISTS MAGASIN (                       \
            IDMAG INTEGER PRIMARY KEY NOT NULL,                     \
            NOMMAG VARCHAR                                          \
        );                                                          \
                                                                    \
        CREATE TABLE IF NOT EXISTS CATEGORIE (                      \
            IDCAT INTEGER PRIMARY KEY NOT NULL,                     \
            NOMCAT VARCHAR                                          \
        );                                                          \
                                                                    \
        CREATE TABLE IF NOT EXISTS OPERATION (                      \
            IDOP INTEGER PRIMARY KEY  NOT NULL ,                    \
            DATEOP DATE NOT NULL  DEFAULT (null) ,                  \
            VALEUR DOUBLE NOT NULL ,                                \
            TYPE VARCHAR NOT NULL ,                                 \
            DESCRIPTION VARCHAR NOT NULL ,                          \
            REFERENCE VARCHAR NOT NULL ,                            \
            MAG INTEGER NOT NULL ,                                  \
            CAT INTEGER NOT NULL ,                                  \
            RESTE DOUBLE,                                           \
            FOREIGN KEY (MAG) REFERENCES MAGASIN(IDMAG),            \
            FOREIGN KEY (CAT) REFERENCES CATEGORIE(IDCAT)           \
        );                                                          \
                                                                    \
        INSERT INTO MAGASIN (IDMAG, NOMMAG) VALUES (-1,\"\");       \
        INSERT INTO CATEGORIE (IDCAT, NOMCAT) VALUES (-1,\"\");     ";

    this->open();
    this->execute(create_script);
    this->close();
}


void DAO::open()
{
    rc = sqlite3_open("bdd.db", &db);
    callback_v.clear();
}


void DAO::execute(string req)
{
    rc = sqlite3_exec(db, req.c_str(), callback, (void*)data, &zErrMsg);

    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        fprintf(stdout,req.c_str());
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout,req.c_str());
    }
}


void DAO::execute(char* req)
{
    rc = sqlite3_exec(db, req, callback, (void*)data, &zErrMsg);

    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        fprintf(stdout,req);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout,req);
    }
}


void DAO::close()
{
    sqlite3_close(db);
}

/*############################ UTILITIES ############################*/

double DAO::getReste(){
    this->open();
    double reste = 0;
    string rq = "SELECT RESTE FROM OPERATION WHERE IDOP=(SELECT MAX(IDOP) FROM OPERATION);";

    this->execute(rq);

    if(callback_v.size() > 0)
        reste = Utilities::string2double(callback_v[0]);

    this->close();
    return reste;
}

/*############################ SELECT ############################*/

Categorie DAO::getCategorie(string knewColName, string knewValue)
{
    this->open();
    string rq = "SELECT IDCAT, NOMCAT FROM CATEGORIE WHERE "+knewColName+" LIKE '"+knewValue+"';";
    this->execute(rq);

    Categorie categorie;
    categorie.setId(atoi(callback_v[0].c_str()));
    categorie.setNom(callback_v[1]);

    this->close();
    return categorie;
}


Magasin DAO::getMagasin(string knewColName, string knewValue)
{
    this->open();
    string rq = "SELECT IDMAG, NOMMAG FROM MAGASIN WHERE "+knewColName+" LIKE '"+knewValue+"';";

    this->execute(rq);

    Magasin magasin;
    magasin.setId(atoi(callback_v[0].c_str()));
    magasin.setNom(callback_v[1]);

    this->close();
    return magasin;
}


string DAO::getTotalAllOperations()
{
    this->open();
    string rq = "SELECT COUNT(*), SUM(VALEUR) FROM OPERATION INNER JOIN MAGASIN ON OPERATION.MAG = MAGASIN.IDMAG INNER JOIN CATEGORIE ON OPERATION.CAT = CATEGORIE.IDCAT;";

    this->execute(rq);

    this->close();
    return (Utilities::string2int(callback_v[0])==0) ? "0" : callback_v[1].c_str();
}


string DAO::getTotalOperationsSelected(QDate d1, QDate d2, string nomMag, string nomCat, string typePmt)
{
    this->open();

    if(nomCat=="")
        nomCat="%%";
    if(nomMag=="")
        nomMag="%%";
    if(typePmt=="")
        typePmt="%%";

    string rq = "SELECT COUNT(*), SUM(VALEUR) FROM OPERATION INNER JOIN MAGASIN ON OPERATION.MAG = MAGASIN.IDMAG INNER JOIN CATEGORIE ON OPERATION.CAT = CATEGORIE.IDCAT WHERE NOMMAG LIKE '"+nomMag+"' AND NOMCAT LIKE '"+nomCat.c_str()+"' AND TYPE LIKE '"+typePmt+"' AND DATEOP BETWEEN ('"+d1.toString("yyyy-MM-dd").toStdString()+"') AND ('"+d2.toString("yyyy-MM-dd").toStdString()+"');";
    this->execute(rq.c_str());

    this->close();
    return (Utilities::string2int(callback_v[0])==0) ? "0" : callback_v[1].c_str();
}


vector<Operation> DAO::getOperationsSelected(QDate d1, QDate d2, string nomMag, string nomCat, string typePmt)
{
    this->open();
    vector<Operation > result;

    if(nomCat=="")
        nomCat="%%";
    if(nomMag=="")
        nomMag="%%";
    if(typePmt=="")
        typePmt="%%";

    string rq = "SELECT IDOP,DATEOP,VALEUR,TYPE,DESCRIPTION,REFERENCE,IDMAG,NOMMAG,IDCAT,NOMCAT,RESTE FROM OPERATION INNER JOIN MAGASIN ON OPERATION.MAG = MAGASIN.IDMAG INNER JOIN CATEGORIE ON OPERATION.CAT = CATEGORIE.IDCAT WHERE NOMMAG LIKE '"+nomMag+"' AND NOMCAT LIKE '"+nomCat.c_str()+"' AND TYPE LIKE '"+typePmt+"' AND DATEOP BETWEEN ('"+d1.toString("yyyy-MM-dd").toStdString()+"') AND ('"+d2.toString("yyyy-MM-dd").toStdString()+"') ORDER BY IDOP DESC;";
    this->execute(rq.c_str());

    for(int i = 0 ; i < callback_v.size();){
        Operation operation;
        operation.setId(atoi(callback_v[i++].c_str()));
        operation.setDate(QDate::fromString(callback_v[i++].c_str(),"yyyy-MM-dd"));
        operation.setValue(stod(callback_v[i++]));
        operation.setTypePmt(callback_v[i++]);
        operation.setDescription(callback_v[i++]);
        operation.setReference(callback_v[i++]);
        int id_mag = Utilities::string2int(callback_v[(i++)]);
        operation.setMagasin(Magasin(id_mag,callback_v[i++]));
        int id_cat = Utilities::string2int(callback_v[(i++)]);
        operation.setCategorie(Categorie(id_cat,callback_v[i++]));
        operation.setReste(stod(callback_v[i++]));
        result.push_back(operation);
    }

    this->close();
    return result;
}


Operation DAO::getOperation(string knewColName, string knewValue)
{
    this->open();

    string rq = "SELECT IDOP,DATEOP,VALEUR,TYPE,DESCRIPTION,REFERENCE,IDMAG,NOMMAG,IDCAT,NOMCAT,RESTE FROM OPERATION INNER JOIN MAGASIN ON OPERATION.MAG = MAGASIN.IDMAG INNER JOIN CATEGORIE ON OPERATION.CAT = CATEGORIE.IDCAT WHERE "+knewColName+" LIKE '"+knewValue+"';";
    this->execute(rq);

    Operation operation;
    operation.setId(atoi(callback_v[0].c_str()));
    operation.setDate(QDate::fromString(callback_v[1].c_str(),"yyyy-MM-dd"));
    operation.setValue(stod(callback_v[2]));
    operation.setTypePmt(callback_v[3]);
    operation.setDescription(callback_v[4]);
    operation.setReference(callback_v[5]);
    int id_mag = Utilities::string2int(callback_v[(6)]);
    operation.setMagasin(Magasin(id_mag,callback_v[7]));
    int id_cat = Utilities::string2int(callback_v[(8)]);
    operation.setCategorie(Categorie(id_cat,callback_v[9]));
    operation.setReste(10);

    this->close();
    return operation;
}


vector<Categorie> DAO::getAllCategories()
{
    this->open();
    vector<Categorie > result;
    string rq = "SELECT * FROM CATEGORIE;";

    this->execute(rq);

    for(int i = 0; i < callback_v.size() ;){
        Categorie categorie;
        categorie.setId(atoi(callback_v[i++].c_str()));
        categorie.setNom(callback_v[i++]);
        result.push_back(categorie);
    }

    this->close();
    return result;
}


vector<Magasin> DAO::getAllMagasins()
{
    this->open();
    vector<Magasin > result;
    string rq = "SELECT * FROM MAGASIN;";

    this->execute(rq);

    for(int i = 0 ; i < callback_v.size();){
        Magasin magasin;
        magasin.setId(atoi(callback_v[i++].c_str()));
        magasin.setNom(callback_v[i++]);
        result.push_back(magasin);
    }

    this->close();
    return result;
}


vector<Operation> DAO::getAllOperations()
{
    this->open();
    vector<Operation > result;
    string rq = "SELECT IDOP,DATEOP,VALEUR,TYPE,DESCRIPTION,REFERENCE,IDMAG,NOMMAG,IDCAT,NOMCAT,RESTE FROM OPERATION INNER JOIN MAGASIN ON OPERATION.MAG = MAGASIN.IDMAG INNER JOIN CATEGORIE ON OPERATION.CAT = CATEGORIE.IDCAT ORDER BY IDOP DESC;";
    std::cout << rq << std::endl;

    this->execute(rq);

    for(int i = 0 ; i < callback_v.size();){
        Operation operation;
        operation.setId(atoi(callback_v[i++].c_str()));
        operation.setDate(QDate::fromString(callback_v[i++].c_str(),"yyyy-MM-dd"));
        operation.setValue(stod(callback_v[i++]));
        operation.setTypePmt(callback_v[i++]);
        operation.setDescription(callback_v[i++]);
        operation.setReference(callback_v[i++]);
        int id_mag = Utilities::string2int(callback_v[(i++)]);
        operation.setMagasin(Magasin(id_mag,callback_v[i++]));
        int id_cat = Utilities::string2int(callback_v[(i++)]);
        operation.setCategorie(Categorie(id_cat,callback_v[i++]));
        operation.setReste(stod(callback_v[i++]));
        result.push_back(operation);
    }

    this->close();
    return result;
}

/*############################ INSERT ############################*/

void DAO::insertOperation(string date, string value, string typePmt, string description,
                          string reference, string magasin, string categorie, string reste)
{
    date = Utilities::escapeString(date);
    value = Utilities::escapeString(value);
    description = Utilities::escapeString(description);
    reference = Utilities::escapeString(reference);

    string idmag = Utilities::nb2string(getMagasin("NOMMAG",magasin).getId());
    string idcat = Utilities::nb2string(getCategorie("NOMCAT",categorie).getId());

    this->open();

    string rq = "INSERT INTO OPERATION (DATEOP,VALEUR,TYPE,DESCRIPTION,REFERENCE,MAG,CAT,RESTE) VALUES ('"+date+"',"+value+",'"+typePmt+"','"+description+"','"+reference+"',"+idmag+","+idcat+","+reste+");";
    this->execute(rq);

    this->close();
}


void DAO::insertMagasin(string nom)
{
    this->open();
    nom = Utilities::escapeString(nom);

    string rq = "INSERT INTO MAGASIN (NOMMAG) VALUES ('"+nom+"');";
    this->execute(rq);

    this->close();
}


void DAO::insertCategorie(string nom)
{
    this->open();
    nom = Utilities::escapeString(nom);

    string rq = "INSERT INTO CATEGORIE (NOMCAT) VALUES ('"+nom+"');";
    this->execute(rq);

    this->close();
}

/*############################ UPDATE ############################*/

void DAO::updateOperation(string id, string col, string value)
{
    this->open();
    value = Utilities::escapeString(value);

    string rq = "UPDATE OPERATION SET "+col+"='"+value+"' WHERE IDOP="+id+";";
    this->execute(rq);

    this->close();
}


void DAO::updateOperation(string id, string date, string value, string description,
                          string reference, string reste)
{
    this->open();
    date = Utilities::escapeString(date);
    value = Utilities::escapeString(value);
    description = Utilities::escapeString(description);
    reference = Utilities::escapeString(reference);

    string rq = "UPDATE OPERATION SET DATEOP='"+date+"',VALEUR='"+value+"',DESCRIPTION='"+description+"',REFERENCE='"+reference+"',RESTE='"+reste+"' WHERE IDOP="+id+";";
    this->execute(rq);

    this->close();
}


void DAO::updateMagasin(string id, string nom)
{
    this->open();
    nom = Utilities::escapeString(nom);

    string rq = "UPDATE MAGASIN SET NOMMAG='"+nom+"' WHERE IDMAG="+id+";";
    this->execute(rq);

    this->close();
}


void DAO::updateCategorie(string id, string nom)
{
    this->open();
    nom = Utilities::escapeString(nom);

    string rq = "UPDATE CATEGORIE SET NOMCAT='"+nom+"' WHERE IDCAT="+id+";";
    this->execute(rq);

    this->close();
}


void DAO::updateOperations(string idBase, string diff)
{
    this->open();

    string rq = "UPDATE OPERATION SET RESTE=RESTE-("+diff+") WHERE IDOP >="+idBase+";";
    this->execute(rq);

    this->close();
}

/*############################ DELETE ############################*/

void DAO::removeOperation(string id)
{
    this->open();
    string rq = "DELETE FROM OPERATION WHERE IDOP="+id+";";

    this->execute(rq);

    this->close();
}


void DAO::removeMagasin(string id)
{
    this->open();
    string rq = "DELETE FROM MAGASIN WHERE IDMAG="+id+";";

    this->execute(rq);

    rq = "UPDATE OPERATION SET MAG=0 WHERE MAG="+id+";";

    this->execute(rq);

    this->close();
}


void DAO::removeCategorie(string id)
{
    this->open();
    string rq = "DELETE FROM CATEGORIE WHERE IDCAT="+id+";";

    this->execute(rq);

    rq = "UPDATE OPERATION SET CAT=0 WHERE CAT="+id+";";

    this->execute(rq);

    this->close();
}
