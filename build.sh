gcc $(mysql_config --cflags) test.c ./lib/server.c ./lib/queries.c ./lib/externals/cJSON.c  $(mysql_config --libs) -lssl -lcrypto -o test -Wall -Wextra -pedantic -g