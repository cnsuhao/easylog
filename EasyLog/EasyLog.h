/*
  简单的日志记录类. (日志而已，何必那么复杂！！！）
  W.J.Chang 2013.12.13

  说明:(EasyLog.h)
  1, 简单的单件实现（自动垃圾回收）
  2, 使用方法：EasyLog::Instance()->WriteLog("Run...");
  3, 日志记录结果：Run...	[2013.12.13 16:38:42 Friday]


*/
#pragma once
#ifndef EASY_LOG_H_8080
#define EASY_LOG_H_8080
#include <memory>
#include <ctime>
#include <iostream>
#include <fstream>
class EasyLog
{
public:
	static EasyLog * Instance(){
		if (0 == _instance.get()){
			_instance.reset(new EasyLog);
		}
		return _instance.get();
	}
	void WriteLog(std::string loginfo) {
		if (loginfo.empty()) {
			return;
		}
		std::fstream fs;
		time_t t = time(0);
		char tmp[64];
		strftime(tmp, sizeof(tmp), "\t[%Y.%m.%d %X %A]", localtime(&t));
		fs.open("EasyLog.txt", std::fstream::app);
		fs.write(loginfo.c_str(), loginfo.size());
		fs << tmp << '\n';
		fs.flush();
		fs.close();
	}
private:
	EasyLog(void){}
	virtual ~EasyLog(void){}
	friend class std::auto_ptr<EasyLog>;
	static std::auto_ptr<EasyLog> _instance;
};
std::auto_ptr<EasyLog> EasyLog::_instance;
#endif