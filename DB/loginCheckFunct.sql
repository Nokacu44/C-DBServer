USE `userDB`;
DROP function IF EXISTS `loginCheckFunct`;

DELIMITER //

CREATE FUNCTION `loginCheckFunct` (usr VARCHAR(50), psw VARCHAR(50))
RETURNS INTEGER
DETERMINISTIC
BEGIN
    DECLARE tot INTEGER;
    
	SELECT COUNT(user_id) INTO tot
	FROM users
	WHERE username = usr AND passw = psw;
    
    RETURN tot;
END //

DELIMITER ;