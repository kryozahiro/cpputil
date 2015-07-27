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

template <class ConcreteApplication>
class Application : public boost::serialization::singleton<ConcreteApplication> {
public:
	//main関数
	int main(int argc, char* argv[]);

	//終了状態かどうか
	bool isEnd();

protected:
	Application();
	virtual ~Application() = default;

	//個別のアプリケーションの動作
	virtual void initOptions(boost::program_options::options_description& options,
			boost::program_options::positional_options_description& positional) = 0;
	virtual int mainImpl(boost::program_options::variables_map& args) = 0;
	virtual void exitHandlerImpl() {}

private:
	//終了ハンドラ
	static void exitHandler(int sig);

	//終了状態
	bool end = false;

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
	return end;
}

template <class ConcreteApplication>
Application<ConcreteApplication>::Application() : options("Allowed options") {
	//シグナルハンドラの設定
	signal(SIGTERM, exitHandler);
	signal(SIGINT, exitHandler);
}

template <class ConcreteApplication>
void Application<ConcreteApplication>::exitHandler(int sig) {
	ConcreteApplication::get_mutable_instance().end = true;
	ConcreteApplication::get_mutable_instance().exitHandlerImpl();
}

}

#endif /* APPLICATION_H_ */
