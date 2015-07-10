/*
 * Logging.h
 *
 *  Created on: 2015/02/08
 *      Author: kryozahiro
 */

#ifndef CPPUTIL_LOGGING_H_
#define CPPUTIL_LOGGING_H_

#include <boost/log/sources/logger.hpp>

namespace cpputil {

//ロギングを行う基本クラス
template <class Logger>
class LoggingBase {
public:
	typedef Logger LoggerType;

	LoggingBase();
	LoggingBase(std::shared_ptr<LoggerType>& logger);
	virtual ~LoggingBase() = default;

	//ロガーの設定
	std::shared_ptr<LoggerType> getLogger();
	virtual void setLogger(std::shared_ptr<LoggerType>& logger);

	//ロガーの有効状態
	bool isLoggerEnabled() const;
	virtual void setLoggerEnabled(bool enabled);

private:
	std::shared_ptr<LoggerType> logger;
	bool loggerEnabled = true;
};

typedef LoggingBase<boost::log::sources::logger> Logging;
typedef LoggingBase<boost::log::sources::logger_mt> LoggingMt;

template <class Logger>
LoggingBase<Logger>::LoggingBase() : logger(new LoggerType()) {
}

template <class Logger>
LoggingBase<Logger>::LoggingBase(std::shared_ptr<LoggerType>& logger) : logger(logger) {
}

template <class Logger>
std::shared_ptr<typename LoggingBase<Logger>::LoggerType> LoggingBase<Logger>::getLogger() {
	return logger;
}

template <class Logger>
void LoggingBase<Logger>::setLogger(std::shared_ptr<LoggerType>& logger) {
	this->logger = logger;
}

template <class Logger>
bool LoggingBase<Logger>::isLoggerEnabled() const {
	return loggerEnabled;
}

template <class Logger>
void LoggingBase<Logger>::setLoggerEnabled(bool enabled) {
	if (!logger and enabled) {
		assert(false);
		return;
	}
	loggerEnabled = enabled;
}

}

#endif /* CPPUTIL_LOGGING_H_ */
