#include "StudentInfo.h"
#include <string>
#include <iostream>

using namespace std;

/*








Student로 통합합시다. 공사중









*/
void StudentInfo::setSleepTime(int st)
{
	sleepTime = st;
}
void StudentInfo::setAwakeTime(int at)
{
	awakeTime = at;
}
void StudentInfo::setCleanFreq(int cf)
{
	cleanFreq = cf;
}
void StudentInfo::setAirConditioning(int ac)
{
	airConditioning = ac;
}
void StudentInfo::setStuGrade(int sg)
{
	stuGrade = sg;
}
void StudentInfo::setLanguage(string lan)
{
	language = lan;
}
void StudentInfo::setHasRefrege(bool hr)
{
	hasRefrege = hr;
}
void StudentInfo::setIsExchange(bool ie)
{
	isExchange = ie;
}
void StudentInfo::setDoSmoke(bool dsmoke)
{
	doSmoke = dsmoke;
}
void StudentInfo::setDoDrink(bool ddrink)
{
	doDrink = ddrink;
}
void StudentInfo::setDoSnore(bool dsnore)
{
	doSnore = dsnore;
}
void StudentInfo::setTotalScore(int totscore)
{
	totalScore = totscore;
}

int StudentInfo::getSleepTime()
{
	return sleepTime;
}
int StudentInfo::getAwakeTime()
{
	return awakeTime;
}
int StudentInfo::getCleanFreq()
{
	return cleanFreq;
}
int StudentInfo::getAirConditioning()
{
	return airConditioning;
}
int StudentInfo::getStuGrade()
{
	return stuGrade;
}
string StudentInfo::getLanguage()
{
	return language;
}
bool StudentInfo::getHasRefrege()
{
	return hasRefrege;
}
bool StudentInfo::getIsExchange()
{
	return isExchange;
}
bool StudentInfo::getDoSmoke()
{
	return doSmoke;
}
bool StudentInfo::getDoDrink()
{
	return doDrink;
}
bool StudentInfo::getDoSnore()
{
	return doSnore;
}
int StudentInfo::getTotalSnore()
{
	return totalScore;
}

void StudentInfo::changeVal()
{
	cout << "Enter the number to change(0 to exit):  " << endl;
	cout << "1. sleep time  2. awake time  3. clean frequency";
	
	return;
}
void StudentInfo::getinfo()
{
	return; 
}
void StudentInfo::evalGrade()
{
	return;
}