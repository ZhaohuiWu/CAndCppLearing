/********************************************************************++
 *   Copyright (c) 2021     All rights reserved.
 * -------------------------------------------------------------------
 * Author   :   Mark Wu
 * Summary  :   打印当月份日历的小程序
--********************************************************************/
#include <stdio.h>
#include <time.h>

const char head[] = " Mon Tue Wed Thu Fri Sat Sun";
int getEndDay(int year, int month);
int getWeekOfFirstDay(int nowDay, int nowWeek);

int main (void)
{
	time_t rawtime;
	struct tm * now;
	
	time(&rawtime);
	now = localtime(&rawtime);
	printf("\n  %s\n", asctime(now));

	int endDay = getEndDay(now->tm_year, now->tm_mon);
	int weekOfFirstDay = getWeekOfFirstDay(now->tm_mday, now->tm_wday);
	int today = now->tm_mday;

	printf("%s\n", head);	// 输出表头

	// 输出第一行占位空格
	if (weekOfFirstDay == 0)
		printf("                        ");
	for (int i = 1; i < weekOfFirstDay; i++)
		printf("    ");

	// 从一号开始输出到月末
	for (int i = 1; i <= endDay; i++)
	{
		if (i == today)
			printf("%3d*", i);
		else
			printf("%4d", i);

		// 周末输出结束后输出换行
		if ((i + weekOfFirstDay - 1) % 7 == 0)
			puts("");
	}

	puts("");
	return 0;
}

// 得到当前所在月份的天数
int getEndDay(int year, int month)
{
	const int days[15] = {31, -1, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (month == 1)
	{
		if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0))
			return 29;
		else
			return 28;
	}
	else
		return days[month];
}

// 推算这月第一天是礼拜几
// 返回值：[0, 6] (礼拜日, 礼拜一 ~ 礼拜六)
int getWeekOfFirstDay(int nowDay, int nowWeek)
{
	int mod = (nowDay - 1) % 7;
	int ans = nowWeek - mod;
	if (ans >= 0)
		return ans;
	else
		return 7 - ans;
}