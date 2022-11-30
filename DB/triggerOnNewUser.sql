DELIMITER //

CREATE TRIGGER newUserPreferences AFTER INSERT ON users
FOR EACH ROW
BEGIN

	DECLARE finished INTEGER DEFAULT 0;
	DECLARE currIngr varchar(100) DEFAULT "";
	DECLARE ingr_cursor CURSOR FOR SELECT ingr_id FROM ingredients;
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET finished = 1;
        
    OPEN ingr_cursor;

	scorriIngredienti: LOOP
		FETCH ingr_cursor INTO currIngr;
		IF finished = 1 THEN 
			LEAVE scorriIngredienti;
		END IF;

		INSERT INTO preferences (user_ref, ingr_ref) VALUES (new.user_id, currIngr);
	END LOOP scorriIngredienti;

	CLOSE ingr_cursor;
END //

DELIMITER ;