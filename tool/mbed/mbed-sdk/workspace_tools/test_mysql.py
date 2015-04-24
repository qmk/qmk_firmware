"""
mbed SDK
Copyright (c) 2011-2014 ARM Limited

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

Author: Przemyslaw Wirkus <Przemyslaw.Wirkus@arm.com>
"""

import re
import MySQLdb as mdb

# Imports from TEST API
from workspace_tools.test_db import BaseDBAccess


class MySQLDBAccess(BaseDBAccess):
    """ Wrapper for MySQL DB access for common test suite interface
    """
    def __init__(self):
        BaseDBAccess.__init__(self)
        self.DB_TYPE = 'mysql'

    def detect_database(self, verbose=False):
        """ detect database and return VERION data structure or string (verbose=True)
        """
        query = 'SHOW VARIABLES LIKE "%version%"'
        rows = self.select_all(query)
        if verbose:
            result = []
            for row in rows:
                result.append("\t%s: %s"% (row['Variable_name'], row['Value']))
            result = "\n".join(result)
        else:
            result = rows
        return result

    def parse_db_connection_string(self, str):
        """ Parsing SQL DB connection string. String should contain:
            - DB Name, user name, password, URL (DB host), name
            Function should return tuple with parsed (host, user, passwd, db) or None if error
            E.g. connection string: 'mysql://username:password@127.0.0.1/db_name'
        """
        result = BaseDBAccess().parse_db_connection_string(str)
        if result is not None:
            (db_type, username, password, host, db_name) = result
            if db_type != 'mysql':
                result = None
        return result

    def is_connected(self):
        """ Returns True if we are connected to database
        """
        return self.db_object is not None

    def connect(self, host, user, passwd, db):
        """ Connects to DB and returns DB object
        """
        try:
            self.db_object = mdb.connect(host=host, user=user, passwd=passwd, db=db)
            # Let's remember connection credentials
            self.db_type = self.DB_TYPE
            self.host = host
            self.user = user
            self.passwd = passwd
            self.db = db
        except mdb.Error, e:
            print "Error %d: %s"% (e.args[0], e.args[1])
            self.db_object = None
            self.db_type = None
            self.host = None
            self.user = None
            self.passwd = None
            self.db = None

    def connect_url(self, db_url):
        """ Connects to database using db_url (database url parsing),
            store host, username, password, db_name
        """
        result = self.parse_db_connection_string(db_url)
        if result is not None:
            (db_type, username, password, host, db_name) = result
            if db_type == self.DB_TYPE:
                self.connect(host, username, password, db_name)

    def reconnect(self):
        """ Reconnects to DB and returns DB object using stored host name,
            database name and credentials (user name and password)
        """
        self.connect(self.host, self.user, self.passwd, self.db)

    def disconnect(self):
        """ Close DB connection
        """
        if self.db_object:
            self.db_object.close()
        self.db_object = None
        self.db_type = None

    def escape_string(self, str):
        """ Escapes string so it can be put in SQL query between quotes
        """
        con = self.db_object
        result = con.escape_string(str)
        return result if result else ''

    def select_all(self, query):
        """ Execute SELECT query and get all results
        """
        con = self.db_object
        cur = con.cursor(mdb.cursors.DictCursor)
        cur.execute(query)
        rows = cur.fetchall()
        return rows

    def insert(self, query, commit=True):
        """ Execute INSERT query, define if you want to commit
        """
        con = self.db_object
        cur = con.cursor()
        cur.execute(query)
        if commit:
            con.commit()
        return cur.lastrowid

    def get_next_build_id(self, name, desc='', location='', type=None, status=None):
        """ Insert new build_id (DB unique build like ID number to send all test results)
        """
        if status is None:
            status = self.BUILD_ID_STATUS_STARTED

        if type is None:
            type = self.BUILD_ID_TYPE_TEST

        query = """INSERT INTO `%s` (%s_name, %s_desc, %s_location, %s_type_fk, %s_status_fk)
                        VALUES ('%s', '%s', '%s', %d, %d)"""% (self.TABLE_BUILD_ID,
                                                               self.TABLE_BUILD_ID,
                                                               self.TABLE_BUILD_ID,
                                                               self.TABLE_BUILD_ID,
                                                               self.TABLE_BUILD_ID,
                                                               self.TABLE_BUILD_ID,
                                                               self.escape_string(name),
                                                               self.escape_string(desc),
                                                               self.escape_string(location),
                                                               type,
                                                               status)
        index = self.insert(query) # Provide inserted record PK
        return index

    def get_table_entry_pk(self, table, column, value, update_db=True):
        """ Checks for entries in tables with two columns (<TABLE_NAME>_pk, <column>)
            If update_db is True updates table entry if value in specified column doesn't exist
        """
        # TODO: table buffering
        result = None
        table_pk = '%s_pk'% table
        query = """SELECT `%s`
                     FROM `%s`
                    WHERE `%s`='%s'"""% (table_pk,
                                         table,
                                         column,
                                         self.escape_string(value))
        rows = self.select_all(query)
        if len(rows) == 1:
            result = rows[0][table_pk]
        elif len(rows) == 0 and update_db:
            # Update DB with new value
            result = self.update_table_entry(table, column, value)
        return result

    def update_table_entry(self, table, column, value):
        """ Updates table entry if value in specified column doesn't exist
            Locks table to perform atomic read + update
        """
        result = None
        con = self.db_object
        cur = con.cursor()
        cur.execute("LOCK TABLES `%s` WRITE"% table)
        table_pk = '%s_pk'% table
        query = """SELECT `%s`
                     FROM `%s`
                    WHERE `%s`='%s'"""% (table_pk,
                                         table,
                                         column,
                                         self.escape_string(value))
        cur.execute(query)
        rows = cur.fetchall()
        if len(rows) == 0:
            query = """INSERT INTO `%s` (%s)
                            VALUES ('%s')"""% (table,
                                               column,
                                               self.escape_string(value))
            cur.execute(query)
            result = cur.lastrowid
        con.commit()
        cur.execute("UNLOCK TABLES")
        return result

    def update_build_id_info(self, build_id, **kw):
        """ Update additional data inside build_id table
            Examples:
            db.update_build_id_info(build_id, _status_fk=self.BUILD_ID_STATUS_COMPLETED, _shuffle_seed=0.0123456789):
        """
        if len(kw):
            con = self.db_object
            cur = con.cursor()
            # Prepare UPDATE query
            # ["`mtest_build_id_pk`=[value-1]", "`mtest_build_id_name`=[value-2]", "`mtest_build_id_desc`=[value-3]"]
            set_list = []
            for col_sufix in kw:
                assign_str = "`%s%s`='%s'"% (self.TABLE_BUILD_ID, col_sufix, self.escape_string(str(kw[col_sufix])))
                set_list.append(assign_str)
            set_str = ', '.join(set_list)
            query = """UPDATE `%s`
                          SET %s
                        WHERE `mtest_build_id_pk`=%d"""% (self.TABLE_BUILD_ID,
                                                          set_str,
                                                          build_id)
            cur.execute(query)
            con.commit()

    def insert_test_entry(self, build_id, target, toolchain, test_type, test_id, test_result, test_output, test_time, test_timeout, test_loop, test_extra=''):
        """ Inserts test result entry to database. All checks regarding existing
            toolchain names in DB are performed.
            If some data is missing DB will be updated
        """
        # Get all table FK and if entry is new try to insert new value
        target_fk = self.get_table_entry_pk(self.TABLE_TARGET, self.TABLE_TARGET + '_name', target)
        toolchain_fk = self.get_table_entry_pk(self.TABLE_TOOLCHAIN, self.TABLE_TOOLCHAIN + '_name', toolchain)
        test_type_fk = self.get_table_entry_pk(self.TABLE_TEST_TYPE, self.TABLE_TEST_TYPE + '_name', test_type)
        test_id_fk = self.get_table_entry_pk(self.TABLE_TEST_ID, self.TABLE_TEST_ID + '_name', test_id)
        test_result_fk = self.get_table_entry_pk(self.TABLE_TEST_RESULT, self.TABLE_TEST_RESULT + '_name', test_result)

        con = self.db_object
        cur = con.cursor()

        query = """ INSERT INTO `%s` (`mtest_build_id_fk`,
                                      `mtest_target_fk`,
                                      `mtest_toolchain_fk`,
                                      `mtest_test_type_fk`,
                                      `mtest_test_id_fk`,
                                      `mtest_test_result_fk`,
                                      `mtest_test_output`,
                                      `mtest_test_time`,
                                      `mtest_test_timeout`,
                                      `mtest_test_loop_no`,
                                      `mtest_test_result_extra`)
                         VALUES (%d, %d, %d, %d, %d, %d, '%s', %.2f, %.2f, %d, '%s')"""% (self.TABLE_TEST_ENTRY,
                                                                                          build_id,
                                                                                          target_fk,
                                                                                          toolchain_fk,
                                                                                          test_type_fk,
                                                                                          test_id_fk,
                                                                                          test_result_fk,
                                                                                          self.escape_string(test_output),
                                                                                          test_time,
                                                                                          test_timeout,
                                                                                          test_loop,
                                                                                          self.escape_string(test_extra))
        cur.execute(query)
        con.commit()
