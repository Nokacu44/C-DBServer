gcc $(mysql_config --cflags) test.c ./lib/server.c ./lib/externals/cJSON.c  $(mysql_config --libs) -lneo4j-client -lssl -lcrypto -o test