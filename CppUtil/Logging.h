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

	LoggingBase() : logger(new LoggerType()) {}
	LoggingBase(std::shared_ptr<LoggerType>& logger) : logger(logger) {}
	virtual ~LoggingBase() = default;

	//ロガーの設定
	std::shared_ptr<LoggerType> getLogger() {
		return logger;
	}
	virtual void setLogger(std::shared_ptr<LoggerType>& logger) {
		this->logger = logger;
	}

	//ロガーの有効状態
	bool isLoggerEnabled() const {
		return loggerEnabled;
	}
	virtual void setLoggerEnabled(bool enabled) {
		if (!logger and enabled) {
			assert(false);
			return;
		}
		loggerEnabled = enabled;
	}

private:
	std::shared_ptr<LoggerType> logger;
	bool loggerEnabled = true;
};

typedef LoggingBase<boost::log::sources::logger> Logging;
typedef LoggingBase<boost::log::sources::logger_mt> LoggingMt;

}

#endif /* CPPUTIL_LOGGING_H_ */
