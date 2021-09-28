#include "pch.h"

class BuildDasTest : public ::testing::Test {
protected:
	Logger* logger;
	RegexService* regexService;
	void SetUp() override {
		logger = new Logger("BuildDasTest");
		regexService = new RegexService(*logger);
	}
};

TEST_F(BuildDasTest, buildEasyDas)
{
	string reg = "ab|c";

	//RegexNode* tree = regexService->generateTree(reg);
}

TEST_F(BuildDasTest, buildDasFromBook)
{
	string reg = "(a|b)*abb";
	int i = 0;
	RegexNode* tree = regexService->generateTree(reg, i);
	int c = 2;
}