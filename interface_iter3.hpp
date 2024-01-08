#include<vector>
#include<string>
#include<fstream>

using namespace std;

enum errorType{
	SUCCESS = 0,
	USER_ERROR = 1,
	INTERNAL_ERROR = 2
};

enum ID{
	DB_FAILED = 10,
	INVALID_INPUT = 20,
	PROTOCOL_FAILED = 30
};

enum difficulty{
	EASY = 0,
	MEDIUM = 1,
	HARD = 2
};

enum subStatus{
	CORRECT = 0,
	INCORRECT = 1,
	COMPILE_TIME_ERROR = 2,
	RUN_TIME_ERROR = 3,
	TIME_LIMIT_EXCEEDED = 4
};

typedef struct status{
	enum errorType err;
	enum ID errId;
}Error;

typedef struct problemResult{
	unsigned int proID;
	status st;
}ProblemResult;

typedef struct method{
	string internalPart;
	string parameter;
	string language;
	string returnType;
}Method;

// not in use
/*
typedef struct testCase{
	string filePath;
}TestCase;
*/

typedef struct problem{
	string title;
	string statement;
	string functionName;
	enum difficulty level;
	vector<Method> function;
	//remove tc from problem beacuse if student call getProblem method it also get testcase along with that, so create new struct to store tc
	//vector<TestCase> tc;
}Problem;

typedef struct submissionResult{
	unsigned int subID;
	status st;
	subStatus sub_st;
}SubmissionResult;

/*
typedef struct returnSubmission{
	vector<SubmissionResult,string> sr;
}ReturnSubmission;
*/


//------------------------------METHODS---------------------------------

//-----------------TEACHER INTERACTION-----------------------
ProblemResult addProblem(unsigned int teachID, Problem p, string tcFile);
// add Problem given by teachID teacher

status addTestCase(unsigned int teachID, unsigned int proID, string tcFile);
// add extra test case for existing problem verifying the teachID.

status addMethod(unsigned int teachID, unsigned int proID, Method m);
// add method part to for the problem give by that particular teacher

/*
ProblemResult updateProblem(unsigned int teachID, unsigned int proID, Problem p);
// update proID problem by teachID teacher
*/

ProblemResult removeProblem(unsigned int teachID, unsigned int proID);
// remove proID problem given by teachID teacher

//------------------STUDENT INTERACTION-----------------------

SubmissionResult submitSolution(unsigned int studID, string filePath, unsigned int proID);
// give proID problem and given file as in formate of path submit file by studID student 

//-------------------GENERAL INTERACTION----------------------

Problem getProblem(unsigned int proID);
// show problem by proID except Method->internalPart & TestCase

//ReturnSubmission viewSubmission(unsigned int proID);
// show submission details according to proId 


