INSERT INTO users (username,passw) VALUES ('Nome1', 'Pass1');
INSERT INTO users (username,passw) VALUES ('Nome2', 'Pass2');
INSERT INTO users (username,passw) VALUES ('Nome3', 'Pass3');
INSERT INTO users (username,passw) VALUES ('Nome4', 'Pass4');

INSERT INTO ingredients (ingr_name) VALUES ('ingr1');
INSERT INTO ingredients (ingr_name) VALUES ('ingr2');
INSERT INTO ingredients (ingr_name) VALUES ('ingr3');
INSERT INTO ingredients (ingr_name) VALUES ('ingr4');
INSERT INTO ingredients (ingr_name) VALUES ('ingr5');

INSERT INTO preferences (value, user_ref, ingr_ref) VALUES (1, 1, 2);
INSERT INTO preferences (value, user_ref, ingr_ref) VALUES (2, 1, 4);
INSERT INTO preferences (value, user_ref, ingr_ref) VALUES (3, 1, 5);
INSERT INTO preferences (value, user_ref, ingr_ref) VALUES (1, 2, 1);
INSERT INTO preferences (value, user_ref, ingr_ref) VALUES (2, 2, 3);
INSERT INTO preferences (value, user_ref, ingr_ref) VALUES (3, 2, 4);
INSERT INTO preferences (value, user_ref, ingr_ref) VALUES (1, 3, 1);
INSERT INTO preferences (value, user_ref, ingr_ref) VALUES (2, 3, 2);
INSERT INTO preferences (value, user_ref, ingr_ref) VALUES (3, 3, 4);
INSERT INTO preferences (value, user_ref, ingr_ref) VALUES (1, 4, 2);
INSERT INTO preferences (value, user_ref, ingr_ref) VALUES (2, 4, 3);
INSERT INTO preferences (value, user_ref, ingr_ref) VALUES (3, 4, 5);