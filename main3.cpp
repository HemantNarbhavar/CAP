//#include "internalMethod3.cpp"
#include "internalFunction.cpp"
ProblemResult addProblem(unsigned int teachID, Problem p, string tcFile)
{
	ProblemResult pr;

	//teachID is found in relation teacher or not
	pr.st = verifyTeacher(teachID);

	if(pr.st.err != SUCCESS)
		return pr;

	//store problem in problem relation
	pr = storeProblem(teachID, p);


	if(pr.st.err != SUCCESS)
		return pr;

	//store test case of problem in testcase relation
	pr.st = storeTestCase(tcFile, pr.proID);

	//if problem is store successfully in problem relation but testcase is give error then remove that problem from problem relation
	if(pr.st.err != SUCCESS)
	{
		removeProblem(teachID, pr.proID);
	}

	return pr;
}

ProblemResult removeProblem(unsigned int teachID, unsigned int proID)
{
	ProblemResult pr;
	
	//teachID is found in relation teacher or not
	pr.st = verifyTeacher(teachID);

	if(pr.st.err != SUCCESS)
		return pr;

	//proID is found in relation problem or not
	pr.st = verifyProblem(proID);

	if(pr.st.err != SUCCESS)
		return pr;

	//delete test case from testcase relation related to given problem
	pr.st = deleteTestCase(proID);
	
	if(pr.st.err != SUCCESS)
		return pr;

	//delete problem from relation problem
	pr = deleteProblem(teachID, proID);

	return pr;
}

status addMethod(unsigned int teachID, unsigned int proID, Method m)
{
	status st;

	st = verifyTeacher(teachID);

	if(st.err != SUCCESS)
		return st;

	st = verifyProblem(proID);

	if(st.err !=  SUCCESS)
		return st;

	// check that problem is give by that teacher or not
	st = relTeacherProblem(teachID, proID);

	if(st.err != SUCCESS)
		return st;
	
	st = storeMethod(m, proID);

	return st;
}


status addTestCase(unsigned int teachID, unsigned int proID, string tcFile)
{
	status st;

	st = verifyTeacher(teachID);

	if(st.err != SUCCESS)
		return st;

	st = verifyProblem(proID);

	if(st.err !=  SUCCESS)
		return st;

	// check that problem is give by that teacher or not
	st = relTeacherProblem(teachID, proID);

	if(st.err != SUCCESS)
		return st;

	// store additional testcase for given proID
	st = storeTestCase(tcFile, proID);

	return st;
}



SubmissionResult submitSolution(unsigned int studID, unsigned int proID, string filePath)
{
	SubmissionResult sr;
	
	//studID is found in relation student or not
	sr.st = verifyStudent(studID);

	if(sr.st.err != SUCCESS)
		return sr;

	//proId is found in relation problem or not
	sr.st = verifyProblem(proID);


	enum subStatus stat = checkSolution(filePath);

	//store Submission of give problem by student
	sr = storeSubmission(filePath,stat,proID,studID);

	if(sr.st.err != SUCCESS)
		return sr;

	return sr;
}

Problem getProblem(unsigned int proID)
{
	Problem p;

	p = giveProblem(proID);
	return p;
}

int main(void)
{
/*
//	status st = verifyTeacher(2);
//      cout << st.err << " "<< st.errId <<endl;

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
        p.level = HARD;
	string tcFile = "1 2 3 4 5";

	Method m;
	m.internalPart = stat;
	m.parameter = "(int A[], int n)";
	m.language = "C";
	m.returnType = "void";

	status st = addMethod(1,7,m);

	ProblemResult pr = addProblem(1,p,tcFile);
//	status st = addTestCase(1,7,tcFile);
        //cout << st.err << " "<< st.errId <<endl;
//	ProblemResult pr = removeProblem(2,7);
	cout << pr.proID << " "<< pr.st.err << " "<< pr.st.errId <<endl;
	
//	SubmissionResult sr = submitSolution(1,19,"addTwoNumber");
//	cout << sr.st.err << " "<< sr.st.errId << endl;	
*/
/*
        ifstream readFile("filetemp.cpp");
        string stat =  "";
        string x;
        while(getline(readFile, x))
        {
                stat.append(x);
                stat.append("\n");
        }
	subStatus sub_st = CORRECT;
	SubmissionResult sr = storeSubmission(stat,sub_st,10,1);
	cout << sr.subID << " "<<sr.st.err<< " ";
*/
/*
	Problem p = getProblem(7);
	cout << p.title <<endl << p.statement <<endl << p.functionName <<endl <<p.level<<endl<<endl;
	for(int i=0; i<p.function.size(); i++)
	{
		cout << p.function.at(i).internalPart <<endl;
		cout << p.function.at(i).parameter <<endl;
		cout << p.function.at(i).language <<endl;
		cout << p.function.at(i).returnType <<endl;
	}
*/

	ifstream readFile("helloworld.cpp");
	string file = "";
	string x;
	while(getline(readFile, x))
	{
		file.append(x);
		file.append("\n");
	}
	enum subStatus stat = checkSolution(file);
}
