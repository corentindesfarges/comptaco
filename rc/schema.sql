CREATE TABLE IF NOT EXISTS"MAGASIN" (
	"IDMAG" INTEGER PRIMARY KEY NOT NULL,
	"NOMMAG" VARCHAR NOT NULL
);

CREATE TABLE IF NOT EXISTS "CATEGORIE" (
	"IDCAT" INTEGER PRIMARY KEY NOT NULL,
	"NOMCAT" VARCHAR NOT NULL
);

CREATE TABLE IF NOT EXISTS "OPERATION" (
	"IDOP" INTEGER PRIMARY KEY  NOT NULL ,
	"DATEOP" DATE NOT NULL  DEFAULT (null) ,
	"VALEUR" DOUBLE NOT NULL ,
	"TYPE" VARCHAR NOT NULL ,
	"DESCRIPTION" VARCHAR NOT NULL ,
	"REFERENCE" VARCHAR NOT NULL ,
	"MAG" INTEGER NOT NULL ,
	"CAT" INTEGER NOT NULL ,
	"RESTE" DOUBLE,
	FOREIGN KEY (MAG) REFERENCES MAGASIN(IDMAG),
	FOREIGN KEY (CAT) REFERENCES CATEGORIE(IDCAT)
);

INSERT INTO MAGASIN (IDMAG, NOMMAG) VALUES (-1,"");
INSERT INTO CATEGORIE (IDCAT, NOMCAT) VALUES (-1,"");