--disable_warnings
--disable_query_log
--disable_result_log
--source ../t/test_init.inc
--source ../t/slave_test_init.inc
--enable_result_log
--enable_query_log
--enable_warnings
--let $MASTER_1_COMMENT_2_1_BACKUP= $MASTER_1_COMMENT_2_1
let $MASTER_1_COMMENT_2_1=
  COMMENT='table "tbl_a", srv "s_2_1"';
--let $CHILD2_1_DROP_TABLES_BACKUP= $CHILD2_1_DROP_TABLES
let $CHILD2_1_DROP_TABLES=
  DROP TABLE IF EXISTS tbl_a;
--let $CHILD2_1_CREATE_TABLES_BACKUP= $CHILD2_1_CREATE_TABLES
let $CHILD2_1_CREATE_TABLES=
  CREATE TABLE tbl_a (
    pkey int NOT NULL,
    PRIMARY KEY (pkey)
  ) $CHILD2_1_ENGINE $CHILD2_1_CHARSET;
--let $CHILD2_1_SELECT_TABLES_BACKUP= $CHILD2_1_SELECT_TABLES
let $CHILD2_1_SELECT_TABLES=
  SELECT pkey FROM tbl_a ORDER BY pkey;
let $CHILD2_1_SELECT_ARGUMENT1=
  SELECT argument FROM mysql.general_log WHERE command_type != 'Execute' AND argument LIKE '%set %';
--let $OUTPUT_CHILD_GROUP2_BACKUP= $OUTPUT_CHILD_GROUP2
--let $OUTPUT_CHILD_GROUP2= 1
--let $USE_GENERAL_LOG_BACKUP= $USE_GENERAL_LOG
--let $USE_GENERAL_LOG= 1
--connection slave1_1
--disable_warnings
--disable_query_log
--disable_result_log
--source ../include/init_spider.inc
--enable_result_log
--enable_query_log
--enable_warnings
set @old_spider_slave_trx_isolation= @@spider_slave_trx_isolation;
set global spider_slave_trx_isolation= 1;
