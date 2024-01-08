#include "postgresql/libpq-fe.h"
#include "interface_iter2.hpp"
#include <iostream>
#include <string>
using namespace std;

//-----------------------------------DB METHODS-------------------------------------------

status verifyTeacher(unsigned int teachID);

status verifyStudent(unsigned int studID);

status verifyProblem(unsigned int proID);

status relTeacherProblem(unsigned int teachID, unsigned int proID);

status storeMethod(Method m, unsigned int proID);

status storeTestCase(string tcFile, unsigned int proID);

status deleteTestCase(unsigned int proID);

ProblemResult storeProblem(unsigned int teachID, Problem p, string tcFile);

ProblemResult deleteProblem(unsigned int teachID, unsigned int proID);

SubmissionResult storeSubmission(string sub_file, subStatus sub_st, unsigned int pro_id, unsigned int studID);

Problem giveProblem(unsigned int proID);

status verifyTeacher(unsigned int teachID)
{
	status st;	
	const char *conninfo;
	PGconn	*conn;
	PGresult *res;
	string select;
	const char *query;
	conninfo = "dbname = cap2";

	conn = PQconnectdb(conninfo);
	if(PQstatus(conn) != CONNECTION_OK)
	{
		cout << PQerrorMessage(conn);
		st.err = INTERNAL_ERROR;
		st.errId = DB_FAILED;
		PQfinish(conn);
		return st;
	}

	select = "SELECT teach_id FROM teacher where teach_id = "+ to_string(teachID)+"";
	
	query = select.c_str();

	res = PQexec(conn,query);

	if(PQntuples(res) == 0)
	{
		cout << "Invalid Teacher id"<<endl;
		st.err = USER_ERROR;
		st.errId = INVALID_INPUT;
		PQclear(res);
		PQfinish(conn);
		return st;
	}

	st.err = SUCCESS;
	PQclear(res);
	PQfinish(conn);
	return st;
}

status verifyStudent(unsigned int studID)
{
	status st;	
	const char *conninfo;
	PGconn	*conn;
	PGresult *res;
	string select;
	const char *query;
	conninfo = "dbname = cap2";

	conn = PQconnectdb(conninfo);
	if(PQstatus(conn) != CONNECTION_OK)
	{
		cout << PQerrorMessage(conn);
		st.err = INTERNAL_ERROR;
		st.errId = DB_FAILED;
		PQfinish(conn);
		return st;
	}

	select = "SELECT stud_id FROM student where stud_id = "+ to_string(studID)+"";
	
	query = select.c_str();

	res = PQexec(conn,query);

	if(PQntuples(res) == 0)
	{
		cout << "Invalid Student id"<<endl;
		st.err = USER_ERROR;
		st.errId = INVALID_INPUT;
		PQclear(res);
		PQfinish(conn);
		return st;
	}

	st.err = SUCCESS;
	PQclear(res);
	PQfinish(conn);
	return st;
}

status verifyProblem(unsigned int proID)
{
	status st;	
	const char *conninfo;
	PGconn	*conn;
	PGresult *res;
	string select;
	const char *query;
	conninfo = "dbname = cap2";

	conn = PQconnectdb(conninfo);
	if(PQstatus(conn) != CONNECTION_OK)
	{
		cout << PQerrorMessage(conn);
		st.err = INTERNAL_ERROR;
		st.errId = DB_FAILED;
		PQfinish(conn);
		return st;
	}

	select = "SELECT pro_id FROM problem where pro_id = "+ to_string(proID)+"";
	
	query = select.c_str();

	res = PQexec(conn,query);

	if(PQntuples(res) == 0)
	{
		cout << "Invalid Problem id"<<endl;
		st.err = USER_ERROR;
		st.errId = INVALID_INPUT;
		PQclear(res);
		PQfinish(conn);
		return st;
	}

	st.err = SUCCESS;
	PQclear(res);
	PQfinish(conn);
	return st;
}

status relTeacherProblem(unsigned int teachID, unsigned int proID)
{
	status st;
	const char *conninfo;
	PGconn *conn;
	PGresult *res;
	string select;
	const char *query;
	conninfo = "dbname = cap2";

	conn = PQconnectdb(conninfo);
	if(PQstatus(conn) != CONNECTION_OK)
	{
		cout << PQerrorMessage(conn);
		st.err = INTERNAL_ERROR;
		st.errId = DB_FAILED;
		PQfinish(conn);
		return st;
	}

	select = "SELECT pro_id FROM problem WHERE teach_id = "+ to_string(teachID) +" AND pro_id = "+ to_string(proID) +"";

	query = select.c_str();

	res = PQexec(conn,query);
	if(PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		cout << PQerrorMessage(conn);
		st.err = INTERNAL_ERROR;
		st.errId = DB_FAILED;
		PQfinish(conn);
		return st;
	}
	unsigned int val = atoi(PQgetvalue(res,0,0));
       	cout <<" val: "<< val <<" proId: "<<proID<<endl; 	
	if(val != proID)
	{
		cout << "No connection btw teacher and problem"<<endl;
		st.err = USER_ERROR;
		st.errId = INVALID_INPUT;
		PQfinish(conn);
		return st;
	}

	st.err = SUCCESS;

	PQclear(res);
	PQfinish(conn);
	return st;
}
	
status storeMethod(Method m, unsigned int proID)
{
	status st;
	const char *conninfo;
	PGconn *conn;
	PGresult *res;
	string insert;
	const char *query;
	conninfo = "dbname = cap2";

	conn = PQconnectdb(conninfo);
	if(PQstatus(conn) != CONNECTION_OK)
	{
		cout << PQerrorMessage(conn);
		st.err = INTERNAL_ERROR;
		st.errId = DB_FAILED;
		PQfinish(conn);
		return st;
	}

	insert = "INSERT INTO method(method_file, lang, returntype, parameter, pro_id) VALUES('"+ m.internalPart +"','"+ m.language +"','"+ m.returnType +"','"+ m.parameter +"',"+ to_string(proID) +")";

	query = insert.c_str();

	res = PQexec(conn,query);
	if(PQresultStatus(res) != PGRES_COMMAND_OK)
	{
		cout << PQerrorMessage(conn);
		st.err = INTERNAL_ERROR;
		st.errId = DB_FAILED;
		PQfinish(conn);
		return st;
	}
	
	st.err = SUCCESS;

	PQclear(res);
	PQfinish(conn);
	return st;
}



status storeTestCase(string tcFile, unsigned int proID)
{
	status st;
	const char *conninfo;
	PGconn *conn;
	PGresult *res;
	string insert;
	const char *query;
	conninfo = "dbname = cap2";

	conn = PQconnectdb(conninfo);
	if(PQstatus(conn) != CONNECTION_OK)
	{
		cout << PQerrorMessage(conn);
		st.err = INTERNAL_ERROR;
		st.errId = DB_FAILED;
		PQfinish(conn);
		return st;
	}

	insert = "INSERT INTO testcase(tc_file, pro_id) VALUES('"+ tcFile +"',"+ to_string(proID) +")";

	query = insert.c_str();

	res = PQexec(conn,query);
	if(PQresultStatus(res) != PGRES_COMMAND_OK)
	{
		cout << PQerrorMessage(conn);
		st.err = INTERNAL_ERROR;
		st.errId = DB_FAILED;
		PQfinish(conn);
		return st;
	}
	
	st.err = SUCCESS;

	PQclear(res);
	PQfinish(conn);
	return st;
}

status deleteTestCase(unsigned int proID)
{
	status st;
	const char *conninfo;
	PGconn	*conn;
	PGresult *res;
	string del;
	const char *query;
	conninfo = "dbname = cap2";

	conn = PQconnectdb(conninfo);
	if(PQstatus(conn) != CONNECTION_OK)
	{
		cout << PQerrorMessage(conn);
		st.err = INTERNAL_ERROR;
		st.errId = DB_FAILED;
		PQfinish(conn);
		return st;
	}

	del = "DELETE FROM testcase WHERE pro_id = "+ to_string(proID) +"";

	query = del.c_str();
	res = PQexec(conn, query);

	st.err = SUCCESS;

	PQclear(res);
	PQfinish(conn);
	return st;
}

ProblemResult storeProblem(unsigned int teachID, Problem p)
{
	ProblemResult pr;
	const char *conninfo;
	PGconn	*conn;
	PGresult *res;
	string insert;
	const char *query;
	conninfo = "dbname = cap2";

	conn = PQconnectdb(conninfo);
	if(PQstatus(conn) != CONNECTION_OK)
	{
		cout << PQerrorMessage(conn);
		pr.st.err = INTERNAL_ERROR;
		pr.st.errId = DB_FAILED;
		PQfinish(conn);
		return pr;
	}

	string level;
	switch(p.level)
	{
		case 0:
			level = "easy";
			break;
		case 1:
			level = "medium";
			break;
		case 2:
			level = "hard";
			break;
		default:
			level = "Invalid";
	}



//	INSERT INTO problem(pro_title, pro_statement, pro_difficulty, fun_name, teach_id) 	VALUES(p.title, p.statement, p.level, p.funtionName, teachID);
	
//	insert = "INSERT INTO problem(pro_title, pro_statement, pro_difficulty, fun_name, teach_id) VALUES("+ p.title +","+ p.statement +", easy ,"+ p.functionName +", "+ to_string(teachID) +" RETURNING pro_id";
	
	insert = "INSERT INTO problem(pro_title, pro_statement, pro_difficulty, fun_name, teach_id) VALUES('"+ p.title +"','"+ p.statement + "','"+ level +"','"+ p.functionName +"',"+ to_string(teachID) +") RETURNING pro_id";
	query = insert.c_str();
	
	res = PQexec(conn, query);
	if(PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		cout << PQerrorMessage(conn);
		pr.st.err = INTERNAL_ERROR;
		pr.st.errId = DB_FAILED;
		PQfinish(conn);
		return pr;
	}

	pr.proID = atoi(PQgetvalue(res,0,0));
	pr.st.err = SUCCESS;
	 
	PQclear(res);
	PQfinish(conn);
	return pr;
}

ProblemResult deleteProblem(unsigned int teachID, unsigned int proID)
{
	ProblemResult pr;
	const char *conninfo;
	PGconn	*conn;
	PGresult *res;
	string del;
	const char *query;
	conninfo = "dbname = cap2";

	conn = PQconnectdb(conninfo);
	if(PQstatus(conn) != CONNECTION_OK)
	{
		cout << PQerrorMessage(conn);
		pr.st.err = INTERNAL_ERROR;
		pr.st.errId = DB_FAILED;
		PQfinish(conn);
		return pr;
	}

	// DELETE FROM problem WHERE pro_id = proID and teach_id = teachID;
	del = "DELETE FROM problem WHERE pro_id = "+ to_string(proID) +" AND teach_id = "+ to_string(teachID) +"";

	query = del.c_str();
	res = PQexec(conn, query);
	string delCount(PQcmdTuples(res));
	if(stoi(delCount) == 0)
	{
		cout << "INVALID_INPUT";
		pr.st.err = USER_ERROR;
		pr.st.errId = INVALID_INPUT;
		PQfinish(conn);
		return pr;
	}

	pr.proID = proID;
	pr.st.err = SUCCESS;
	PQclear(res);
	PQfinish(conn);
	return pr;
}


SubmissionResult storeSubmission(string sub_file, subStatus sub_st, unsigned int proID, unsigned int studID)
{
	SubmissionResult sr;
	const char *conninfo;
	PGconn	*conn;
	PGresult *res;
	string insert;
	const char *query;
	conninfo = "dbname = cap2";

	conn = PQconnectdb(conninfo);
	if(PQstatus(conn) != CONNECTION_OK)
	{
		cout << PQerrorMessage(conn);
		sr.st.err = INTERNAL_ERROR;
		sr.st.errId = DB_FAILED;
		PQfinish(conn);
		return sr;
	}

	string stat;
	switch(sub_st)
	{
		case 0:
			stat = "correct";
			break;
		case 1:
			stat = "incorrect";
			break;
		default:
			stat = "Inavlid";
	}
	
	insert = "INSERT INTO submission(sub_status, sub_file, pro_id, stud_id) VALUES('"+ stat +"','"+ sub_file +"',"+ to_string(proID) + ","+ to_string(studID) +") RETURNING sub_id";
	
	query = insert.c_str();

	res = PQexec(conn,query);
	if(PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		cout << PQerrorMessage(conn);
		sr.st.err = INTERNAL_ERROR;
		sr.st.errId = DB_FAILED;
		PQfinish(conn);
		return sr;
	}

	sr.subID = atoi(PQgetvalue(res,0,0));
	sr.sub_st = sub_st;
	sr.st.err = SUCCESS;
	 
	PQclear(res);
	PQfinish(conn);
	return sr;
}


Problem giveProblem(unsigned int proID)
{
	Problem p;
	const char *conninfo;
	PGconn *conn;
	PGresult *res;
	string select;
	const char *query;
	conninfo = "dbname = cap2";

	conn = PQconnectdb(conninfo);
	if(PQstatus(conn) != CONNECTION_OK)
	{
		cout << PQerrorMessage(conn);
		PQfinish(conn);
		return p;
	}

	select = "SELECT pro_title, convert_from(pro_statement, 'UTF8'), pro_difficulty,fun_name FROM problem WHERE pro_id = "+ to_string(proID) +"";
	
	query = select.c_str();

	res = PQexec(conn,query);
	if(PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		cout << PQerrorMessage(conn);
		PQfinish(conn);
		return p;
	}

	p.title = PQgetvalue(res,0,0);
	p.statement = PQgetvalue(res,0,1);
	enum difficulty d;
	string l =  PQgetvalue(res,0,2);
	if(l == "easy")
		d = EASY;
	else if(l == "medium")
		d = MEDIUM;
	else 
		d = HARD;
	p.level = d;
	p.functionName = PQgetvalue(res,0,3);


	vector<Method> m;

	select = "SELECT convert_from(method_file, 'UTF8'), lang, returntype, parameter FROM method WHERE pro_id = "+ to_string(proID) +"";
	
	query = select.c_str();

	res = PQexec(conn,query);
	if(PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		cout << PQerrorMessage(conn);
		PQfinish(conn);
		return p;
	}

	Method temp;

	for(int i = 0; i < PQntuples(res); i++)
	{
		temp.internalPart = PQgetvalue(res,i,0);
		temp.language = PQgetvalue(res,i,1);
		temp.returnType = PQgetvalue(res,i,2);
		temp.parameter = PQgetvalue(res,i,3);
		m.push_back(temp);
	}
	
	p.function = m;	

	PQclear(res);
	PQfinish(conn);
	return p;


/*		title
		statement
		functionName
		level
		vector<Method> function
*/
}

//int main(void)
//{
//	status st = verifyTeacher(2);
//	cout << st.err << " "<< st.errId <<endl;
/*
	ifstream readFile("filetemp.cpp");
	string stat =  "";
	string x;
	while(getline(readFile, x))
	{
		stat.append(x);
		stat.append("\n");
	}

	Problem p;
	p.title = "reveresArray";
	p.statement = stat;
	p.functionName = "reverse";
	p.level = EASY;
	ProblemResult pr = addProblem(4,p);

	cout << pr.proID << " "<< pr.st.err << " "<< pr.st.errId <<endl;
*/
//}
	
