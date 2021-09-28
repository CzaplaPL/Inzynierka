#include "pch.h"
#include <vector>
#include "../Translator/lekser/DAS/DasServices.h"
class BuildDasTest : public ::testing::Test {
protected:
	Logger* logger;
	int id;
	RegexService* regexService;
	DasServices* dasServices;

	BuildDasTest()
	{
		logger = new Logger("BuildDasTest");
		regexService = new RegexService(*logger);
		dasServices = new DasServices(*logger);
		id = 0;
	}
	void SetUp() override {

		id = 0;
	}
};

TEST_F(BuildDasTest, testNullableFunction)
{
	string reg = "ab|c";
	RegexNode* tree = regexService->generateTree(reg,id);
	EXPECT_FALSE(dasServices->nullable(tree));

	reg = "a?";
	tree = regexService->generateTree(reg, id);
	EXPECT_FALSE(!dasServices->nullable(tree));

	reg = "a*";
	tree = regexService->generateTree(reg, id);
	EXPECT_FALSE(!dasServices->nullable(tree));

	reg = "a*|b";
	tree = regexService->generateTree(reg, id);
	EXPECT_FALSE(!dasServices->nullable(tree));
}

TEST_F(BuildDasTest, buildDasFromBook)
{
	string reg = "(a|b)*abb";
	
	RegexNode* tree = regexService->generateTree(reg, id);
	int c = 2;
}