#include "sensor_db.h"
#include <stdio.h>
#include <stdlib.h>

MYSQL *init_connection(char clear_up_flag)
{
	MYSQL *con = mysql_init(NULL);
	if(con == NULL)
	{
		fprintf(stderr,"%s\n",mysql_error(con));
		return NULL;
	}
	if(mysql_real_connect(con,"studev.groept.be","a13_syssoft","a13_syssoft","a13_syssoft",3306,NULL,0) == NULL)
	{
		fprintf(stderr,"%s\n",mysql_error(con));
		mysql_close(con);
		return NULL;
	}
	if(mysql_query(con,"CREATE TABLE IF NOT EXISTS lyu_yanqiu(id int AUTO_INCREMENT,sensor_id int,sensor_value decimal(4,2),timestamp timestamp,PRIMARY KEY (id))") != 0)
	{
		fprintf(stderr,"%s\n",mysql_error(con));
		mysql_close(con);
		return NULL;
	}
	if(clear_up_flag == 1)
	{
		if(mysql_query(con,"TRUNCATE TABLE lyu_yanqiu") != 0)
		{
			fprintf(stderr,"%s\n",mysql_error(con));
			mysql_close(con);
			return NULL;
		}
	}
	return con;
}

void disconnect(MYSQL *conn)
{
	mysql_close(conn);
	mysql_library_end();
}

int insert_sensor(MYSQL *conn, sensor_id_t id, sensor_value_t value, sensor_ts_t ts)
{
	char statement[100];
	sprintf(statement,"INSERT INTO lyu_yanqiu (sensor_id,sensor_value,timestamp) VALUES (%d,%.2f,FROM_UNIXTIME(%ld))",id,value,ts);
	return mysql_query(conn,statement);
}

int insert_sensor_from_file(MYSQL *conn, FILE *sensor_data)
{
	int elem_size = sizeof(sensor_id_t)+sizeof(sensor_value_t)+sizeof(sensor_ts_t);
	void *init_buf = malloc(100*elem_size);
	int read_elem_num = 0;
	sensor_id_t id;
	sensor_value_t value;
	sensor_ts_t ts;
	int flag;
	while((read_elem_num = fread(init_buf,elem_size,100,sensor_data))>0)
	{
		void *buf = init_buf;
		int i;
		for(i=0;i<read_elem_num;i++)
		{
			id = *(sensor_id_t*)buf;
			buf = (int8_t*)buf+sizeof(sensor_id_t);
			value = *(sensor_value_t*)buf;
			buf = (int8_t*)buf+sizeof(sensor_value_t);
			ts = *(sensor_ts_t*)buf;
			buf = (int8_t*)buf+sizeof(sensor_ts_t);
			char statement[100];
			sprintf(statement,"INSERT INTO lyu_yanqiu (sensor_id,sensor_value,timestamp) VALUES (%d,%.2f,FROM_UNIXTIME(%ld))",id,value,ts);
			flag = mysql_query(conn,statement);
			if(flag != 0)
			{
				fprintf(stderr,"%s\n",mysql_error(conn));
				free(init_buf);
				init_buf = NULL;
				return flag;
			}
		}
	}
	free(init_buf);
	init_buf = NULL;
	return 0;
}

MYSQL_RES *find_sensor_all(MYSQL *conn)
{
	if(mysql_query(conn,"SELECT * FROM lyu_yanqiu") == 0)
		return mysql_store_result(conn);
	else
	{
		fprintf(stderr,"%s\n",mysql_error(conn));
		return NULL;
	}
}

MYSQL_RES *find_sensor_by_value(MYSQL *conn, sensor_value_t value_t)
{
	char statement[100];
	sprintf(statement,"SELECT * FROM lyu_yanqiu WHERE sensor_value=%.2f",value_t);
	if(mysql_query(conn,statement) == 0)
		return mysql_store_result(conn);
	else
	{
		fprintf(stderr,"%s\n",mysql_error(conn));
		return NULL;
	}
}

MYSQL_RES *find_sensor_exceed_value(MYSQL *conn, sensor_value_t value_t)
{
	char statement[100];
	sprintf(statement,"SELECT * FROM lyu_yanqiu WHERE sensor_value>%.2f",value_t);
	if(mysql_query(conn,statement) == 0)
		return mysql_store_result(conn);
	else
	{
		fprintf(stderr,"%s\n",mysql_error(conn));
		return NULL;
	}
}

MYSQL_RES *find_sensor_by_timestamp(MYSQL *conn, sensor_ts_t ts_t)
{
	char statement[100];
	sprintf(statement,"SELECT * FROM lyu_yanqiu WHERE UNIX_TIMESTAMP(timestamp)=%ld",ts_t);
	if(mysql_query(conn,statement) == 0)
		return mysql_store_result(conn);
	else
	{
		fprintf(stderr,"%s\n",mysql_error(conn));
		return NULL;
	}
}

MYSQL_RES *find_sensor_later_timestamp(MYSQL *conn, sensor_ts_t ts_t)
{
	char statement[100];
	sprintf(statement,"SELECT * FROM lyu_yanqiu WHERE UNIX_TIMESTAMP(timestamp)>%ld",ts_t);
	if(mysql_query(conn,statement) == 0)
		return mysql_store_result(conn);
	else
	{
		fprintf(stderr,"%s\n",mysql_error(conn));
		return NULL;
	}
}

int get_result_size(MYSQL_RES *result)
{
	return (int)mysql_num_rows(result);
}

const char *get_error_message(MYSQL *conn)
{
	return mysql_error(conn); 
}

void print_result(MYSQL_RES *result)
{
	MYSQL_ROW row;
	while((row = mysql_fetch_row(result)))
	{
		printf("id: %s   sensor_id: %s   sensor_value: %s   timestamp: %s\n",row[0],row[1],row[2],row[3]);
	}
}

void free_result(MYSQL_RES *result)
{
	mysql_free_result(result);
}














