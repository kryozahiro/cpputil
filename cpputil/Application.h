/*
 * Application.h
 *
 *  Created on: 2013/04/14
 *      Author: kryozahiro
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <csignal>
#include <iostream>
#include <boost/serialization/singleton.hpp>
#include <boost/program_options.hpp>

namespace cpputil {

namespace detail {
	//終了ハンドラ
	extern "C" void cppUtilExitHandler(int sig);
}

//終了状態かどうか
bool isEnd();

//! アプリケーションクラス
/** コマンドライン引数のパースや終了時のシグナルハンドラの設定を行う
 */
template <class ConcreteApplication>
class Application : public boost::serialization::singleton<ConcreteApplication> {
public:
	//! main関数
	int main(int argc, char* argv[]);

	//! 終了状態かどうか
	bool isEnd();

protected:
	Application();
	virtual ~Application() = default;

	//! オプションの初期化
	virtual void initOptions(boost::program_options::options_description& options,
			boost::program_options::positional_options_description& positional) = 0;

	//! 個別のアプリケーションの動作
	virtual int mainImpl(boost::program_options::variables_map& args) = 0;

private:
	//プログラムオプション
	boost::program_options::options_description options;
	boost::program_options::positional_options_description positional;
};

template <class ConcreteApplication>
int Application<ConcreteApplication>::main(int argc, char* argv[]) {
	//オプションの設定
	options.add_options()("help,h", "produce help message");
	initOptions(options, positional);

	//オプションのパース
	boost::program_options::variables_map args;
	try {
		boost::program_options::store(
				boost::program_options::command_line_parser(argc, argv).options(options).positional(positional).run(),
				args);
		boost::program_options::notify(args);
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		std::cerr << options << std::endl;
		return EXIT_FAILURE;
	}

	//ヘルプメッセージの表示
	if (args.count("help")) {
		std::cout << options << std::endl;
		return EXIT_SUCCESS;
	}

	//個別のアプリケーションの動作
	return mainImpl(args);
}

template <class ConcreteApplication>
bool Application<ConcreteApplication>::isEnd() {
	return isEnd();
}

template <class ConcreteApplication>
Application<ConcreteApplication>::Application() : options("Allowed options") {
	//シグナルハンドラの設定
	signal(SIGTERM, detail::cppUtilExitHandler);
	signal(SIGINT, detail::cppUtilExitHandler);
}

}

#endif /* APPLICATION_H_ */
