﻿#include "pch.h"

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::ApplicationModel;
using namespace Windows::Storage;

int wmain(int argc, wchar_t* argv[], wchar_t* envp[]) {
	init_apartment();

	auto localSettings = ApplicationData::Current().LocalSettings();

	if (argc == 1) {
		std::wcout << L"Julia Version Manager Preview" << std::endl;
		std::wcout << std::endl;
		std::wcout << L"juliaup command line utility enables configuration of the default Julia version from the command line." << std::endl;
		std::wcout << std::endl;
		std::wcout << L"usage: juliaup [<command>] [<options>]" << std::endl;
		std::wcout << std::endl;
		std::wcout << L"The following commands are available:" << std::endl;
		std::wcout << std::endl;
		std::wcout << L"  setdefault    Set the default Julia version" << std::endl;
		std::wcout << std::endl;
		std::wcout << L"For more details on a specific command, pass it the help argument. [-?]" << std::endl;
		std::wcout << std::endl;
		std::wcout << L"The following options are available:" << std::endl;
		std::wcout << L"  -v,--version  Display the version of the tool" << std::endl;
		std::wcout << L"  --info        Display general info of the tool" << std::endl;
		std::wcout << std::endl;
	}
	else if (argc > 1) {
		auto firstArg = std::wstring_view(argv[1]);

		if (firstArg == L"-v" || firstArg == L"--version") {
			if (argc == 2) {
				// TODO Extract proper version from somewhere so that it is not hardcoded.
				std::wcout << L"v1.0.0.0" << std::endl;
			}
			else {
				std::wcout << L"ERROR: The " << firstArg << L" argument does not accept any additional arguments." << std::endl;
			}
		}
		else if (firstArg == L"--info") {
			if (argc == 2) {
				std::wcout << L"Julia Version Manager Preview" << std::endl;
				std::wcout << L"Copyright (c) David Anthoff" << std::endl;
			}
			else {
				std::wcout << L"ERROR: The --info argument does not accept any additional arguments." << std::endl;
			}
		}
		else if (firstArg == L"setdefault") {
			if (argc == 3) {
				auto secondArg = std::wstring{ argv[2] };

				// TODO Come up with a less hardcoded version of this.
				if (secondArg == L"1.4.2" || secondArg == L"1.4.1" || secondArg == L"1.4.0") {
					localSettings.Values().Insert(L"version", box_value(winrt::hstring{ secondArg }));

					std::wcout << L"Configured the default Julia version to be " << secondArg << L"." << std::endl;
				}
				else {
					// TODO Come up with a less hardcoded version of this.
					std::wcout << L"ERROR: '" << secondArg << L"' is not a valid Julia version. Valid values are '1.4.0', '1.4.1' or '1.4.2'." << std::endl;
				}
			}
			else {
				std::wcout << L"ERROR: The setdefault command only accepts one additional argument." << std::endl;
			}
		}
		else {
			std::wcout << L"ERROR: '" << firstArg << L"' is not a recognized command." << std::endl;
		}
	}
	else {
		std::wcout << L"Internal error." << std::endl;
	}

	return 0;
}