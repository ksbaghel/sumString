// sumString.cpp : Defines the entry point for the console application.
/*
Given a string of digits, the task is to check if it is a ‘sum-string’. A string S is called a sum-string if 
a rightmost substring can be written as sum of two substrings before it and same is recursively true for substrings 
before it.

Example:
12243660 - Yes
1111112223  - No
*/

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

int str2num(string &s)
{
	int num = 0;
	int i = 0;
	while (i<s.length())
	{
		num = num * 10 + s[i] - '0';
		i++;
	}

	return num;
}

string addStringNum(string &s1, string &s2)
{
	string res = "";
	int carry = 0;
	int l1 = s1.length();
	int l2 = s2.length();
	int i = 1; 
	while (i <= l1 && i <= l2)
	{
		int n1 = s1[l1 - i] - '0';
		int n2 = s2[l2 - i] - '0';
		int sum = n1 + n2 + carry;
		carry = sum / 10;
		int n = sum - carry * 10;
		res = char(n + '0') + res;
		i++;
	}

	while (i <= l1)
	{
		int n1 = s1[l1 - i] - '0';
		int sum = n1 + carry;
		carry = sum / 10;
		int n = sum - carry * 10;
		res = char(n + '0') + res;
		i++;
	}

	while (i <= l2)
	{
		int n2 = s2[l2 - i] - '0';
		int sum = n2 + carry;
		carry = sum / 10;
		int n = sum - carry * 10;
		res = char(n + '0') + res;
		i++;
	}
	if (carry > 0)
	{
		res = char(carry + '0') + res;
	}

	return res;
}

bool possibleSumString(string &s, int beg, int l1, int l2)
{
	string s1 = s.substr(beg, l1);
	string s2 = s.substr(beg + l1, l2);
	string s3 = addStringNum(s1, s2);
	//Now check if length of s3 is more than remaing length in s
	if (s3.length() > s.length() - beg - l1 - l2) return false;

	//now check if s3 exists
	string temp = s.substr(beg + l1 + l2, s3.length());
	if (temp.compare(s3) == 0)
	{
		//if remaining legth is zero
		if (beg + l1 + l2 + s3.length() == s.length()) return true;
		return possibleSumString(s, beg + l1, l2, s3.length());
	}

	return false;
}

bool isSumString(string s)
{
	int len = s.length();
	if (len < 3) return false;

	for (int i = 1; i<len; i++)
	{
		for (int j = 1; i + j<len; j++)
		{
			if (possibleSumString(s, 0, i, j))
			{
				return true;
			}
		}
	}

	return false;
}

int main()
{
	string s;
	cin >> s;
	cout << isSumString(s) << endl;
	return 0;
}
