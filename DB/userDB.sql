DROP DATABASE IF EXISTS userDB;
CREATE DATABASE userDB;
USE userDB;
SET NAMES utf8;

CREATE TABLE IF NOT EXISTS users(
	user_id INT AUTO_INCREMENT PRIMARY KEY,
	username VARCHAR(50) NOT NULL UNIQUE,
	passw VARCHAR(15) NOT NULL);
	
CREATE TABLE IF NOT EXISTS ingredients(
	ingr_id INT AUTO_INCREMENT PRIMARY KEY,
	ingr_name VARCHAR(50) NOT NULL UNIQUE);
    
CREATE TABLE IF NOT EXISTS preferences(
	value INT DEFAULT 0,
    user_ref INT NOT NULL REFERENCES users.user_id ON DELETE CASCADE ON UPDATE CASCADE,
    ingr_ref INT NOT NULL,
    FOREIGN KEY(user_ref) REFERENCES users(user_id) ON DELETE CASCADE ON UPDATE CASCADE,
	FOREIGN KEY(ingr_ref) REFERENCES ingredients(ingr_id) ON DELETE CASCADE ON UPDATE CASCADE);
    
INSERT INTO users (username,passw) VALUES ('admin', 'admin');

INSERT INTO ingredients (ingr_name) VALUES ('');
INSERT INTO ingredients (ingr_name) VALUES ('Eragrostideae');
INSERT INTO ingredients (ingr_name) VALUES ('Vitis Vinifera');
INSERT INTO ingredients (ingr_name) VALUES ('Anise');
INSERT INTO ingredients (ingr_name) VALUES ('Apple');
INSERT INTO ingredients (ingr_name) VALUES ('Blackberry');
INSERT INTO ingredients (ingr_name) VALUES ('Prunus');
INSERT INTO ingredients (ingr_name) VALUES ('Vitis');
INSERT INTO ingredients (ingr_name) VALUES ('Papaya');
INSERT INTO ingredients (ingr_name) VALUES ('Pear');
INSERT INTO ingredients (ingr_name) VALUES ('Damson');
INSERT INTO ingredients (ingr_name) VALUES ('Rubus Idaeus');
INSERT INTO ingredients (ingr_name) VALUES ('Juniperus Communis');
INSERT INTO ingredients (ingr_name) VALUES ('Saccharum');
INSERT INTO ingredients (ingr_name) VALUES ('Maize');
INSERT INTO ingredients (ingr_name) VALUES ('Corn');
INSERT INTO ingredients (ingr_name) VALUES ('Grape ');
INSERT INTO ingredients (ingr_name) VALUES ('Vaccinium Myrtillus');
INSERT INTO ingredients (ingr_name) VALUES ('Plum');
INSERT INTO ingredients (ingr_name) VALUES ('Oryza Sativa');
INSERT INTO ingredients (ingr_name) VALUES ('Coffee');
INSERT INTO ingredients (ingr_name) VALUES ('Strawberry');
INSERT INTO ingredients (ingr_name) VALUES ('Coffea');
INSERT INTO ingredients (ingr_name) VALUES ('Yerba Mate');
INSERT INTO ingredients (ingr_name) VALUES ('Camellia Sinensis');
INSERT INTO ingredients (ingr_name) VALUES ('Plant');
INSERT INTO ingredients (ingr_name) VALUES ('Aspalathus');
INSERT INTO ingredients (ingr_name) VALUES ('Barley');
INSERT INTO ingredients (ingr_name) VALUES ('Flowering plant');
INSERT INTO ingredients (ingr_name) VALUES ('Cereal Grains');
INSERT INTO ingredients (ingr_name) VALUES ('Grape');
INSERT INTO ingredients (ingr_name) VALUES ('Theobroma');
INSERT INTO ingredients (ingr_name) VALUES ('Roselle');
INSERT INTO ingredients (ingr_name) VALUES ('Glycine');
INSERT INTO ingredients (ingr_name) VALUES ('Fruits');
INSERT INTO ingredients (ingr_name) VALUES ('Poacceae');
INSERT INTO ingredients (ingr_name) VALUES ('Vegetables');
INSERT INTO ingredients (ingr_name) VALUES ('http://www.wikidata.org/entity/Q1093742');
INSERT INTO ingredients (ingr_name) VALUES ('http://www.wikidata.org/entity/Q147316');
INSERT INTO ingredients (ingr_name) VALUES ('http://www.wikidata.org/entity/Q169');
INSERT INTO ingredients (ingr_name) VALUES ('http://www.wikidata.org/entity/Q12330939');
INSERT INTO ingredients (ingr_name) VALUES ('http://www.wikidata.org/entity/Q177092');
INSERT INTO ingredients (ingr_name) VALUES ('http://www.wikidata.org/entity/Q503');
INSERT INTO ingredients (ingr_name) VALUES ('http://www.wikidata.org/entity/Q3342808');
INSERT INTO ingredients (ingr_name) VALUES ('"http://www.wikidata.org/entity/Q10817602');
INSERT INTO ingredients (ingr_name) VALUES ('http://www.wikidata.org/entity/Q13179');
INSERT INTO ingredients (ingr_name) VALUES ('http://www.wikidata.org/entity/Q5812410');
INSERT INTO ingredients (ingr_name) VALUES ('http://www.wikidata.org/entity/Q5881191');
INSERT INTO ingredients (ingr_name) VALUES ('http://www.wikidata.org/entity/Q14458220');
INSERT INTO ingredients (ingr_name) VALUES ('http://www.wikidata.org/entity/Q83376');
INSERT INTO ingredients (ingr_name) VALUES ('http://www.wikidata.org/entity/Q60708120');
INSERT INTO ingredients (ingr_name) VALUES ('http://www.wikidata.org/entity/Q2224510');
INSERT INTO ingredients (ingr_name) VALUES ('http://www.wikidata.org/entity/Q1150849');

