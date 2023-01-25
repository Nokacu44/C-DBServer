DROP DATABASE IF EXISTS userDB;
CREATE DATABASE userDB;
USE userDB;
SET NAMES utf8;

CREATE TABLE IF NOT EXISTS users(
	user_id INT AUTO_INCREMENT PRIMARY KEY,
	username VARCHAR(50) NOT NULL UNIQUE,
	passw VARCHAR(15) NOT NULL,
    nome VARCHAR(30),
    cognome VARCHAR(30),
    phone VARCHAR(15),
    address VARCHAR(25),
    cap VARCHAR(8),
    city VARCHAR(20),
    province VARCHAR(25));
	
CREATE TABLE IF NOT EXISTS ingredients(
	ingr_id INT AUTO_INCREMENT PRIMARY KEY,
	ingr_name VARCHAR(50) NOT NULL UNIQUE);
    
CREATE TABLE IF NOT EXISTS preferences(
	value INT DEFAULT 0,
    user_ref INT NOT NULL REFERENCES users.user_id ON DELETE CASCADE ON UPDATE CASCADE,
    ingr_ref INT NOT NULL,
    FOREIGN KEY(user_ref) REFERENCES users(user_id) ON DELETE CASCADE ON UPDATE CASCADE,
	FOREIGN KEY(ingr_ref) REFERENCES ingredients(ingr_id) ON DELETE CASCADE ON UPDATE CASCADE);
    
INSERT INTO ingredients (ingr_name) VALUES ('speciale');
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

INSERT INTO ingredients (ingr_name) VALUES ('ananas');
INSERT INTO ingredients (ingr_name) VALUES ('noce di cocco');
INSERT INTO ingredients (ingr_name) VALUES ('mirtillo');
INSERT INTO ingredients (ingr_name) VALUES ('lampone');
INSERT INTO ingredients (ingr_name) VALUES ('succo di lampone');
INSERT INTO ingredients (ingr_name) VALUES ('mirtillo europeo');
INSERT INTO ingredients (ingr_name) VALUES ('succo di mirtillo');
INSERT INTO ingredients (ingr_name) VALUES ('fragola');
INSERT INTO ingredients (ingr_name) VALUES ('succo di fragola');
INSERT INTO ingredients (ingr_name) VALUES ('succo di ananas');
INSERT INTO ingredients (ingr_name) VALUES ('rum');
INSERT INTO ingredients (ingr_name) VALUES ('malibu rum');
INSERT INTO ingredients (ingr_name) VALUES ('bacardi rum');
INSERT INTO ingredients (ingr_name) VALUES ('bumbu rum');
INSERT INTO ingredients (ingr_name) VALUES ('bacardi');
INSERT INTO ingredients (ingr_name) VALUES ('bacardi breezer');
INSERT INTO ingredients (ingr_name) VALUES ('latte di cocco');
INSERT INTO ingredients (ingr_name) VALUES ('menta');
INSERT INTO ingredients (ingr_name) VALUES ('gin');
INSERT INTO ingredients (ingr_name) VALUES ('melone');
INSERT INTO ingredients (ingr_name) VALUES ('mango');
INSERT INTO ingredients (ingr_name) VALUES ('frutto della passione');
INSERT INTO ingredients (ingr_name) VALUES ('banana');
INSERT INTO ingredients (ingr_name) VALUES ('limone');


