
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "manageDB.h"


manageDB::manageDB(){

    zErrMsg = 0;


    rc = sqlite3_open("../sql_database/sfm.db", &db);

    if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return;
    } else {
      fprintf(stderr, "Opened database successfully\n");
    }
    sqlite3_close(db);

}




}


