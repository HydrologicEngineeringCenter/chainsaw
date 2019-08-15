#pragma once

class Version
{
	public:
		Version();
		~Version();
		void updateVersion(std::string newNum);
		static void printVersion();

	private:
		void getFields();
		void getFields(std::string newNum);
		static int getMajor();
		static int getMinor();
		static int getBuild();
		static int getPatch();

	private:
		int major;
		int minor;
		int build;
		int patch;
};

