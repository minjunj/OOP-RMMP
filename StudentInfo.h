#ifndef STUDENTINFO_H
#define STUDENTINFO_H

#include <string>
#include <iostream>

using namespace std;

class StudentInfo
{
private:
	int sleepTime;
	int awakeTime;
	int cleanFreq;
	int airConditioning;
	int stuGrade;
	
	string language;

	bool hasRefrege;
	bool isExchange;
	bool doSmoke;
	bool doDrink;
	bool doSnore;

	int totalScore;

public:
	void setSleepTime(int st);
	void setAwakeTime(int at);
	void setCleanFreq(int cf);
	void setAirConditioning(int ac);
	void setStuGrade(int sg);
	void setLanguage(string lan);
	void setHasRefrege(bool hr);
	void setIsExchange(bool ie);
	void setDoSmoke(bool dsmoke);
	void setDoDrink(bool ddrink);
	void setDoSnore(bool dsnore);
	void setTotalScore(int totscore);

	int getSleepTime();
	int getAwakeTime();
	int getCleanFreq();
	int getAirConditioning();
	int getStuGrade();
	string getLanguage();
	bool getHasRefrege();
	bool getIsExchange();
	bool getDoSmoke();
	bool getDoDrink();
	bool getDoSnore();
	int getTotalSnore();

	void changeVal();
	void getinfo();
	void evalGrade();
};

#endif