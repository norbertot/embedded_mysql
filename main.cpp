#include <my_global.h>
#include <mysql.h>

int main(int argc, char **argv) {
    static char *server_options[] = {
            "mysql_test", // An unused string
            "--datadir=/tmp/mysql_embedded_data", // Your data dir
            NULL };
    int num_elements = (sizeof(server_options) / sizeof(char *)) - 1;

    static char *server_groups[] = { "libmysqld_server",
                                     "libmysqld_client", NULL };


    // Init MySQL lib and connection
    mysql_library_init(num_elements, server_options, server_groups);
    MYSQL *con = mysql_init(NULL);

    if (con == NULL) {
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }

    mysql_options(con, MYSQL_READ_DEFAULT_GROUP, "libmysqld_client");
    mysql_options(con, MYSQL_OPT_USE_EMBEDDED_CONNECTION, NULL);

    // Connect to no host/port -> Embedded mode
    if (mysql_real_connect(con, NULL, NULL, NULL, NULL, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }

    // Create a sample empty DB, named "aNewDatabase"
    if (mysql_query(con, "CREATE DATABASE aNewDatabase")) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }

    // Close connection
    mysql_close(con);
    exit(0);
}