-- Create user
GRANT USAGE ON *.* TO 'gk'@'localhost';
DROP USER 'gk'@'localhost';
CREATE USER 'gk'@'localhost' IDENTIFIED BY 'gk';
GRANT USAGE ON * . * TO 'gk'@'localhost' IDENTIFIED BY 'gk' WITH MAX_QUERIES_PER_HOUR 0 MAX_CONNECTIONS_PER_HOUR 0 MAX_UPDATES_PER_HOUR 0 MAX_USER_CONNECTIONS 0 ;

GRANT SELECT , INSERT, 
EXECUTE ON * . *
TO 'gk'@'localhost'
WITH MAX_QUERIES_PER_HOUR 0
MAX_CONNECTIONS_PER_HOUR 0
MAX_UPDATES_PER_HOUR 0




-- Create user
GRANT USAGE ON *.* TO 'nh-web'@'localhost';
DROP USER 'nh-web'@'localhost';
CREATE USER 'nh-web'@'localhost' IDENTIFIED BY 'nh-web';
GRANT USAGE ON * . * TO 'gk'@'localhost' IDENTIFIED BY 'nh-web' WITH MAX_QUERIES_PER_HOUR 0 MAX_CONNECTIONS_PER_HOUR 0 MAX_UPDATES_PER_HOUR 0 MAX_USER_CONNECTIONS 0 ;

GRANT SELECT, 
EXECUTE ON * . *
TO 'nh-web'@'localhost'
WITH MAX_QUERIES_PER_HOUR 0
MAX_CONNECTIONS_PER_HOUR 0
MAX_UPDATES_PER_HOUR 0;